CC=gcc
AR=ar
CPPFLAGS= -Wall -O3
LDFLAGS=
LIBS=

GETOPTH_OBJS=getopth.o
GETOPTH_HEADERS=getopth.h
EXAMPLE_OBJS=examples/example.o
GETOPTH=getopth.a

libs:$(GETOPTH)

all: $(GETOPTH) example

$(GETOPTH):$(GETOPTH_OBJS)
	$(AR) -rc $@ $(GETOPTH_OBJS)

example: $(EXAMPLE_OBJS) $(GETOPTH)
	$(LINK.c) $^ -o $@

$(GETOPTH_OBJS):$(GETOPTH_HEADERS)

clean:
	rm *.o *.a examples/*.o example
