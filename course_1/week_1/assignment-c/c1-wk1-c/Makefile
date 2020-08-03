## -*- Makefile -*-
##
## User: jake
## Time: Aug 2, 2020 5:18:33 PM
## Makefile created by Oracle Developer Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = gcc
BASICOPTS = -g
CFLAGS = $(BASICOPTS)


# Define the target directories.
TARGETDIR_c1-wk1-appliction-c=GNU-amd64-Linux


all: $(TARGETDIR_c1-wk1-appliction-c)/c1-wk1-appliction-c

## Target: c1-wk1-appliction-c
OBJS_c1-wk1-appliction-c =  \
	$(TARGETDIR_c1-wk1-appliction-c)/multiply.o \
	$(TARGETDIR_c1-wk1-appliction-c)/main.o
SYSLIBS_c1-wk1-appliction-c = -lm 
USERLIBS_c1-wk1-appliction-c = -lgmp $(SYSLIBS_c1-wk1-appliction-c) 
DEPLIBS_c1-wk1-appliction-c =   
LDLIBS_c1-wk1-appliction-c = $(USERLIBS_c1-wk1-appliction-c)


# Link or archive
$(TARGETDIR_c1-wk1-appliction-c)/c1-wk1-appliction-c: $(TARGETDIR_c1-wk1-appliction-c) $(OBJS_c1-wk1-appliction-c) $(DEPLIBS_c1-wk1-appliction-c)
	$(LINK.c) $(CFLAGS_c1-wk1-appliction-c) $(CPPFLAGS_c1-wk1-appliction-c) -o $@ $(OBJS_c1-wk1-appliction-c) $(LDLIBS_c1-wk1-appliction-c)


# Compile source files into .o files
$(TARGETDIR_c1-wk1-appliction-c)/multiply.o: $(TARGETDIR_c1-wk1-appliction-c) multiply.c
	$(COMPILE.c) $(CFLAGS_c1-wk1-appliction-c) $(CPPFLAGS_c1-wk1-appliction-c) -o $@ multiply.c

$(TARGETDIR_c1-wk1-appliction-c)/main.o: $(TARGETDIR_c1-wk1-appliction-c) main.c
	$(COMPILE.c) $(CFLAGS_c1-wk1-appliction-c) $(CPPFLAGS_c1-wk1-appliction-c) -o $@ main.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_c1-wk1-appliction-c)/c1-wk1-appliction-c \
		$(TARGETDIR_c1-wk1-appliction-c)/multiply.o \
		$(TARGETDIR_c1-wk1-appliction-c)/main.o
	rm -f -r $(TARGETDIR_c1-wk1-appliction-c)


# Create the target directory (if needed)
$(TARGETDIR_c1-wk1-appliction-c):
	mkdir -p $(TARGETDIR_c1-wk1-appliction-c)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux

