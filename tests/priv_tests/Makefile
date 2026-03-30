
# setup toolchain
CROSS_COMPILE ?= riscv64-unknown-elf-
CC:=$(CROSS_COMPILE)gcc
AS:=$(CROSS_COMPILE)as
LD:=$(CROSS_COMPILE)ld
OBJCOPY:=$(CROSS_COMPILE)objcopy
OBJDUMP:=$(CROSS_COMPILE)objdump
READELF:=$(CROSS_COMPILE)readelf


# setup test settings
ROOT_DIR := $(shell pwd)

XLEN ?= 64
PLATFORM_DIR ?= $(ROOT_DIR)/platform
OUTPUTS_DIR ?= $(ROOT_DIR)
EXTENSION ?= Zicsr
TEST_NAME ?= ALL
LOG_LEVEL ?= LOG_INFO
PRINT_OFFSET ?= 100

ifeq ($(XLEN),64)
ISA ?= rv64imafdcvh_zicsr_zifencei_zicntr_zvl512b_zve64d_zba_zbb_zbc_zbs
ABI := lp64d
else
ISA ?= rv32imafdcv_zicsr_zifencei_zicntr_zba_zbb_zbc_zbs
ABI := ilp32
endif

SPIKE := $(CHV_VERIF_SHARED_DIR)/riscv-verif-tools/riscv-isa-sim/build/spike

# source and includes
SRC += main.c 
SRC += handlers.S
SRC += $(addprefix $(ROOT_DIR)/utils/, $(notdir $(wildcard $(ROOT_DIR)/utils/*.c)))
SRC += $(addprefix $(PLATFORM_DIR)/, $(notdir $(wildcard $(PLATFORM_DIR)/*.c)))
SRC += $(addprefix $(PLATFORM_DIR)/, $(notdir $(wildcard $(PLATFORM_DIR)/*.S)))
ifeq ($(TEST_NAME),ALL)
	SRC += $(addprefix $(PLATFORM_DIR)/$(EXTENSION)/, $(notdir $(wildcard $(PLATFORM_DIR)/$(EXTENSION)/*.c)))
	SRC += $(addprefix $(ROOT_DIR)/tests/$(EXTENSION)/, $(notdir $(wildcard $(ROOT_DIR)/tests/$(EXTENSION)/*.c)))
else
	SRC += $(addprefix $(PLATFORM_DIR)/$(EXTENSION)/, $(notdir $(wildcard $(PLATFORM_DIR)/$(EXTENSION)/init.c)))
	SRC += $(addprefix $(ROOT_DIR)/tests/$(EXTENSION)/, $(notdir $(wildcard $(ROOT_DIR)/tests/$(EXTENSION)/init.c)))
	SRC += $(addprefix $(PLATFORM_DIR)/$(EXTENSION)/, $(notdir $(wildcard $(PLATFORM_DIR)/$(EXTENSION)/$(TEST_NAME).c)))
	SRC += $(addprefix $(ROOT_DIR)/tests/$(EXTENSION)/, $(notdir $(wildcard $(ROOT_DIR)/tests/$(EXTENSION)/$(TEST_NAME).c)))
endif

LD_SCRIPT:=$(OUTPUTS_DIR)/$(EXTENSION).ld

INC_DIRS += $(ROOT_DIR)/include
INC_DIRS += $(PLATFORM_DIR)
INC_DIRS += $(ROOT_DIR)/tests/$(EXTENSION)

# build flags
INCFLAGS := $(addprefix -I, $(INC_DIRS))
CFLAGS := -march=$(ISA) -mabi=$(ABI) -mcmodel=medany -DLOG_LEVEL=$(LOG_LEVEL) -DPRINT_OFFSET=0x$(PRINT_OFFSET) -O0 -g
LDFLAGS := -ffreestanding -nostartfiles -static  -nostdlib -fno-builtin-sprintf -T$(LD_SCRIPT)

ifneq ($(TEST_NAME),ALL)
	CFLAGS += -DTEST_NAME=$(TEST_NAME)
endif

# targets
all: create_linker create_elf

create_linker:
	$(CC) $(INCFLAGS) -E -x assembler-with-cpp linker.ld | grep "^[^#;]" > $(OUTPUTS_DIR)/$(EXTENSION).ld

create_elf:
	$(CC) $(INCFLAGS) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(OUTPUTS_DIR)/$(EXTENSION).elf

spike: clean all
	$(SPIKE) --isa=$(ISA)_svnapot -m0x80000000:0x100000000 $(EXTENSION).elf

clean:
	rm -f $(EXTENSION).elf
	rm -f $(EXTENSION).ld


.PHONY: all spike clean create_linker create_elf
