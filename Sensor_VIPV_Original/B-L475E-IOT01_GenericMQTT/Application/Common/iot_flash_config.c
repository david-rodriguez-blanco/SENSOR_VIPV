/**
  ******************************************************************************
  * @file    iot_flash_config.c
  * @author  MCD Application Team
  * @brief   configuration in flash memory.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V.
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "rfu.h"
#ifdef USE_FIREWALL
#include "firewall_wrapper.h"
#endif
#include "flash.h"
#include "iot_flash_config.h"
#include "msg.h"

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define PEM_READ_LINE_SIZE    120
#define PEM_READ_BUFFER_SIZE  8192  /**< Max size which can be got from the terminal in a single getInputString(). */

/* Private macros ------------------------------------------------------------*/
#ifdef ENABLE_TRACE_FLASH
#define TRACE_FLASH msg_info
#else
#define TRACE_FLASH(...)
#endif

/* Private variables ---------------------------------------------------------*/
/** Do not zero-initialize the static user configuration.
 *  Otherwise, it must be entered manually each time the device FW is updated by STLink.
 */

/* to workaround a limitation of SFMI tools which support a single section      */
/* so do not mark structure as _no_init                                         */
#ifdef __ICCARM__ /* IAR */
extern void __ICFEDIT_region_FIXED_LOC_start__;
const  user_config_t	*lUserConfigPtr = &__ICFEDIT_region_FIXED_LOC_start__;

#elif defined (__CC_ARM ) /* Keil / armcc */
user_config_t __uninited_region_start__ __attribute__((section("UNINIT_FIXED_LOC"), zero_init));
const  user_config_t	*lUserConfigPtr = &__uninited_region_start__;

#elif defined (__GNUC__) /* GNU compiler */

//Eliminamos esta configuracion de inicializacion
//user_config_t __uninited_region_start__ __attribute__((section("UNINIT_FIXED_LOC")));
//const  user_config_t	*lUserConfigPtr = &__uninited_region_start__;


//char* _mi_CertificadoTLS =  NULL; //se redefine más adelante para que no ocupe memoria global

const char mi_ssid[] = MI_SSID_WIFI;
const char mi_psk[] = MI_PSWRD_WIFI;
const WIFI_Ecn_t mi_security_mode = MI_SCRTYLVL;
const uint64_t mi_magico = USER_CONF_MAGIC;

const char mi_deviceIoT_name[]= CREDENCIALES_SERV_IOT;

user_config_t __inited_region_start__ __attribute__((section("UNINIT_FIXED_LOC")));;

const  user_config_t	*lUserConfigPtr = &__inited_region_start__;


#endif

/* Private function prototypes -----------------------------------------------*/
int CaptureAndFlashPem(char *pem_name, char const *flash_addr, bool restricted_area);
/* Functions Definition ------------------------------------------------------*/

/**
  * @brief  Get a line from the console (user input).
  * @param  Out:  inputString   Pointer to buffer for input line.
  * @param  In:   len           Max length for line.
  * @retval Number of bytes read from the terminal.
  */
int getInputString(char *inputString, size_t len)
{
  size_t currLen = 0;
  int c = 0;

  c = getchar();

  while ((c != EOF) && ((currLen + 1) < len) && (c != '\r') && (c != '\n') )
  {
    if (c == '\b')
    {
      if (currLen != 0)
      {
        --currLen;
        inputString[currLen] = 0;
        printf(" \b");
      }
    }
    else
    {
      if (currLen < (len-1))
      {
        inputString[currLen] = c;
      }

      ++currLen;
    }
    c = getchar();
  }
  if (currLen != 0)
  { /* Close the string in the input buffer... only if a string was written to it. */
    inputString[currLen] = '\0';
  }
  if (c == '\r')
  {
    c = getchar(); /* assume there is '\n' after '\r'. Just discard it. */
  }

  return currLen;
}

#ifdef USE_C2C
/**
  * @brief  Check whether the C2C parameters are present in Flash memory.
  *         Returns the parameters if present.
  * @param  Out:  oper_ap_code       SIM operator Access Point code
  * @param  Out:  username           username
  * @param  Out:  password           password
  * @param  Out:  use_internal_sim  Use the embedded SIM rather than the external slot
  * @retval   0 if the parameters are present in Flash.
  *          -1 if the parameters are not present in Flash.
  */
