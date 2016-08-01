CC = gcc
CXX = g++
CXXFLAGS = -O3 -DNDEBUG -std=c++11
CFLAGS = -O3 -DNDEBUG

all: pi_xs128 pi_xs1024 pi_gsl_mersenne pi_cpp11 pi_well1024

pi_xs128: pi_xs128.c
	$(CC) $(CFLAGS) pi_xs128.c -o pi_xs128 -lrandamu -lm

pi_xs1024: pi_xs1024.c
	$(CC) $(CFLAGS) pi_xs1024.c -o pi_xs1024 -lrandamu -lm

pi_well1024: pi_well1024.c
	$(CC) $(CFLAGS) pi_well1024.c -o pi_well1024 -lrandamu -lm

pi_gsl_mersenne: pi_gsl_mersenne.c
	$(CC) $(CFLAGS) pi_gsl_mersenne.c -o pi_gsl_mersenne -lgsl -lgslcblas -lm

pi_cpp11: pi_cpp11.cc
	$(CXX) $(CXXFLAGS) pi_cpp11.cc -o pi_cpp11

clean:
	rm pi_gsl_mersenne pi_xs128 pi_xs1024 pi_cpp11 pi_well1024
