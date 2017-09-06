CC=gcc
FILES=Caller.c CreateArray.c
OUT_EXE = Caller.out
build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)
clean:
	rm -f *.o $(OUT_EXE)