int checkC2cCredentials(const char ** const oper_ap_code, const char ** const username, const char ** const password, bool * use_internal_sim)
{
  bool is_soapc_present = 0;

  if (lUserConfigPtr->c2c_config.magic == USER_CONF_MAGIC)
  {
    is_soapc_present = true;
    if (oper_ap_code == NULL)
    {
      return -2;
    }

    *use_internal_sim = lUserConfigPtr->c2c_config.use_internal_sim;
    *oper_ap_code = lUserConfigPtr->c2c_config.oper_ap_code;
    *username = lUserConfigPtr->c2c_config.username;
    *password = lUserConfigPtr->c2c_config.password;
  }

  return (is_soapc_present) ? 0 : -1;
}


/**
  * @brief  Write the C2C parameters to the Flash memory.
  * @retval Error code
  *             0    Success
  *             <0   Unrecoverable error
  */
int updateC2cCredentials(void)
{
  c2c_config_t c2c_config;
  int ret = 0;

  memset(&c2c_config, 0, sizeof(c2c_config_t));

#if 0  /* Build this code if you want the user to choose the SIM slot. By default, the external slot is used. */
  {
    char c;
    do
    {
        printf("\rSelect the SIM slot (0 - External, 1 - Internal): \b");
        c = getchar();
    }
    while ( (c < '0')  || (c > '1'));
    c2c_config.use_internal_sim = (bool) (c - '0');
    printf("\nYou have selected the %s SIM.\n", (c2c_config.use_internal_sim == true) ? "external" : "internal");
  }
#endif
  
  printf("\nEnter Sim Operator Access Point Code (e.g. EM or ESEYE1 etc): ");
  getInputString(c2c_config.oper_ap_code, USER_CONF_C2C_SOAPC_MAX_LENGTH);
  printf("You have entered <%s> as the Sim Operator Access Point Code.\n", c2c_config.oper_ap_code);

  printf("\nEnter the username (it can be NULL) (max 16 char):  ");
  getInputString(c2c_config.username, USER_CONF_C2C_USERID_MAX_LENGTH);
  printf("You have entered <%s> as the username.\n", c2c_config.username);

  printf("\nEnter the password (it can be NULL) (max 16 char):  ");
  getInputString(c2c_config.password, USER_CONF_C2C_PSW_MAX_LENGTH);
  printf("You have entered <%s> as the password.\n", c2c_config.password);

  c2c_config.magic = USER_CONF_MAGIC;

  ret = FLASH_update((uint32_t)&lUserConfigPtr->c2c_config, &c2c_config, sizeof(c2c_config_t));

  if (ret < 0)
  {
    msg_error("Failed updating the C2C configuration in Flash.\n");
  }

  msg_info("\n");
  return ret;
}
#endif /* USE_C2C */

#ifdef USE_WIFI
/**
  * @brief  Check whether the Wifi parameters are present in Flash memory.
  *         Returns the parameters if present.
  * @param  Out:  ssid              Wifi SSID.
  * @param  Out:  psk               Wifi security password.
  * @param  Out:  security_mode     See @ref wifi_network_security_t definition.
  * @retval   0 if the parameters are present in Flash.
  *          -1 if the parameters are not present in Flash.
  */
