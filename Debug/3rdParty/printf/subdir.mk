################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../3rdParty/printf/printf-stdarg.c 

OBJS += \
./3rdParty/printf/printf-stdarg.o 

C_DEPS += \
./3rdParty/printf/printf-stdarg.d 


# Each subdirectory must supply rules for building sources it contributes
3rdParty/printf/%.o: ../3rdParty/printf/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	arm-none-eabi-gcc -I"/Users/ymaksime/Documents/UW/EE542/huskyDrone/3rdParty/FreeRTOS/include" -I"/Users/ymaksime/Documents/UW/EE542/huskyDrone/3rdParty/FreeRTOS/portable/GCC/ARM_CM3" -I"/Users/ymaksime/Documents/UW/EE542/huskyDrone/autoPilot/inc" -I"/Users/ymaksime/Documents/UW/EE542/huskyDrone/3rdParty/Core/CM3/CoreSupport" -I"/Users/ymaksime/Documents/UW/EE542/huskyDrone/3rdParty/Core/CM3/DeviceSupport/NXP/LPC17xx" -I"/Users/ymaksime/Documents/UW/EE542/huskyDrone/3rdParty/Drivers/include" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


