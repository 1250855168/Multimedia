# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/china/xxx/音乐播放器

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/china/xxx/音乐播放器/build

# Include any dependencies generated for this target.
include CMakeFiles/video.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/video.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/video.dir/flags.make

CMakeFiles/video.dir/main.cc.o: CMakeFiles/video.dir/flags.make
CMakeFiles/video.dir/main.cc.o: ../main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/china/xxx/音乐播放器/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/video.dir/main.cc.o"
	/usr/local/arm/5.4.0/usr/bin/arm-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/video.dir/main.cc.o -c /home/china/xxx/音乐播放器/main.cc

CMakeFiles/video.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/video.dir/main.cc.i"
	/usr/local/arm/5.4.0/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/china/xxx/音乐播放器/main.cc > CMakeFiles/video.dir/main.cc.i

CMakeFiles/video.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/video.dir/main.cc.s"
	/usr/local/arm/5.4.0/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/china/xxx/音乐播放器/main.cc -o CMakeFiles/video.dir/main.cc.s

CMakeFiles/video.dir/main.cc.o.requires:

.PHONY : CMakeFiles/video.dir/main.cc.o.requires

CMakeFiles/video.dir/main.cc.o.provides: CMakeFiles/video.dir/main.cc.o.requires
	$(MAKE) -f CMakeFiles/video.dir/build.make CMakeFiles/video.dir/main.cc.o.provides.build
.PHONY : CMakeFiles/video.dir/main.cc.o.provides

CMakeFiles/video.dir/main.cc.o.provides.build: CMakeFiles/video.dir/main.cc.o


CMakeFiles/video.dir/src/mplayer.cc.o: CMakeFiles/video.dir/flags.make
CMakeFiles/video.dir/src/mplayer.cc.o: ../src/mplayer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/china/xxx/音乐播放器/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/video.dir/src/mplayer.cc.o"
	/usr/local/arm/5.4.0/usr/bin/arm-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/video.dir/src/mplayer.cc.o -c /home/china/xxx/音乐播放器/src/mplayer.cc

CMakeFiles/video.dir/src/mplayer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/video.dir/src/mplayer.cc.i"
	/usr/local/arm/5.4.0/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/china/xxx/音乐播放器/src/mplayer.cc > CMakeFiles/video.dir/src/mplayer.cc.i

CMakeFiles/video.dir/src/mplayer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/video.dir/src/mplayer.cc.s"
	/usr/local/arm/5.4.0/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/china/xxx/音乐播放器/src/mplayer.cc -o CMakeFiles/video.dir/src/mplayer.cc.s

CMakeFiles/video.dir/src/mplayer.cc.o.requires:

.PHONY : CMakeFiles/video.dir/src/mplayer.cc.o.requires

CMakeFiles/video.dir/src/mplayer.cc.o.provides: CMakeFiles/video.dir/src/mplayer.cc.o.requires
	$(MAKE) -f CMakeFiles/video.dir/build.make CMakeFiles/video.dir/src/mplayer.cc.o.provides.build
.PHONY : CMakeFiles/video.dir/src/mplayer.cc.o.provides

CMakeFiles/video.dir/src/mplayer.cc.o.provides.build: CMakeFiles/video.dir/src/mplayer.cc.o


CMakeFiles/video.dir/src/DCList.cc.o: CMakeFiles/video.dir/flags.make
CMakeFiles/video.dir/src/DCList.cc.o: ../src/DCList.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/china/xxx/音乐播放器/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/video.dir/src/DCList.cc.o"
	/usr/local/arm/5.4.0/usr/bin/arm-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/video.dir/src/DCList.cc.o -c /home/china/xxx/音乐播放器/src/DCList.cc

CMakeFiles/video.dir/src/DCList.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/video.dir/src/DCList.cc.i"
	/usr/local/arm/5.4.0/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/china/xxx/音乐播放器/src/DCList.cc > CMakeFiles/video.dir/src/DCList.cc.i

CMakeFiles/video.dir/src/DCList.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/video.dir/src/DCList.cc.s"
	/usr/local/arm/5.4.0/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/china/xxx/音乐播放器/src/DCList.cc -o CMakeFiles/video.dir/src/DCList.cc.s

CMakeFiles/video.dir/src/DCList.cc.o.requires:

.PHONY : CMakeFiles/video.dir/src/DCList.cc.o.requires

CMakeFiles/video.dir/src/DCList.cc.o.provides: CMakeFiles/video.dir/src/DCList.cc.o.requires
	$(MAKE) -f CMakeFiles/video.dir/build.make CMakeFiles/video.dir/src/DCList.cc.o.provides.build
.PHONY : CMakeFiles/video.dir/src/DCList.cc.o.provides

CMakeFiles/video.dir/src/DCList.cc.o.provides.build: CMakeFiles/video.dir/src/DCList.cc.o


