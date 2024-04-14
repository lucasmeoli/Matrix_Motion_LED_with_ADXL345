################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f429xx.s 

OBJS += \
./Startup/startup_stm32f429xx.o 

S_DEPS += \
./Startup/startup_stm32f429xx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/CMSIS/Include" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/BSP/STM32F4xx_Nucleo_144" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Inc" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/Core/Inc" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Inc" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Src" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Src/Max7219" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Src/Adxl345" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Inc/Adxl345" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Inc/Max7219" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Inc/Utils" -I"/home/lpmeoli/Especializacion/trabajos_practicos/bimestre_01/PdC_Workspace/accelerometer_LED_Matrix/Drivers/API/Src/Utils" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32f429xx.d ./Startup/startup_stm32f429xx.o

.PHONY: clean-Startup

