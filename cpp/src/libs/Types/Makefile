##
## This Makefile compile the Types Library which is a library of types
## used in the project.
##

# Include the configuration file
include ../../../config.mk

## Types sources
CPP_SRC		:= String.cpp

## Types objects
CPP_OBJ		:= $(CPP_SRC:.cpp=.o)

## Error if no target is specified
all:
	@echo "${COLOR_RED}Error: No target specified on libs Makefile${NO_COLOR}"

## Build the Types library
build: ${CPP_OBJ}
	@echo "${COLOR_YELLOW}Building Types library...${NO_COLOR}"

## Clean the Types library
clean:
	@echo "${COLOR_YELLOW}Cleaning Types library...${NO_COLOR}"

## Compile all the sources
%.o: %.cpp
	@echo "${COLOR_GREEN}Compiling $<...${NO_COLOR}"
	${CPP_CC} ${CPP_FLAGS} -c $< -o $@