int checkWiFiCredentials(const char ** const ssid, const char ** const psk, uint8_t * const security_mode)
{
	  const char mi_CertificadoTLS[] = "-----BEGIN CERTIFICATE-----\n"
	  "MIIF2DCCA8CgAwIBAgIQTKr5yttjb+Af907YWwOGnTANBgkqhkiG9w0BAQwFADCB\n"
	  "hTELMAkGA1UEBhMCR0IxGzAZBgNVBAgTEkdyZWF0ZXIgTWFuY2hlc3RlcjEQMA4G\n"
	  "A1UEBxMHU2FsZm9yZDEaMBgGA1UEChMRQ09NT0RPIENBIExpbWl0ZWQxKzApBgNV\n"
	  "BAMTIkNPTU9ETyBSU0EgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkwHhcNMTAwMTE5\n"
	  "MDAwMDAwWhcNMzgwMTE4MjM1OTU5WjCBhTELMAkGA1UEBhMCR0IxGzAZBgNVBAgT\n"
	  "EkdyZWF0ZXIgTWFuY2hlc3RlcjEQMA4GA1UEBxMHU2FsZm9yZDEaMBgGA1UEChMR\n"
	  "Q09NT0RPIENBIExpbWl0ZWQxKzApBgNVBAMTIkNPTU9ETyBSU0EgQ2VydGlmaWNh\n"
	  "dGlvbiBBdXRob3JpdHkwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCR\n"
	  "6FSS0gpWsawNJN3Fz0RndJkrN6N9I3AAcbxT38T6KhKPS38QVr2fcHK3YX/JSw8X\n"
	  "pz3jsARh7v8Rl8f0hj4K+j5c+ZPmNHrZFGvnnLOFoIJ6dq9xkNfs/Q36nGz637CC\n"
	  "9BR++b7Epi9Pf5l/tfxnQ3K9DADWietrLNPtj5gcFKt+5eNu/Nio5JIk2kNrYrhV\n"
	  "/erBvGy2i/MOjZrkm2xpmfh4SDBF1a3hDTxFYPwyllEnvGfDyi62a+pGx8cgoLEf\n"
	  "Zd5ICLqkTqnyg0Y3hOvozIFIQ2dOciqbXL1MGyiKXCJ7tKuY2e7gUYPDCUZObT6Z\n"
	  "+pUX2nwzV0E8jVHtC7ZcryxjGt9XyD+86V3Em69FmeKjWiS0uqlWPc9vqv9JWL7w\n"
	  "qP/0uK3pN/u6uPQLOvnoQ0IeidiEyxPx2bvhiWC4jChWrBQdnArncevPDt09qZah\n"
	  "SL0896+1DSJMwBGB7FY79tOi4lu3sgQiUpWAk2nojkxl8ZEDLXB0AuqLZxUpaVIC\n"
	  "u9ffUGpVRr+goyhhf3DQw6KqLCGqR84onAZFdr+CGCe01a60y1Dma/RMhnEw6abf\n"
	  "Fobg2P9A3fvQQoh/ozM6LlweQRGBY84YcWsr7KaKtzFcOmpH4MN5WdYgGq/yapiq\n"
	  "crxXStJLnbsQ/LBMQeXtHT1eKJ2czL+zUdqnR+WEUwIDAQABo0IwQDAdBgNVHQ4E\n"
	  "FgQUu69+Aj36pvE8hI6t7jiY7NkyMtQwDgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB\n"
	  "/wQFMAMBAf8wDQYJKoZIhvcNAQEMBQADggIBAArx1UaEt65Ru2yyTUEUAJNMnMvl\n"
	  "wFTPoCWOAvn9sKIN9SCYPBMtrFaisNZ+EZLpLrqeLppysb0ZRGxhNaKatBYSaVqM\n"
	  "4dc+pBroLwP0rmEdEBsqpIt6xf4FpuHA1sj+nq6PK7o9mfjYcwlYRm6mnPTXJ9OV\n"
	  "2jeDchzTc+CiR5kDOF3VSXkAKRzH7JsgHAckaVd4sjn8OoSgtZx8jb8uk2Intzna\n"
	  "FxiuvTwJaP+EmzzV1gsD41eeFPfR60/IvYcjt7ZJQ3mFXLrrkguhxuhoqEwWsRqZ\n"
	  "CuhTLJK7oQkYdQxlqHvLI7cawiiFwxv/0Cti76R7CZGYZ4wUAc1oBmpjIXUDgIiK\n"
	  "boHGhfKppC3n9KUkEEeDys30jXlYsQab5xoq2Z0B15R97QNKyvDb6KkBPvVWmcke\n"
	  "jkk9u+UJueBPSZI9FoJAzMxZxuY67RIuaTxslbH9qh17f4a+Hg4yRvv7E491f0yL\n"
	  "S0Zj/gA0QHDBw7mh3aZw4gSzQbzpgJHqZJx64SIDqZxubw5lT2yHh17zbqD5daWb\n"
	  "QOhTsiedSrnAdyGN/4fy3ryM7xfft0kL0fJuMAsaDk527RH89elWsn2/x20Kk4yl\n"
	  "0MC2Hb46TpSi125sC8KKfPog88Tk5c0NqMuRkrF8hey1FGlmDoLnzc7ILaZRfyHB\n"
	  "NVOFBkpdn627G190\n"
	  "-----END CERTIFICATE-----"
	  		;
	__inited_region_start__.iot_config.magic = mi_magico;
	__inited_region_start__.ca_tls_magic = mi_magico;
    __inited_region_start__.device_tls_magic = mi_magico;
    __inited_region_start__.wifi_config.magic = mi_magico;
	strcpy(__inited_region_start__.tls_root_ca_cert, mi_CertificadoTLS);
	strcpy( __inited_region_start__.iot_config.device_name ,mi_deviceIoT_name );
	 strcpy( __inited_region_start__.wifi_config.ssid , mi_ssid );
	 strcpy( __inited_region_start__.wifi_config.psk , mi_psk );
	 __inited_region_start__.wifi_config.security_mode = mi_security_mode;

  bool is_ssid_present = 0;	//lo tomamos así (1)para que devuelva las credenciales tomadas íntegras

  if (lUserConfigPtr->wifi_config.magic == USER_CONF_MAGIC)
  {
    is_ssid_present = true;
    if ((ssid == NULL) ||(psk == NULL) || (security_mode == NULL))
    {
      return -2;
    }
    *ssid = lUserConfigPtr->wifi_config.ssid;
    *psk = lUserConfigPtr->wifi_config.psk;
    *security_mode = lUserConfigPtr->wifi_config.security_mode;
  }

  return (is_ssid_present) ? 0 : -1;
}


