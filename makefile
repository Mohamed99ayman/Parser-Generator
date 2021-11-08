CC=g++
CFLAGS=-std=c++11 -I.
OBJ = main.o left.o First.o Follow.o Parse_table.o Panic_mode.o

part2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
clean:
	rm *.o