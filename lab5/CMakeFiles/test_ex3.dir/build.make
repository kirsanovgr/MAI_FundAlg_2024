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
CMAKE_SOURCE_DIR = /home/matvey/Unik/labs_C/sem3/FundAlg/lab5/build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/matvey/Unik/labs_C/sem3/FundAlg/lab5

# Include any dependencies generated for this target.
include CMakeFiles/test_ex3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_ex3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_ex3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_ex3.dir/flags.make

CMakeFiles/test_ex3.dir/ex3/test_logical_values_array.cpp.o: CMakeFiles/test_ex3.dir/flags.make
CMakeFiles/test_ex3.dir/ex3/test_logical_values_array.cpp.o: ex3/test_logical_values_array.cpp
CMakeFiles/test_ex3.dir/ex3/test_logical_values_array.cpp.o: CMakeFiles/test_ex3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matvey/Unik/labs_C/sem3/FundAlg/lab5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_ex3.dir/ex3/test_logical_values_array.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_ex3.dir/ex3/test_logical_values_array.cpp.o -MF CMakeFiles/test_ex3.dir/ex3/test_logical_values_array.cpp.o.d -o CMakeFiles/test_ex3.dir/ex3/test_logical_values_array.cpp.o -c /home/matvey/Unik/labs_C/sem3/FundAlg/lab5/ex3/test_logical_values_array.cpp

CMakeFiles/test_ex3.dir/ex3/test_logical_values_array.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_ex3.dir/ex3/test_logical_values_array.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matvey/Unik/labs_C/sem3/FundAlg/lab5/ex3/test_logical_values_array.cpp > CMakeFiles/test_ex3.dir/ex3/test_logical_values_array.cpp.i

CMakeFiles/test_ex3.dir/ex3/test_logical_values_array.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_ex3.dir/ex3/test_logical_values_array.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matvey/Unik/labs_C/sem3/FundAlg/lab5/ex3/test_logical_values_array.cpp -o CMakeFiles/test_ex3.dir/ex3/test_logical_values_array.cpp.s

CMakeFiles/test_ex3.dir/ex3/ex3.cpp.o: CMakeFiles/test_ex3.dir/flags.make
CMakeFiles/test_ex3.dir/ex3/ex3.cpp.o: ex3/ex3.cpp
CMakeFiles/test_ex3.dir/ex3/ex3.cpp.o: CMakeFiles/test_ex3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matvey/Unik/labs_C/sem3/FundAlg/lab5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test_ex3.dir/ex3/ex3.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_ex3.dir/ex3/ex3.cpp.o -MF CMakeFiles/test_ex3.dir/ex3/ex3.cpp.o.d -o CMakeFiles/test_ex3.dir/ex3/ex3.cpp.o -c /home/matvey/Unik/labs_C/sem3/FundAlg/lab5/ex3/ex3.cpp

CMakeFiles/test_ex3.dir/ex3/ex3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_ex3.dir/ex3/ex3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matvey/Unik/labs_C/sem3/FundAlg/lab5/ex3/ex3.cpp > CMakeFiles/test_ex3.dir/ex3/ex3.cpp.i

CMakeFiles/test_ex3.dir/ex3/ex3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_ex3.dir/ex3/ex3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matvey/Unik/labs_C/sem3/FundAlg/lab5/ex3/ex3.cpp -o CMakeFiles/test_ex3.dir/ex3/ex3.cpp.s

# Object files for target test_ex3
test_ex3_OBJECTS = \
"CMakeFiles/test_ex3.dir/ex3/test_logical_values_array.cpp.o" \
"CMakeFiles/test_ex3.dir/ex3/ex3.cpp.o"

# External object files for target test_ex3
test_ex3_EXTERNAL_OBJECTS =

test_ex3: CMakeFiles/test_ex3.dir/ex3/test_logical_values_array.cpp.o
test_ex3: CMakeFiles/test_ex3.dir/ex3/ex3.cpp.o
test_ex3: CMakeFiles/test_ex3.dir/build.make
test_ex3: /usr/lib/x86_64-linux-gnu/libgtest.a
test_ex3: CMakeFiles/test_ex3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/matvey/Unik/labs_C/sem3/FundAlg/lab5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_ex3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_ex3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_ex3.dir/build: test_ex3
.PHONY : CMakeFiles/test_ex3.dir/build

CMakeFiles/test_ex3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_ex3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_ex3.dir/clean

CMakeFiles/test_ex3.dir/depend:
	cd /home/matvey/Unik/labs_C/sem3/FundAlg/lab5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/matvey/Unik/labs_C/sem3/FundAlg/lab5/build /home/matvey/Unik/labs_C/sem3/FundAlg/lab5/build /home/matvey/Unik/labs_C/sem3/FundAlg/lab5 /home/matvey/Unik/labs_C/sem3/FundAlg/lab5 /home/matvey/Unik/labs_C/sem3/FundAlg/lab5/CMakeFiles/test_ex3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_ex3.dir/depend

