################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FreeRTOS/list.c \
../src/FreeRTOS/queue.c \
../src/FreeRTOS/tasks.c 

OBJS += \
./src/FreeRTOS/list.o \
./src/FreeRTOS/queue.o \
./src/FreeRTOS/tasks.o 

C_DEPS += \
./src/FreeRTOS/list.d \
./src/FreeRTOS/queue.d \
./src/FreeRTOS/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
src/FreeRTOS/%.o: ../src/FreeRTOS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	arm-none-eabi-gcc -I"/home/jenya/Documents/DEV/ee542/src/Common Demo Tasks/include" -I"/home/jenya/Documents/DEV/ee542/src/FreeRTOS/include" -I"/home/jenya/Documents/DEV/ee542/src/FreeRTOS/portable/GCC/ARM_CM3" -I"/home/jenya/Documents/DEV/ee542/src/LPCUSB" -I"/home/jenya/Documents/DEV/ee542/src" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


