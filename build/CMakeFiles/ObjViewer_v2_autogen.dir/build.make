# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/winfordt/ObjViewer_v2.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/winfordt/ObjViewer_v2.0/build

# Utility rule file for ObjViewer_v2_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/ObjViewer_v2_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ObjViewer_v2_autogen.dir/progress.make

CMakeFiles/ObjViewer_v2_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/winfordt/ObjViewer_v2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target ObjViewer_v2"
	/usr/bin/cmake -E cmake_autogen /home/winfordt/ObjViewer_v2.0/build/CMakeFiles/ObjViewer_v2_autogen.dir/AutogenInfo.json Debug

ObjViewer_v2_autogen: CMakeFiles/ObjViewer_v2_autogen
ObjViewer_v2_autogen: CMakeFiles/ObjViewer_v2_autogen.dir/build.make
.PHONY : ObjViewer_v2_autogen

# Rule to build all files generated by this target.
CMakeFiles/ObjViewer_v2_autogen.dir/build: ObjViewer_v2_autogen
.PHONY : CMakeFiles/ObjViewer_v2_autogen.dir/build

CMakeFiles/ObjViewer_v2_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ObjViewer_v2_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ObjViewer_v2_autogen.dir/clean

CMakeFiles/ObjViewer_v2_autogen.dir/depend:
	cd /home/winfordt/ObjViewer_v2.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/winfordt/ObjViewer_v2.0 /home/winfordt/ObjViewer_v2.0 /home/winfordt/ObjViewer_v2.0/build /home/winfordt/ObjViewer_v2.0/build /home/winfordt/ObjViewer_v2.0/build/CMakeFiles/ObjViewer_v2_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ObjViewer_v2_autogen.dir/depend
