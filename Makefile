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
AS:=$(PREFIX)as
OBJCOPY:=$(PREFIX)objcopy
STRIP:=$(PREFIX)strip
DEFINES=-DARM9

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
LIBS=-L$(LIBNDS)/lib -lnds9

# Collection of files
# $(wildcard $(SRCDIR)*.c) doesn't recurse
CFILES=$(shell find $(SRCDIR) -type f -iname "*.c")
RESFILES=$(shell find $(RESDIR) -type f -iname "*.png")
ASMFILES=$(patsubst $(RESDIR)%.png, $(SRCDIR)res/%.s, $(RESFILES))
OFILES=$(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(CFILES)) $(patsubst $(SRCDIR)res/%.s, $(OBJDIR)%.out, $(ASMFILES))

# Code generation options
# vvv Allows ARM and Thumb instruction sets together (v5 TE architecture on the NDS) vvv
ARMARCH=-mthumb -mthumb-interwork
CFLAGS:=-Wall -O2 -march=armv5te -mtune=arm946e-s $(ARMARCH) $(DEFINES) $(INCLUDES)
CXXFLAGS:=$(CFLAGS) -fno-rtti
LDFLAGS:=-specs=ds_arm9.specs $(ARMARCH)
ASFLAGS:=-march=armv5te -mcpu=arm946e-s $(ARMARCH)

# Make targets

all: clean nds

# Build .nds file from ELF binary
nds: link
	ndstool -c $(BUILDDIR)$(TARGET).nds -9 $(BUILDDIR)$(TARGET).elf -b icon.bmp "$(GAME_TITLE);$(GAME_SUBTITLE1);$(GAME_SUBTITLE2)" -g LCDT 2K $(GAME_TITLE)

# Linking
link: $(OFILES)
	$(CC) $(LDFLAGS) -o $(BUILDDIR)$(TARGET).elf $^ $(LIBS)

# Compile
$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Converting .png files to ASM with grit
$(SRCDIR)res/%.s: $(RESDIR)%.png
	grit $< -gb -gB16 -gT! -fts -fh -o$(basename $@)
	mv $(basename $@).h $(INCLDIR)res/

# Assembling (works only for resources at the moment)
$(OBJDIR)%.out: $(SRCDIR)res/%.s
	$(AS) $(ASFLAGS) -o $@ $<

# Cleanup build output
clean:
	rm -rf $(BUILDDIR)* $(OBJDIR)*