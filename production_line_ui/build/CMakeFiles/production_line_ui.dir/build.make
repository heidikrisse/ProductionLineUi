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
include CMakeFiles/production_line_ui.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/production_line_ui.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/production_line_ui.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/production_line_ui.dir/flags.make

CMakeFiles/production_line_ui.dir/production_line_ui_autogen/mocs_compilation.cpp.o: CMakeFiles/production_line_ui.dir/flags.make
CMakeFiles/production_line_ui.dir/production_line_ui_autogen/mocs_compilation.cpp.o: production_line_ui_autogen/mocs_compilation.cpp
CMakeFiles/production_line_ui.dir/production_line_ui_autogen/mocs_compilation.cpp.o: CMakeFiles/production_line_ui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heidi/projects/ProductionLineUi/production_line_ui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/production_line_ui.dir/production_line_ui_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/production_line_ui.dir/production_line_ui_autogen/mocs_compilation.cpp.o -MF CMakeFiles/production_line_ui.dir/production_line_ui_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/production_line_ui.dir/production_line_ui_autogen/mocs_compilation.cpp.o -c /home/heidi/projects/ProductionLineUi/production_line_ui/build/production_line_ui_autogen/mocs_compilation.cpp

CMakeFiles/production_line_ui.dir/production_line_ui_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/production_line_ui.dir/production_line_ui_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heidi/projects/ProductionLineUi/production_line_ui/build/production_line_ui_autogen/mocs_compilation.cpp > CMakeFiles/production_line_ui.dir/production_line_ui_autogen/mocs_compilation.cpp.i

CMakeFiles/production_line_ui.dir/production_line_ui_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/production_line_ui.dir/production_line_ui_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heidi/projects/ProductionLineUi/production_line_ui/build/production_line_ui_autogen/mocs_compilation.cpp -o CMakeFiles/production_line_ui.dir/production_line_ui_autogen/mocs_compilation.cpp.s

CMakeFiles/production_line_ui.dir/main.cpp.o: CMakeFiles/production_line_ui.dir/flags.make
CMakeFiles/production_line_ui.dir/main.cpp.o: ../main.cpp
CMakeFiles/production_line_ui.dir/main.cpp.o: CMakeFiles/production_line_ui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heidi/projects/ProductionLineUi/production_line_ui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/production_line_ui.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/production_line_ui.dir/main.cpp.o -MF CMakeFiles/production_line_ui.dir/main.cpp.o.d -o CMakeFiles/production_line_ui.dir/main.cpp.o -c /home/heidi/projects/ProductionLineUi/production_line_ui/main.cpp

CMakeFiles/production_line_ui.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/production_line_ui.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heidi/projects/ProductionLineUi/production_line_ui/main.cpp > CMakeFiles/production_line_ui.dir/main.cpp.i

CMakeFiles/production_line_ui.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/production_line_ui.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heidi/projects/ProductionLineUi/production_line_ui/main.cpp -o CMakeFiles/production_line_ui.dir/main.cpp.s

CMakeFiles/production_line_ui.dir/src/mainwindow.cpp.o: CMakeFiles/production_line_ui.dir/flags.make
CMakeFiles/production_line_ui.dir/src/mainwindow.cpp.o: ../src/mainwindow.cpp
CMakeFiles/production_line_ui.dir/src/mainwindow.cpp.o: CMakeFiles/production_line_ui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heidi/projects/ProductionLineUi/production_line_ui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/production_line_ui.dir/src/mainwindow.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/production_line_ui.dir/src/mainwindow.cpp.o -MF CMakeFiles/production_line_ui.dir/src/mainwindow.cpp.o.d -o CMakeFiles/production_line_ui.dir/src/mainwindow.cpp.o -c /home/heidi/projects/ProductionLineUi/production_line_ui/src/mainwindow.cpp

CMakeFiles/production_line_ui.dir/src/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/production_line_ui.dir/src/mainwindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heidi/projects/ProductionLineUi/production_line_ui/src/mainwindow.cpp > CMakeFiles/production_line_ui.dir/src/mainwindow.cpp.i

CMakeFiles/production_line_ui.dir/src/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/production_line_ui.dir/src/mainwindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heidi/projects/ProductionLineUi/production_line_ui/src/mainwindow.cpp -o CMakeFiles/production_line_ui.dir/src/mainwindow.cpp.s

CMakeFiles/production_line_ui.dir/src/mqtt_client.cpp.o: CMakeFiles/production_line_ui.dir/flags.make
CMakeFiles/production_line_ui.dir/src/mqtt_client.cpp.o: ../src/mqtt_client.cpp
CMakeFiles/production_line_ui.dir/src/mqtt_client.cpp.o: CMakeFiles/production_line_ui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heidi/projects/ProductionLineUi/production_line_ui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/production_line_ui.dir/src/mqtt_client.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/production_line_ui.dir/src/mqtt_client.cpp.o -MF CMakeFiles/production_line_ui.dir/src/mqtt_client.cpp.o.d -o CMakeFiles/production_line_ui.dir/src/mqtt_client.cpp.o -c /home/heidi/projects/ProductionLineUi/production_line_ui/src/mqtt_client.cpp

CMakeFiles/production_line_ui.dir/src/mqtt_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/production_line_ui.dir/src/mqtt_client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heidi/projects/ProductionLineUi/production_line_ui/src/mqtt_client.cpp > CMakeFiles/production_line_ui.dir/src/mqtt_client.cpp.i

CMakeFiles/production_line_ui.dir/src/mqtt_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/production_line_ui.dir/src/mqtt_client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heidi/projects/ProductionLineUi/production_line_ui/src/mqtt_client.cpp -o CMakeFiles/production_line_ui.dir/src/mqtt_client.cpp.s

