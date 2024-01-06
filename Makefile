OS           := $(shell uname -s)

NAME         := ObjViewer_v2

SRC_DIR      := src
BUILD_DIR    := build
MODEL_DIR    := $(SRC_DIR)/model
DOCS_DIR     := docs
DVI_DIR      := manual
DVI_FILE     := manual.texi

ifeq ($(OS), Linux)
APP          := $(NAME)
OPEN         := xdg-open
RUN          := ./$(BUILD_DIR)/$(APP)
else
APP          := $(NAME).app
OPEN         := open
RUN          := $(OPEN) $(BUILD_DIR)/$(APP)
endif

LINT         := clang-format
LINT_CONF    := .clang-format
LINT_DIR     := materials/linters

CP           := cp -rf
TAR          := tar cvzf
RM           := rm -rf

MAKEDVI      := makeinfo --html
BUILDER      := cmake

MAKEFLAGS    += --no-print-directory

all: install run

install:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(BUILDER) .. && $(MAKE)

uninstall:
	$(RM) $(BUILD_DIR)

run:
	$(RUN)

dvi:
	$(MAKEDVI) $(DOCS_DIR)/$(DVI_FILE)
	mv $(DVI_DIR) $(DOCS_DIR)
	$(OPEN) $(DOCS_DIR)/$(DVI_DIR)/index.html

dist:
	mkdir ../$(NAME)
	$(CP) * ../$(NAME)
	mv ../$(NAME) .
	$(TAR) $(NAME).tgz $(NAME)
	mv $(NAME).tgz $(HOME)/Desktop

check-style:
	$(CP) $(LINT_DIR)/$(LINT_CONF) .
	find $(SRC_DIR) -name '*.cc' -o -name '*.c' -o -name '*.h' | xargs clang-format -style=google -n
	$(RM) $(LINT_CONF)

test gcov_report check-valgrind:
	mkdir -p $(MODEL_DIR)/$(BUILD_DIR)
	cd $(MODEL_DIR)/$(BUILD_DIR) && $(BUILDER) .. && $(MAKE) $@

.PHONY: test gcov_report check-valgrind

clean: uninstall
	$(RM) $(MODEL_DIR)/$(BUILD_DIR)

fclean: clean
	$(RM) $(DOCS_DIR)/$(DVI_DIR)

rebuild:
	$(MAKE) clean
	$(MAKE) install
