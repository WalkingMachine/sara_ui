# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/lucas/Sara_QT_work/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lucas/Sara_QT_work/build

# Utility rule file for sara_qt_window_automoc.

# Include the progress variables for this target.
include sara_qt_test1/CMakeFiles/sara_qt_window_automoc.dir/progress.make

sara_qt_test1/CMakeFiles/sara_qt_window_automoc:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/lucas/Sara_QT_work/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic moc for target sara_qt_window"
	cd /home/lucas/Sara_QT_work/build/sara_qt_test1 && /usr/bin/cmake -E cmake_autogen /home/lucas/Sara_QT_work/build/sara_qt_test1/CMakeFiles/sara_qt_window_automoc.dir/ ""

sara_qt_window_automoc: sara_qt_test1/CMakeFiles/sara_qt_window_automoc
sara_qt_window_automoc: sara_qt_test1/CMakeFiles/sara_qt_window_automoc.dir/build.make

.PHONY : sara_qt_window_automoc

# Rule to build all files generated by this target.
sara_qt_test1/CMakeFiles/sara_qt_window_automoc.dir/build: sara_qt_window_automoc

.PHONY : sara_qt_test1/CMakeFiles/sara_qt_window_automoc.dir/build

sara_qt_test1/CMakeFiles/sara_qt_window_automoc.dir/clean:
	cd /home/lucas/Sara_QT_work/build/sara_qt_test1 && $(CMAKE_COMMAND) -P CMakeFiles/sara_qt_window_automoc.dir/cmake_clean.cmake
.PHONY : sara_qt_test1/CMakeFiles/sara_qt_window_automoc.dir/clean

sara_qt_test1/CMakeFiles/sara_qt_window_automoc.dir/depend:
	cd /home/lucas/Sara_QT_work/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lucas/Sara_QT_work/src /home/lucas/Sara_QT_work/src/sara_qt_test1 /home/lucas/Sara_QT_work/build /home/lucas/Sara_QT_work/build/sara_qt_test1 /home/lucas/Sara_QT_work/build/sara_qt_test1/CMakeFiles/sara_qt_window_automoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sara_qt_test1/CMakeFiles/sara_qt_window_automoc.dir/depend

