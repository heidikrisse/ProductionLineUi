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

# Utility rule file for unit_tests_autogen.

# Include any custom commands dependencies for this target.
include unit_test/CMakeFiles/unit_tests_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include unit_test/CMakeFiles/unit_tests_autogen.dir/progress.make

unit_test/CMakeFiles/unit_tests_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/heidi/projects/ProductionLineUi/production_line_ui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target unit_tests"
	cd /home/heidi/projects/ProductionLineUi/production_line_ui/build/unit_test && /usr/bin/cmake -E cmake_autogen /home/heidi/projects/ProductionLineUi/production_line_ui/build/unit_test/CMakeFiles/unit_tests_autogen.dir/AutogenInfo.json ""

unit_tests_autogen: unit_test/CMakeFiles/unit_tests_autogen
unit_tests_autogen: unit_test/CMakeFiles/unit_tests_autogen.dir/build.make
.PHONY : unit_tests_autogen

# Rule to build all files generated by this target.
unit_test/CMakeFiles/unit_tests_autogen.dir/build: unit_tests_autogen
.PHONY : unit_test/CMakeFiles/unit_tests_autogen.dir/build

unit_test/CMakeFiles/unit_tests_autogen.dir/clean:
	cd /home/heidi/projects/ProductionLineUi/production_line_ui/build/unit_test && $(CMAKE_COMMAND) -P CMakeFiles/unit_tests_autogen.dir/cmake_clean.cmake
.PHONY : unit_test/CMakeFiles/unit_tests_autogen.dir/clean

unit_test/CMakeFiles/unit_tests_autogen.dir/depend:
	cd /home/heidi/projects/ProductionLineUi/production_line_ui/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/heidi/projects/ProductionLineUi/production_line_ui /home/heidi/projects/ProductionLineUi/production_line_ui/unit_test /home/heidi/projects/ProductionLineUi/production_line_ui/build /home/heidi/projects/ProductionLineUi/production_line_ui/build/unit_test /home/heidi/projects/ProductionLineUi/production_line_ui/build/unit_test/CMakeFiles/unit_tests_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unit_test/CMakeFiles/unit_tests_autogen.dir/depend

