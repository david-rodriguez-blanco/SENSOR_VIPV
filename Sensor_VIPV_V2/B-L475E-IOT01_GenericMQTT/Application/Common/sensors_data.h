/**
  ******************************************************************************
  * @file    sensors_data.h
  * @author  MCD Application Team
  * @brief   Header for configuration
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

/* Define to prevent recursive inclusion -------------------------------------*/

#include <stdbool.h>

#ifndef __sensors_data_h
#define __sensors_data_h
#ifdef __cplusplus
 extern "C" {
#endif

int init_sensors(void);
int PrepareSensorsData(char * Buffer, int Size, char * deviceID);

/*--------Estructura de todos los datos de una medición------------------------*/
typedef struct{

	float temperatura;
	float irradiancia[5];
	float presion;
	float humedad;

	float alebeo;
	float cabeceo;
	float guino_brujula;

	float latitud;
	float longitud;
	float altitud;
	float velocidad;
	bool ubicacion_fix;

	int agno;
	int mes;
	int dia;
	int hora;
	int min;
	int seg;

}megaDato;

typedef struct{

	char irradiancia_1[255];
	char irradiancia_2[255];
	char irradiancia_3[255];
	char irradiancia_4[255];
	char irradiancia_5[255];

	char temperatura[255];
	char presion[255];
	char humedad[255];

	char alabeo[255];
	char cabeceo[255];
	char guino_brujula[255];

	char latitud[255];
	char longitud[255];
	char altitud[255];

	char velocidad[255];

	bool ubicacion_fix;

	char tiempo_concat[255]; 				// Concatenación de una fecha, junto con la sucesión de horas

	int agno;
	int mes;
	int dia;
	int hora;
	int min;
	int seg;

}megaDatoConcat;


#ifdef __cplusplus
}
#endif
#endif /* __sensors_data_h */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
