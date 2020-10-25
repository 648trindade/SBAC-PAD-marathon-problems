EXEFILE   = mdf
CPUCC     = gcc
CPPFLAGS  = -std=c11 -m64 -O3
DEFS      =
INCLUDES  =
LIBDIR    =
LIBS     =  -lm
LINK     =  $(LIBDIR) $(LIBS)

CPU_COMPILE = $(CPUCC) $(DEFS) $(INCLUDES) $(CPPFLAGS)


all: mdf

	$(CPU_COMPILE)	mdf.o $(LINK) -o $(EXEFILE) $(PAPILIBS)

mdf:
	$(CPU_COMPILE) -c mdf.c


clean:
	rm *.o mdf