/**
  * @brief  Write the Wifi parameters to the Flash memory.
  * @retval Error code
  *             0    Success
  *             <0   Unrecoverable error
  */
int updateWiFiCredentials(void)
{
  wifi_config_t wifi_config;
  int ret = 0;

  memset(&wifi_config, 0, sizeof(wifi_config_t));

  printf("\nEnter SSID: ");

  getInputString(wifi_config.ssid, USER_CONF_WIFI_SSID_MAX_LENGTH);
  msg_info("You have entered %s as the ssid.\n", wifi_config.ssid);

  printf("\n");
  char c;
  do
  {
      printf("\rEnter Security Mode (0 - Open, 1 - WEP, 2 - WPA, 3 - WPA2): \b");
      c = getchar();
  }
  while ( (c < '0')  || (c > '3'));
  wifi_config.security_mode = c - '0';
  msg_info("\nYou have entered %d as the security mode.\n", wifi_config.security_mode);

  if (wifi_config.security_mode != 0)
  {
    printf("\nEnter password: ");
    getInputString(wifi_config.psk, sizeof(wifi_config.psk));
  }

  wifi_config.magic = USER_CONF_MAGIC;

  ret = FLASH_update((uint32_t)&lUserConfigPtr->wifi_config, &wifi_config, sizeof(wifi_config_t));

  if (ret < 0)
  {
    msg_error("Failed updating the wifi configuration in Flash.\n");
  }

  printf("\n");
  return ret;
}
#endif /* USE_WIFI */


/**
  * @brief  Get one PEM string (ASCII format of TLS certificates and keys) from the console (user input).
  * @param  Out: key_read_buffer    Destination buffer.
  * @param  In:  max_len            Maximum length to be written to the destination buffer.
  * @retval Number of characters read into the output buffer.
  */
int enterPemString(char * read_buffer, size_t max_len)
{
  int i = 0;
  int read_len = 0;
  bool eof = false;
  read_len = getInputString(&read_buffer[i], max_len);

  while ( (read_len >= 0) && (i < max_len) && !eof )
  {
    i += read_len;
    read_buffer[i++] = '\n';
    read_len = getInputString(&read_buffer[i], max_len);
    eof = (strncmp(&read_buffer[i], "-----END",8) == 0);
    if (eof)
    {
        i += read_len;
        read_buffer[i++] = '\n';
        read_len = getInputString(&read_buffer[i], max_len);
        if (read_len != 0) eof =false;
    }
  }

  if (i >= max_len)
  {
   msg_error("Certificate is too long , allocated size is %d\n",max_len);
   return 0;
  }
  read_buffer[++i] = '\0';
  return i;
}


