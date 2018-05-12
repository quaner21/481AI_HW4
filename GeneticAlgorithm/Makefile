
CPP = g++ -std=c++11 -g -O -frounding-math -fsignaling-nans

all: genetic test

test: genetic_test
	./genetic_test

genetic: Genetic_algorithm.cpp
	${CPP} Genetic_algorithm.cpp -o genetic_test

headers: TrainingData.hh

clean:
	rm -f genetic_test
