/**
  ******************************************************************************
  * @file    sensors_data.c
  * @author  MCD Application Team
  * @brief   Manage sensors of STM32L475 IoT board.
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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "sensors_data.h"

#include "stm32l4xx_hal.h"
#include "stm32l475e_iot01.h"
#include "stm32l475e_iot01_tsensor.h"
#include "stm32l475e_iot01_hsensor.h"
#include "stm32l475e_iot01_psensor.h"
#include "stm32l475e_iot01_magneto.h"
#include "stm32l475e_iot01_gyro.h"
#include "stm32l475e_iot01_accelero.h"
#include "msg.h"

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/

/**
  * @brief  init_sensors
  * @param  none
  * @retval 0 in case of success
  *         -1 in case of failure
  */
int init_sensors(void)
{
  int ret = 0;
  
  if (HSENSOR_OK != BSP_HSENSOR_Init())
  {
    msg_error("BSP_HSENSOR_Init() returns %d\n", ret);
    ret = -1;
  }
  
  if (TSENSOR_OK != BSP_TSENSOR_Init())
  {
    msg_error("BSP_TSENSOR_Init() returns %d\n", ret);
    ret = -1;
  }
  
  if (PSENSOR_OK != BSP_PSENSOR_Init())
  {
    msg_error("BSP_PSENSOR_Init() returns %d\n", ret);
    ret = -1;
  }
  
  if (MAGNETO_OK != BSP_MAGNETO_Init())
  {
    msg_error("BSP_MAGNETO_Init() returns %d\n", ret);
    ret = -1;
  }

  if (GYRO_OK != BSP_GYRO_Init())
  {
    msg_error("BSP_GYRO_Init() returns %d\n", ret);
    ret = -1;
  }
  
  if (ACCELERO_OK != BSP_ACCELERO_Init())
  {
    msg_error("BSP_ACCELERO_Init() returns %d\n", ret);
    ret = -1;
  }
  
  return ret;
}

/**
  * @brief  fill the buffer with the sensor values
  * @param  none
  * @param Buffer is the char pointer for the buffer to be filled
  * @param Size size of the above buffer
  * @retval 0 in case of success
  *         -1 in case of failure
  */