/**
  * @brief  Ask user and write the TLS certificates and key to the Flash memory.
  * @param  none
  * @retval Error code
  *             0    Success
  *             <0   Unrecoverable error
  */

 int CaptureAndFlashPem(char *pem_name, char const *flash_addr, bool restricted_area)
 {
  char * key_read_buffer = NULL;
  int    ret = 0;
  const char mi_CertificadoTLS[] = "-----BEGIN CERTIFICATE-----\n"
  	  "MIIF2DCCA8CgAwIBAgIQTKr5yttjb+Af907YWwOGnTANBgkqhkiG9w0BAQwFADCB\n"
  	  "hTELMAkGA1UEBhMCR0IxGzAZBgNVBAgTEkdyZWF0ZXIgTWFuY2hlc3RlcjEQMA4G\n"
  	  "A1UEBxMHU2FsZm9yZDEaMBgGA1UEChMRQ09NT0RPIENBIExpbWl0ZWQxKzApBgNV\n"
  	  "BAMTIkNPTU9ETyBSU0EgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkwHhcNMTAwMTE5\n"
  	  "MDAwMDAwWhcNMzgwMTE4MjM1OTU5WjCBhTELMAkGA1UEBhMCR0IxGzAZBgNVBAgT\n"
  	  "EkdyZWF0ZXIgTWFuY2hlc3RlcjEQMA4GA1UEBxMHU2FsZm9yZDEaMBgGA1UEChMR\n"
  	  "Q09NT0RPIENBIExpbWl0ZWQxKzApBgNVBAMTIkNPTU9ETyBSU0EgQ2VydGlmaWNh\n"
  	  "dGlvbiBBdXRob3JpdHkwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCR\n"
  	  "6FSS0gpWsawNJN3Fz0RndJkrN6N9I3AAcbxT38T6KhKPS38QVr2fcHK3YX/JSw8X\n"
  	  "pz3jsARh7v8Rl8f0hj4K+j5c+ZPmNHrZFGvnnLOFoIJ6dq9xkNfs/Q36nGz637CC\n"
  	  "9BR++b7Epi9Pf5l/tfxnQ3K9DADWietrLNPtj5gcFKt+5eNu/Nio5JIk2kNrYrhV\n"
  	  "/erBvGy2i/MOjZrkm2xpmfh4SDBF1a3hDTxFYPwyllEnvGfDyi62a+pGx8cgoLEf\n"
  	  "Zd5ICLqkTqnyg0Y3hOvozIFIQ2dOciqbXL1MGyiKXCJ7tKuY2e7gUYPDCUZObT6Z\n"
  	  "+pUX2nwzV0E8jVHtC7ZcryxjGt9XyD+86V3Em69FmeKjWiS0uqlWPc9vqv9JWL7w\n"
  	  "qP/0uK3pN/u6uPQLOvnoQ0IeidiEyxPx2bvhiWC4jChWrBQdnArncevPDt09qZah\n"
  	  "SL0896+1DSJMwBGB7FY79tOi4lu3sgQiUpWAk2nojkxl8ZEDLXB0AuqLZxUpaVIC\n"
  	  "u9ffUGpVRr+goyhhf3DQw6KqLCGqR84onAZFdr+CGCe01a60y1Dma/RMhnEw6abf\n"
  	  "Fobg2P9A3fvQQoh/ozM6LlweQRGBY84YcWsr7KaKtzFcOmpH4MN5WdYgGq/yapiq\n"
  	  "crxXStJLnbsQ/LBMQeXtHT1eKJ2czL+zUdqnR+WEUwIDAQABo0IwQDAdBgNVHQ4E\n"
  	  "FgQUu69+Aj36pvE8hI6t7jiY7NkyMtQwDgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB\n"
  	  "/wQFMAMBAf8wDQYJKoZIhvcNAQEMBQADggIBAArx1UaEt65Ru2yyTUEUAJNMnMvl\n"
  	  "wFTPoCWOAvn9sKIN9SCYPBMtrFaisNZ+EZLpLrqeLppysb0ZRGxhNaKatBYSaVqM\n"
  	  "4dc+pBroLwP0rmEdEBsqpIt6xf4FpuHA1sj+nq6PK7o9mfjYcwlYRm6mnPTXJ9OV\n"
  	  "2jeDchzTc+CiR5kDOF3VSXkAKRzH7JsgHAckaVd4sjn8OoSgtZx8jb8uk2Intzna\n"
  	  "FxiuvTwJaP+EmzzV1gsD41eeFPfR60/IvYcjt7ZJQ3mFXLrrkguhxuhoqEwWsRqZ\n"
  	  "CuhTLJK7oQkYdQxlqHvLI7cawiiFwxv/0Cti76R7CZGYZ4wUAc1oBmpjIXUDgIiK\n"
  	  "boHGhfKppC3n9KUkEEeDys30jXlYsQab5xoq2Z0B15R97QNKyvDb6KkBPvVWmcke\n"
  	  "jkk9u+UJueBPSZI9FoJAzMxZxuY67RIuaTxslbH9qh17f4a+Hg4yRvv7E491f0yL\n"
  	  "S0Zj/gA0QHDBw7mh3aZw4gSzQbzpgJHqZJx64SIDqZxubw5lT2yHh17zbqD5daWb\n"
  	  "QOhTsiedSrnAdyGN/4fy3ryM7xfft0kL0fJuMAsaDk527RH89elWsn2/x20Kk4yl\n"
  	  "0MC2Hb46TpSi125sC8KKfPog88Tk5c0NqMuRkrF8hey1FGlmDoLnzc7ILaZRfyHB\n"
  	  "NVOFBkpdn627G190\n"
  	  "-----END CERTIFICATE-----"
  	  		;
  key_read_buffer = malloc(PEM_READ_BUFFER_SIZE);
  if (key_read_buffer == NULL)
  {
    msg_error("Could not allocate %d bytes for the console readbuffer.\n", PEM_READ_BUFFER_SIZE);
    return -1;
  }

  memset(key_read_buffer, 0, PEM_READ_BUFFER_SIZE);
  printf("\nEnter your %s:   (Como es tedioso introducirlo, se hace mediante codigo).\n",pem_name);

  strcpy(key_read_buffer, mi_CertificadoTLS); //entrada artificial del certificado

  if(key_read_buffer == NULL){
	  enterPemString(key_read_buffer, PEM_READ_BUFFER_SIZE);
  }


  msg_info("read TLS Certificate: --->\n%s\n<---\n", key_read_buffer);

  /* Write to Flash. */
  TRACE_FLASH("writing to %lx\n", flash_addr);

#ifdef FIREWALL_MBEDLIB
  if (restricted_area)
  {
    ret = FLASH_firewall_update((uint32_t)flash_addr, key_read_buffer, strlen(key_read_buffer) + 1);  /* Append the closing \0*/
  }
  else
#endif
  {
    ret = FLASH_update((uint32_t)flash_addr, key_read_buffer, strlen(key_read_buffer) + 1);  /* Append the closing \0*/
  }

  free(key_read_buffer);

  return ret;
 }