CMakeFiles/video.dir/src/lcd.cc.o: CMakeFiles/video.dir/flags.make
CMakeFiles/video.dir/src/lcd.cc.o: ../src/lcd.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/china/xxx/音乐播放器/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/video.dir/src/lcd.cc.o"
	/usr/local/arm/5.4.0/usr/bin/arm-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/video.dir/src/lcd.cc.o -c /home/china/xxx/音乐播放器/src/lcd.cc

CMakeFiles/video.dir/src/lcd.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/video.dir/src/lcd.cc.i"
	/usr/local/arm/5.4.0/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/china/xxx/音乐播放器/src/lcd.cc > CMakeFiles/video.dir/src/lcd.cc.i

CMakeFiles/video.dir/src/lcd.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/video.dir/src/lcd.cc.s"
	/usr/local/arm/5.4.0/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/china/xxx/音乐播放器/src/lcd.cc -o CMakeFiles/video.dir/src/lcd.cc.s

CMakeFiles/video.dir/src/lcd.cc.o.requires:

.PHONY : CMakeFiles/video.dir/src/lcd.cc.o.requires

CMakeFiles/video.dir/src/lcd.cc.o.provides: CMakeFiles/video.dir/src/lcd.cc.o.requires
	$(MAKE) -f CMakeFiles/video.dir/build.make CMakeFiles/video.dir/src/lcd.cc.o.provides.build
.PHONY : CMakeFiles/video.dir/src/lcd.cc.o.provides

CMakeFiles/video.dir/src/lcd.cc.o.provides.build: CMakeFiles/video.dir/src/lcd.cc.o


CMakeFiles/video.dir/src/ts.cc.o: CMakeFiles/video.dir/flags.make
CMakeFiles/video.dir/src/ts.cc.o: ../src/ts.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/china/xxx/音乐播放器/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/video.dir/src/ts.cc.o"
	/usr/local/arm/5.4.0/usr/bin/arm-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/video.dir/src/ts.cc.o -c /home/china/xxx/音乐播放器/src/ts.cc

CMakeFiles/video.dir/src/ts.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/video.dir/src/ts.cc.i"
	/usr/local/arm/5.4.0/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/china/xxx/音乐播放器/src/ts.cc > CMakeFiles/video.dir/src/ts.cc.i

CMakeFiles/video.dir/src/ts.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/video.dir/src/ts.cc.s"
	/usr/local/arm/5.4.0/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/china/xxx/音乐播放器/src/ts.cc -o CMakeFiles/video.dir/src/ts.cc.s

CMakeFiles/video.dir/src/ts.cc.o.requires:

.PHONY : CMakeFiles/video.dir/src/ts.cc.o.requires

CMakeFiles/video.dir/src/ts.cc.o.provides: CMakeFiles/video.dir/src/ts.cc.o.requires
	$(MAKE) -f CMakeFiles/video.dir/build.make CMakeFiles/video.dir/src/ts.cc.o.provides.build
.PHONY : CMakeFiles/video.dir/src/ts.cc.o.provides

CMakeFiles/video.dir/src/ts.cc.o.provides.build: CMakeFiles/video.dir/src/ts.cc.o


# Object files for target video
video_OBJECTS = \
"CMakeFiles/video.dir/main.cc.o" \
"CMakeFiles/video.dir/src/mplayer.cc.o" \
"CMakeFiles/video.dir/src/DCList.cc.o" \
"CMakeFiles/video.dir/src/lcd.cc.o" \
"CMakeFiles/video.dir/src/ts.cc.o"

# External object files for target video
video_EXTERNAL_OBJECTS =

video: CMakeFiles/video.dir/main.cc.o
video: CMakeFiles/video.dir/src/mplayer.cc.o
video: CMakeFiles/video.dir/src/DCList.cc.o
video: CMakeFiles/video.dir/src/lcd.cc.o
video: CMakeFiles/video.dir/src/ts.cc.o
video: CMakeFiles/video.dir/build.make
video: /home/china/arm-jpeg/lib/libjpeg.so
video: CMakeFiles/video.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/china/xxx/音乐播放器/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable video"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/video.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/video.dir/build: video

.PHONY : CMakeFiles/video.dir/build

CMakeFiles/video.dir/requires: CMakeFiles/video.dir/main.cc.o.requires
CMakeFiles/video.dir/requires: CMakeFiles/video.dir/src/mplayer.cc.o.requires
CMakeFiles/video.dir/requires: CMakeFiles/video.dir/src/DCList.cc.o.requires
CMakeFiles/video.dir/requires: CMakeFiles/video.dir/src/lcd.cc.o.requires
CMakeFiles/video.dir/requires: CMakeFiles/video.dir/src/ts.cc.o.requires

.PHONY : CMakeFiles/video.dir/requires

CMakeFiles/video.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/video.dir/cmake_clean.cmake
.PHONY : CMakeFiles/video.dir/clean

CMakeFiles/video.dir/depend:
	cd /home/china/xxx/音乐播放器/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/china/xxx/音乐播放器 /home/china/xxx/音乐播放器 /home/china/xxx/音乐播放器/build /home/china/xxx/音乐播放器/build /home/china/xxx/音乐播放器/build/CMakeFiles/video.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/video.dir/depend

