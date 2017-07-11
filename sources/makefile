CROSS_COMPILE := aarch64-linux-android-
CC            := $(CROSS_COMPILE)gcc
CPPC          := $(CROSS_COMPILE)g++
LD            := $(CROSS_COMPILE)gcc
ARCH          := arm64

SYSROOT       := $(NDK_PATH)/platforms/android-21/arch-arm64
CFLAGS        := -std=c99 -O2 -Wall -fPIE
LDFLAGS       := -fPIE -pie -ldl
SYS_CFLAGS    += --sysroot=$(SYSROOT)
SYS_LDFLAGS   += --sysroot=$(SYSROOT)
SYSINCLUDE    := $(SYSROOT)/usr/include/
INCLUDE       += $(LIBUSB_PATH)

Progs         := main.c usbwrapper.c
OUT           := out
OBJDIR        := objs
OBJs          :=  $(addprefix $(OBJDIR)/, $(notdir $(Progs:.c=.o)))
VPATH         := $(Progs)

ifeq ($(LIBUSB_PATH),)
$(error Please setup LIBUSB_PATH)
else
$(info Found libusb at $(LIBUSB_PATH))
endif

$(shell mkdir -p $(OUT))
$(shell mkdir -p $(OBJDIR))

.PHONY : clean all

all: main

$(OBJs) : $(OBJDIR)/%.o : %.c
	$(info Compiling $(<F))
	@$(CC) -c $(CFLAGS) -I $(INCLUDE) -I $(SYSINCLUDE) $< -o $@ $(SYS_CFLAGS)

main: $(OBJs)
	@$(CC) -o $(OUT)/$@ $^ $(LDFLAGS) $(SYS_LDFLAGS)
	$(info Generated.)

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(OUT)
	$(info Cleanup has been done.)
