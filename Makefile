export PATH := $(DEVKITPRO)/tools/bin:$(DEVKITARM)/bin:$(PATH)

TARGET := lcdtest
SOURCE := $(wildcard src/*.c)
BUILD := build/
LIBDIR := /opt/devkitpro/libnds/lib
LIBS = -lnds9
PREFIX := arm-none-eabi-

DEFINITIONS = -DARM9
ARCH =

CC := $(PREFIX)gcc
CFLAGS=-specs=ds_arm9.specs -o $(TARGET).elf -O2 -Wall -std=c99
LDFLAGS=-mthumb -mthumb-interwork $(LIBS)

default: $(SOURCE)
	$(CC) $(CFLAGS)