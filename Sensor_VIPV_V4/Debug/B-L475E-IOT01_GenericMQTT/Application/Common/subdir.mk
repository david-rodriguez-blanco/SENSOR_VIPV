################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../B-L475E-IOT01_GenericMQTT/Application/Common/STM32CubeRTCInterface.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/cloud.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/entropy_hardware_poll.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/flash_l4.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/heap.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/http_util.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/iot_flash_config.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/mbedtls_net.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/net.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/net_tcp_wifi.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/net_tls_mbedtls.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/paho_timer.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/rfu.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/sensors_data.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/timedate.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/timingSystem.c \
../B-L475E-IOT01_GenericMQTT/Application/Common/wifi_net.c 

OBJS += \
./B-L475E-IOT01_GenericMQTT/Application/Common/STM32CubeRTCInterface.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/cloud.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/entropy_hardware_poll.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/flash_l4.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/heap.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/http_util.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/iot_flash_config.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/mbedtls_net.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/net.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/net_tcp_wifi.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/net_tls_mbedtls.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/paho_timer.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/rfu.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/sensors_data.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/timedate.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/timingSystem.o \
./B-L475E-IOT01_GenericMQTT/Application/Common/wifi_net.o 

C_DEPS += \
./B-L475E-IOT01_GenericMQTT/Application/Common/STM32CubeRTCInterface.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/cloud.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/entropy_hardware_poll.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/flash_l4.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/heap.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/http_util.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/iot_flash_config.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/mbedtls_net.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/net.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/net_tcp_wifi.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/net_tls_mbedtls.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/paho_timer.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/rfu.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/sensors_data.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/timedate.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/timingSystem.d \
./B-L475E-IOT01_GenericMQTT/Application/Common/wifi_net.d 


# Each subdirectory must supply rules for building sources it contributes
B-L475E-IOT01_GenericMQTT/Application/Common/%.o B-L475E-IOT01_GenericMQTT/Application/Common/%.su: ../B-L475E-IOT01_GenericMQTT/Application/Common/%.c B-L475E-IOT01_GenericMQTT/Application/Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' -DUSE_WIFI -DSENSOR -DDEBUG -DENABLE_IOT_INFO -DGENERICMQTT -DUSE_HAL_DRIVER -DENABLE_IOT_WARNING -DUSE_MBED_TLS -DENABLE_IOT_ERROR -DSTM32L475xx -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/LIS3MDL -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/LPS22HB -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/LSM6DSL -I../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTClient-C -I../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MbedTLS -I../B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/cJSON -I../B-L475E-IOT01_GenericMQTT/Application/Common -I../B-L475E-IOT01_GenericMQTT/Application/GenericMQTT -I../B-L475E-IOT01_GenericMQTT/Application/Wifi -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP/B-L475E-IOT01 -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/HTS221 -I../B-L475E-IOT01_GenericMQTT/Drivers/BSP -I../B-L475E-IOT01_GenericMQTT/Drivers/CMSIS -I../B-L475E-IOT01_GenericMQTT/Drivers/STM32L4xx_HAL_Driver -I../Core/Inc/minmea-master -I../Middlewares/ST/STM32_MotionFX_Library/Inc -O0 -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-B-2d-L475E-2d-IOT01_GenericMQTT-2f-Application-2f-Common

