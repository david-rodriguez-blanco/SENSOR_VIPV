################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../B-L475E-IOT01_GenericMQTT/Application/Wifi/es_wifi_io.c \
../B-L475E-IOT01_GenericMQTT/Application/Wifi/wifi.c 

OBJS += \
./B-L475E-IOT01_GenericMQTT/Application/Wifi/es_wifi_io.o \
./B-L475E-IOT01_GenericMQTT/Application/Wifi/wifi.o 

C_DEPS += \
./B-L475E-IOT01_GenericMQTT/Application/Wifi/es_wifi_io.d \
./B-L475E-IOT01_GenericMQTT/Application/Wifi/wifi.d 


# Each subdirectory must supply rules for building sources it contributes
B-L475E-IOT01_GenericMQTT/Application/Wifi/%.o B-L475E-IOT01_GenericMQTT/Application/Wifi/%.su: ../B-L475E-IOT01_GenericMQTT/Application/Wifi/%.c B-L475E-IOT01_GenericMQTT/Application/Wifi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' -DUSE_WIFI -DSENSOR -DDEBUG -DENABLE_IOT_INFO -DGENERICMQTT -DUSE_HAL_DRIVER -DENABLE_IOT_WARNING -DUSE_MBED_TLS -DENABLE_IOT_ERROR -DSTM32L475xx -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/LIS3MDL -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/LPS22HB -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/LSM6DSL -I../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTClient-C -I../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MbedTLS -I../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/cJSON -I../B-L475E-IOT01_GenericMQTT/Application/Common -I../B-L475E-IOT01_GenericMQTT/Application/GenericMQTT -I../B-L475E-IOT01_GenericMQTT/Application/Wifi -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP/B-L475E-IOT01 -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/HTS221 -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP -I../B-L475E-IOT01_GenericMQTT/Drivers/CMSIS -I../B-L475E-IOT01_GenericMQTT/Drivers/STM32L4xx_HAL_Driver -I../Core/Inc/minmea-master -I../Middlewares/ST/STM32_MotionFX_Library/Inc -O0 -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-B-2d-L475E-2d-IOT01_GenericMQTT-2f-Application-2f-Wifi

clean-B-2d-L475E-2d-IOT01_GenericMQTT-2f-Application-2f-Wifi:
	-$(RM) ./B-L475E-IOT01_GenericMQTT/Application/Wifi/es_wifi_io.d ./B-L475E-IOT01_GenericMQTT/Application/Wifi/es_wifi_io.o ./B-L475E-IOT01_GenericMQTT/Application/Wifi/es_wifi_io.su ./B-L475E-IOT01_GenericMQTT/Application/Wifi/wifi.d ./B-L475E-IOT01_GenericMQTT/Application/Wifi/wifi.o ./B-L475E-IOT01_GenericMQTT/Application/Wifi/wifi.su

.PHONY: clean-B-2d-L475E-2d-IOT01_GenericMQTT-2f-Application-2f-Wifi

