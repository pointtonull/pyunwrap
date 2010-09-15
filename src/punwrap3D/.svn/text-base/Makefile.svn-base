CC = gcc #-4.2
DEBUG = -g
CFLAGS = -Wall -funroll-loops -O1 $(DEBUG)
UNAME = $(shell uname)
ifeq "$(UNAME)" "Darwin"
	CFLAGS += -DDARWIN
endif
AR=ar
RANLIB=ranlib

CLEANUPS = $(shell find . -maxdepth 1 -name "*.o")
CLEANUPS += $(shell find . -maxdepth 1 -name "*~")
CLEANALLS = $(CLEANUPS) $(shell find . -maxdepth 1 -name "libunwrap3D.a")

SRCS=$(shell find . -maxdepth 1 -name "*.c" -and -not -name "unwrap_phase.c")
SRCS -= ./unwrap_phase.c
OBJS=$(SRCS:.c=.o)

all: libunwrap3D.a

$(OBJS): 
	@echo $(SRCS)
	$(CC) $(CFLAGS) -c $*.c

libunwrap3D.a: $(OBJS)
	$(AR) -rvu $@ $(OBJS)
	$(RANLIB) $@

clean:
	@echo $(CLEANUPS)
ifneq ($(strip $(CLEANUPS)),)
	\rm $(CLEANUPS)
endif

cleanall:
ifneq ($(strip $(CLEANALLS)),)
	\rm $(CLEANALLS)
endif