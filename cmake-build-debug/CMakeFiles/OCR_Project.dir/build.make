# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/corentin.ourvoy/afs/clion-2018.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/corentin.ourvoy/afs/clion-2018.2.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/corentin.ourvoy/afs/OCR_Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/corentin.ourvoy/afs/OCR_Project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/OCR_Project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OCR_Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OCR_Project.dir/flags.make

CMakeFiles/OCR_Project.dir/Backprop.c.o: CMakeFiles/OCR_Project.dir/flags.make
CMakeFiles/OCR_Project.dir/Backprop.c.o: ../Backprop.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/corentin.ourvoy/afs/OCR_Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/OCR_Project.dir/Backprop.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OCR_Project.dir/Backprop.c.o   -c /home/corentin.ourvoy/afs/OCR_Project/Backprop.c

CMakeFiles/OCR_Project.dir/Backprop.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OCR_Project.dir/Backprop.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/corentin.ourvoy/afs/OCR_Project/Backprop.c > CMakeFiles/OCR_Project.dir/Backprop.c.i

CMakeFiles/OCR_Project.dir/Backprop.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OCR_Project.dir/Backprop.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/corentin.ourvoy/afs/OCR_Project/Backprop.c -o CMakeFiles/OCR_Project.dir/Backprop.c.s

CMakeFiles/OCR_Project.dir/Layer.c.o: CMakeFiles/OCR_Project.dir/flags.make
CMakeFiles/OCR_Project.dir/Layer.c.o: ../Layer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/corentin.ourvoy/afs/OCR_Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/OCR_Project.dir/Layer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OCR_Project.dir/Layer.c.o   -c /home/corentin.ourvoy/afs/OCR_Project/Layer.c

CMakeFiles/OCR_Project.dir/Layer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OCR_Project.dir/Layer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/corentin.ourvoy/afs/OCR_Project/Layer.c > CMakeFiles/OCR_Project.dir/Layer.c.i

CMakeFiles/OCR_Project.dir/Layer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OCR_Project.dir/Layer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/corentin.ourvoy/afs/OCR_Project/Layer.c -o CMakeFiles/OCR_Project.dir/Layer.c.s

CMakeFiles/OCR_Project.dir/Network.c.o: CMakeFiles/OCR_Project.dir/flags.make
CMakeFiles/OCR_Project.dir/Network.c.o: ../Network.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/corentin.ourvoy/afs/OCR_Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/OCR_Project.dir/Network.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OCR_Project.dir/Network.c.o   -c /home/corentin.ourvoy/afs/OCR_Project/Network.c

CMakeFiles/OCR_Project.dir/Network.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OCR_Project.dir/Network.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/corentin.ourvoy/afs/OCR_Project/Network.c > CMakeFiles/OCR_Project.dir/Network.c.i

CMakeFiles/OCR_Project.dir/Network.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OCR_Project.dir/Network.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/corentin.ourvoy/afs/OCR_Project/Network.c -o CMakeFiles/OCR_Project.dir/Network.c.s

CMakeFiles/OCR_Project.dir/Node.c.o: CMakeFiles/OCR_Project.dir/flags.make
CMakeFiles/OCR_Project.dir/Node.c.o: ../Node.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/corentin.ourvoy/afs/OCR_Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/OCR_Project.dir/Node.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OCR_Project.dir/Node.c.o   -c /home/corentin.ourvoy/afs/OCR_Project/Node.c

CMakeFiles/OCR_Project.dir/Node.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OCR_Project.dir/Node.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/corentin.ourvoy/afs/OCR_Project/Node.c > CMakeFiles/OCR_Project.dir/Node.c.i

CMakeFiles/OCR_Project.dir/Node.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OCR_Project.dir/Node.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/corentin.ourvoy/afs/OCR_Project/Node.c -o CMakeFiles/OCR_Project.dir/Node.c.s

CMakeFiles/OCR_Project.dir/SaveAndLoad.c.o: CMakeFiles/OCR_Project.dir/flags.make
CMakeFiles/OCR_Project.dir/SaveAndLoad.c.o: ../SaveAndLoad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/corentin.ourvoy/afs/OCR_Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/OCR_Project.dir/SaveAndLoad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OCR_Project.dir/SaveAndLoad.c.o   -c /home/corentin.ourvoy/afs/OCR_Project/SaveAndLoad.c

CMakeFiles/OCR_Project.dir/SaveAndLoad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OCR_Project.dir/SaveAndLoad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/corentin.ourvoy/afs/OCR_Project/SaveAndLoad.c > CMakeFiles/OCR_Project.dir/SaveAndLoad.c.i

CMakeFiles/OCR_Project.dir/SaveAndLoad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OCR_Project.dir/SaveAndLoad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/corentin.ourvoy/afs/OCR_Project/SaveAndLoad.c -o CMakeFiles/OCR_Project.dir/SaveAndLoad.c.s

CMakeFiles/OCR_Project.dir/main.c.o: CMakeFiles/OCR_Project.dir/flags.make
CMakeFiles/OCR_Project.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/corentin.ourvoy/afs/OCR_Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/OCR_Project.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OCR_Project.dir/main.c.o   -c /home/corentin.ourvoy/afs/OCR_Project/main.c

CMakeFiles/OCR_Project.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OCR_Project.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/corentin.ourvoy/afs/OCR_Project/main.c > CMakeFiles/OCR_Project.dir/main.c.i

