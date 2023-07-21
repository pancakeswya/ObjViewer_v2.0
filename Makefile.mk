OS           := $(shell uname -s)

OPEN         := $(if $(filter Linux,$(OS)),xdg-open,open)

VALGRIND     := valgrind --tool=memcheck --trace-children=yes --track-origins=yes --leak-check=full

CP           := cp -rf
TAR          := tar cvzf
RM           := rm -rf

MAKEFLAGS    += --no-print-directory
