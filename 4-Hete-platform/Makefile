SYSTEMC_AMS=$$SCAMS_HOME
SYSTEMC=$$SYSTEMC_HOME

PLATFORM= $(shell uname -s)
ARCH=$(shell getconf LONG_BIT)

ifeq ($(PLATFORM),Darwin)
SYSC_LIBDIR := $(SYSTEMC)/lib-macosx
SCAMS_LIBDIR := $(SYSTEMC_AMS)/lib-macosx
endif
ifeq ($(PLATFORM),Linux)
SYSC_LIBDIR := $(SYSTEMC)/lib-linux
SCAMS_LIBDIR := $(SYSTEMC_AMS)/lib-linux
endif

ifeq ($(ARCH),64)
SYSC_LIBDIR := $(SYSC_LIBDIR)64
SCAMS_LIBDIR := $(SCAMS_LIBDIR)64
endif

LIBS = $(SCAMS_LIBDIR)/libsystemc-ams.a \
	   $(SYSC_LIBDIR)/libsystemc.a \
	   -lpthread

INCDIR = -I./include/ -I. -I$(SYSTEMC)/include/ -I$(SYSTEMC_AMS)/include

CXX=g++
CFLAGS= -c
LD=g++

EXECUTABLE=./bin/xtea.x

all: $(EXECUTABLE)


$(EXECUTABLE): obj/main.o obj/valvola.o obj/serbatoio.o obj/controller.o obj/serbatoioTLM.o obj/valvola_i.o obj/valvolaTLM.o obj/xtea_RTL.o obj/xtea_RTL_transactor.o
	@ $(LD) -o $@ $(INCDIR) $^ $(LIBS)

obj/serbatoio.o: src/serbatoio.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/main.o: src/main.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/valvola.o: src/valvola.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/controller.o: src/xtea_LT_testbench.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/serbatoioTLM.o: src/serbatoio_TLM.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/valvola_i.o: src/valvola_i.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/valvolaTLM.o: src/valvola_tlm.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/xtea_RTL.o: src/xtea_RTL.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/xtea_RTL_transactor.o: src/xtea_RTL_transactor.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

clean:
		@echo Cleaning
		@rm -f obj/*.o *~
		@rm -f *.vcd
		@rm -f $(EXECUTABLE)

.PHONY: all clean
