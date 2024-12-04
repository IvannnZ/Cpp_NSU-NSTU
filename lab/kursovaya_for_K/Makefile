File = main.cpp Polynom.cpp
OutputFile = main

CC = g++

RunComand = ./

all: Compile Run Clear

Compile:
	$(CC) $(File) -o $(OutputFile)

Run: Compile
	$(RunComand)$(OutputFile)


Clear:
	rm $(OutputFile)

Prompt_data:
	echo "Polynom.h:"
	cat Polynom.h
	echo "Polynom.cpp:"
	cat Polynom.cpp
	echo "main.cpp:"
	cat main.cpp

