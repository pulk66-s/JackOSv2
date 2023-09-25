##
## MJackOS Project, main Makefile, compile all the source files
##
## @author: pulk66-s
## last update: 2023.09.20
##

# Includes
include mk/config.mk

# first rule: building everything
all: build_everything

# Build everything in the project
build_everything:
	@echo -e "${GREEN}Building everything${NC}"
	@make -C src
	@echo -e "${GREEN}Building everything done${NC}"

# Cleaning the whole project
clean:
	@echo -e "${GREEN}Cleaning everything${NC}"
	rm -rf $(BIN_DIR)/*
	@make -C src clean
	@echo -e "${GREEN}Cleaning everything done${NC}"

# Rebuilding the whole project
re: clean all

# Run the project with default software
run: run_qemu

# Run the project with qemu
run_qemu:
	$(QEMU) $(QEMU_FLAGS) $(KERNEL_IMG)
