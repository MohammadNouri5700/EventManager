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
CMAKE_COMMAND = /opt/poky/3.1.16/sysroots/x86_64-pokysdk-linux/usr/bin/cmake

# The command to remove a file.
RM = /opt/poky/3.1.16/sysroots/x86_64-pokysdk-linux/usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/git/Event_manager11/Event_manager

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/git/Event_manager11/Event_manager/cmake-build-release-system

# Utility rule file for test-ci.

# Include the progress variables for this target.
include lib/curl/tests/CMakeFiles/test-ci.dir/progress.make

lib/curl/tests/CMakeFiles/test-ci:
	cd /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests && /usr/bin/perl /home/user/git/Event_manager11/Event_manager/lib/curl/tests/runtests.pl -a -p !flaky -r -rm "\$$TFLAGS"

test-ci: lib/curl/tests/CMakeFiles/test-ci
test-ci: lib/curl/tests/CMakeFiles/test-ci.dir/build.make

.PHONY : test-ci

# Rule to build all files generated by this target.
lib/curl/tests/CMakeFiles/test-ci.dir/build: test-ci

.PHONY : lib/curl/tests/CMakeFiles/test-ci.dir/build

lib/curl/tests/CMakeFiles/test-ci.dir/clean:
	cd /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests && $(CMAKE_COMMAND) -P CMakeFiles/test-ci.dir/cmake_clean.cmake
.PHONY : lib/curl/tests/CMakeFiles/test-ci.dir/clean

lib/curl/tests/CMakeFiles/test-ci.dir/depend:
	cd /home/user/git/Event_manager11/Event_manager/cmake-build-release-system && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/git/Event_manager11/Event_manager /home/user/git/Event_manager11/Event_manager/lib/curl/tests /home/user/git/Event_manager11/Event_manager/cmake-build-release-system /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests/CMakeFiles/test-ci.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/curl/tests/CMakeFiles/test-ci.dir/depend

