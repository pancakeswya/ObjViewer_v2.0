OS           := $(shell uname -s)

NAME         := ObjViewer_v2

APP          := $(if $(filter Linux,$(OS)),$(NAME),$(NAME).app)

SRC_DIR      := src
INC_DIR      := includes
BUILD_DIR    := build
LIB_DIR      := src/libobj
DOCS_DIR     := docs
DVI_DIR      := manual
DVI_FILE     := manual.texi

OPEN         := $(if $(filter Linux,$(OS)),xdg-open,open)
ifeq ($(OS), Linux)
RUN          := ./$(BUILD_DIR)/$(APP)
else
RUN          := $(OPEN) $(BUILD_DIR)/$(APP)
endif

CP           := cp -rf
TAR          := tar cvzf
RM           := rm -rf

MAKEDVI      := makeinfo --html
BUILDER      := cmake

MAKEFLAGS    += --no-print-directory

all: install run

install:
	mkdir $(BUILD_DIR)
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
	find $(SRC_DIR) $(INC_DIR) -name '*.cc' -o -name '*.c' -o -name '*.h' | xargs clang-format -style=google -n

.PHONY: test gcov_report check-valgrind

test gcov_report check-valgrind:

clean: uninstall

fclean: clean
	$(RM) $(DOCS_DIR)/$(DVI_DIR)

rebuild:
	$(MAKE) clean
	$(MAKE) install
