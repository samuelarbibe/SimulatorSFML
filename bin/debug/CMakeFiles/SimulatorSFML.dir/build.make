# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/samuelarbibe/Github/SimulatorSFML

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/samuelarbibe/Github/SimulatorSFML/bin/debug

# Include any dependencies generated for this target.
include CMakeFiles/SimulatorSFML.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SimulatorSFML.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SimulatorSFML.dir/flags.make

CMakeFiles/SimulatorSFML.dir/src/Simulator/Engine.cpp.o: CMakeFiles/SimulatorSFML.dir/flags.make
CMakeFiles/SimulatorSFML.dir/src/Simulator/Engine.cpp.o: ../../src/Simulator/Engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/samuelarbibe/Github/SimulatorSFML/bin/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SimulatorSFML.dir/src/Simulator/Engine.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SimulatorSFML.dir/src/Simulator/Engine.cpp.o -c /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Engine.cpp

CMakeFiles/SimulatorSFML.dir/src/Simulator/Engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SimulatorSFML.dir/src/Simulator/Engine.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Engine.cpp > CMakeFiles/SimulatorSFML.dir/src/Simulator/Engine.cpp.i

CMakeFiles/SimulatorSFML.dir/src/Simulator/Engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SimulatorSFML.dir/src/Simulator/Engine.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Engine.cpp -o CMakeFiles/SimulatorSFML.dir/src/Simulator/Engine.cpp.s

CMakeFiles/SimulatorSFML.dir/src/Simulator/Intersection.cpp.o: CMakeFiles/SimulatorSFML.dir/flags.make
CMakeFiles/SimulatorSFML.dir/src/Simulator/Intersection.cpp.o: ../../src/Simulator/Intersection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/samuelarbibe/Github/SimulatorSFML/bin/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SimulatorSFML.dir/src/Simulator/Intersection.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SimulatorSFML.dir/src/Simulator/Intersection.cpp.o -c /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Intersection.cpp

CMakeFiles/SimulatorSFML.dir/src/Simulator/Intersection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SimulatorSFML.dir/src/Simulator/Intersection.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Intersection.cpp > CMakeFiles/SimulatorSFML.dir/src/Simulator/Intersection.cpp.i

CMakeFiles/SimulatorSFML.dir/src/Simulator/Intersection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SimulatorSFML.dir/src/Simulator/Intersection.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Intersection.cpp -o CMakeFiles/SimulatorSFML.dir/src/Simulator/Intersection.cpp.s

CMakeFiles/SimulatorSFML.dir/src/Simulator/Lane.cpp.o: CMakeFiles/SimulatorSFML.dir/flags.make
CMakeFiles/SimulatorSFML.dir/src/Simulator/Lane.cpp.o: ../../src/Simulator/Lane.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/samuelarbibe/Github/SimulatorSFML/bin/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SimulatorSFML.dir/src/Simulator/Lane.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SimulatorSFML.dir/src/Simulator/Lane.cpp.o -c /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Lane.cpp

CMakeFiles/SimulatorSFML.dir/src/Simulator/Lane.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SimulatorSFML.dir/src/Simulator/Lane.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Lane.cpp > CMakeFiles/SimulatorSFML.dir/src/Simulator/Lane.cpp.i

CMakeFiles/SimulatorSFML.dir/src/Simulator/Lane.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SimulatorSFML.dir/src/Simulator/Lane.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Lane.cpp -o CMakeFiles/SimulatorSFML.dir/src/Simulator/Lane.cpp.s

CMakeFiles/SimulatorSFML.dir/src/main.cpp.o: CMakeFiles/SimulatorSFML.dir/flags.make
CMakeFiles/SimulatorSFML.dir/src/main.cpp.o: ../../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/samuelarbibe/Github/SimulatorSFML/bin/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SimulatorSFML.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SimulatorSFML.dir/src/main.cpp.o -c /Users/samuelarbibe/Github/SimulatorSFML/src/main.cpp

CMakeFiles/SimulatorSFML.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SimulatorSFML.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/samuelarbibe/Github/SimulatorSFML/src/main.cpp > CMakeFiles/SimulatorSFML.dir/src/main.cpp.i

CMakeFiles/SimulatorSFML.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SimulatorSFML.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/samuelarbibe/Github/SimulatorSFML/src/main.cpp -o CMakeFiles/SimulatorSFML.dir/src/main.cpp.s

CMakeFiles/SimulatorSFML.dir/src/Simulator/Road.cpp.o: CMakeFiles/SimulatorSFML.dir/flags.make
CMakeFiles/SimulatorSFML.dir/src/Simulator/Road.cpp.o: ../../src/Simulator/Road.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/samuelarbibe/Github/SimulatorSFML/bin/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/SimulatorSFML.dir/src/Simulator/Road.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SimulatorSFML.dir/src/Simulator/Road.cpp.o -c /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Road.cpp

CMakeFiles/SimulatorSFML.dir/src/Simulator/Road.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SimulatorSFML.dir/src/Simulator/Road.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Road.cpp > CMakeFiles/SimulatorSFML.dir/src/Simulator/Road.cpp.i

CMakeFiles/SimulatorSFML.dir/src/Simulator/Road.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SimulatorSFML.dir/src/Simulator/Road.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Road.cpp -o CMakeFiles/SimulatorSFML.dir/src/Simulator/Road.cpp.s

