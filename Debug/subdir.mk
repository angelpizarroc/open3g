################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../coninfo.c \
../corebase.c \
../main.c \
../mainlog.c \
../monitor.c 

OBJS += \
./coninfo.o \
./corebase.o \
./main.o \
./mainlog.o \
./monitor.o 

C_DEPS += \
./coninfo.d \
./corebase.d \
./main.d \
./mainlog.d \
./monitor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


