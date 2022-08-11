# nds-lcdtest makefile

TARGET=lcdtest

# Check for devkitARM and devkitPro env. variables
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitPro)
endif

# Local variables used in the rest of the file
PREFIX=arm-none-eabi-
CC:=$(PREFIX)gcc
CXX:=$(PREFIX)g++
OBJCOPY:=$(PREFIX)objcopy
STRIP:=$(PREFIX)strip

# NDS game file metadata
GAME_TITLE=lcdtest
GAME_SUBTITLE1=Test the NDS LCDs
GAME_SUBTITLE2=Made by @twokilohertz
GAME_ICON=res/icon.bmp

# Allow seeing compiler command lines with make V=1 (similar to autotools' silent)
ifeq ($(V),1)
    SILENTMSG := @true
    SILENTCMD :=
else
    SILENTMSG := @echo
    SILENTCMD := @
endif

# Library paths
LIBNDS:=$(DEVKITPRO)/libnds

# Project directory paths
BUILDDIR=build/
OBJDIR=obj/
SRCDIR=src/
INCLDIR=include/
RESDIR=res/

# Includes and links
INCLUDES:=-I$(LIBNDS)/include -I$(INCLDIR)
LINKS=-L$(LIBNDS)/lib -lnds9

# Collection of files
CFILES=$(wildcard $(SRCDIR)*.c)
OFILES=$(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(CFILES))
RESFILES=$(patsubst $(RESDIR)%.png, $(RESDIR)%.s, $(wildcard $(RESDIR)*.png))

# Code generation options
# vvv Allows ARM and Thumb instruction sets together (v5 TE architecture on the NDS) vvv
ARMARCH=-mthumb -mthumb-interwork
CFLAGS:=-Wall -O2 -march=armv5te -mtune=arm946e-s $(ARMARCH) $(INCLUDES)
CXXFLAGS:=$(CFLAGS) -fno-rtti
LDFLAGS:=-specs=ds_arm9.specs $(ARMARCH) $(LINKS)

# Make targets

all: clean nds

nds: $(TARGET)
	ndstool -c $(BUILDDIR)$(TARGET).nds -9 $(BUILDDIR)$(TARGET).elf -b res/icon_256_colour.bmp "$(GAME_TITLE);$(GAME_SUBTITLE1);$(GAME_SUBTITLE2)"

$(TARGET): $(OFILES)
	$(CC) $(LDFLAGS) $(OFILES) -o $(BUILDDIR)$@.elf

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)* $(OBJDIR)* $(RESDIR)*.s $(RESDIR)*.h

grit: $(RESFILES)

$(RESDIR)%.s: $(RESDIR)%.png
	grit $< -gb -gB16 -fts -o$@