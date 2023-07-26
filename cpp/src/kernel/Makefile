##
## Makefile for all kernel stuff
##

## Include the configuration file
include ./../../config.mk

## Kernel source files
SRC			:=	./main.cpp

## Kernel ASM source files
ASM_SRC		:=

## Kernel object files
OBJ			:=	$(SRC:.cpp=.cpp.o) $(ASM_SRC:.s=.s.o)

## Kernel ELF file
KERNEL_ELF	:=	../../bin/$(KERNEL_ELF_NAME)
KERNEL_BIN	:=	../../bin/$(KERNEL_BIN_NAME)

all: build

# Build the kernel
build: __build_message $(OBJ)
	$(LD) -Ttext 0x1000 $(OBJ) -o $(KERNEL_ELF)
	objcopy -O binary $(KERNEL_ELF) $(KERNEL_BIN)

__build_message:
	@echo -e "$(GREEN)Building the kernel...$(NC)"

# Clean the kernel
clean:
	@echo -e "$(GREEN)Cleaning the kernel...$(NC)"
	@$(RM) $(OBJ)

# Full Clean the kernel
fclean: clean

# Rebuild the kernel
re: fclean build

# Compile the cpp sources
%.cpp.o: %.cpp
	@echo -e "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CC_FLAGS) -c $< -o $@

# Compile the asm sources
%.s.o: %.s
	@echo -e "$(YELLOW)Compiling $<...$(NC)"
	@$(AS) $(AS_FLAGS) $< -o $@
