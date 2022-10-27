################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/Src/btn.c \
../Components/Src/btn_config.c \
../Components/Src/led.c \
../Components/Src/led_config.c \
../Components/Src/serial_api.c \
../Components/Src/serial_api_config.c 

OBJS += \
./Components/Src/btn.o \
./Components/Src/btn_config.o \
./Components/Src/led.o \
./Components/Src/led_config.o \
./Components/Src/serial_api.o \
./Components/Src/serial_api_config.o 

C_DEPS += \
./Components/Src/btn.d \
./Components/Src/btn_config.d \
./Components/Src/led.d \
./Components/Src/led_config.d \
./Components/Src/serial_api.d \
./Components/Src/serial_api_config.d 


# Each subdirectory must supply rules for building sources it contributes
Components/Src/%.o Components/Src/%.su: ../Components/Src/%.c Components/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Components/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-Src

clean-Components-2f-Src:
	-$(RM) ./Components/Src/btn.d ./Components/Src/btn.o ./Components/Src/btn.su ./Components/Src/btn_config.d ./Components/Src/btn_config.o ./Components/Src/btn_config.su ./Components/Src/led.d ./Components/Src/led.o ./Components/Src/led.su ./Components/Src/led_config.d ./Components/Src/led_config.o ./Components/Src/led_config.su ./Components/Src/serial_api.d ./Components/Src/serial_api.o ./Components/Src/serial_api.su ./Components/Src/serial_api_config.d ./Components/Src/serial_api_config.o ./Components/Src/serial_api_config.su

.PHONY: clean-Components-2f-Src