CMakeFiles/SimulatorSFML.dir/src/Simulator/Vehicle.cpp.o: CMakeFiles/SimulatorSFML.dir/flags.make
CMakeFiles/SimulatorSFML.dir/src/Simulator/Vehicle.cpp.o: ../../src/Simulator/Vehicle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/samuelarbibe/Github/SimulatorSFML/bin/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/SimulatorSFML.dir/src/Simulator/Vehicle.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SimulatorSFML.dir/src/Simulator/Vehicle.cpp.o -c /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Vehicle.cpp

CMakeFiles/SimulatorSFML.dir/src/Simulator/Vehicle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SimulatorSFML.dir/src/Simulator/Vehicle.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Vehicle.cpp > CMakeFiles/SimulatorSFML.dir/src/Simulator/Vehicle.cpp.i

CMakeFiles/SimulatorSFML.dir/src/Simulator/Vehicle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SimulatorSFML.dir/src/Simulator/Vehicle.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Vehicle.cpp -o CMakeFiles/SimulatorSFML.dir/src/Simulator/Vehicle.cpp.s

CMakeFiles/SimulatorSFML.dir/src/Simulator/Map.cpp.o: CMakeFiles/SimulatorSFML.dir/flags.make
CMakeFiles/SimulatorSFML.dir/src/Simulator/Map.cpp.o: ../../src/Simulator/Map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/samuelarbibe/Github/SimulatorSFML/bin/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/SimulatorSFML.dir/src/Simulator/Map.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SimulatorSFML.dir/src/Simulator/Map.cpp.o -c /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Map.cpp

CMakeFiles/SimulatorSFML.dir/src/Simulator/Map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SimulatorSFML.dir/src/Simulator/Map.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Map.cpp > CMakeFiles/SimulatorSFML.dir/src/Simulator/Map.cpp.i

CMakeFiles/SimulatorSFML.dir/src/Simulator/Map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SimulatorSFML.dir/src/Simulator/Map.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/samuelarbibe/Github/SimulatorSFML/src/Simulator/Map.cpp -o CMakeFiles/SimulatorSFML.dir/src/Simulator/Map.cpp.s

# Object files for target SimulatorSFML
SimulatorSFML_OBJECTS = \
"CMakeFiles/SimulatorSFML.dir/src/Simulator/Engine.cpp.o" \
"CMakeFiles/SimulatorSFML.dir/src/Simulator/Intersection.cpp.o" \
"CMakeFiles/SimulatorSFML.dir/src/Simulator/Lane.cpp.o" \
"CMakeFiles/SimulatorSFML.dir/src/main.cpp.o" \
"CMakeFiles/SimulatorSFML.dir/src/Simulator/Road.cpp.o" \
"CMakeFiles/SimulatorSFML.dir/src/Simulator/Vehicle.cpp.o" \
"CMakeFiles/SimulatorSFML.dir/src/Simulator/Map.cpp.o"

# External object files for target SimulatorSFML
SimulatorSFML_EXTERNAL_OBJECTS =

SimulatorSFML: CMakeFiles/SimulatorSFML.dir/src/Simulator/Engine.cpp.o
SimulatorSFML: CMakeFiles/SimulatorSFML.dir/src/Simulator/Intersection.cpp.o
SimulatorSFML: CMakeFiles/SimulatorSFML.dir/src/Simulator/Lane.cpp.o
SimulatorSFML: CMakeFiles/SimulatorSFML.dir/src/main.cpp.o
SimulatorSFML: CMakeFiles/SimulatorSFML.dir/src/Simulator/Road.cpp.o
SimulatorSFML: CMakeFiles/SimulatorSFML.dir/src/Simulator/Vehicle.cpp.o
SimulatorSFML: CMakeFiles/SimulatorSFML.dir/src/Simulator/Map.cpp.o
SimulatorSFML: CMakeFiles/SimulatorSFML.dir/build.make
SimulatorSFML: /Library/Frameworks/./sfml-audio.framework/Versions/2.5.1/sfml-audio
SimulatorSFML: /Library/Frameworks/./sfml-graphics.framework/Versions/2.5.1/sfml-graphics
SimulatorSFML: /Library/Frameworks/./sfml-window.framework/Versions/2.5.1/sfml-window
SimulatorSFML: /Library/Frameworks/./sfml-system.framework/Versions/2.5.1/sfml-system
SimulatorSFML: CMakeFiles/SimulatorSFML.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/samuelarbibe/Github/SimulatorSFML/bin/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable SimulatorSFML"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SimulatorSFML.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SimulatorSFML.dir/build: SimulatorSFML

.PHONY : CMakeFiles/SimulatorSFML.dir/build

CMakeFiles/SimulatorSFML.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SimulatorSFML.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SimulatorSFML.dir/clean

CMakeFiles/SimulatorSFML.dir/depend:
	cd /Users/samuelarbibe/Github/SimulatorSFML/bin/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/samuelarbibe/Github/SimulatorSFML /Users/samuelarbibe/Github/SimulatorSFML /Users/samuelarbibe/Github/SimulatorSFML/bin/debug /Users/samuelarbibe/Github/SimulatorSFML/bin/debug /Users/samuelarbibe/Github/SimulatorSFML/bin/debug/CMakeFiles/SimulatorSFML.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SimulatorSFML.dir/depend

