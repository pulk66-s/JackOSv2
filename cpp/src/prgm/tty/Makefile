##
## This program is used to build the tty program
##

## Include the configuration file
include ../../../config.mk

## All tty sources files
CPP_SRC		=	./TTY.cpp

## All objects needed
CPP_OBJ		=	$(CPP_SRC:.cpp=.o)

## Error if no target is selected
all:
	@echo "${COLOR_RED}No target selected${NO_COLOR}"
	exit 1

## Build the whole project
build: $(CPP_OBJ)

## Clean the whole project
clean:
	@echo "${COLOR_YELLOW}Cleaning ${PROJECT_NAME} tty...${NO_COLOR}"
	$(RM) $(CPP_OBJ)

%.o: %.cpp:
	@echo "${COLOR_GREEN}Building ${PROJECT_NAME} tty...${NO_COLOR}"
	$(CPP) $(CPPFLAGS) -c $< -o $@
