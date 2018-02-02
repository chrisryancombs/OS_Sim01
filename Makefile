all: main.c
	gcc main.c configread.c metaread.c utilities.c -o Sim01

clean:
	rm -rf ./Sim01
