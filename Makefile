all: main.c
	gcc main.c configread.c metaread.c -o Sim01

clean:
	rm -rf ./Sim01
