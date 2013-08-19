################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Dot.cpp \
../src/Exception.cpp \
../src/SDLAbstractionLayer.cpp \
../src/SDLGameSavesTest.cpp \
../src/SimpleLoadSave.cpp \
../src/Test.cpp 

OBJS += \
./src/Dot.o \
./src/Exception.o \
./src/SDLAbstractionLayer.o \
./src/SDLGameSavesTest.o \
./src/SimpleLoadSave.o \
./src/Test.o 

CPP_DEPS += \
./src/Dot.d \
./src/Exception.d \
./src/SDLAbstractionLayer.d \
./src/SDLGameSavesTest.d \
./src/SimpleLoadSave.d \
./src/Test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