CMakeFiles/production_line_ui.dir/src/json_parser.cpp.o: CMakeFiles/production_line_ui.dir/flags.make
CMakeFiles/production_line_ui.dir/src/json_parser.cpp.o: ../src/json_parser.cpp
CMakeFiles/production_line_ui.dir/src/json_parser.cpp.o: CMakeFiles/production_line_ui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heidi/projects/ProductionLineUi/production_line_ui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/production_line_ui.dir/src/json_parser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/production_line_ui.dir/src/json_parser.cpp.o -MF CMakeFiles/production_line_ui.dir/src/json_parser.cpp.o.d -o CMakeFiles/production_line_ui.dir/src/json_parser.cpp.o -c /home/heidi/projects/ProductionLineUi/production_line_ui/src/json_parser.cpp

CMakeFiles/production_line_ui.dir/src/json_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/production_line_ui.dir/src/json_parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heidi/projects/ProductionLineUi/production_line_ui/src/json_parser.cpp > CMakeFiles/production_line_ui.dir/src/json_parser.cpp.i

CMakeFiles/production_line_ui.dir/src/json_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/production_line_ui.dir/src/json_parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heidi/projects/ProductionLineUi/production_line_ui/src/json_parser.cpp -o CMakeFiles/production_line_ui.dir/src/json_parser.cpp.s

CMakeFiles/production_line_ui.dir/unit_test/unit_tests.cpp.o: CMakeFiles/production_line_ui.dir/flags.make
CMakeFiles/production_line_ui.dir/unit_test/unit_tests.cpp.o: ../unit_test/unit_tests.cpp
CMakeFiles/production_line_ui.dir/unit_test/unit_tests.cpp.o: CMakeFiles/production_line_ui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heidi/projects/ProductionLineUi/production_line_ui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/production_line_ui.dir/unit_test/unit_tests.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/production_line_ui.dir/unit_test/unit_tests.cpp.o -MF CMakeFiles/production_line_ui.dir/unit_test/unit_tests.cpp.o.d -o CMakeFiles/production_line_ui.dir/unit_test/unit_tests.cpp.o -c /home/heidi/projects/ProductionLineUi/production_line_ui/unit_test/unit_tests.cpp

CMakeFiles/production_line_ui.dir/unit_test/unit_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/production_line_ui.dir/unit_test/unit_tests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heidi/projects/ProductionLineUi/production_line_ui/unit_test/unit_tests.cpp > CMakeFiles/production_line_ui.dir/unit_test/unit_tests.cpp.i

CMakeFiles/production_line_ui.dir/unit_test/unit_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/production_line_ui.dir/unit_test/unit_tests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heidi/projects/ProductionLineUi/production_line_ui/unit_test/unit_tests.cpp -o CMakeFiles/production_line_ui.dir/unit_test/unit_tests.cpp.s

# Object files for target production_line_ui
production_line_ui_OBJECTS = \
"CMakeFiles/production_line_ui.dir/production_line_ui_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/production_line_ui.dir/main.cpp.o" \
"CMakeFiles/production_line_ui.dir/src/mainwindow.cpp.o" \
"CMakeFiles/production_line_ui.dir/src/mqtt_client.cpp.o" \
"CMakeFiles/production_line_ui.dir/src/json_parser.cpp.o" \
"CMakeFiles/production_line_ui.dir/unit_test/unit_tests.cpp.o"

# External object files for target production_line_ui
production_line_ui_EXTERNAL_OBJECTS =

production_line_ui: CMakeFiles/production_line_ui.dir/production_line_ui_autogen/mocs_compilation.cpp.o
production_line_ui: CMakeFiles/production_line_ui.dir/main.cpp.o
production_line_ui: CMakeFiles/production_line_ui.dir/src/mainwindow.cpp.o
production_line_ui: CMakeFiles/production_line_ui.dir/src/mqtt_client.cpp.o
production_line_ui: CMakeFiles/production_line_ui.dir/src/json_parser.cpp.o
production_line_ui: CMakeFiles/production_line_ui.dir/unit_test/unit_tests.cpp.o
production_line_ui: CMakeFiles/production_line_ui.dir/build.make
production_line_ui: /usr/lib/x86_64-linux-gnu/libQt5Charts.so.5.15.3
production_line_ui: paho.mqtt.c/src/libpaho-mqtt3a.so.1.3.12
production_line_ui: paho.mqtt.cpp/src/libpaho-mqttpp3.so.1.2.0
production_line_ui: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
production_line_ui: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
production_line_ui: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
production_line_ui: /usr/local/lib/libpaho-mqtt3a.so
production_line_ui: CMakeFiles/production_line_ui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/heidi/projects/ProductionLineUi/production_line_ui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable production_line_ui"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/production_line_ui.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/production_line_ui.dir/build: production_line_ui
.PHONY : CMakeFiles/production_line_ui.dir/build

CMakeFiles/production_line_ui.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/production_line_ui.dir/cmake_clean.cmake
.PHONY : CMakeFiles/production_line_ui.dir/clean

CMakeFiles/production_line_ui.dir/depend:
	cd /home/heidi/projects/ProductionLineUi/production_line_ui/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/heidi/projects/ProductionLineUi/production_line_ui /home/heidi/projects/ProductionLineUi/production_line_ui /home/heidi/projects/ProductionLineUi/production_line_ui/build /home/heidi/projects/ProductionLineUi/production_line_ui/build /home/heidi/projects/ProductionLineUi/production_line_ui/build/CMakeFiles/production_line_ui.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/production_line_ui.dir/depend

