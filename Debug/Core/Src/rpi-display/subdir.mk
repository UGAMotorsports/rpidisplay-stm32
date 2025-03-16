################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/rpi-display/rpi-display.c 

C_DEPS += \
./Core/Src/rpi-display/rpi-display.d 

OBJS += \
./Core/Src/rpi-display/rpi-display.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/rpi-display/%.o Core/Src/rpi-display/%.su Core/Src/rpi-display/%.cyclo: ../Core/Src/rpi-display/%.c Core/Src/rpi-display/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-rpi-2d-display

clean-Core-2f-Src-2f-rpi-2d-display:
	-$(RM) ./Core/Src/rpi-display/rpi-display.cyclo ./Core/Src/rpi-display/rpi-display.d ./Core/Src/rpi-display/rpi-display.o ./Core/Src/rpi-display/rpi-display.su

.PHONY: clean-Core-2f-Src-2f-rpi-2d-display