/* Warning:
 *  The device key pair should only be updated if the application uses it.
 *  The connection security mode may chosen by the user during the device configuration.
 *  Therefore, updateTLSCredentials() must be called only after the IoT device configuration has been selected.
 */
int updateTLSCredentials(void)
{
  int ret = 0;

  if ( (checkTLSRootCA() == -1)
      || dialog_ask("\nDo you want to update the root CA certificate(s)? [y/n]\n") )
  {
    printf("\nUpdating TLS security credentials.\n");
    printf("\nEnter the x509 certificates or keys as per the following format:\n");
    printf("-----BEGIN CERTIFICATE-----\n");
    printf("YMPGn8u67GB9t+aEMr5P+1gmIgNb1LTV+/Xjli5wwOQuvfwu7uJBVcA0Ln0kcmnL\n");
    printf("R7EUQIN9Z/SG9jGr8XmksrUuEvmEF/Bibyc+E1ixVA0hmnM3oTDPb5Lc9un8rNsu\n");
    printf(".......\n");
    printf("-----END CERTIFICATE-----\n");
    printf("-----BEGIN CERTIFICATE-----\n");
    printf("YMPGn8u67GB9t+aEMr5P+1gmIgNb1LTV+/Xjli5wwOQuvfwu7uJBVcA0Ln0kcmnL\n");
    printf(".......\n");
    printf("-----END CERTIFICATE-----\n");
    printf("\n.......\n");

    ret = CaptureAndFlashPem("root CA",lUserConfigPtr->tls_root_ca_cert, false);
    if (ret == 0)
    {
      uint64_t magic = USER_CONF_MAGIC;
      ret = FLASH_update((uint32_t)&lUserConfigPtr->ca_tls_magic, &magic, sizeof(uint64_t));
    }
  }

  if ( (ret == 0) && app_needs_device_keypair() )
  {
    if (checkTLSDeviceConfig() == -1)
    {
      ret |= CaptureAndFlashPem("device certificate",lUserConfigPtr->tls_device_cert, false);
      ret |= CaptureAndFlashPem("device key",lUserConfigPtr->tls_device_key, true);
    }
    else
    {
      if (dialog_ask("Do you want to update the device certificate? [y/n]\n"))
      {
        ret |= CaptureAndFlashPem("device certificate",lUserConfigPtr->tls_device_cert, false);
      }

      if (dialog_ask("Do you want to update the device key? [y/n]\n"))
      {
        ret |= CaptureAndFlashPem("device key",lUserConfigPtr->tls_device_key, true);
      }
    }

    if (ret == 0)
    {
      uint64_t magic = USER_CONF_MAGIC;
      ret = FLASH_update((uint32_t)&lUserConfigPtr->device_tls_magic, &magic, sizeof(uint64_t));
    }
  }

  if (ret < 0)
  {
    msg_error("Failed updating the TLS configuration in Flash.\n");
  }

  return ret;
}


