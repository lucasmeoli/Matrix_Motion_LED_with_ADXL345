################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/API_decode_coordinates.c 

OBJS += \
./Drivers/API/Src/API_decode_coordinates.o 

C_DEPS += \
./Drivers/API/Src/API_decode_coordinates.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su Drivers/API/Src/%.cyclo: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Inc -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/CMSIS/Include" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/BSP/STM32F4xx_Nucleo_144" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/Core/Inc" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Inc" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Src" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Src/Max7219" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Src/Adxl345" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Inc/Adxl345" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Inc/Max7219" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Inc/Utils" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Src/Utils" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/API_decode_coordinates.cyclo ./Drivers/API/Src/API_decode_coordinates.d ./Drivers/API/Src/API_decode_coordinates.o ./Drivers/API/Src/API_decode_coordinates.su

.PHONY: clean-Drivers-2f-API-2f-Src

