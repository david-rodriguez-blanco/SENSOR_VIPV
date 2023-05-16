################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/Inc/minmea-master/subdir.mk
-include B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/cJSON/subdir.mk
-include B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MbedTLS/subdir.mk
-include B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTPacket/subdir.mk
-include B-L475E-IOT01_GenericMQTT/Middlewares/Third_Party/MQTTClient-C/subdir.mk
-include B-L475E-IOT01_GenericMQTT/Drivers/STM32L4xx_HAL_Driver/subdir.mk
-include B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/LSM6DSL/subdir.mk
-include B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/LPS22HB/subdir.mk
-include B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/LIS3MDL/subdir.mk
-include B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/HTS221/subdir.mk
-include B-L475E-IOT01_GenericMQTT/Drivers/BSP/B-L475E-IOT01/subdir.mk
-include B-L475E-IOT01_GenericMQTT/Drivers/BSP/subdir.mk
-include B-L475E-IOT01_GenericMQTT/Application/Wifi/subdir.mk
-include B-L475E-IOT01_GenericMQTT/Application/Common/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := VIPV_Original
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
VIPV_Original.elf \

MAP_FILES += \
VIPV_Original.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
VIPV_Original.list \


# All Target
all: main-build

# Main-build Target
main-build: VIPV_Original.elf secondary-outputs

# Tool invocations
VIPV_Original.elf VIPV_Original.map: $(OBJS) $(USER_OBJS) C:\Users\David\Documents\SENSOR_VIPV\Sensor_VIPV_Original\STM32L475VGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "VIPV_Original.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\David\Documents\SENSOR_VIPV\Sensor_VIPV_Original\STM32L475VGTX_FLASH.ld" -Wl,-Map="VIPV_Original.map" -Wl,--gc-sections -static -L../Middlewares/ST/STM32_MotionFX_Library/Lib --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -u _printf_float -u _scanf_float
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

VIPV_Original.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "VIPV_Original.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) VIPV_Original.elf VIPV_Original.list VIPV_Original.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
