################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/LCD/lcd.c \
../src/LCD/lcd_driver.c \
../src/LCD/system_fixed_be_8_15.c 

OBJS += \
./src/LCD/lcd.o \
./src/LCD/lcd_driver.o \
./src/LCD/system_fixed_be_8_15.o 

C_DEPS += \
./src/LCD/lcd.d \
./src/LCD/lcd_driver.d \
./src/LCD/system_fixed_be_8_15.d 


# Each subdirectory must supply rules for building sources it contributes
src/LCD/%.o: ../src/LCD/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	arm-none-eabi-gcc -I/home/jenya/Documents/UW/2011-2012/2.Winter/EE542/Project/FreeRTOSV7.1.0/Source/include -I/home/jenya/Documents/UW/2011-2012/2.Winter/EE542/Project/FreeRTOSV7.1.0/Source/portable/GCC/ARM_CM3 -I"/home/jenya/Documents/DEV/test/src/Common Demo Tasks/include" -I/home/jenya/Documents/DEV/test/src/FreeRTOS/include -I/home/jenya/Documents/DEV/test/src/FreeRTOS/portable/GCC/ARM_CM3 -I/home/jenya/Documents/DEV/test/src/LCD -I/home/jenya/Documents/DEV/test/src/LPCUSB -I/home/jenya/Documents/DEV/test/src/webserver/httpd-fs -I/home/jenya/Documents/DEV/test/src -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


