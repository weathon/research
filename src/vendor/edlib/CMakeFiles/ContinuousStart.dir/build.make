# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_SOURCE_DIR = /home/wg25r/CMT/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wg25r/CMT/src

# Utility rule file for ContinuousStart.

# Include the progress variables for this target.
include vendor/edlib/CMakeFiles/ContinuousStart.dir/progress.make

vendor/edlib/CMakeFiles/ContinuousStart:
	cd /home/wg25r/CMT/src/vendor/edlib && /usr/bin/ctest -D ContinuousStart

ContinuousStart: vendor/edlib/CMakeFiles/ContinuousStart
ContinuousStart: vendor/edlib/CMakeFiles/ContinuousStart.dir/build.make

.PHONY : ContinuousStart

# Rule to build all files generated by this target.
vendor/edlib/CMakeFiles/ContinuousStart.dir/build: ContinuousStart

.PHONY : vendor/edlib/CMakeFiles/ContinuousStart.dir/build

vendor/edlib/CMakeFiles/ContinuousStart.dir/clean:
	cd /home/wg25r/CMT/src/vendor/edlib && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousStart.dir/cmake_clean.cmake
.PHONY : vendor/edlib/CMakeFiles/ContinuousStart.dir/clean

vendor/edlib/CMakeFiles/ContinuousStart.dir/depend:
	cd /home/wg25r/CMT/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wg25r/CMT/src /home/wg25r/CMT/src/vendor/edlib /home/wg25r/CMT/src /home/wg25r/CMT/src/vendor/edlib /home/wg25r/CMT/src/vendor/edlib/CMakeFiles/ContinuousStart.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/edlib/CMakeFiles/ContinuousStart.dir/depend

