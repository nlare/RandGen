all:
	g++ -fopenmp main.cpp -o randgen
clean:
	rm randgen
