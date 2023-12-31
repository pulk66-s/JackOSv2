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
				Heap/Heap.cpp \
				Heap/HeapObject.cpp \
				IDT/IDT.cpp \
				IDT/interrupts.cpp \
				IDT/Handler/ISRHandler.cpp \
				IDT/Handler/IRQHandler.cpp \
				IDT/Handler/handlers.cpp \
				PIC/PIC.cpp \
				GDT/GDT.cpp \
				keyboard/Keyboard.cpp \

ASM_SRC		=	GDT/load_gdt.s \
				IDT/interrupts.s \

## Project objects
CPP_OBJ		= $(CPP_SRC:.cpp=.cpp.o)
ASM_OBJ		= $(ASM_SRC:.s=.s.o)

## Error if no target is selected
all:
	@echo "${COLOR_RED}No target selected${NO_COLOR}"
	exit 1

__build_message:
	@echo "${COLOR_YELLOW}Building ${PROJECT_NAME} kernel...${NO_COLOR}"

## Build the whole kernel
build: __build_message build_cpp

## Build all .cpp files into .o files
build_cpp: $(CPP_OBJ) $(ASM_OBJ)

## Clean all .o files
clean:
	@echo "${COLOR_YELLOW}Cleaning ${PROJECT_NAME} kernel...${NO_COLOR}"
	@$(RM) $(CPP_OBJ)

## Build each .o file from its .cpp file
%.cpp.o: %.cpp
	@echo "${COLOR_GREEN}Building $<...${NO_COLOR}"
	$(CPP_CC) $(CPP_FLAGS) -c $< -o $@

## Build each .o file from its .s file
%.s.o: %.s
	@echo "${COLOR_GREEN}Building $<...${NO_COLOR}"
	$(ASM_CC) $(ASM_FLAGS) $< -o $@