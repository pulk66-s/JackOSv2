##
## This Makefile is used to compile all the project sources
##

## Include the configuration file
include ../config.mk

###############################
### NON UPDATABLE VARIABLES ###
###############################

## Boot sector directory
BOOT_DIR		:= ./boot/

## Kernel code directory
KERNEL_DIR 		:= ./kernel/

## GRUB variables
GRUB_FILE		:= grub2-file
GRUB_FILE_FLAGS	:= --is-x86-multiboot
GRUB_MKRESCUE	:= grub2-mkrescue

## Error if no target is selected
all:
	@echo "${COLOR_RED}No target selected${NO_COLOR}"
	exit 1

## Build the whole project
build: create_file_arch build_submakefiles linking
	$(if ifeq ($(shell ${GRUB_FILE} ${GRUB_FILE_FLAGS} ${BIN_NAME} && echo true), true) \
		, echo "${COLOR_GREEN}SUCCESS: ${BIN_NAME} is multiboot${NO_COLOR}"\
		,echo "${COLOR_RED}ERROR: ${BIN_NAME} is not multiboot${NO_COLOR}" && exit 1 \
	)
	cp ${GRUB_CFG} ${ISO_GRUB_FOLDER}/grub.cfg
	${GRUB_MKRESCUE} -o ${ISO_NAME} ${ISO_FOLDER}

## Create all the mandatory files for the architecture
create_file_arch:
	@echo "${COLOR_YELLOW}Creating all the mandatory files for the architecture...${NO_COLOR}"
	mkdir -p ${BIN_FOLDER} ${ISO_FOLDER} ${ISO_GRUB_FOLDER} ${ISO_BOOT_FOLDER}

## Linking all objects files
linking:
	@echo "${COLOR_YELLOW}Linking all objects files...${NO_COLOR}"
	# Grep all .o files in project
	$(eval OBJ := $(shell find . -type f -name '*.o'))
	@echo "ALL OBJ: ${OBJ}"
	${CPP_CC} ${CPP_LINKER_FLAGS} ${OBJ}

## Build all submakefiles
build_submakefiles:
	@echo "${COLOR_YELLOW}Building ${PROJECT_NAME} submakefiles...${NO_COLOR}"
	@$(MAKE) -C $(BOOT_DIR) build
	@$(MAKE) -C $(KERNEL_DIR) build

## Clean the whole project except the executable
clean:
	@echo "${COLOR_YELLOW}Cleaning ${PROJECT_NAME} sources...${NO_COLOR}"
	@$(MAKE) -C $(BOOT_DIR) clean
	@$(MAKE) -C $(KERNEL_DIR) clean

## Clean the whole project
fclean: clean
	@echo "${COLOR_YELLOW}Cleaning ${PROJECT_NAME} executable...${NO_COLOR}"
	${RM} -rf ${BIN_FOLDER}
