##
## This Mafile contains every variable that can be updated
## to fit your needs.
##

###########################
### UPDATABLE VARIABLES ###
###########################

# Echo color
export COLOR_RED 		:= $$(printf '\033[0;31m')
export COLOR_GREEN 		:= $$(printf '\033[0;32m')
export COLOR_YELLOW		:= $$(printf '\033[0;33m')
export NO_COLOR			:= $$(printf '\033[0m')

## Names information

# ISO folder for GRUB
export ISO_FOLDER		:= ${BIN_FOLDER}/isodir
export ISO_BOOT_FOLDER	:= ${ISO_FOLDER}/boot
export ISO_GRUB_FOLDER	:= ${ISO_BOOT_FOLDER}/grub

# Other
export PROJECT_FOLDER	:= ${HOME}/Perso/JackOS
export PROJECT_NAME		:= JackOS
export BIN_FOLDER		:= ${PROJECT_FOLDER}/cpp/bin
export ISO_NAME			:= ${BIN_FOLDER}/${PROJECT_NAME}.iso
export BIN_NAME			:= ${ISO_BOOT_FOLDER}/${PROJECT_NAME}.bin
export LINKER_FILE		:= ${PROJECT_FOLDER}/cpp/src/linker.ld
export GRUB_CFG			:= ${PROJECT_FOLDER}/cpp/src/grub.cfg

# All your cross compiler binaries
export BIN_DIR			:= ${HOME}/opt/cross/bin

# ASM Cross Compiler
export ASM_CC 			:= ${BIN_DIR}/i686-elf-as
export ASM_FLAGS 		:=

# C++ Cross Compiler
export CPP_CC 			:= ${BIN_DIR}/i686-elf-g++
export CPP_FLAGS		:= -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
export CPP_LINKER_FLAGS	:= -T $(LINKER_FILE) -o ${BIN_NAME} -ffreestanding -O2 -nostdlib -lgcc

## Run executable
export QEMU				:= qemu-system-i386
export QEMU_FLAGS		:= -accel tcg,thread=single	\
	-cpu core2duo                                  	\
	-m 128                                         	\
	-no-reboot                                     	\
	-drive format=raw,media=cdrom,file=${ISO_NAME}	\
	-serial stdio                                  	\
	-smp 1                                         	\
	-usb                                           	\
	-vga std
