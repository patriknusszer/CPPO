# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_SOURCE_DIR = /Users/nusszerpatrik/CLionProjects/CPPO

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nusszerpatrik/CLionProjects/CPPO/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CPPO.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CPPO.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CPPO.dir/flags.make

CMakeFiles/CPPO.dir/CPPO.cpp.o: CMakeFiles/CPPO.dir/flags.make
CMakeFiles/CPPO.dir/CPPO.cpp.o: ../CPPO.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nusszerpatrik/CLionProjects/CPPO/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CPPO.dir/CPPO.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CPPO.dir/CPPO.cpp.o -c /Users/nusszerpatrik/CLionProjects/CPPO/CPPO.cpp

CMakeFiles/CPPO.dir/CPPO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CPPO.dir/CPPO.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nusszerpatrik/CLionProjects/CPPO/CPPO.cpp > CMakeFiles/CPPO.dir/CPPO.cpp.i

CMakeFiles/CPPO.dir/CPPO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CPPO.dir/CPPO.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nusszerpatrik/CLionProjects/CPPO/CPPO.cpp -o CMakeFiles/CPPO.dir/CPPO.cpp.s

# Object files for target CPPO
CPPO_OBJECTS = \
"CMakeFiles/CPPO.dir/CPPO.cpp.o"

# External object files for target CPPO
CPPO_EXTERNAL_OBJECTS =

CPPO: CMakeFiles/CPPO.dir/CPPO.cpp.o
CPPO: CMakeFiles/CPPO.dir/build.make
CPPO: CMakeFiles/CPPO.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/nusszerpatrik/CLionProjects/CPPO/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable CPPO"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CPPO.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CPPO.dir/build: CPPO

.PHONY : CMakeFiles/CPPO.dir/build

CMakeFiles/CPPO.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CPPO.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CPPO.dir/clean

CMakeFiles/CPPO.dir/depend:
	cd /Users/nusszerpatrik/CLionProjects/CPPO/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nusszerpatrik/CLionProjects/CPPO /Users/nusszerpatrik/CLionProjects/CPPO /Users/nusszerpatrik/CLionProjects/CPPO/cmake-build-debug /Users/nusszerpatrik/CLionProjects/CPPO/cmake-build-debug /Users/nusszerpatrik/CLionProjects/CPPO/cmake-build-debug/CMakeFiles/CPPO.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CPPO.dir/depend
