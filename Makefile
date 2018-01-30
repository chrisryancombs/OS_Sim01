all: main.c
	gcc main.c configread.c -o Sim01

clean:
	rm -rf ./Sim01
