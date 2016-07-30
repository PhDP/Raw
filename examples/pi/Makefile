CC = gcc
CFLAGS = -O3 -DNDEBUG

all: pi_xs1024 pi_well1024 pi_gsl_mersenne

pi_xs1024: pi_xs1024.c
	$(CC) $(CFLAGS) pi_xs1024.c -o pi_xs1024 -lrandamu -lm

pi_well1024: pi_well1024.c
	$(CC) $(CFLAGS) pi_well1024.c -o pi_well1024 -lrandamu -lm

pi_gsl_mersenne: pi_gsl_mersenne.c
	$(CC) $(CFLAGS) pi_gsl_mersenne.c -o pi_gsl_mersenne -lgsl -lgslcblas -lm

clean:
	rm pi_gsl_mersenne pi_well1024 pi_xs1024
