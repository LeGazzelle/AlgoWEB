# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /opt/JetBrains/clion-2016.2.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/JetBrains/clion-2016.2.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AlgoWEB.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AlgoWEB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AlgoWEB.dir/flags.make

CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.o: CMakeFiles/AlgoWEB.dir/flags.make
CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.o: ../src/test/AlgoWEB.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.o -c /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/test/AlgoWEB.cpp

CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/test/AlgoWEB.cpp > CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.i

CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/test/AlgoWEB.cpp -o CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.s

CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.o.requires:

.PHONY : CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.o.requires

CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.o.provides: CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.o.requires
	$(MAKE) -f CMakeFiles/AlgoWEB.dir/build.make CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.o.provides.build
.PHONY : CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.o.provides

CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.o.provides.build: CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.o


CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.o: CMakeFiles/AlgoWEB.dir/flags.make
CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.o: ../src/FileIO/GraphIO.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.o -c /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/FileIO/GraphIO.cpp

CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/FileIO/GraphIO.cpp > CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.i

CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/FileIO/GraphIO.cpp -o CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.s

CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.o.requires:

.PHONY : CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.o.requires

CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.o.provides: CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.o.requires
	$(MAKE) -f CMakeFiles/AlgoWEB.dir/build.make CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.o.provides.build
.PHONY : CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.o.provides

CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.o.provides.build: CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.o


CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.o: CMakeFiles/AlgoWEB.dir/flags.make
CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.o: ../src/Graphs/FastGraphs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.o -c /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/Graphs/FastGraphs.cpp

CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/Graphs/FastGraphs.cpp > CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.i

CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/Graphs/FastGraphs.cpp -o CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.s

CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.o.requires:

.PHONY : CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.o.requires

CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.o.provides: CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.o.requires
	$(MAKE) -f CMakeFiles/AlgoWEB.dir/build.make CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.o.provides.build
.PHONY : CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.o.provides

CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.o.provides.build: CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.o


CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.o: CMakeFiles/AlgoWEB.dir/flags.make
CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.o: ../src/Graphs/VertexConverter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.o -c /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/Graphs/VertexConverter.cpp

CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/Graphs/VertexConverter.cpp > CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.i

CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/Graphs/VertexConverter.cpp -o CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.s

CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.o.requires:

.PHONY : CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.o.requires

CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.o.provides: CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.o.requires
	$(MAKE) -f CMakeFiles/AlgoWEB.dir/build.make CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.o.provides.build
.PHONY : CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.o.provides

CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.o.provides.build: CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.o


CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.o: CMakeFiles/AlgoWEB.dir/flags.make
CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.o: ../src/BFS/BFS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.o -c /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/BFS/BFS.cpp

CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/BFS/BFS.cpp > CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.i

CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/BFS/BFS.cpp -o CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.s

CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.o.requires:

.PHONY : CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.o.requires

CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.o.provides: CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.o.requires
	$(MAKE) -f CMakeFiles/AlgoWEB.dir/build.make CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.o.provides.build
.PHONY : CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.o.provides

CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.o.provides.build: CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.o


CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.o: CMakeFiles/AlgoWEB.dir/flags.make
CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.o: ../src/MSTWeight/MSTWCompare.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.o -c /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/MSTWeight/MSTWCompare.cpp

CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/MSTWeight/MSTWCompare.cpp > CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.i

CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/src/MSTWeight/MSTWCompare.cpp -o CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.s

CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.o.requires:

.PHONY : CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.o.requires

CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.o.provides: CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.o.requires
	$(MAKE) -f CMakeFiles/AlgoWEB.dir/build.make CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.o.provides.build
.PHONY : CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.o.provides

CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.o.provides.build: CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.o


# Object files for target AlgoWEB
AlgoWEB_OBJECTS = \
"CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.o" \
"CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.o" \
"CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.o" \
"CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.o" \
"CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.o" \
"CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.o"

# External object files for target AlgoWEB
AlgoWEB_EXTERNAL_OBJECTS =

AlgoWEB: CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.o
AlgoWEB: CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.o
AlgoWEB: CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.o
AlgoWEB: CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.o
AlgoWEB: CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.o
AlgoWEB: CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.o
AlgoWEB: CMakeFiles/AlgoWEB.dir/build.make
AlgoWEB: libboost_graph.a
AlgoWEB: libboost_regex.a
AlgoWEB: CMakeFiles/AlgoWEB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable AlgoWEB"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AlgoWEB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AlgoWEB.dir/build: AlgoWEB

.PHONY : CMakeFiles/AlgoWEB.dir/build

CMakeFiles/AlgoWEB.dir/requires: CMakeFiles/AlgoWEB.dir/src/test/AlgoWEB.cpp.o.requires
CMakeFiles/AlgoWEB.dir/requires: CMakeFiles/AlgoWEB.dir/src/FileIO/GraphIO.cpp.o.requires
CMakeFiles/AlgoWEB.dir/requires: CMakeFiles/AlgoWEB.dir/src/Graphs/FastGraphs.cpp.o.requires
CMakeFiles/AlgoWEB.dir/requires: CMakeFiles/AlgoWEB.dir/src/Graphs/VertexConverter.cpp.o.requires
CMakeFiles/AlgoWEB.dir/requires: CMakeFiles/AlgoWEB.dir/src/BFS/BFS.cpp.o.requires
CMakeFiles/AlgoWEB.dir/requires: CMakeFiles/AlgoWEB.dir/src/MSTWeight/MSTWCompare.cpp.o.requires

.PHONY : CMakeFiles/AlgoWEB.dir/requires

CMakeFiles/AlgoWEB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AlgoWEB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AlgoWEB.dir/clean

CMakeFiles/AlgoWEB.dir/depend:
	cd /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/cmake-build-debug /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/cmake-build-debug /home/gabriel/Workspaces/JetBrainWorkspace/CLion/AlgoWEB/cmake-build-debug/CMakeFiles/AlgoWEB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AlgoWEB.dir/depend
