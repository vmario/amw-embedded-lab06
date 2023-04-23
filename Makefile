.PHONY: clean build all program reset sizebefore sizeafter

MCU_TARGET_ATmega644P = atmega644p
MCU_TARGET_ATmega1284P = atmega1284p

FUSES_ATmega644P = -U hfuse:w:0xd9:m -U lfuse:w:0xe2:m -U efuse:w:0xff:m
FUSES_ATmega1284P = -U hfuse:w:0xd9:m -U lfuse:w:0xe2:m -U efuse:w:0xff:m

MCU_TARGET = ${MCU_TARGET_${CONFIGURATION}}
F_CPU = 8000000

USRBIN ?= C:/msys64/usr/bin/
TOOLCHAIN ?= C:/Bin/avr8-gnu-toolchain-win32_x86_64/bin/avr-
AVRDUDE ?= C:/Bin/avrdude-v7.1-windows-x64/avrdude

CC = $(TOOLCHAIN)gcc
CXX = $(TOOLCHAIN)g++
OBJCOPY = $(TOOLCHAIN)objcopy
SIZE = $(TOOLCHAIN)size
OBJDUMP = $(TOOLCHAIN)objdump
NM = $(TOOLCHAIN)nm
RM = $(USRBIN)rm -f
RMDIR = $(USRBIN)rm -rf
MKDIR = $(USRBIN)mkdir

FORMAT = ihex
MSG_SIZE_BEFORE = Size before:
MSG_SIZE_AFTER = Size after:

DEPDIR = dep
OBJDIR = obj
TARGETDIR = bin

INCLUDES = -I.
LIBS = -lm
CFLAGS = -mmcu=$(MCU_TARGET)
CFLAGS += -std=c99 -Wall -Wundef -Wextra -pedantic -Wstrict-prototypes
CFLAGS += -Os -flto
CFLAGS += -Wa,-adhlns=$(<:%.c=$(OBJDIR)/%.lst)
CFLAGS += -MD -MP -MF $(DEPDIR)/$(basename $(@F)).d
CXXFLAGS = -mmcu=$(MCU_TARGET)
CXXFLAGS += -std=c++14 -Wall -Wundef -Wextra -pedantic
CXXFLAGS += -Os -flto -fno-exceptions
CXXFLAGS += -Wa,-adhlns=$(<:%.cpp=$(OBJDIR)/%.lst)
CXXFLAGS += -MD -MP -MF $(DEPDIR)/$(basename $(@F)).d
LDFLAGS = -mmcu=$(MCU_TARGET)
LDFLAGS += -Os -flto
LDFLAGS += -Wl,-u,vfprintf -lprintf_flt -lm 
LDFLAGS += -Wl,-Map=$(TARGET).map,--cref
DEFS = -DF_CPU=$(F_CPU)ul

SRCS = $(wildcard *.cpp)
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.cpp=.o))
DEPS = $(addprefix $(DEPDIR)/,$(SRCS:.cpp=.d))
TARGET = $(TARGETDIR)/laboratory

all: sizebefore build sizeafter

build: $(TARGET).hex $(TARGET).lss $(TARGET).sym

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

$(TARGET).elf: $(OBJS) | $(TARGETDIR)
	$(CXX) $(LDFLAGS) $(LIBS) $(DEFS) -o $@ $(OBJS)

$(TARGET).lss: $(TARGET).elf
	$(OBJDUMP) -h -S $< > $@

$(TARGET).sym: $(TARGET).elf
	$(NM) -n $< > $@

$(OBJDIR)/%.o: %.c | $(OBJDIR) $(DEPDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFS) -o $@ -c $<

$(OBJDIR)/%.o: %.cpp | $(OBJDIR) $(DEPDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFS) -o $@ -c $<

$(TARGETDIR):
	$(MKDIR) $(TARGETDIR)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(DEPDIR):
	$(MKDIR) $(DEPDIR)

-include $(DEPS)

clean:
	$(RM) $(DEPS)
	$(RM) $(OBJS)
	$(RMDIR) $(OBJDIR)
	$(RM) $(DEPS)
	$(RMDIR) $(DEPDIR)
	$(RM) $(TARGET).map
	$(RM) $(TARGET).lss
	$(RM) $(TARGET).sym
	$(RM) $(TARGET).elf
	$(RM) $(TARGET).hex
	$(RMDIR) $(TARGETDIR)

program: all
	$(AVRDUDE) -c usbasp -p $(MCU_TARGET) ${FUSES_${CONFIGURATION}} -U flash:w:$(TARGET).hex:i

erase:
	$(AVRDUDE) -c usbasp -p $(MCU_TARGET) -e

reset:
	$(AVRDUDE) -c usbasp -p $(MCU_TARGET) -v

fuses:
	$(AVRDUDE) -c usbasp -p $(MCU_TARGET) ${FUSES_${CONFIGURATION}}

HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET).hex
ELFSIZE = $(SIZE) -A $(TARGET).elf
AVRMEM = avr-mem.sh $(TARGET).elf $(MCU)

sizebefore:
	@if test -f $(TARGET).elf; then echo; echo $(MSG_SIZE_BEFORE); $(ELFSIZE); \
	$(AVRMEM) 2>/dev/null; echo; fi

sizeafter:
	@if test -f $(TARGET).elf; then echo; echo $(MSG_SIZE_AFTER); $(ELFSIZE); \
	$(AVRMEM) 2>/dev/null; echo; fi
