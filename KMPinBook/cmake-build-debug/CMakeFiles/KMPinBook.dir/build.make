# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = "E:\CLion 2017.2.3\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "E:\CLion 2017.2.3\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "F:\G\Data Structures and Algorithms\KMPinBook"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "F:\G\Data Structures and Algorithms\KMPinBook\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/KMPinBook.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/KMPinBook.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/KMPinBook.dir/flags.make

CMakeFiles/KMPinBook.dir/main.cpp.obj: CMakeFiles/KMPinBook.dir/flags.make
CMakeFiles/KMPinBook.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="F:\G\Data Structures and Algorithms\KMPinBook\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/KMPinBook.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\KMPinBook.dir\main.cpp.obj -c "F:\G\Data Structures and Algorithms\KMPinBook\main.cpp"

CMakeFiles/KMPinBook.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KMPinBook.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "F:\G\Data Structures and Algorithms\KMPinBook\main.cpp" > CMakeFiles\KMPinBook.dir\main.cpp.i

CMakeFiles/KMPinBook.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KMPinBook.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "F:\G\Data Structures and Algorithms\KMPinBook\main.cpp" -o CMakeFiles\KMPinBook.dir\main.cpp.s

CMakeFiles/KMPinBook.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/KMPinBook.dir/main.cpp.obj.requires

CMakeFiles/KMPinBook.dir/main.cpp.obj.provides: CMakeFiles/KMPinBook.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\KMPinBook.dir\build.make CMakeFiles/KMPinBook.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/KMPinBook.dir/main.cpp.obj.provides

CMakeFiles/KMPinBook.dir/main.cpp.obj.provides.build: CMakeFiles/KMPinBook.dir/main.cpp.obj


# Object files for target KMPinBook
KMPinBook_OBJECTS = \
"CMakeFiles/KMPinBook.dir/main.cpp.obj"

# External object files for target KMPinBook
KMPinBook_EXTERNAL_OBJECTS =

KMPinBook.exe: CMakeFiles/KMPinBook.dir/main.cpp.obj
KMPinBook.exe: CMakeFiles/KMPinBook.dir/build.make
KMPinBook.exe: CMakeFiles/KMPinBook.dir/linklibs.rsp
KMPinBook.exe: CMakeFiles/KMPinBook.dir/objects1.rsp
KMPinBook.exe: CMakeFiles/KMPinBook.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="F:\G\Data Structures and Algorithms\KMPinBook\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable KMPinBook.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\KMPinBook.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/KMPinBook.dir/build: KMPinBook.exe

.PHONY : CMakeFiles/KMPinBook.dir/build

CMakeFiles/KMPinBook.dir/requires: CMakeFiles/KMPinBook.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/KMPinBook.dir/requires

CMakeFiles/KMPinBook.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\KMPinBook.dir\cmake_clean.cmake
.PHONY : CMakeFiles/KMPinBook.dir/clean

CMakeFiles/KMPinBook.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "F:\G\Data Structures and Algorithms\KMPinBook" "F:\G\Data Structures and Algorithms\KMPinBook" "F:\G\Data Structures and Algorithms\KMPinBook\cmake-build-debug" "F:\G\Data Structures and Algorithms\KMPinBook\cmake-build-debug" "F:\G\Data Structures and Algorithms\KMPinBook\cmake-build-debug\CMakeFiles\KMPinBook.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/KMPinBook.dir/depend

