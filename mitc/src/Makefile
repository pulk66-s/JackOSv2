##
## This Makefile compile the sources of the MIT C version of Jackos
## The Sources are all the sources code of the MIT C version of Jackos
##

## Include the configuration file
include ../config.mk

## All the existing dirs
DIRS			:= 

## Kernel LD Flags
KERN_LD_FLAGS	:= $(LD_FLAGS) -T $(KERNEL_LINKER)

## Include the submakefiles
include boot/Makefrag
include kernel/Makefrag

## All the existing dirs replacing src/ in each line with obj/
DIRS			:= $(subst $(SRC_DIR),$(OBJ_DIR),$(DIRS))

## By default it build the kernel
all: build

## Building the project
build: __build_message build_file_arch $(KERNEL_IMG)

## Building the file architecture
build_file_arch:
	@echo -e "$(GREEN)Building File Architecture...$(NC)"
	@for folder in $(GENERATED_FOLDERS); do \
		mkdir -p $$folder; \
	done
	echo "DIRS: $(DIRS)"
	@for folder in $(DIRS); do \
		mkdir -p $$folder; \
	done

## Building submodules
submodules:
	@for submodule in $(SUBMODULES); do \
		$(MAKE) -C $$submodule build; \
	done

__build_message:
	@echo -e "$(GREEN)Building $(OS_NAME) Sources...$(NC)"
	echo "BOOT OBJ $(BOOT_DIR)/.s.o"
	echo "ASM SRC $(ASM_SOURCES)"

## Cleaning the project
clean:
	@echo -e "$(GREEN)Cleaning $(OS_NAME) Sources...$(NC)"
	@for folder in $(GENERATED_FOLDERS); do \
		$(RM) -rf $$folder; \
	done

## Building sources
fclean: clean
	@echo -e "$(GREEN)Full Cleaning $(OS_NAME) Sources...$(NC)"

## Rebuilding sources
re: fclean build

## Creating the kernel image
$(KERNEL_IMG): $(BOOT_BIN)
	@echo -e "$(GREEN)Building $(OS_NAME) Image...$(NC)"
	@dd if=/dev/zero of=$(KERNEL_IMG)~ count=10000 2> /dev/null
	@dd if=$(BOOT_BIN) of=$(KERNEL_IMG)~ conv=notrunc 2> /dev/null
	@mv $(KERNEL_IMG)~ $(KERNEL_IMG)