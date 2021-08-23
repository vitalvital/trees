#ifndef TREES_ALIQUOT_H
#define TREES_ALIQUOT_H
#define BASE 10
#ifndef ULONG_LONG_MAX
#define ULONG_LONG_MAX ULLONG_MAX
#endif

static unsigned long *Primes;

struct Number {
    unsigned long long a;   // number
    char ch[20];            // number as a string
//    int is_factored;
    unsigned long long factors[50];
    int powers[50];
    int lastPrimeIndex;
};

void generatePrimes(unsigned int limit);

void inverse(void);

void factor(struct Number *N);

void perfect(void);

void printNumber(struct Number *N);

void destiny(void);

void cycles(void);

#endif // TREES_ALIQUOT_H
