all: main.c
	gcc `pkg-config --cflags gtk+-3.0` -o main.out main.c `pkg-config --libs gtk+-3.0`

clean:
	$(RM) *.out
