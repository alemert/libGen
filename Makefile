################################################################################
# makefile for test util
################################################################################

MAKE_INCLUDE_PATH=mk.inc

# ------------------------------------------------------------------------------
# Compiler and BIT
# ------------------------------------------------------------------------------
CC=gcc
BIT = 64

# ------------------------------------------------------------------------------
# debugger
# ------------------------------------------------------------------------------
DBGOPT = -g -D__TDD__

# ------------------------------------------------------------------------------
# sources
# ------------------------------------------------------------------------------
SOURCES = file.c string.c fork.c

# ------------------------------------------------------------------------------
# main source
# ------------------------------------------------------------------------------
MAIN = 

# ------------------------------------------------------------------------------
# BINARY
# ------------------------------------------------------------------------------
BINARY = 

# ------------------------------------------------------------------------------
# libraries dynamic & static
# ------------------------------------------------------------------------------
LIBRARY = libsogen.so

ARCHIVE  = libsogen.a

# ------------------------------------------------------------------------------
# rollout includes
# ------------------------------------------------------------------------------
ROLLOUT_INC = genlib.h

# ------------------------------------------------------------------------------
# do not change includes
# ------------------------------------------------------------------------------
include $(MAKE_INCLUDE_PATH)/general.modules.mk

# ------------------------------------------------------------------------------
#
# ------------------------------------------------------------------------------

TEST = t_file_000 t_string_000 t_fork_000
include $(MAKE_INCLUDE_PATH)/test.mk


