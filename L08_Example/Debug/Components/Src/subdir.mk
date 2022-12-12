################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/Src/__template.c \
../Components/Src/btn.c \
../Components/Src/btn_config.c \
../Components/Src/dio.c \
../Components/Src/disp.c \
../Components/Src/disp_config.c 

OBJS += \
./Components/Src/__template.o \
./Components/Src/btn.o \
./Components/Src/btn_config.o \
./Components/Src/dio.o \
./Components/Src/disp.o \
./Components/Src/disp_config.o 

C_DEPS += \
./Components/Src/__template.d \
./Components/Src/btn.d \
./Components/Src/btn_config.d \
./Components/Src/dio.d \
./Components/Src/disp.d \
./Components/Src/disp_config.d 


# Each subdirectory must supply rules for building sources it contributes
Components/Src/%.o Components/Src/%.su: ../Components/Src/%.c Components/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/PP/Dydaktyka/MATERIALY/SM_MATERIALY/NUCLEO-F756ZG-Examples-ver-2022-23/L08_Example/Components/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-Src

clean-Components-2f-Src:
	-$(RM) ./Components/Src/__template.d ./Components/Src/__template.o ./Components/Src/__template.su ./Components/Src/btn.d ./Components/Src/btn.o ./Components/Src/btn.su ./Components/Src/btn_config.d ./Components/Src/btn_config.o ./Components/Src/btn_config.su ./Components/Src/dio.d ./Components/Src/dio.o ./Components/Src/dio.su ./Components/Src/disp.d ./Components/Src/disp.o ./Components/Src/disp.su ./Components/Src/disp_config.d ./Components/Src/disp_config.o ./Components/Src/disp_config.su

.PHONY: clean-Components-2f-Src

