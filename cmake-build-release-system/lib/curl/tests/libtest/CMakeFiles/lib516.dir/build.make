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

# Include any dependencies generated for this target.
include lib/curl/tests/libtest/CMakeFiles/lib516.dir/depend.make

# Include the progress variables for this target.
include lib/curl/tests/libtest/CMakeFiles/lib516.dir/progress.make

# Include the compile flags for this target's objects.
include lib/curl/tests/libtest/CMakeFiles/lib516.dir/flags.make

lib/curl/tests/libtest/CMakeFiles/lib516.dir/lib516.c.o: lib/curl/tests/libtest/CMakeFiles/lib516.dir/flags.make
lib/curl/tests/libtest/CMakeFiles/lib516.dir/lib516.c.o: ../lib/curl/tests/libtest/lib516.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/git/Event_manager11/Event_manager/cmake-build-release-system/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/curl/tests/libtest/CMakeFiles/lib516.dir/lib516.c.o"
	cd /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lib516.dir/lib516.c.o   -c /home/user/git/Event_manager11/Event_manager/lib/curl/tests/libtest/lib516.c

lib/curl/tests/libtest/CMakeFiles/lib516.dir/lib516.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib516.dir/lib516.c.i"
	cd /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/git/Event_manager11/Event_manager/lib/curl/tests/libtest/lib516.c > CMakeFiles/lib516.dir/lib516.c.i

lib/curl/tests/libtest/CMakeFiles/lib516.dir/lib516.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib516.dir/lib516.c.s"
	cd /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/git/Event_manager11/Event_manager/lib/curl/tests/libtest/lib516.c -o CMakeFiles/lib516.dir/lib516.c.s

lib/curl/tests/libtest/CMakeFiles/lib516.dir/__/__/lib/timediff.c.o: lib/curl/tests/libtest/CMakeFiles/lib516.dir/flags.make
lib/curl/tests/libtest/CMakeFiles/lib516.dir/__/__/lib/timediff.c.o: ../lib/curl/lib/timediff.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/git/Event_manager11/Event_manager/cmake-build-release-system/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lib/curl/tests/libtest/CMakeFiles/lib516.dir/__/__/lib/timediff.c.o"
	cd /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lib516.dir/__/__/lib/timediff.c.o   -c /home/user/git/Event_manager11/Event_manager/lib/curl/lib/timediff.c

lib/curl/tests/libtest/CMakeFiles/lib516.dir/__/__/lib/timediff.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib516.dir/__/__/lib/timediff.c.i"
	cd /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/git/Event_manager11/Event_manager/lib/curl/lib/timediff.c > CMakeFiles/lib516.dir/__/__/lib/timediff.c.i

lib/curl/tests/libtest/CMakeFiles/lib516.dir/__/__/lib/timediff.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib516.dir/__/__/lib/timediff.c.s"
	cd /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/git/Event_manager11/Event_manager/lib/curl/lib/timediff.c -o CMakeFiles/lib516.dir/__/__/lib/timediff.c.s

lib/curl/tests/libtest/CMakeFiles/lib516.dir/first.c.o: lib/curl/tests/libtest/CMakeFiles/lib516.dir/flags.make
lib/curl/tests/libtest/CMakeFiles/lib516.dir/first.c.o: ../lib/curl/tests/libtest/first.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/git/Event_manager11/Event_manager/cmake-build-release-system/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object lib/curl/tests/libtest/CMakeFiles/lib516.dir/first.c.o"
	cd /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lib516.dir/first.c.o   -c /home/user/git/Event_manager11/Event_manager/lib/curl/tests/libtest/first.c

lib/curl/tests/libtest/CMakeFiles/lib516.dir/first.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib516.dir/first.c.i"
	cd /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/git/Event_manager11/Event_manager/lib/curl/tests/libtest/first.c > CMakeFiles/lib516.dir/first.c.i

lib/curl/tests/libtest/CMakeFiles/lib516.dir/first.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib516.dir/first.c.s"
	cd /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/git/Event_manager11/Event_manager/lib/curl/tests/libtest/first.c -o CMakeFiles/lib516.dir/first.c.s

# Object files for target lib516
lib516_OBJECTS = \
"CMakeFiles/lib516.dir/lib516.c.o" \
"CMakeFiles/lib516.dir/__/__/lib/timediff.c.o" \
"CMakeFiles/lib516.dir/first.c.o"

# External object files for target lib516
lib516_EXTERNAL_OBJECTS =

lib/curl/tests/libtest/lib516: lib/curl/tests/libtest/CMakeFiles/lib516.dir/lib516.c.o
lib/curl/tests/libtest/lib516: lib/curl/tests/libtest/CMakeFiles/lib516.dir/__/__/lib/timediff.c.o
lib/curl/tests/libtest/lib516: lib/curl/tests/libtest/CMakeFiles/lib516.dir/first.c.o
lib/curl/tests/libtest/lib516: lib/curl/tests/libtest/CMakeFiles/lib516.dir/build.make
lib/curl/tests/libtest/lib516: lib/curl/lib/libcurl.so.4.8.0
lib/curl/tests/libtest/lib516: /usr/lib/x86_64-linux-gnu/libssl.so
lib/curl/tests/libtest/lib516: /usr/lib/x86_64-linux-gnu/libcrypto.so
lib/curl/tests/libtest/lib516: /usr/lib/x86_64-linux-gnu/libz.so
lib/curl/tests/libtest/lib516: lib/curl/tests/libtest/CMakeFiles/lib516.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/git/Event_manager11/Event_manager/cmake-build-release-system/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable lib516"
	cd /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests/libtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib516.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/curl/tests/libtest/CMakeFiles/lib516.dir/build: lib/curl/tests/libtest/lib516

.PHONY : lib/curl/tests/libtest/CMakeFiles/lib516.dir/build

lib/curl/tests/libtest/CMakeFiles/lib516.dir/clean:
	cd /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests/libtest && $(CMAKE_COMMAND) -P CMakeFiles/lib516.dir/cmake_clean.cmake
.PHONY : lib/curl/tests/libtest/CMakeFiles/lib516.dir/clean

lib/curl/tests/libtest/CMakeFiles/lib516.dir/depend:
	cd /home/user/git/Event_manager11/Event_manager/cmake-build-release-system && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/git/Event_manager11/Event_manager /home/user/git/Event_manager11/Event_manager/lib/curl/tests/libtest /home/user/git/Event_manager11/Event_manager/cmake-build-release-system /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests/libtest /home/user/git/Event_manager11/Event_manager/cmake-build-release-system/lib/curl/tests/libtest/CMakeFiles/lib516.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/curl/tests/libtest/CMakeFiles/lib516.dir/depend

