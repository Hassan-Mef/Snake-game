all: ./a.out

compRun:
	g++ -std=c++11 Snake.cpp  -o r.out

test: clean compTest; ./a.out

run: clean compRun; ./r.out

clean:
	rm -f *.out