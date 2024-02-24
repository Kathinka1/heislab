
EXECUTABLE  = elevator

COMPILER    = gcc #This used to be clang!
CFLAGS      = -Wall -g -std=gnu11 -fsanitize=address
LDFLAGS     = -fsanitize=address
EXCLUDE     = '*test*'


SOURCEDIR = source
OBJECTDIR = build

SOURCES := $(patsubst $(SOURCEDIR)/%, %, $(shell find $(SOURCEDIR) -name '*.c'  ! -name $(EXCLUDE)  ! -path $(EXCLUDE)))
OBJECTS = $(addprefix $(OBJECTDIR)/, $(SOURCES:.c=.o))

all: $(EXECUTABLE) 

rebuild: clean all
	
clean:
	rm -f $(EXECUTABLE)
	rm -rf $(OBJECTDIR)

debug: $(OBJECTS)
	@echo Compiling project with debug
	$(COMPILER) -std=gnu99 -ggdb -Og -g3 $^ -o $@ $(LDFLAGS)

## executable depends on object files: link them
$(EXECUTABLE): $(OBJECTS) 
	$(COMPILER) $^ -o $@ $(LDFLAGS)

## object files depend on source files: compile them
$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c
	@mkdir -p $(@D)
	$(COMPILER) -o $@ -c $(CFLAGS) $<

	
.PHONY: all rebuild clean

