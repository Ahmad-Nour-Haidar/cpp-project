# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\cpp\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/class_BST.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/class_BST.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/class_BST.dir/flags.make

CMakeFiles/class_BST.dir/class_BST.cpp.obj: CMakeFiles/class_BST.dir/flags.make
CMakeFiles/class_BST.dir/class_BST.cpp.obj: ../class_BST.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\cpp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/class_BST.dir/class_BST.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\class_BST.dir\class_BST.cpp.obj -c D:\cpp\class_BST.cpp

CMakeFiles/class_BST.dir/class_BST.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/class_BST.dir/class_BST.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\cpp\class_BST.cpp > CMakeFiles\class_BST.dir\class_BST.cpp.i

CMakeFiles/class_BST.dir/class_BST.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/class_BST.dir/class_BST.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\cpp\class_BST.cpp -o CMakeFiles\class_BST.dir\class_BST.cpp.s

# Object files for target class_BST
class_BST_OBJECTS = \
"CMakeFiles/class_BST.dir/class_BST.cpp.obj"

# External object files for target class_BST
class_BST_EXTERNAL_OBJECTS =

class_BST.exe: CMakeFiles/class_BST.dir/class_BST.cpp.obj
class_BST.exe: CMakeFiles/class_BST.dir/build.make
class_BST.exe: CMakeFiles/class_BST.dir/linklibs.rsp
class_BST.exe: CMakeFiles/class_BST.dir/objects1.rsp
class_BST.exe: CMakeFiles/class_BST.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\cpp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable class_BST.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\class_BST.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/class_BST.dir/build: class_BST.exe

.PHONY : CMakeFiles/class_BST.dir/build

CMakeFiles/class_BST.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\class_BST.dir\cmake_clean.cmake
.PHONY : CMakeFiles/class_BST.dir/clean

CMakeFiles/class_BST.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\cpp D:\cpp D:\cpp\cmake-build-debug D:\cpp\cmake-build-debug D:\cpp\cmake-build-debug\CMakeFiles\class_BST.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/class_BST.dir/depend

