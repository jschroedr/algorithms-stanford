## -*- Makefile -*-
##
## User: jake
## Time: Aug 15, 2020 4:43:24 PM
## Makefile created by Oracle Developer Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = gcc
BASICOPTS = -g
CFLAGS = $(BASICOPTS)


# Define the target directories.
TARGETDIR_sortandcount=dist/Debug/GNU-Linux


all: $(TARGETDIR_sortandcount)/sortandcount

## Target: sortandcount
OBJS_sortandcount =  \
	$(TARGETDIR_sortandcount)/inversion.o \
	$(TARGETDIR_sortandcount)/main.o
USERLIBS_sortandcount = -lgmp $(SYSLIBS_sortandcount) 
DEPLIBS_sortandcount =  
LDLIBS_sortandcount = $(USERLIBS_sortandcount)


# Link or archive
$(TARGETDIR_sortandcount)/sortandcount: $(TARGETDIR_sortandcount) $(OBJS_sortandcount) $(DEPLIBS_sortandcount)
	$(LINK.c) $(CFLAGS_sortandcount) $(CPPFLAGS_sortandcount) -o $@ $(OBJS_sortandcount) $(LDLIBS_sortandcount)


# Compile source files into .o files
$(TARGETDIR_sortandcount)/inversion.o: $(TARGETDIR_sortandcount) inversion.c
	$(COMPILE.c) $(CFLAGS_sortandcount) $(CPPFLAGS_sortandcount) -o $@ inversion.c

$(TARGETDIR_sortandcount)/main.o: $(TARGETDIR_sortandcount) main.c
	$(COMPILE.c) $(CFLAGS_sortandcount) $(CPPFLAGS_sortandcount) -o $@ main.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_sortandcount)/sortandcount \
		$(TARGETDIR_sortandcount)/inversion.o \
		$(TARGETDIR_sortandcount)/main.o
	rm -f -r $(TARGETDIR_sortandcount)


# Create the target directory (if needed)
$(TARGETDIR_sortandcount):
	mkdir -p $(TARGETDIR_sortandcount)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux

