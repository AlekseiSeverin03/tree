
all:
	gcc -c file_operations.cpp graph_dump.cpp tree.cpp main.cpp
	gcc    file_operations.o   graph_dump.o   tree.o   main.o  -o main
	./main
	dot dump.dot -T pdf -o dump.pdf
	open dump.pdf

	rm *.o
