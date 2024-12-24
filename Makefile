-include .config

ENGINE_NAME := fischi
SANDBOX_NAME := sandbox

SRC_DIR := src/engine
INCLUDE_DIR := include
LIB_DIR := lib
BUILD_DIR := build
OBJ_DIR := build/obj
DIST_DIR := build/dist
SANDBOX_SRC_DIR := src/sandbox

CC := gcc
CFLAGS := -Wall -Wextra -fPIC
CFLAGS += -I$(INCLUDE_DIR)
ifeq ($(CONFIG_DEBUG), y)
    CFLAGS += -g -O0
else
    CFLAGS += -O$(CONFIG_OPTIMIZATION_LEVEL)
endif

ifeq ($(CONFIG_ENABLE_WERROR), y)
    CFLAGS += -Werror
endif

CFLAGS += $(CONFIG_EXTRA_CFLAGS)

LDFLAGS := -shared
SANDBOX_LDFLAGS := -L$(BUILD_DIR)

SRC_EXT := c
OBJ_EXT := o
LIB_EXT := so

SRCS := $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJS := $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(OBJ_DIR)/%.$(OBJ_EXT), $(SRCS))
ENGINE_TARGET := $(BUILD_DIR)/lib$(ENGINE_NAME).$(LIB_EXT)
SANDBOX_SRCS := $(wildcard $(SANDBOX_SRC_DIR)/*.$(SRC_EXT))
SANDBOX_OBJS := $(patsubst $(SANDBOX_SRC_DIR)/%.$(SRC_EXT), $(OBJ_DIR)/%.$(OBJ_EXT), $(SANDBOX_SRCS))
SANDBOX_TARGET := $(BUILD_DIR)/$(SANDBOX_NAME)

KCONFIG_CONFIG := .config
KCONFIG_HEADER := $(INCLUDE_DIR)/config.h

.PHONY: all clean debug release dist sandbox menuconfig

all: $(ENGINE_TARGET) $(SANDBOX_TARGET)

menuconfig:
	kconfig-mconf Kconfig

conf:
	kconfig-mconf Kconfig

$(KCONFIG_CONFIG):
	@echo "Run 'make menuconfig' to generate configuration."

$(KCONFIG_HEADER): $(KCONFIG_CONFIG)
	kconfig-conf --header $(KCONFIG_HEADER) Kconfig

$(BUILD_DIR):
	@mkdir -p $@

$(INCLUDE_DIR):
	@mkdir -p $@

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ENGINE_TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

sandbox: $(SANDBOX_TARGET)

$(OBJ_DIR)/%.$(OBJ_EXT): $(SANDBOX_SRC_DIR)/%.$(SRC_EXT) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(SANDBOX_TARGET): $(SANDBOX_OBJS) $(ENGINE_TARGET)
	$(CC) $^ $(SANDBOX_LDFLAGS) -o $@

clean:
	@rm -rf $(BUILD_DIR) $(DIST_DIR) $(KCONFIG_CONFIG) $(KCONFIG_HEADER)
