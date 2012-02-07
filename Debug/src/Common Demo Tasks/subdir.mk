################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Common\ Demo\ Tasks/BlockQ.c \
../src/Common\ Demo\ Tasks/GenQTest.c \
../src/Common\ Demo\ Tasks/PollQ.c \
../src/Common\ Demo\ Tasks/QPeek.c \
../src/Common\ Demo\ Tasks/blocktim.c \
../src/Common\ Demo\ Tasks/flash.c \
../src/Common\ Demo\ Tasks/integer.c \
../src/Common\ Demo\ Tasks/recmutex.c \
../src/Common\ Demo\ Tasks/semtest.c 

OBJS += \
./src/Common\ Demo\ Tasks/BlockQ.o \
./src/Common\ Demo\ Tasks/GenQTest.o \
./src/Common\ Demo\ Tasks/PollQ.o \
./src/Common\ Demo\ Tasks/QPeek.o \
./src/Common\ Demo\ Tasks/blocktim.o \
./src/Common\ Demo\ Tasks/flash.o \
./src/Common\ Demo\ Tasks/integer.o \
./src/Common\ Demo\ Tasks/recmutex.o \
./src/Common\ Demo\ Tasks/semtest.o 

C_DEPS += \
./src/Common\ Demo\ Tasks/BlockQ.d \
./src/Common\ Demo\ Tasks/GenQTest.d \
./src/Common\ Demo\ Tasks/PollQ.d \
./src/Common\ Demo\ Tasks/QPeek.d \
./src/Common\ Demo\ Tasks/blocktim.d \
./src/Common\ Demo\ Tasks/flash.d \
./src/Common\ Demo\ Tasks/integer.d \
./src/Common\ Demo\ Tasks/recmutex.d \
./src/Common\ Demo\ Tasks/semtest.d 


# Each subdirectory must supply rules for building sources it contributes
src/Common\ Demo\ Tasks/BlockQ.o: ../src/Common\ Demo\ Tasks/BlockQ.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	arm-none-eabi-gcc -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/include" -I"/home/jenya/Documents/DEV/ee542/src/Common Demo Tasks/include" -I"/home/jenya/Documents/DEV/ee542/src" -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/portable/GCC/ARM_CM3" -I"/home/jenya/Documents/DEV/ee542/3rdParty/LPX17xx/CM3" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"src/Common Demo Tasks/BlockQ.d" -MT"src/Common\ Demo\ Tasks/BlockQ.d" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Common\ Demo\ Tasks/GenQTest.o: ../src/Common\ Demo\ Tasks/GenQTest.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	arm-none-eabi-gcc -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/include" -I"/home/jenya/Documents/DEV/ee542/src/Common Demo Tasks/include" -I"/home/jenya/Documents/DEV/ee542/src" -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/portable/GCC/ARM_CM3" -I"/home/jenya/Documents/DEV/ee542/3rdParty/LPX17xx/CM3" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"src/Common Demo Tasks/GenQTest.d" -MT"src/Common\ Demo\ Tasks/GenQTest.d" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Common\ Demo\ Tasks/PollQ.o: ../src/Common\ Demo\ Tasks/PollQ.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	arm-none-eabi-gcc -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/include" -I"/home/jenya/Documents/DEV/ee542/src/Common Demo Tasks/include" -I"/home/jenya/Documents/DEV/ee542/src" -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/portable/GCC/ARM_CM3" -I"/home/jenya/Documents/DEV/ee542/3rdParty/LPX17xx/CM3" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"src/Common Demo Tasks/PollQ.d" -MT"src/Common\ Demo\ Tasks/PollQ.d" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Common\ Demo\ Tasks/QPeek.o: ../src/Common\ Demo\ Tasks/QPeek.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	arm-none-eabi-gcc -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/include" -I"/home/jenya/Documents/DEV/ee542/src/Common Demo Tasks/include" -I"/home/jenya/Documents/DEV/ee542/src" -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/portable/GCC/ARM_CM3" -I"/home/jenya/Documents/DEV/ee542/3rdParty/LPX17xx/CM3" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"src/Common Demo Tasks/QPeek.d" -MT"src/Common\ Demo\ Tasks/QPeek.d" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Common\ Demo\ Tasks/blocktim.o: ../src/Common\ Demo\ Tasks/blocktim.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	arm-none-eabi-gcc -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/include" -I"/home/jenya/Documents/DEV/ee542/src/Common Demo Tasks/include" -I"/home/jenya/Documents/DEV/ee542/src" -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/portable/GCC/ARM_CM3" -I"/home/jenya/Documents/DEV/ee542/3rdParty/LPX17xx/CM3" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"src/Common Demo Tasks/blocktim.d" -MT"src/Common\ Demo\ Tasks/blocktim.d" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Common\ Demo\ Tasks/flash.o: ../src/Common\ Demo\ Tasks/flash.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	arm-none-eabi-gcc -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/include" -I"/home/jenya/Documents/DEV/ee542/src/Common Demo Tasks/include" -I"/home/jenya/Documents/DEV/ee542/src" -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/portable/GCC/ARM_CM3" -I"/home/jenya/Documents/DEV/ee542/3rdParty/LPX17xx/CM3" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"src/Common Demo Tasks/flash.d" -MT"src/Common\ Demo\ Tasks/flash.d" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Common\ Demo\ Tasks/integer.o: ../src/Common\ Demo\ Tasks/integer.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	arm-none-eabi-gcc -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/include" -I"/home/jenya/Documents/DEV/ee542/src/Common Demo Tasks/include" -I"/home/jenya/Documents/DEV/ee542/src" -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/portable/GCC/ARM_CM3" -I"/home/jenya/Documents/DEV/ee542/3rdParty/LPX17xx/CM3" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"src/Common Demo Tasks/integer.d" -MT"src/Common\ Demo\ Tasks/integer.d" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Common\ Demo\ Tasks/recmutex.o: ../src/Common\ Demo\ Tasks/recmutex.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	arm-none-eabi-gcc -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/include" -I"/home/jenya/Documents/DEV/ee542/src/Common Demo Tasks/include" -I"/home/jenya/Documents/DEV/ee542/src" -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/portable/GCC/ARM_CM3" -I"/home/jenya/Documents/DEV/ee542/3rdParty/LPX17xx/CM3" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"src/Common Demo Tasks/recmutex.d" -MT"src/Common\ Demo\ Tasks/recmutex.d" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Common\ Demo\ Tasks/semtest.o: ../src/Common\ Demo\ Tasks/semtest.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	arm-none-eabi-gcc -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/include" -I"/home/jenya/Documents/DEV/ee542/src/Common Demo Tasks/include" -I"/home/jenya/Documents/DEV/ee542/src" -I"/home/jenya/Documents/DEV/ee542/3rdParty/FreeRTOS/portable/GCC/ARM_CM3" -I"/home/jenya/Documents/DEV/ee542/3rdParty/LPX17xx/CM3" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"src/Common Demo Tasks/semtest.d" -MT"src/Common\ Demo\ Tasks/semtest.d" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


