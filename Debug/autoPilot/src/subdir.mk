################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../autoPilot/src/driverGps.c \
../autoPilot/src/hwConfig.c \
../autoPilot/src/main.c \
../autoPilot/src/taskGps.c \
../autoPilot/src/taskLed.c \
../autoPilot/src/util.c 

OBJS += \
./autoPilot/src/driverGps.o \
./autoPilot/src/hwConfig.o \
./autoPilot/src/main.o \
./autoPilot/src/taskGps.o \
./autoPilot/src/taskLed.o \
./autoPilot/src/util.o 

C_DEPS += \
./autoPilot/src/driverGps.d \
./autoPilot/src/hwConfig.d \
./autoPilot/src/main.d \
./autoPilot/src/taskGps.d \
./autoPilot/src/taskLed.d \
./autoPilot/src/util.d 


# Each subdirectory must supply rules for building sources it contributes
autoPilot/src/%.o: ../autoPilot/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	arm-none-eabi-gcc -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/include" -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/portable/GCC/ARM_CM3" -I"/home/jenya/Documents/DEV/ee542/autoPilot/inc" -I"/home/jenya/Documents/DEV/ee542/3rdParty/Core/CM3/CoreSupport" -I"/home/jenya/Documents/DEV/ee542/3rdParty/Core/CM3/DeviceSupport/NXP/LPC17xx" -I"/home/jenya/Documents/DEV/ee542/3rdParty/Drivers/include" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


