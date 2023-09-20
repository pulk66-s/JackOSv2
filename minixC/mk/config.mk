##
## Makefile configuration file
## It contains everything that can be modified by the user
##
## @author: pulk66-s
## last update: 2023.09.20
##

# Must not be changed by the user
RELATIVE_ROOT_PATH	?=	.

# The name of the project
PROJECT_NAME		:= 	MJackOS

# The name of the output file
OUTPUT_NAME 		:= 	$(PROJECT_NAME)

# The path of all generated binaries
BIN_FOLDER			:=	$(RELATIVE_ROOT_PATH)/bin

#########################
## Makefile log colors ##
#########################

NC		:=	\033[0m
RED		:=	\033[0;31m
GREEN	:=	\033[0;32m
YELLOW	:=	\033[0;33m
