OBJ = $(wildcard *.c)

OBJ = $(patsubst %.c, %.o, $(wildcard *.c))

final.exe : $(OBJ)
	gcc -o $@ $^

clean: 
	rm *.o	

