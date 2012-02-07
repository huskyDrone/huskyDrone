################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../3rdParty/LPX17xx/CM3/cr_startup_lpc17.c 

OBJS += \
./3rdParty/LPX17xx/CM3/cr_startup_lpc17.o 

C_DEPS += \
./3rdParty/LPX17xx/CM3/cr_startup_lpc17.d 


# Each subdirectory must supply rules for building sources it contributes
3rdParty/LPX17xx/CM3/%.o: ../3rdParty/LPX17xx/CM3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	arm-none-eabi-gcc -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/include" -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/portable/GCC/ARM_CM3" -I"/home/jenya/Documents/DEV/ee542/3rdParty/LPX17xx/CM3" -I"/home/jenya/Documents/DEV/ee542/autoPilot/inc" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


