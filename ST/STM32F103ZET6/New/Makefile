# Make variables (CC, GDB, etc...)
TC      = arm-none-eabi-
CC      = $(TC)gcc           
AS      = $(TC)as
LD      = $(TC)ld
AR      = $(TC)ar
GDB     = $(TC)gdb
OBJCOPY = $(TC)objcopy

# Source files, Object files, etc...
TOP = $(shell pwd)
STMLIB = $(TOP)/libs/STM32_USB-FS-Device_Lib_V4.0.0/Libraries

INC += -I$(TOP)/inc
INC += -I$(STMLIB)/CMSIS/Include
INC += -I$(STMLIB)/CMSIS/Device/ST/STM32F10x/Include
INC += -I$(STMLIB)/STM32F10x_StdPeriph_Driver/inc
INC += -I$(TOP)/tools
INC += -I$(TOP)/led
INC += -I$(TOP)/pwm

TARGET = Demo
SRC = $(shell find ./ -name '*.c')  

STARTUP = $(STMLIB)/CMSIS/Device/ST/STM32F10x/Source/Templates/gcc_ride7/startup_stm32f10x_hd.S

OBJ = $(SRC:%.c=%.o)          
#OBJ += $(STARTUP:%.S=%.o)


# Adjust TypeOfMCU in use, see CMSIS file "stm32f10x.h"
# STM32F103RBT (128KB FLASH, 20KB RAM) --> TypeOfMCU=STM32F10X_MD
# STM32F103ZET (512KB FLASH, 64KB RAM) --> TypeOfMCU=STM32F10X_HD
TypeOfMCU = STM32F10X_HD

MCU  = -mcpu=cortex-m3 -mthumb -mlittle-endian 
MACRO  = -D$(TypeOfMCU) -DUSE_STDPERIPH_DRIVER
CFLAGS = -c -Wall $(MCU) $(MACRO) $(INC) -std=c99

LINKER = stm32_flash.ld
LDFLAGS  = $(MCU) -T$(LINKER) 
LDFLAGS += -Wl,--gc-sections --specs=nano.specs --specs=nosys.specs 
LDFLAGS += -Wl,--start-group -lgcc -lc -lm -Wl,--end-group 
LDFLAGS += -Wl,-Map=Demo.map -Wl,-cref,-u,Reset_Handler -Wl,--defsym=malloc_getpagesize_P=0x80 
ARFLAGS = cr

# Rules shared between targets and prerequisites
PHONY += all
all: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $(TARGET).elf
	$(OBJCOPY) -Obinary $(TARGET).elf $(TARGET).bin
	$(OBJCOPY) -Oihex $(TARGET).elf $(TARGET).hex

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

# %.o: %.S
# 	$(CC) $(CFLAGS) $< -o $@

PHONY += clean
clean:
	rm -f $(shell find ./ -name '*.o')
	rm -f $(shell find ./ -name '*.d')
	rm -f $(shell find ./ -name '*.map')
	rm -f $(shell find ./ -name '*.elf')
	rm -f $(shell find ./ -name '*.bin')
	rm -f $(shell find ./ -name '*.hex')

PHONY += st-flash
stlink: all 
	st-flash write $(TARGET).bin 0x08000000

.PHONY: PHONY
