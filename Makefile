PREFIX ?= $(shell pwd)/../prefix/$(CROSS:%-=%)
SOC?=linkit
NAME   :=app
TARGET :=arm-none-eabi
CROSS  :=$(TARGET)-
CPU    :=arm
INCLUDE:=-Iinclude -I$(PREFIX)/include $(SOC_INC) \
	-I$(PREFIX)/include/aws-iot
COPTS  ?=-march=armv7-a -mthumb
AARCH  :=$(shell echo $(COPTS) | sed -e 's/.*armv\([0-9]\).*/\1/g')
MOPTS  :=$(COPTS) \
	-DCFG_AARCH=$(AARCH) \
	-fno-builtin -fno-common \
	-ffunction-sections -fdata-sections -fshort-enums
CONFIG ?=
ASFLAGS:=$(MOPTS) $(CONFIG) -O2 -g -Wall -Werror -D __ASSEMBLY__
CFLAGS :=$(MOPTS) $(CONFIG) -O2 -g -Wall -Werror
LSCRIPT?=rom.ld
LDFLAGS:=$(MOPTS) -g -nostartfiles -nodefaultlibs \
	-L$(PREFIX)/lib -L$(PREFIX)/bin/$(SOC) -T$(LSCRIPT)	\
	-Wl,--start-group -lhcos -lc -lgcc $(SOC_LIB) \
	-lmbedcrypto -lmbedtls -lmbedx509 \
	-ljerrycore -ljerrylibm -laws-iot \
	-Wl,--end-group

MSCRIPT:=$(PREFIX)/share/mod.ld
LIB    :=lib$(NAME).a

ALL    :=
CLEAN  :=
CPU    :=arm

VPATH  :=src
VOBJ   :=$(patsubst %.S,%.o, \
		$(patsubst %.c,%.o, \
		$(patsubst %.cpp, %.o, \
			$(notdir $(foreach DIR,$(VPATH),\
				$(wildcard $(DIR)/*.S)	\
				$(wildcard $(DIR)/*.c) 	\
				$(wildcard $(DIR)/*.cpp))))))
default:all

include $(PREFIX)/share/Makefile.rule

ddd:$(F)
	ddd --debugger $(CROSS)gdb -x openocd.gdb $(F)
	
ddd-attach:
	echo "target remote 127.0.0.1:3333" > attach.gdb
	ddd --debugger $(CROSS)gdb -x attach.gdb $(F)

brd-dbg:
	openocd -f bin/$(SOC)/cmsis.cfg -s bin
	
brd-console:
	echo "pu port             /dev/ttyACM0" >~/.minirc.cdc
	echo "pu lock             /var/lock" >>~/.minirc.cdc
	echo "pu baudrate         $(BAUD)" >>~/.minirc.cdc
	echo "pu bits             8" >>~/.minirc.cdc
	echo "pu parity           N" >>~/.minirc.cdc
	echo "pu stopbits         1" >>~/.minirc.cdc
	minicom cdc
