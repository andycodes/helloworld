python build.py mps3-an547
make -f makefile_armv8m board=mps3-an547 qemu
make -f makefile_armv8m board=mps3-an547 gdbserver
make -f makefile_armv8m board=mps3-an547 gdb

python build.py mps2-an505
make -f makefile_armv8m board=mps2-an505 qemu
make -f makefile_armv8m board=mps2-an505 gdbserver
make -f makefile_armv8m board=mps2-an505 gdb


python build.py netp