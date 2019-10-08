################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../imc/PerceptronMulticapa.cpp \
../imc/util.cpp 

OBJS += \
./imc/PerceptronMulticapa.o \
./imc/util.o 

CPP_DEPS += \
./imc/PerceptronMulticapa.d \
./imc/util.d 


# Each subdirectory must supply rules for building sources it contributes
imc/%.o: ../imc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


