TODO: writeme

# compilation commands
# (we should probably setup build automation softwares i.e.make/cmake to simply the build process)
# for now, to create the datasets D1 to D7, run
~/.../team-25/hw3$ g++ -I./include ./src/CreateFiles.cpp -o create_file
# and run with
~/.../team-25/hw3$ ./create_file

# TODO:
# (1) CreateFiles.cpp
# Since we are creating multiple files for D1 to D7, we should have the files created in directory:
~/.../team-25/hw3/src/data/D1
~/.../team-25/hw3/src/data/D2
~/.../team-25/hw3/src/data/D3
... etc

# (2) Workload.cpp
# which would run accessing benchmarks to the files in D1 to D7.
# 