CMakeFiles/OCR_Project.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OCR_Project.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/corentin.ourvoy/afs/OCR_Project/main.c -o CMakeFiles/OCR_Project.dir/main.c.s

CMakeFiles/OCR_Project.dir/Trainer.c.o: CMakeFiles/OCR_Project.dir/flags.make
CMakeFiles/OCR_Project.dir/Trainer.c.o: ../Trainer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/corentin.ourvoy/afs/OCR_Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/OCR_Project.dir/Trainer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OCR_Project.dir/Trainer.c.o   -c /home/corentin.ourvoy/afs/OCR_Project/Trainer.c

CMakeFiles/OCR_Project.dir/Trainer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OCR_Project.dir/Trainer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/corentin.ourvoy/afs/OCR_Project/Trainer.c > CMakeFiles/OCR_Project.dir/Trainer.c.i

CMakeFiles/OCR_Project.dir/Trainer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OCR_Project.dir/Trainer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/corentin.ourvoy/afs/OCR_Project/Trainer.c -o CMakeFiles/OCR_Project.dir/Trainer.c.s

CMakeFiles/OCR_Project.dir/Transition.c.o: CMakeFiles/OCR_Project.dir/flags.make
CMakeFiles/OCR_Project.dir/Transition.c.o: ../Transition.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/corentin.ourvoy/afs/OCR_Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/OCR_Project.dir/Transition.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OCR_Project.dir/Transition.c.o   -c /home/corentin.ourvoy/afs/OCR_Project/Transition.c

CMakeFiles/OCR_Project.dir/Transition.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OCR_Project.dir/Transition.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/corentin.ourvoy/afs/OCR_Project/Transition.c > CMakeFiles/OCR_Project.dir/Transition.c.i

CMakeFiles/OCR_Project.dir/Transition.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OCR_Project.dir/Transition.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/corentin.ourvoy/afs/OCR_Project/Transition.c -o CMakeFiles/OCR_Project.dir/Transition.c.s

CMakeFiles/OCR_Project.dir/UI.c.o: CMakeFiles/OCR_Project.dir/flags.make
CMakeFiles/OCR_Project.dir/UI.c.o: ../UI.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/corentin.ourvoy/afs/OCR_Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/OCR_Project.dir/UI.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OCR_Project.dir/UI.c.o   -c /home/corentin.ourvoy/afs/OCR_Project/UI.c

CMakeFiles/OCR_Project.dir/UI.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OCR_Project.dir/UI.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/corentin.ourvoy/afs/OCR_Project/UI.c > CMakeFiles/OCR_Project.dir/UI.c.i

CMakeFiles/OCR_Project.dir/UI.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OCR_Project.dir/UI.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/corentin.ourvoy/afs/OCR_Project/UI.c -o CMakeFiles/OCR_Project.dir/UI.c.s

# Object files for target OCR_Project
OCR_Project_OBJECTS = \
"CMakeFiles/OCR_Project.dir/Backprop.c.o" \
"CMakeFiles/OCR_Project.dir/Layer.c.o" \
"CMakeFiles/OCR_Project.dir/Network.c.o" \
"CMakeFiles/OCR_Project.dir/Node.c.o" \
"CMakeFiles/OCR_Project.dir/SaveAndLoad.c.o" \
"CMakeFiles/OCR_Project.dir/main.c.o" \
"CMakeFiles/OCR_Project.dir/Trainer.c.o" \
"CMakeFiles/OCR_Project.dir/Transition.c.o" \
"CMakeFiles/OCR_Project.dir/UI.c.o"

# External object files for target OCR_Project
OCR_Project_EXTERNAL_OBJECTS =

OCR_Project: CMakeFiles/OCR_Project.dir/Backprop.c.o
OCR_Project: CMakeFiles/OCR_Project.dir/Layer.c.o
OCR_Project: CMakeFiles/OCR_Project.dir/Network.c.o
OCR_Project: CMakeFiles/OCR_Project.dir/Node.c.o
OCR_Project: CMakeFiles/OCR_Project.dir/SaveAndLoad.c.o
OCR_Project: CMakeFiles/OCR_Project.dir/main.c.o
OCR_Project: CMakeFiles/OCR_Project.dir/Trainer.c.o
OCR_Project: CMakeFiles/OCR_Project.dir/Transition.c.o
OCR_Project: CMakeFiles/OCR_Project.dir/UI.c.o
OCR_Project: CMakeFiles/OCR_Project.dir/build.make
OCR_Project: CMakeFiles/OCR_Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/corentin.ourvoy/afs/OCR_Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C executable OCR_Project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OCR_Project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OCR_Project.dir/build: OCR_Project

.PHONY : CMakeFiles/OCR_Project.dir/build

CMakeFiles/OCR_Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OCR_Project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OCR_Project.dir/clean

CMakeFiles/OCR_Project.dir/depend:
	cd /home/corentin.ourvoy/afs/OCR_Project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/corentin.ourvoy/afs/OCR_Project /home/corentin.ourvoy/afs/OCR_Project /home/corentin.ourvoy/afs/OCR_Project/cmake-build-debug /home/corentin.ourvoy/afs/OCR_Project/cmake-build-debug /home/corentin.ourvoy/afs/OCR_Project/cmake-build-debug/CMakeFiles/OCR_Project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OCR_Project.dir/depend

