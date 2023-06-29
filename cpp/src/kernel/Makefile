##
## KERNEL Makefile compilation
## This Makefile is used to compile the kernel
##

## Include the configuration file
include ../../config.mk

## Project sources

###############################
### NON UPDATABLE VARIABLES ###
###############################

CPP_SRC		= 	Kernel.cpp \
				main.cpp \
				VGA/VGA.cpp \

## Project objects
CPP_OBJ		= $(CPP_SRC:.cpp=.o)

## Error if no target is selected
all:
	@echo "${COLOR_RED}No target selected${NO_COLOR}"
	exit 1

__build_message:
	@echo "${COLOR_YELLOW}Building ${PROJECT_NAME} kernel...${NO_COLOR}"

## Build the whole kernel
build: __build_message build_cpp

## Build all .cpp files into .o files
build_cpp: $(CPP_OBJ)

## Clean all .o files
clean:
	@echo "${COLOR_YELLOW}Cleaning ${PROJECT_NAME} kernel...${NO_COLOR}"
	@$(RM) $(CPP_OBJ)

## Build each .o file from its .cpp file
%.o: %.cpp
	@echo "${COLOR_GREEN}Building $<...${NO_COLOR}"
	$(CPP_CC) $(CPP_FLAGS) -c $< -o $@
