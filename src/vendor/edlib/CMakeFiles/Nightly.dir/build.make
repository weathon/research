# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wg25r/research/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wg25r/research/src

# Utility rule file for Nightly.

# Include the progress variables for this target.
include vendor/edlib/CMakeFiles/Nightly.dir/progress.make

vendor/edlib/CMakeFiles/Nightly:
	cd /home/wg25r/research/src/vendor/edlib && /usr/bin/ctest -D Nightly

Nightly: vendor/edlib/CMakeFiles/Nightly
Nightly: vendor/edlib/CMakeFiles/Nightly.dir/build.make

.PHONY : Nightly

# Rule to build all files generated by this target.
vendor/edlib/CMakeFiles/Nightly.dir/build: Nightly

.PHONY : vendor/edlib/CMakeFiles/Nightly.dir/build

vendor/edlib/CMakeFiles/Nightly.dir/clean:
	cd /home/wg25r/research/src/vendor/edlib && $(CMAKE_COMMAND) -P CMakeFiles/Nightly.dir/cmake_clean.cmake
.PHONY : vendor/edlib/CMakeFiles/Nightly.dir/clean

vendor/edlib/CMakeFiles/Nightly.dir/depend:
	cd /home/wg25r/research/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wg25r/research/src /home/wg25r/research/src/vendor/edlib /home/wg25r/research/src /home/wg25r/research/src/vendor/edlib /home/wg25r/research/src/vendor/edlib/CMakeFiles/Nightly.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/edlib/CMakeFiles/Nightly.dir/depend

