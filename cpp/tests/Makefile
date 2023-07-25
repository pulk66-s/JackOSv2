##
## This Makefile is used to build the tests
## It is called by the global Makefile
##

## Include configuration file
include ../config.mk

## Test Executable
## Home Made Tester
TESTER		:=	CppTester

## Tests Sources
TESTS_SRC	:=	./boot_sector/bootSignature.cpp

## By default we are building the tests
all: __build_message  __tests_file_arch
	$(TESTER) $(TESTS_SRC)

__tests_file_arch:
	mkdir -p ./bin
	cp ../bin/$(BOOT_BIN_NAME) ./bin/

__build_message:
	@echo "$(GREEN)Building the tests...$(NC)"