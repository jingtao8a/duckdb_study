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
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/example/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/example/main.cpp.o: /home/yuxintao/duckdb_study/example/main.cpp
CMakeFiles/main.dir/example/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuxintao/duckdb_study/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/example/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/example/main.cpp.o -MF CMakeFiles/main.dir/example/main.cpp.o.d -o CMakeFiles/main.dir/example/main.cpp.o -c /home/yuxintao/duckdb_study/example/main.cpp

CMakeFiles/main.dir/example/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/example/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuxintao/duckdb_study/example/main.cpp > CMakeFiles/main.dir/example/main.cpp.i

CMakeFiles/main.dir/example/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/example/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuxintao/duckdb_study/example/main.cpp -o CMakeFiles/main.dir/example/main.cpp.s

CMakeFiles/main.dir/src/texttable.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/texttable.cpp.o: /home/yuxintao/duckdb_study/src/texttable.cpp
CMakeFiles/main.dir/src/texttable.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuxintao/duckdb_study/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/src/texttable.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/texttable.cpp.o -MF CMakeFiles/main.dir/src/texttable.cpp.o.d -o CMakeFiles/main.dir/src/texttable.cpp.o -c /home/yuxintao/duckdb_study/src/texttable.cpp

CMakeFiles/main.dir/src/texttable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/texttable.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuxintao/duckdb_study/src/texttable.cpp > CMakeFiles/main.dir/src/texttable.cpp.i

CMakeFiles/main.dir/src/texttable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/texttable.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuxintao/duckdb_study/src/texttable.cpp -o CMakeFiles/main.dir/src/texttable.cpp.s

CMakeFiles/main.dir/src/bplustree.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/bplustree.cpp.o: /home/yuxintao/duckdb_study/src/bplustree.cpp
CMakeFiles/main.dir/src/bplustree.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuxintao/duckdb_study/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/src/bplustree.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/bplustree.cpp.o -MF CMakeFiles/main.dir/src/bplustree.cpp.o.d -o CMakeFiles/main.dir/src/bplustree.cpp.o -c /home/yuxintao/duckdb_study/src/bplustree.cpp

CMakeFiles/main.dir/src/bplustree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/bplustree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuxintao/duckdb_study/src/bplustree.cpp > CMakeFiles/main.dir/src/bplustree.cpp.i

CMakeFiles/main.dir/src/bplustree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/bplustree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuxintao/duckdb_study/src/bplustree.cpp -o CMakeFiles/main.dir/src/bplustree.cpp.s

CMakeFiles/main.dir/src/duckdbms.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/duckdbms.cpp.o: /home/yuxintao/duckdb_study/src/duckdbms.cpp
CMakeFiles/main.dir/src/duckdbms.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuxintao/duckdb_study/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/src/duckdbms.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/duckdbms.cpp.o -MF CMakeFiles/main.dir/src/duckdbms.cpp.o.d -o CMakeFiles/main.dir/src/duckdbms.cpp.o -c /home/yuxintao/duckdb_study/src/duckdbms.cpp

CMakeFiles/main.dir/src/duckdbms.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/duckdbms.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuxintao/duckdb_study/src/duckdbms.cpp > CMakeFiles/main.dir/src/duckdbms.cpp.i

CMakeFiles/main.dir/src/duckdbms.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/duckdbms.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuxintao/duckdb_study/src/duckdbms.cpp -o CMakeFiles/main.dir/src/duckdbms.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/example/main.cpp.o" \
"CMakeFiles/main.dir/src/texttable.cpp.o" \
"CMakeFiles/main.dir/src/bplustree.cpp.o" \
"CMakeFiles/main.dir/src/duckdbms.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

/home/yuxintao/duckdb_study/bin/main: CMakeFiles/main.dir/example/main.cpp.o
/home/yuxintao/duckdb_study/bin/main: CMakeFiles/main.dir/src/texttable.cpp.o
/home/yuxintao/duckdb_study/bin/main: CMakeFiles/main.dir/src/bplustree.cpp.o
/home/yuxintao/duckdb_study/bin/main: CMakeFiles/main.dir/src/duckdbms.cpp.o
/home/yuxintao/duckdb_study/bin/main: CMakeFiles/main.dir/build.make
/home/yuxintao/duckdb_study/bin/main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yuxintao/duckdb_study/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable /home/yuxintao/duckdb_study/bin/main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: /home/yuxintao/duckdb_study/bin/main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/yuxintao/duckdb_study/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yuxintao/duckdb_study /home/yuxintao/duckdb_study /home/yuxintao/duckdb_study/build /home/yuxintao/duckdb_study/build /home/yuxintao/duckdb_study/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

