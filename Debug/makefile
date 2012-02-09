################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include autoPilot/src/subdir.mk
-include 3rdParty/printf/subdir.mk
-include 3rdParty/FreeRTOS/portable/MemMang/subdir.mk
-include 3rdParty/FreeRTOS/portable/GCC/ARM_CM3/subdir.mk
-include 3rdParty/FreeRTOS/subdir.mk
-include 3rdParty/Drivers/source/subdir.mk
-include 3rdParty/Core/CM3/DeviceSupport/NXP/LPC17xx/startup/arm/subdir.mk
-include 3rdParty/Core/CM3/DeviceSupport/NXP/LPC17xx/subdir.mk
-include 3rdParty/Core/CM3/CoreSupport/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
ee542.hex \

SECONDARY_LIST += \
ee542.lst \

SECONDARY_SIZE += \
ee542.siz \


# All Target
all: ee542.elf secondary-outputs

# Tool invocations
ee542.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Linux GCC C Linker'
	arm-none-eabi-gcc -T"/home/jenya/Documents/DEV/ee542/autoPilot/rtosdemo_rdb1768_Debug.ld" -nostartfiles -Wl,-Map,ee542.map -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "ee542.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ee542.hex: ee542.elf
	@echo 'Invoking: ARM Sourcery Linux GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary ee542.elf  "ee542.hex"
	@echo 'Finished building: $@'
	@echo ' '

ee542.lst: ee542.elf
	@echo 'Invoking: ARM Sourcery Linux GNU Create Listing'
	arm-none-eabi-objdump -h -S ee542.elf > "ee542.lst"
	@echo 'Finished building: $@'
	@echo ' '

ee542.siz: ee542.elf
	@echo 'Invoking: ARM Sourcery Linux GNU Print Size'
	arm-none-eabi-size  --format=berkeley ee542.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) ee542.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