int PrepareSensorsData(char * Buffer, int Size, char * deviceID)
{
#if (defined(BLUEMIX) || defined(AWS) || defined(EXOSITEHTTP)) || defined(GROVESTREAMS) || defined(UBIDOTS)
  float    TEMPERATURE_Value;
  float    HUMIDITY_Value;
  float    PRESSURE_Value;
  int16_t  ACC_Value[3];
  float    GYR_Value[3];
  int16_t  MAG_Value[3];
  uint16_t PROXIMITY_Value;

  char * Buff = Buffer;
  int BuffSize = Size;
  int snprintfreturn = 0;

  TEMPERATURE_Value = BSP_TSENSOR_ReadTemp();
  HUMIDITY_Value = BSP_HSENSOR_ReadHumidity();
  PRESSURE_Value = BSP_PSENSOR_ReadPressure();
  BSP_ACCELERO_AccGetXYZ(ACC_Value);
  BSP_GYRO_GetXYZ(GYR_Value);
  BSP_MAGNETO_GetXYZ(MAG_Value);

#ifdef BLUEMIX
  snprintfreturn = snprintf( Buff, BuffSize, "{\"d\":{"
           "\"temperature\": %.2f, \"humidity\": %.2f, \"pressure\": %.2f, \"proximity\": %d, "
           "\"acc_x\": %d, \"acc_y\": %d, \"acc_z\": %d, "
           "\"gyr_x\": %.0f, \"gyr_y\": %.0f, \"gyr_z\": %.0f, "
           "\"mag_x\": %d, \"mag_y\": %d, \"mag_z\": %d"
             "}}",
           TEMPERATURE_Value, HUMIDITY_Value, PRESSURE_Value, PROXIMITY_Value,
           ACC_Value[0], ACC_Value[1], ACC_Value[2],
           GYR_Value[0], GYR_Value[1], GYR_Value[2],
           MAG_Value[0], MAG_Value[1], MAG_Value[2] );

#elif defined(AWS)
  if (deviceID != NULL)
  {
    snprintfreturn = snprintf( Buff, BuffSize, "{\"deviceId\":\"%s\","
             "\"temperature\": %.2f, \"humidity\": %.2f, \"pressure\": %.2f, \"proximity\": %d, "
             "\"acc_x\": %d, \"acc_y\": %d, \"acc_z\": %d, "
             "\"gyr_x\": %.0f, \"gyr_y\": %.0f, \"gyr_z\": %.0f, "
             "\"mag_x\": %d, \"mag_y\": %d, \"mag_z\": %d"
             "}",
             deviceID,
             TEMPERATURE_Value, HUMIDITY_Value, PRESSURE_Value, PROXIMITY_Value,
             ACC_Value[0], ACC_Value[1], ACC_Value[2],
             GYR_Value[0], GYR_Value[1], GYR_Value[2],
             MAG_Value[0], MAG_Value[1], MAG_Value[2] );
  }
  else
  {
  snprintfreturn = snprintf( Buff, BuffSize, "{\n \"state\": {\n  \"reported\": {\n"
           "   \"temperature\": %.2f,\n   \"humidity\": %.2f,\n   \"pressure\": %.2f,\n   \"proximity\": %d,\n"
           "   \"acc_x\": %d, \"acc_y\": %d, \"acc_z\": %d,\n"
           "   \"gyr_x\": %.0f, \"gyr_y\": %.0f, \"gyr_z\": %.0f,\n"
           "   \"mag_x\": %d, \"mag_y\": %d, \"mag_z\": %d\n"
           "  }\n }\n}",
           TEMPERATURE_Value, HUMIDITY_Value, PRESSURE_Value, PROXIMITY_Value,
           ACC_Value[0], ACC_Value[1], ACC_Value[2],
           GYR_Value[0], GYR_Value[1], GYR_Value[2],
           MAG_Value[0], MAG_Value[1], MAG_Value[2] );
  }
#elif defined(EXOSITEHTTP)
  snprintfreturn = snprintf( Buff, BuffSize, 
           "temperature=%.2f&"
           "humidity=%.2f&"
           "pressure=%.2f&"
           "proximity=%d&"
           "acc_x=%d&"
           "acc_y=%d&"
           "acc_z=%d&"
           "gyr_x=%.0f&"
           "gyr_y=%.0f&"
           "gyr_z=%.0f&"
           "mag_x=%d&"
           "mag_y=%d&"
           "mag_z=%d",
           TEMPERATURE_Value, HUMIDITY_Value, PRESSURE_Value, PROXIMITY_Value,
           ACC_Value[0], ACC_Value[1], ACC_Value[2],
           GYR_Value[0], GYR_Value[1], GYR_Value[2],
           MAG_Value[0], MAG_Value[1], MAG_Value[2] );
  
#elif defined(GROVESTREAMS)
      snprintfreturn = snprintf( Buff, BuffSize, "["
             "{\"compId\":\"%s\",\"streamId\": \"temperature\", \"data\": %.2f },\n" 
             "{\"compId\":\"%s\",\"streamId\": \"humidity\", \"data\": %.2f },\n"
             "{\"compId\":\"%s\",\"streamId\": \"pressure\", \"data\": %.2f },\n" 
             "{\"compId\":\"%s\",\"streamId\": \"proximity\", \"data\": %d },\n"
             "{\"compId\":\"%s\",\"streamId\": \"acc_x\", \"data\": %d },\n" 
             "{\"compId\":\"%s\",\"streamId\": \"acc_y\", \"data\": %d },\n" 
             "{\"compId\":\"%s\",\"streamId\": \"acc_z\", \"data\": %d },\n"
             "{\"compId\":\"%s\",\"streamId\": \"gyr_x\", \"data\": %.0f },\n" 
             "{\"compId\":\"%s\",\"streamId\": \"gyr_y\", \"data\": %.0f },\n" 
             "{\"compId\":\"%s\",\"streamId\": \"gyr_z\", \"data\": %.0f },\n"
             "{\"compId\":\"%s\",\"streamId\": \"mag_x\", \"data\": %d },\n" 
             "{\"compId\":\"%s\",\"streamId\": \"mag_y\", \"data\": %d },\n" 
             "{\"compId\":\"%s\",\"streamId\": \"mag_z\", \"data\": %d }\n"
             "]",
             deviceID, TEMPERATURE_Value, 
             deviceID, HUMIDITY_Value, 
             deviceID, PRESSURE_Value, 
             deviceID, PROXIMITY_Value,
             deviceID, ACC_Value[0], 
             deviceID, ACC_Value[1], 
             deviceID, ACC_Value[2],
             deviceID, GYR_Value[0], 
             deviceID, GYR_Value[1], 
             deviceID, GYR_Value[2],
             deviceID, MAG_Value[0], 
             deviceID, MAG_Value[1], 
             deviceID, MAG_Value[2] );
#elif defined(UBIDOTS)
      snprintfreturn = snprintf( Buff, BuffSize, "{\n"
           " \"temperature\": %.2f,\n \"humidity\": %.2f,\n \"pressure\": %.2f,\n \"proximity\": %d,\n"
           " \"acc_x\": %d, \"acc_y\": %d, \"acc_z\": %d,\n"
           " \"gyr_x\": %.0f, \"gyr_y\": %.0f, \"gyr_z\": %.0f,\n"
           " \"mag_x\": %d, \"mag_y\": %d, \"mag_z\": %d\n"
           "}",
           TEMPERATURE_Value, HUMIDITY_Value, PRESSURE_Value, PROXIMITY_Value,
           ACC_Value[0], ACC_Value[1], ACC_Value[2],
           GYR_Value[0], GYR_Value[1], GYR_Value[2],
           MAG_Value[0], MAG_Value[1], MAG_Value[2] );
#endif

  /* Check total size to be less than buffer size
            * if the return is >=0 and <n, then
            * the entire string was successfully formatted; if the return is
            * >=n, the string was truncated (but there is still a null char
            * at the end of what was written); if the return is <0, there was
            * an error.
            */
  if (snprintfreturn >= 0 && snprintfreturn < Size)
  {
      return 0;
  }
  else if(snprintfreturn >= Size)
  {
      msg_error("Data Pack truncated\n");
      return 0;
  }
  else
  {
      msg_error("Data Pack Error\n");
      return -1;
  }
#else
  return -1;  /* Not used in this configuration. */
#endif /* (defined(BLUEMIX) || defined(AWS) || defined(EXOSITEHTTP)) || defined(UBIDOTS) */
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
