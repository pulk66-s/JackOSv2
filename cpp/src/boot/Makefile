##
## Makefile building the boot submodule
##

## Include configuration file
include ./../../config.mk

## Boot ASM Sources
ASM_SRC		:=	./boot_sector.s

## Boot objects
OBJ			:=	$(ASM_SRC:.s=.s.o)

## Boot target
BOOT_BIN	:=	../../bin/$(BOOT_BIN_NAME)
BOOT_ELF	:=	../../bin/$(BOOT_ELF_NAME)

## Raise error when no target selected
all:
	@echo -e "$(RED)Error, no target selected in ./src/boot$(NC)"
	exit 1

# Build the application
build: __build_message $(OBJ)
	@echo -e "$(GREEN)Linking the boot system$(NC)"
	$(LD) $(LD_FLAGS) $(OBJ) -o $(BOOT_ELF)
	objcopy -O binary $(BOOT_ELF) $(BOOT_BIN)

__build_message:
	@echo -e "$(GREEN)Building the boot system$(NC)"

# Cleaning all the object file
clean:
	@echo -e "$(GREEN)Cleaning the boot system$(NC)"
	$(RM) $(OBJ)

# Cleaning the application and the binary
fclean: clean
	@echo -e "$(GREEN)Full Cleaning the boot system$(NC)"
	$(RM) $(BOOT_BIN)

re: fclean build

# Compile the .s file to .s.o
%.s.o: %.s
	@echo -e "$(GREEN)Compiling $<$(NC)"
	$(AS) $(AS_FLAGS) $< -o $@