clean-B-2d-L475E-2d-IOT01_GenericMQTT-2f-Application-2f-Common:
	-$(RM) ./B-L475E-IOT01_GenericMQTT/Application/Common/STM32CubeRTCInterface.d ./B-L475E-IOT01_GenericMQTT/Application/Common/STM32CubeRTCInterface.o ./B-L475E-IOT01_GenericMQTT/Application/Common/STM32CubeRTCInterface.su ./B-L475E-IOT01_GenericMQTT/Application/Common/cloud.d ./B-L475E-IOT01_GenericMQTT/Application/Common/cloud.o ./B-L475E-IOT01_GenericMQTT/Application/Common/cloud.su ./B-L475E-IOT01_GenericMQTT/Application/Common/entropy_hardware_poll.d ./B-L475E-IOT01_GenericMQTT/Application/Common/entropy_hardware_poll.o ./B-L475E-IOT01_GenericMQTT/Application/Common/entropy_hardware_poll.su ./B-L475E-IOT01_GenericMQTT/Application/Common/flash_l4.d ./B-L475E-IOT01_GenericMQTT/Application/Common/flash_l4.o ./B-L475E-IOT01_GenericMQTT/Application/Common/flash_l4.su ./B-L475E-IOT01_GenericMQTT/Application/Common/heap.d ./B-L475E-IOT01_GenericMQTT/Application/Common/heap.o ./B-L475E-IOT01_GenericMQTT/Application/Common/heap.su ./B-L475E-IOT01_GenericMQTT/Application/Common/http_util.d ./B-L475E-IOT01_GenericMQTT/Application/Common/http_util.o ./B-L475E-IOT01_GenericMQTT/Application/Common/http_util.su ./B-L475E-IOT01_GenericMQTT/Application/Common/iot_flash_config.d ./B-L475E-IOT01_GenericMQTT/Application/Common/iot_flash_config.o ./B-L475E-IOT01_GenericMQTT/Application/Common/iot_flash_config.su ./B-L475E-IOT01_GenericMQTT/Application/Common/mbedtls_net.d ./B-L475E-IOT01_GenericMQTT/Application/Common/mbedtls_net.o ./B-L475E-IOT01_GenericMQTT/Application/Common/mbedtls_net.su ./B-L475E-IOT01_GenericMQTT/Application/Common/net.d ./B-L475E-IOT01_GenericMQTT/Application/Common/net.o ./B-L475E-IOT01_GenericMQTT/Application/Common/net.su ./B-L475E-IOT01_GenericMQTT/Application/Common/net_tcp_wifi.d ./B-L475E-IOT01_GenericMQTT/Application/Common/net_tcp_wifi.o ./B-L475E-IOT01_GenericMQTT/Application/Common/net_tcp_wifi.su ./B-L475E-IOT01_GenericMQTT/Application/Common/net_tls_mbedtls.d ./B-L475E-IOT01_GenericMQTT/Application/Common/net_tls_mbedtls.o ./B-L475E-IOT01_GenericMQTT/Application/Common/net_tls_mbedtls.su ./B-L475E-IOT01_GenericMQTT/Application/Common/paho_timer.d ./B-L475E-IOT01_GenericMQTT/Application/Common/paho_timer.o ./B-L475E-IOT01_GenericMQTT/Application/Common/paho_timer.su ./B-L475E-IOT01_GenericMQTT/Application/Common/rfu.d ./B-L475E-IOT01_GenericMQTT/Application/Common/rfu.o ./B-L475E-IOT01_GenericMQTT/Application/Common/rfu.su ./B-L475E-IOT01_GenericMQTT/Application/Common/sensors_data.d ./B-L475E-IOT01_GenericMQTT/Application/Common/sensors_data.o ./B-L475E-IOT01_GenericMQTT/Application/Common/sensors_data.su ./B-L475E-IOT01_GenericMQTT/Application/Common/timedate.d ./B-L475E-IOT01_GenericMQTT/Application/Common/timedate.o ./B-L475E-IOT01_GenericMQTT/Application/Common/timedate.su ./B-L475E-IOT01_GenericMQTT/Application/Common/timingSystem.d ./B-L475E-IOT01_GenericMQTT/Application/Common/timingSystem.o ./B-L475E-IOT01_GenericMQTT/Application/Common/timingSystem.su ./B-L475E-IOT01_GenericMQTT/Application/Common/wifi_net.d ./B-L475E-IOT01_GenericMQTT/Application/Common/wifi_net.o ./B-L475E-IOT01_GenericMQTT/Application/Common/wifi_net.su

.PHONY: clean-B-2d-L475E-2d-IOT01_GenericMQTT-2f-Application-2f-Common

