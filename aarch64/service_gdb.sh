port_id=$1
echo ${port_id}
qemu-system-aarch64 -M virt -cpu cortex-a710 -nographic -kernel kernel.elf -S -gdb tcp::${port_id}
