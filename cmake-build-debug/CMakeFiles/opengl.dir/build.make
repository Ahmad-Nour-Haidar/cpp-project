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
include CMakeFiles/opengl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/opengl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/opengl.dir/flags.make

CMakeFiles/opengl.dir/texture.cpp.obj: CMakeFiles/opengl.dir/flags.make
CMakeFiles/opengl.dir/texture.cpp.obj: ../texture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\cpp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/opengl.dir/texture.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\opengl.dir\texture.cpp.obj -c D:\cpp\texture.cpp

CMakeFiles/opengl.dir/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl.dir/texture.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\cpp\texture.cpp > CMakeFiles\opengl.dir\texture.cpp.i

CMakeFiles/opengl.dir/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl.dir/texture.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\cpp\texture.cpp -o CMakeFiles\opengl.dir\texture.cpp.s

# Object files for target opengl
opengl_OBJECTS = \
"CMakeFiles/opengl.dir/texture.cpp.obj"

# External object files for target opengl
opengl_EXTERNAL_OBJECTS =

opengl.exe: CMakeFiles/opengl.dir/texture.cpp.obj
opengl.exe: CMakeFiles/opengl.dir/build.make
opengl.exe: CMakeFiles/opengl.dir/linklibs.rsp
opengl.exe: CMakeFiles/opengl.dir/objects1.rsp
opengl.exe: CMakeFiles/opengl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\cpp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable opengl.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\opengl.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/opengl.dir/build: opengl.exe

.PHONY : CMakeFiles/opengl.dir/build

CMakeFiles/opengl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\opengl.dir\cmake_clean.cmake
.PHONY : CMakeFiles/opengl.dir/clean

CMakeFiles/opengl.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\cpp D:\cpp D:\cpp\cmake-build-debug D:\cpp\cmake-build-debug D:\cpp\cmake-build-debug\CMakeFiles\opengl.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/opengl.dir/depend
