################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.c \
../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTConnectServer.c \
../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.c \
../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTFormat.c \
../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTPacket.c \
../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.c \
../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.c \
../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSubscribeServer.c \
../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.c \
../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeServer.c 

OBJS += \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.o \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTConnectServer.o \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.o \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTFormat.o \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTPacket.o \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.o \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.o \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSubscribeServer.o \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.o \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeServer.o 

C_DEPS += \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.d \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTConnectServer.d \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.d \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTFormat.d \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTPacket.d \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.d \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.d \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSubscribeServer.d \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.d \
./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeServer.d 


# Each subdirectory must supply rules for building sources it contributes
B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/%.o B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/%.su: ../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/%.c B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DGENERICMQTT -DUSE_HAL_DRIVER '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' -DENABLE_IOT_WARNING -DUSE_WIFI -DSENSOR -DUSE_MBED_TLS -DENABLE_IOT_ERROR -DSTM32L475xx -DENABLE_IOT_INFO -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/LIS3MDL -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/LPS22HB -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/LSM6DSL -I../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTClient-C -I../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MbedTLS -I../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/cJSON -I../B-L475E-IOT01_GenericMQTT/Application/Common -I../B-L475E-IOT01_GenericMQTT/Application/GenericMQTT -I../B-L475E-IOT01_GenericMQTT/Application/Wifi -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP/B-L475E-IOT01 -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/HTS221 -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP -I../B-L475E-IOT01_GenericMQTT/Drivers/CMSIS -I../B-L475E-IOT01_GenericMQTT/Drivers/STM32L4xx_HAL_Driver -I../Core/Inc/minmea-master -I../Middlewares/ST/STM32_MotionFX_Library/Inc -I../Middlewares/ST/STM32_MotionDI_Library/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-B-2d-L475E-2d-IOT01_GenericMQTT-2f-Middlewares-2f-Third_Party-2f-MQTTPacket

clean-B-2d-L475E-2d-IOT01_GenericMQTT-2f-Middlewares-2f-Third_Party-2f-MQTTPacket:
	-$(RM) ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.d ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.o ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.su ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTConnectServer.d ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTConnectServer.o ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTConnectServer.su ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.d ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.o ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.su ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTFormat.d ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTFormat.o ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTFormat.su ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTPacket.d ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTPacket.o ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTPacket.su ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.d ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.o ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.su ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.d ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.o ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.su ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSubscribeServer.d ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSubscribeServer.o ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTSubscribeServer.su ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.d ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.o ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.su ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeServer.d ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeServer.o ./B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeServer.su

.PHONY: clean-B-2d-L475E-2d-IOT01_GenericMQTT-2f-Middlewares-2f-Third_Party-2f-MQTTPacket

