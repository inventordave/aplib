
ap: ap.c ap.h APlib.c APlib.h APlib-output.c APlib-output.h Dave_IEEE754.c Dave_IEEE754.h getOptions.h tests.c tests.h colorconsole libd

	gcc -Wall -mconsole -g ap.c tests.c APlib-output.c APlib.c Dave_IEEE754.c cc.o regexd.o   -o ap.exe

colorconsole: ansivt2.c ansivt2.h
	gcc -c ansivt2.c  -o cc.o
	
clean:
	rm -f *.o
	rm -f *.exe
	rm -f *stackdump
	rm -f *.gch



# Below is copied from Werner Stroop's wregex library Makefile. I've embedded the required components in this "APlib" repo for internal regex functionality. A full snapshot of his repo can be found as one of "my" public repositories at https://github.com/inventordave2/regex_w . Also, probably from Werner's own Github page.

CC=gcc
CFLAGS=-c -Wall
LDFLAGS=

# Add your source files here:
LIB_SOURCES=wrx_comp.c wrx_exec.c wrx_prnt.c wrx_free.c wrx_err.c
LIB_OBJECTS=$(LIB_SOURCES:.c=.o)


ifeq ($(BUILD),debug)
# Debug
CFLAGS += -O0 -g
LDFLAGS +=
LIB=regexd.o
ARFLAGS= r
else
# Release mode
CFLAGS += -O2 -DNDEBUG
LDFLAGS += -s
LIB=regex.o
ARFLAGS= rs
endif

lib: $(LIB)

libd:
	make BUILD=debug lib

$(LIB): $(LIB_OBJECTS)
	ar $(ARFLAGS) $@ $^

.c.o:
	$(CC) $(CFLAGS) $< -o $@

wrx_comp.o : wregex.h wrxcfg.h
wrx_exec.o : wregex.h wrxcfg.h	
wrx_prnt.o : wregex.h wrxcfg.h
wrx_free.o : wregex.h
wrx_err.o : wrxcfg.h

