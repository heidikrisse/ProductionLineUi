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
CMAKE_SOURCE_DIR = /home/heidi/projects/ProductionLineUi/production_line_ui

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/heidi/projects/ProductionLineUi/production_line_ui/build

# Include any dependencies generated for this target.
include paho.mqtt.c/test/CMakeFiles/test1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include paho.mqtt.c/test/CMakeFiles/test1.dir/compiler_depend.make

# Include the progress variables for this target.
include paho.mqtt.c/test/CMakeFiles/test1.dir/progress.make

# Include the compile flags for this target's objects.
include paho.mqtt.c/test/CMakeFiles/test1.dir/flags.make

paho.mqtt.c/test/CMakeFiles/test1.dir/test1.c.o: paho.mqtt.c/test/CMakeFiles/test1.dir/flags.make
paho.mqtt.c/test/CMakeFiles/test1.dir/test1.c.o: ../paho.mqtt.c/test/test1.c
paho.mqtt.c/test/CMakeFiles/test1.dir/test1.c.o: paho.mqtt.c/test/CMakeFiles/test1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heidi/projects/ProductionLineUi/production_line_ui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object paho.mqtt.c/test/CMakeFiles/test1.dir/test1.c.o"
	cd /home/heidi/projects/ProductionLineUi/production_line_ui/build/paho.mqtt.c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT paho.mqtt.c/test/CMakeFiles/test1.dir/test1.c.o -MF CMakeFiles/test1.dir/test1.c.o.d -o CMakeFiles/test1.dir/test1.c.o -c /home/heidi/projects/ProductionLineUi/production_line_ui/paho.mqtt.c/test/test1.c

paho.mqtt.c/test/CMakeFiles/test1.dir/test1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test1.dir/test1.c.i"
	cd /home/heidi/projects/ProductionLineUi/production_line_ui/build/paho.mqtt.c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/heidi/projects/ProductionLineUi/production_line_ui/paho.mqtt.c/test/test1.c > CMakeFiles/test1.dir/test1.c.i

paho.mqtt.c/test/CMakeFiles/test1.dir/test1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test1.dir/test1.c.s"
	cd /home/heidi/projects/ProductionLineUi/production_line_ui/build/paho.mqtt.c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/heidi/projects/ProductionLineUi/production_line_ui/paho.mqtt.c/test/test1.c -o CMakeFiles/test1.dir/test1.c.s

# Object files for target test1
test1_OBJECTS = \
"CMakeFiles/test1.dir/test1.c.o"

# External object files for target test1
test1_EXTERNAL_OBJECTS =

paho.mqtt.c/test/test1: paho.mqtt.c/test/CMakeFiles/test1.dir/test1.c.o
paho.mqtt.c/test/test1: paho.mqtt.c/test/CMakeFiles/test1.dir/build.make
paho.mqtt.c/test/test1: paho.mqtt.c/src/libpaho-mqtt3c.so.1.3.12
paho.mqtt.c/test/test1: paho.mqtt.c/test/CMakeFiles/test1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/heidi/projects/ProductionLineUi/production_line_ui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test1"
	cd /home/heidi/projects/ProductionLineUi/production_line_ui/build/paho.mqtt.c/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
paho.mqtt.c/test/CMakeFiles/test1.dir/build: paho.mqtt.c/test/test1
.PHONY : paho.mqtt.c/test/CMakeFiles/test1.dir/build

paho.mqtt.c/test/CMakeFiles/test1.dir/clean:
	cd /home/heidi/projects/ProductionLineUi/production_line_ui/build/paho.mqtt.c/test && $(CMAKE_COMMAND) -P CMakeFiles/test1.dir/cmake_clean.cmake
.PHONY : paho.mqtt.c/test/CMakeFiles/test1.dir/clean

paho.mqtt.c/test/CMakeFiles/test1.dir/depend:
	cd /home/heidi/projects/ProductionLineUi/production_line_ui/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/heidi/projects/ProductionLineUi/production_line_ui /home/heidi/projects/ProductionLineUi/production_line_ui/paho.mqtt.c/test /home/heidi/projects/ProductionLineUi/production_line_ui/build /home/heidi/projects/ProductionLineUi/production_line_ui/build/paho.mqtt.c/test /home/heidi/projects/ProductionLineUi/production_line_ui/build/paho.mqtt.c/test/CMakeFiles/test1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : paho.mqtt.c/test/CMakeFiles/test1.dir/depend
