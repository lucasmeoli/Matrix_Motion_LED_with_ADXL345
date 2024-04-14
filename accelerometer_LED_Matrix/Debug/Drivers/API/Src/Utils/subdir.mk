################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/Utils/API_debounce.c \
../Drivers/API/Src/Utils/API_delay.c \
../Drivers/API/Src/Utils/API_uart.c 

OBJS += \
./Drivers/API/Src/Utils/API_debounce.o \
./Drivers/API/Src/Utils/API_delay.o \
./Drivers/API/Src/Utils/API_uart.o 

C_DEPS += \
./Drivers/API/Src/Utils/API_debounce.d \
./Drivers/API/Src/Utils/API_delay.d \
./Drivers/API/Src/Utils/API_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/Utils/%.o Drivers/API/Src/Utils/%.su Drivers/API/Src/Utils/%.cyclo: ../Drivers/API/Src/Utils/%.c Drivers/API/Src/Utils/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Inc -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/CMSIS/Include" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/BSP/STM32F4xx_Nucleo_144" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/Core/Inc" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Inc" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Src" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Src/Max7219" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Src/Adxl345" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Inc/Adxl345" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Inc/Max7219" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Inc/Utils" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Src/Utils" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src-2f-Utils

clean-Drivers-2f-API-2f-Src-2f-Utils:
	-$(RM) ./Drivers/API/Src/Utils/API_debounce.cyclo ./Drivers/API/Src/Utils/API_debounce.d ./Drivers/API/Src/Utils/API_debounce.o ./Drivers/API/Src/Utils/API_debounce.su ./Drivers/API/Src/Utils/API_delay.cyclo ./Drivers/API/Src/Utils/API_delay.d ./Drivers/API/Src/Utils/API_delay.o ./Drivers/API/Src/Utils/API_delay.su ./Drivers/API/Src/Utils/API_uart.cyclo ./Drivers/API/Src/Utils/API_uart.d ./Drivers/API/Src/Utils/API_uart.o ./Drivers/API/Src/Utils/API_uart.su

.PHONY: clean-Drivers-2f-API-2f-Src-2f-Utils

