# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_SOURCE_DIR = /home/yuxintao/duckdb_study

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yuxintao/duckdb_study/build

# Include any dependencies generated for this target.
include CMakeFiles/testtexttable.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/testtexttable.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/testtexttable.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testtexttable.dir/flags.make

CMakeFiles/testtexttable.dir/test/testtexttable.cpp.o: CMakeFiles/testtexttable.dir/flags.make
CMakeFiles/testtexttable.dir/test/testtexttable.cpp.o: /home/yuxintao/duckdb_study/test/testtexttable.cpp
CMakeFiles/testtexttable.dir/test/testtexttable.cpp.o: CMakeFiles/testtexttable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuxintao/duckdb_study/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testtexttable.dir/test/testtexttable.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testtexttable.dir/test/testtexttable.cpp.o -MF CMakeFiles/testtexttable.dir/test/testtexttable.cpp.o.d -o CMakeFiles/testtexttable.dir/test/testtexttable.cpp.o -c /home/yuxintao/duckdb_study/test/testtexttable.cpp

CMakeFiles/testtexttable.dir/test/testtexttable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testtexttable.dir/test/testtexttable.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuxintao/duckdb_study/test/testtexttable.cpp > CMakeFiles/testtexttable.dir/test/testtexttable.cpp.i

CMakeFiles/testtexttable.dir/test/testtexttable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testtexttable.dir/test/testtexttable.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuxintao/duckdb_study/test/testtexttable.cpp -o CMakeFiles/testtexttable.dir/test/testtexttable.cpp.s

CMakeFiles/testtexttable.dir/src/texttable.cpp.o: CMakeFiles/testtexttable.dir/flags.make
CMakeFiles/testtexttable.dir/src/texttable.cpp.o: /home/yuxintao/duckdb_study/src/texttable.cpp
CMakeFiles/testtexttable.dir/src/texttable.cpp.o: CMakeFiles/testtexttable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuxintao/duckdb_study/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/testtexttable.dir/src/texttable.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testtexttable.dir/src/texttable.cpp.o -MF CMakeFiles/testtexttable.dir/src/texttable.cpp.o.d -o CMakeFiles/testtexttable.dir/src/texttable.cpp.o -c /home/yuxintao/duckdb_study/src/texttable.cpp

CMakeFiles/testtexttable.dir/src/texttable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testtexttable.dir/src/texttable.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuxintao/duckdb_study/src/texttable.cpp > CMakeFiles/testtexttable.dir/src/texttable.cpp.i

CMakeFiles/testtexttable.dir/src/texttable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testtexttable.dir/src/texttable.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuxintao/duckdb_study/src/texttable.cpp -o CMakeFiles/testtexttable.dir/src/texttable.cpp.s

# Object files for target testtexttable
testtexttable_OBJECTS = \
"CMakeFiles/testtexttable.dir/test/testtexttable.cpp.o" \
"CMakeFiles/testtexttable.dir/src/texttable.cpp.o"

# External object files for target testtexttable
testtexttable_EXTERNAL_OBJECTS =

/home/yuxintao/duckdb_study/bin/testtexttable: CMakeFiles/testtexttable.dir/test/testtexttable.cpp.o
/home/yuxintao/duckdb_study/bin/testtexttable: CMakeFiles/testtexttable.dir/src/texttable.cpp.o
/home/yuxintao/duckdb_study/bin/testtexttable: CMakeFiles/testtexttable.dir/build.make
/home/yuxintao/duckdb_study/bin/testtexttable: CMakeFiles/testtexttable.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yuxintao/duckdb_study/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable /home/yuxintao/duckdb_study/bin/testtexttable"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testtexttable.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testtexttable.dir/build: /home/yuxintao/duckdb_study/bin/testtexttable
.PHONY : CMakeFiles/testtexttable.dir/build

CMakeFiles/testtexttable.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testtexttable.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testtexttable.dir/clean

CMakeFiles/testtexttable.dir/depend:
	cd /home/yuxintao/duckdb_study/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yuxintao/duckdb_study /home/yuxintao/duckdb_study /home/yuxintao/duckdb_study/build /home/yuxintao/duckdb_study/build /home/yuxintao/duckdb_study/build/CMakeFiles/testtexttable.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testtexttable.dir/depend

