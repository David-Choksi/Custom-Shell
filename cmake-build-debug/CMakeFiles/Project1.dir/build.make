# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /private/var/folders/80/y6myzh851tb29xjnj038hpf40000gn/T/AppTranslocation/E0A99B2B-60F6-40FF-947B-CDA6438E2A46/d/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /private/var/folders/80/y6myzh851tb29xjnj038hpf40000gn/T/AppTranslocation/E0A99B2B-60F6-40FF-947B-CDA6438E2A46/d/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/dawoodchoksi/Desktop/EECS 3221 Operating Systems/Project1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/dawoodchoksi/Desktop/EECS 3221 Operating Systems/Project1/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Project1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Project1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Project1.dir/flags.make

CMakeFiles/Project1.dir/myshell.c.o: CMakeFiles/Project1.dir/flags.make
CMakeFiles/Project1.dir/myshell.c.o: ../myshell.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/dawoodchoksi/Desktop/EECS 3221 Operating Systems/Project1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Project1.dir/myshell.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Project1.dir/myshell.c.o   -c "/Users/dawoodchoksi/Desktop/EECS 3221 Operating Systems/Project1/myshell.c"

CMakeFiles/Project1.dir/myshell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project1.dir/myshell.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/dawoodchoksi/Desktop/EECS 3221 Operating Systems/Project1/myshell.c" > CMakeFiles/Project1.dir/myshell.c.i

CMakeFiles/Project1.dir/myshell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project1.dir/myshell.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/dawoodchoksi/Desktop/EECS 3221 Operating Systems/Project1/myshell.c" -o CMakeFiles/Project1.dir/myshell.c.s

# Object files for target Project1
Project1_OBJECTS = \
"CMakeFiles/Project1.dir/myshell.c.o"

# External object files for target Project1
Project1_EXTERNAL_OBJECTS =

Project1: CMakeFiles/Project1.dir/myshell.c.o
Project1: CMakeFiles/Project1.dir/build.make
Project1: CMakeFiles/Project1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/dawoodchoksi/Desktop/EECS 3221 Operating Systems/Project1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Project1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Project1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Project1.dir/build: Project1

.PHONY : CMakeFiles/Project1.dir/build

CMakeFiles/Project1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Project1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Project1.dir/clean

CMakeFiles/Project1.dir/depend:
	cd "/Users/dawoodchoksi/Desktop/EECS 3221 Operating Systems/Project1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/dawoodchoksi/Desktop/EECS 3221 Operating Systems/Project1" "/Users/dawoodchoksi/Desktop/EECS 3221 Operating Systems/Project1" "/Users/dawoodchoksi/Desktop/EECS 3221 Operating Systems/Project1/cmake-build-debug" "/Users/dawoodchoksi/Desktop/EECS 3221 Operating Systems/Project1/cmake-build-debug" "/Users/dawoodchoksi/Desktop/EECS 3221 Operating Systems/Project1/cmake-build-debug/CMakeFiles/Project1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Project1.dir/depend

