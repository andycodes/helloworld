

make -f makefile_armv8m board=mps3-an547 gdbserver
make -f makefile_armv8m board=mps3-an547 gdb


make -f makefile_armv8m board=mps2-an505 gdbserver
make -f makefile_armv8m board=mps2-an505 gdb


python build.py netp

make -f makefile_armv7m board=netduinoplus2 gdbserver
make -f makefile_armv7m board=netduinoplus2 gdb



cmake .. -DCUR_PLAT=mps3-an547