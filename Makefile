TARGET = BASE_STM32F407VET6
BUILD = Build

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

CPU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
DEFS = -DSTM32F407xx -DDEBUG
INCLUDES = -IInc -IDrivers \
           -IDrivers/ST7735S \
           -IDrivers/CMSIS/Include \
           -IDrivers/CMSIS/Device/ST/STM32F4xx/Include

CFLAGS = $(CPU) -std=gnu11 -O0 -g3 -Wall -ffunction-sections -fdata-sections \
         -MMD -MP $(DEFS) $(INCLUDES)
ASFLAGS = $(CPU) -x assembler-with-cpp -MMD -MP $(DEFS) $(INCLUDES)
LDFLAGS = $(CPU) -T STM32F407xx_FLASH.ld --specs=nano.specs \
          -Wl,--gc-sections,-Map=$(BUILD)/$(TARGET).map,--print-memory-usage

SRC = $(wildcard Src/*.c Inc/*.c Drivers/*.c Drivers/ST7735S/*.c)
OBJ = $(patsubst %.c,$(BUILD)/%.o,$(SRC)) $(BUILD)/startup_stm32f407xx.o

.PHONY: all build flash clean
all: flash

build: $(BUILD)/$(TARGET).bin

flash: build
	st-flash --reset write $(BUILD)/$(TARGET).bin 0x08000000

$(BUILD)/$(TARGET).elf: $(OBJ) STM32F407xx_FLASH.ld
	$(CC) $(OBJ) $(LDFLAGS) -lm -o $@
	$(SIZE) $@

$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/startup_stm32f407xx.o: startup_stm32f407xx.s
	@mkdir -p $(dir $@)
	$(CC) $(ASFLAGS) -c $< -o $@

-include $(OBJ:.o=.d)

clean:
	rm -r $(BUILD)