/**
  * @brief  Check if TLS root CA certificates are present in Flash memory.
  * @param  void
  * @retval 0 Configured,
           -1 Not configured.
  */
int checkTLSRootCA()
{
  return (lUserConfigPtr->ca_tls_magic == USER_CONF_MAGIC) ? 0 : -1;

}


/**
  * @brief  Check if the device TLS credentials (device certificate and device private key)
            are present in Flash memory.
  * @param  void
  * @retval 0 Configured,
           -1 Not configured.
  */
int checkTLSDeviceConfig()
{
  return (lUserConfigPtr->device_tls_magic == USER_CONF_MAGIC) ? 0 : -1;
}


/**
  * @brief  Store the IoT device configuration in Flash.
  * @param  In: config    Configuration data.
  * @retval  0  Success
  *         -1  Error
  */
int setIoTDeviceConfig(iot_config_t *config)
{
  int ret = 0;
  config->magic = USER_CONF_MAGIC;

  if (FLASH_update((uint32_t)&lUserConfigPtr->iot_config, config, sizeof(iot_config_t)) < 0)
  {
    msg_error("Failed programming the IOT config into Flash.\n");
    ret = -1;
  }

  return ret;
}

#ifdef AWS
/* Deprecated; only for AWS. */
/**
  * @brief  Get the MQTT broker address (AWS endpoint) from Flash memory.
  * @param  Out:  address   Pointer to location of the server address.
  * @retval  0  Success:  The server address is configured and returned to the caller.
  *         -1  Error:    No server address is configured.
  */
int getServerAddress(const char ** const address)
{
  int ret = -1;

  if (address != NULL)
  {
    if (lUserConfigPtr->iot_config.magic == USER_CONF_MAGIC)
    {
      *address = lUserConfigPtr->iot_config.server_name;
      ret = 0;
    } else {
      *address = NULL;
    }
  }
  return ret;
}
#endif /* AWS */

/**
  * @brief  Get the device configuration from Flash.
  * @param  Out:  name    Pointer to the location of the device configuration. NULL if absent.
  * @retval   0   Success:  The device configuration is configured and returned to the caller.
  *          -1   Error:    Device configuration absent.

  */
