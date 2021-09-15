%.o:%.c
	arm-linux-gcc -mthumb -c -o $@ $^ -fno-builtin
	
%.o:%.S
	arm-linux-gcc -c -o $@ $^