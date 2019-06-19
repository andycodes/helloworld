mytest: radix-tree.o test.o                                                                                                
	gcc -Wall -fno-builtin $^ -o $@
radix-tree.o: radix-tree.c
	gcc -c $^ -o $@
test.c: test.o
	gcc -c $^ -o $@

clean:
	rm radix-tree.o test.o mytest