int getIoTDeviceConfig(const char ** const name)
{
  int ret = -1;

  if (name != NULL)
  {
    if (lUserConfigPtr->iot_config.magic == USER_CONF_MAGIC)
    {
      *name = lUserConfigPtr->iot_config.device_name;
      ret = 0;
    } else {
      *name = NULL;
    }
  }
  return ret;
}

/**
  * @brief  Check if an IoT device configuration is present in Flash memory.
  * @retval 0:  Configuration present.
  *        -1:  No configuration.
  */
int checkIoTDeviceConfig()
{
  return (lUserConfigPtr->iot_config.magic == USER_CONF_MAGIC) ? 0 : -1;
}


/**
  * @brief  Get the TLS certificates and private key addresses in the Flash memory.
  * @param  Out: ca_cert        CA certificate / trust chain (PEM format: string)
  * @param  Out: device_cert    Device certificate (PEM format: string)
  * @param  Out: private_key    Device private key (PEM format: string)
  * @retval 0:    TLS credentials found, and passed back to the caller.
  *        -1:    TLS credentials not found.
  */
int getTLSKeys(const char ** const root_ca_cert, const char ** const device_cert, const char ** const private_key)
{
  int rc = -1;
  if (  (lUserConfigPtr->ca_tls_magic == USER_CONF_MAGIC)
      && ( (lUserConfigPtr->device_tls_magic == USER_CONF_MAGIC) || !app_needs_device_keypair() )  )
  {
    if (root_ca_cert != NULL)    *root_ca_cert = lUserConfigPtr->tls_root_ca_cert;
    if (device_cert !=NULL)      *device_cert = lUserConfigPtr->tls_device_cert;
    if (private_key!= NULL)      *private_key = lUserConfigPtr->tls_device_key;
    rc = 0;
  }
  else
  {
    if (root_ca_cert != NULL)    *root_ca_cert = NULL;
    if (device_cert !=NULL)      *device_cert = NULL;
    if (private_key!= NULL)      *private_key = NULL;
  }
  return rc;
}

#ifdef RFU
/**
  * @brief  Firmware version management dialog.
  *         Allows:
  *             - Selecting a different FW version for the next boot, if already programmed in the other Flash bank.
  *             - Download a FW file from an HTTP URL and program it to the other FLASH bank.
  */
#define DEFAULT_FW_URL      "http://192.168.3.113/Project-gentit.sfu"
#define MAX_FW_URL_LENGTH   100

int updateFirmwareVersion()
{

  printf("\n*** Firmware version management ***\n");
  printf("\nPress the BLUE user button within the next 5 seconds\nto change the firmware version\n");

  if (Button_WaitForPush(5000))
  {
    char fw_url[MAX_FW_URL_LENGTH];
    strncpy(fw_url, DEFAULT_FW_URL, sizeof(fw_url));

    printf("\nEnter the URL of the new firmware file:(By default: %s) :", fw_url);
    getInputString(fw_url, sizeof(fw_url));
    msg_info("read: --->\n%s\n<---\n", fw_url);

    printf("Downloading and programming the new firmware into the alternate Flash bank.\n");

    int ret = rfu_update(fw_url);
    switch (ret)
    {
      case RFU_OK:
        printf("\nProgramming done. Now you can reset the board.\n\n");
        break;
      case RFU_ERR_HTTP:
        printf("\nError: Programming failed. Reason: HTTP error - check your network connection, "
               "and that the HTTP server supports HTTP/1.1 and the progressive download.\n\n");
        break;
      case RFU_ERR_FF:
        printf("\nError: Programming failed. Reason: Invalid firmware fileformat - check that the IAR simple-code format is used.\n\n");
        break;
      case RFU_ERR_FLASH:
        printf("\nError: Programming failed. Reason: Flash memory erase/write - check that the firmware file matches the SoC Flash memory mapping"
               "and write protection settings. Double check that there is no illegal write to the Flash address range.\n\n");
        break;
      default:
        printf("\nError: Programming failed. Unknown reason.\n\n");
    }
  }

  return 0;
}
#endif /* RFU support */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
