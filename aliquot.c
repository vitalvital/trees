#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// #include <malloc.h>
#include <limits.h>
#include <time.h>
// #include <include/gmp.h>

#define BASE 10

static unsigned long *Primes;
struct Number {
    unsigned long long a;                //number
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

void printNumber(struct Number *N) {
    int i;

    printf("\n%lld = ", N->a);
    if (N->a == 1 || N->a == 0) {
        printf("\b\b ");
        return;
    }

    for (i = 0; i <= N->lastPrimeIndex; i++) {
        printf("%lld", N->factors[i]);
        if (N->powers[i] > 1)
            printf("^%d*", N->powers[i]);
        else
            printf("*");
    }
    printf("\b ");
}

void generatePrimes(unsigned int limit) {
    time_t t1, t2;
    time(&t1);
    char *yn;        //prime - not prime flag
    int pix;        //number of primes
    unsigned long long i;
    unsigned long long k;
    unsigned long long prime;

    limit = (limit + 1) / 2;
    yn = (char *) calloc(limit, sizeof(int));
    pix = 1;
    for (i = 0; i < limit; i++)
        yn[i] = '1';

    for (i = 0; i < limit; i++)
        if (yn[i] == '1') {
            prime = i + i + 3;
            for (k = i + prime; k < limit; k += prime)
                yn[k] = '0';
            pix++;
        }

    Primes = (unsigned long *) calloc(pix + 2, sizeof(unsigned long));

    Primes[0] = 2;
    pix = 1;
    for (i = 0; i < limit; i++)
        if (yn[i] == '1') Primes[pix++] = i + i + 3;
    Primes[pix] = 0;
    time(&t2);
    printf(" Generated %d primes in %ld seconds\n", pix, t2 - t1);
}

void factor(struct Number *N) {
    int i = 0;
    int ii = 0;
    unsigned long long number;
    double limit;

    number = N->a;
    if (number == 1) {
        N->lastPrimeIndex = 0;
        return;
    }
    limit = (unsigned long) sqrt((double) number); // NOLINT(cppcoreguidelines-narrowing-conversions)

    while (Primes[i] <= limit + 2) {    // NOLINT(cppcoreguidelines-narrowing-conversions)
        if (number % Primes[i] == 0) {
            N->factors[ii] = Primes[i];
            N->powers[ii] = 1;
            number /= Primes[i];
            limit = sqrt((double) number);
            ii++;
        }
        while (number % Primes[i] == 0) {
            N->powers[ii - 1]++;
            number /= Primes[i];
            limit = sqrt((double) number);
        }

        i++;
    }
    if (number != 1) {
        N->factors[ii] = number;
        N->powers[ii] = 1;
        N->lastPrimeIndex = ii;
    } else
        N->lastPrimeIndex = ii - 1;
}


void perfect(void) {
    struct Number N;
    int i;
    int power;
    unsigned long long subproduct;
    //unsigned long long result;
    char ch[20];
    unsigned long long product = 1;
    char* input_end_ptr;


    printf("\ninput number n= ");
    scanf("%s", (char *) (&N.ch));
    //getchar();
    //fflush(stdin);
    if (strlen(N.ch) > 19) {
        printf("\nThe number is too big\n");
        return;
    }
//	N.a = _atoi64(N.ch);
//    N.a = atoll(N.ch);
    N.a = strtoll(N.ch, &input_end_ptr, BASE);

//    N.is_factored = 0;
    for (i = 0; i < 50; i++)
        N.factors[i] = 1;

    for (i = 0; i < 50; i++)
        N.powers[i] = 1;

    factor(&N);
    printNumber(&N);

    i = 0;

    while (N.factors[i] != 1) {
        subproduct = N.factors[i];
        for (power = 0; power < N.powers[i]; power++) {
            //			    if(_UI64_MAX/subproduct > N.factors[i])	// overflow protection
            if (ULONG_LONG_MAX / subproduct > N.factors[i])    // overflow protection
                subproduct *= N.factors[i];
            else {
                printf("\nOverflow 1");
                return;                            /* DONE (V#1#): Write a function for an alternative way of calculating
				                perfectness without triggering overflow 1 */
            }
        }

        subproduct = (subproduct - 1) / (N.factors[i] - 1);

        // if(_UI64_MAX/product > subproduct)
        if (ULONG_LONG_MAX / product > subproduct)    //overflow protection
            product *= subproduct;
        else {
            printf("\nOverflow 2");
            return;
        }

        i++;
    }
    product = product - N.a;

    // _ui64toa( product, ch, 10);
    sprintf(ch, "%lld", product);   // TODO - refactor 'ch' misnomer
    printf("\n%s", ch);


}

//////////////////////////////////////////////////////////////////////////////////
void destiny(void) {
    struct Number N;
    int i, j = 0;
    int power;
    unsigned long long subproduct;
    char ch;
    unsigned long long product;
    char* input_end_ptr;

    printf("\ninput number n= ");
    scanf("%s", N.ch);
    //getchar();
    fflush(stdin);
    if (strlen(N.ch) > 19) {
        printf("\nThe number is too big\n");
        return;
    }
//    N.a = atoll(N.ch);
    N.a = strtoll(N.ch, &input_end_ptr, BASE);

    while (N.a != 1) {
        // _i64toa(N.a, N.ch, 10);
        sprintf(N.ch, "%lld", N.a);
//        N.is_factored = 0;
        for (i = 0; i < 50; i++)
            N.factors[i] = 1;

        for (i = 0; i < 50; i++)
            N.powers[i] = 1;

        factor(&N);
        printNumber(&N);
        if (strlen(N.ch) > 18) {
            printf("\nThe number is getting too big. Can no longer guarantee accuracy\n");
            return;
        }
        product = 1;
        if (ULONG_LONG_MAX / N.factors[N.lastPrimeIndex] > N.factors[N.lastPrimeIndex]) {
            for (i = 0; i <= N.lastPrimeIndex; i++) {
                subproduct = N.factors[i];
                for (power = 0; power < N.powers[i]; power++)
                    if (ULONG_LONG_MAX / subproduct > N.factors[i])    //overflow protection
                        subproduct *= N.factors[i];
                    else {
                        printf("\nOverflow 2");
                        return;
                    }

                subproduct = (subproduct - 1) / (N.factors[i] - 1);
                if (ULONG_LONG_MAX / product > subproduct)    //overflow protection
                    product *= subproduct;
                else {
                    printf("\nOverflow 3");
                    return;
                }
            }
            N.a = product - N.a;
        } else {
            printf("\nOverflow 1");
            unsigned long long sum = 1;
            unsigned long long factor1;
            unsigned long long factor2;
            unsigned long long factor3;
            unsigned long long factor4;
            unsigned long long factor5;
            unsigned long long factor6;
            int i1, i2, i3, i4, i5, i6, p1, p2, p3, p4, p5, p6;
            for (i1 = 0; i1 <= N.lastPrimeIndex; i1++) {
                factor1 = 1;
                for (p1 = 1; p1 <= N.powers[i1]; p1++) {
                    factor1 *= N.factors[i1];
                    sum += factor1;
                    for (i2 = i1 + 1; i2 <= N.lastPrimeIndex; i2++) {
                        factor2 = 1;
                        for (p2 = 1; p2 <= N.powers[i2]; p2++) {
                            factor2 *= N.factors[i2];
                            sum += factor1 * factor2;
                            for (i3 = i2 + 1; i3 <= N.lastPrimeIndex; i3++) {
                                factor3 = 1;
                                for (p3 = 1; p3 <= N.powers[i3]; p3++) {
                                    factor3 *= N.factors[i3];
                                    sum += factor1 * factor2 * factor3;
                                    for (i4 = i3 + 1; i4 <= N.lastPrimeIndex; i4++) {
                                        factor4 = 1;
                                        for (p4 = 1; p4 <= N.powers[i4]; p4++) {
                                            factor4 *= N.factors[i4];
                                            sum += factor1 * factor2 * factor3 * factor4;
                                            for (i5 = i4 + 1; i5 <= N.lastPrimeIndex; i5++) {
                                                factor5 = 1;
                                                for (p5 = 1; p5 <= N.powers[i5]; p5++) {
                                                    factor5 *= N.factors[i5];
                                                    sum += factor1 * factor2 * factor3 * factor4 * factor5;
                                                    for (i6 = i5 + 1; i6 <= N.lastPrimeIndex; i6++) {
                                                        factor6 = 1;
                                                        for (p6 = 1; p6 <= N.powers[i6]; p6++) {
                                                            factor6 *= N.factors[i6];
                                                            sum += factor1 * factor2 * factor3 * factor4 * factor5 *
                                                                   factor6;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                }

            }
            N.a = sum - N.a;
        }


        j++;

        if (j > 100) {
            printf(" Press C to continue ");
            ch = getchar(); // NOLINT(cppcoreguidelines-narrowing-conversions)
            if (ch == 'c') {
                j = 0;
                fflush(stdin);
                continue;
            } else
                return;
        }
    }


}

void inverse(void) {
    printf("\n\tInverse perfectness\n\n");
}

////////////////////////////////////////////////////////////////////////////////
/// Test function for running various tests
/// Currently testing prime generation optimizations
////////////////////////////////////////////////////////////////////////////////
void test(void) {
    struct Number N;
    int k;
    long cycle;
    int cyclesFound = 0;
    unsigned long long beginning;
    unsigned long long end;
    unsigned long long l;
    char string[20];
//    unsigned long long subproduct;
//    char ch;
//    unsigned long long product;
    time_t t1, t2;
    time(&t1);
    char* input_end_ptr;

    unsigned long long sum;
    unsigned long long factor1;
    unsigned long long factor2;
    unsigned long long factor3;
    unsigned long long factor4;
    unsigned long long factor5;
    unsigned long long factor6;
    unsigned long long factor7;
    unsigned long long factor8;
//    unsigned long long factor9;
    int i1, i2, i3, i4, i5, i6, i7, i8, p1, p2, p3, p4, p5, p6, p7, p8;


    printf("\ninput cycle = ");
    scanf("%s", string);
//    scanf("%d", &cycle);
    cycle = strtol(string, &input_end_ptr, BASE);

    printf("\ninput beginning = ");
//    beginning = atoll(string);
    scanf("%s", string);
    beginning = strtoll(string, &input_end_ptr, BASE);
    printf("\ninput end = ");
    scanf("%s", string);
//    end = atoll(string);
    end = strtoll(string, &input_end_ptr, BASE);

    struct Number *social;
    social = (struct Number *) calloc(cycle, sizeof(struct Number));

    for (l = beginning; l < end; l++) {
        N.a = l;
        // _i64toa( l, string, 10);
        // printf("Testing %s", string);
        // printf("\b/");

        for (k = 0; k < cycle; k++) {
            printf("\b\b%2d", k);
            factor(&N);
            if (N.a == 1)
                break;
            if (strlen(N.ch) > 18) {
                printf("\nThe number is getting too big. Can no longer guarantee accuracy\n");
                break;
            }
            // product = 1;
            sum = 1;
            for (i1 = 0; i1 <= N.lastPrimeIndex; i1++) {
                factor1 = 1;
                for (p1 = 1; p1 <= N.powers[i1]; p1++) {
                    factor1 *= N.factors[i1];
                    sum += factor1;
                    for (i2 = i1 + 1; i2 <= N.lastPrimeIndex; i2++) {
                        factor2 = 1;
                        for (p2 = 1; p2 <= N.powers[i2]; p2++) {
                            factor2 *= N.factors[i2];
                            sum += factor1 * factor2;
                            for (i3 = i2 + 1; i3 <= N.lastPrimeIndex; i3++) {
                                factor3 = 1;
                                for (p3 = 1; p3 <= N.powers[i3]; p3++) {
                                    factor3 *= N.factors[i3];
                                    sum += factor1 * factor2 * factor3;
                                    for (i4 = i3 + 1; i4 <= N.lastPrimeIndex; i4++) {
                                        factor4 = 1;
                                        for (p4 = 1; p4 <= N.powers[i4]; p4++) {
                                            factor4 *= N.factors[i4];
                                            sum += factor1 * factor2 * factor3 * factor4;
                                            for (i5 = i4 + 1; i5 <= N.lastPrimeIndex; i5++) {
                                                factor5 = 1;
                                                for (p5 = 1; p5 <= N.powers[i5]; p5++) {
                                                    factor5 *= N.factors[i5];
                                                    sum += factor1 * factor2 * factor3 * factor4 * factor5;
                                                    for (i6 = i5 + 1; i6 <= N.lastPrimeIndex; i6++) {
                                                        factor6 = 1;
                                                        for (p6 = 1; p6 <= N.powers[i6]; p6++) {
                                                            factor6 *= N.factors[i6];
                                                            sum += factor1 * factor2 * factor3 * factor4 * factor5 *
                                                                   factor6;
                                                            for (i7 = i6 + 1; i7 <= N.lastPrimeIndex; i7++) {
                                                                factor7 = 1;
                                                                for (p7 = 1; p7 <= N.powers[i7]; p7++) {
                                                                    factor7 *= N.factors[i7];
                                                                    sum += factor1 * factor2 * factor3 * factor4 *
                                                                           factor5 * factor6 * factor7;
                                                                    for (i8 = i7 + 1; i8 <= N.lastPrimeIndex; i8++) {
                                                                        factor8 = 1;
                                                                        for (p8 = 1; p8 <= N.powers[i8]; p8++) {
                                                                            factor8 *= N.factors[i8];
                                                                            sum += factor1 * factor2 * factor3 *
                                                                                   factor4 * factor5 * factor6 *
                                                                                   factor7 * factor8;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            N.a = sum - N.a;

            social[k] = N;
        }
        if (social[cycle - 1].a == l) {
            printf("\b");
            printf("\nCycle found:");
            cyclesFound++;
            int t;
            for (t = 0; t < cycle; t++)
                printNumber(&social[t]);
            printf("\n");
        }
    }
    time(&t2);
    printf(" Found %d cycles in %ld seconds\n", cyclesFound, t2 - t1);
}

///////////////////////////////////////////////////////////////////////////////
// Function for finding cycles
///////////////////////////////////////////////////////////////////////////////
void cycles(void) {
    char string[20];
    struct Number N;
    int i, k;
    long cycle;
    int cyclesFound = 0;
    unsigned long long beginning;

    unsigned long long end;
    unsigned long long l;
//    char string[20];
//    char ch1[20];
    int power;
    unsigned long long subproduct;
//    char ch;
    unsigned long long product;
    time_t t1, t2;
    time(&t1);
    char* input_end_ptr;

    printf("\ninput cycle = ");
//    scanf("%d", &cycle);
    scanf("%s", string);
    cycle = strtol(string, &input_end_ptr, BASE);

    printf("\ninput beginning = ");
//    beginning = atoll(string);
    scanf("%s", string);
    beginning = strtoll(string, &input_end_ptr, BASE);

    printf("\ninput end = ");
//    end = _atoi64(string);
//    scanf("%lld", &end);
    scanf("%s", string);
    end = strtoll(string, &input_end_ptr, BASE);
    struct Number *social;
    social = (struct Number *) calloc(cycle + 1, sizeof(struct Number));

    for (l = beginning; l < end; l++) {
        N.a = l;
        for (k = 0; k < cycle; k++) {
            printf("\b%d", k);
            factor(&N);

            if (N.a == 1)
                break;
            product = 1;
            /* TODO (V#1#): test time for different methods of calculating
                            perfectness */

            if (ULONG_LONG_MAX / N.factors[N.lastPrimeIndex] > N.factors[N.lastPrimeIndex]) {
                for (i = 0; i <= N.lastPrimeIndex; i++) {
                    subproduct = N.factors[i];
                    for (power = 0; power < N.powers[i]; power++)
                        if (ULONG_LONG_MAX / subproduct > N.factors[i])    //overflow protection
                            subproduct *= N.factors[i];
                        else {
                            printf("\nOverflow 1");
                            N.a = 1;
                            break;
                        }

                    subproduct = (subproduct - 1) / (N.factors[i] - 1);
                    if (ULONG_LONG_MAX / product > subproduct)    //overflow protection
                        product *= subproduct;
                    else {
                        printf("\nOverflow 2");
                        N.a = 1;
                        break;
                    }
                }
                N.a = product - N.a;
            }
            social[k] = N;
        }

        if (social[cycle - 1].a == l) {
            printf("\nCycle found:");
            cyclesFound++;
            int t;
            for (t = 0; t < cycle; t++)
                printNumber(&social[t]);
            printf("\b\n");
        }
    }
    time(&t2);
    printf(" Found %d primes in %ld seconds\n", cyclesFound, t2 - t1);
}


int main() {
    int ch;
    printf("\n\tGenerating Primes.");

    generatePrimes(INT_MAX / 16);


    printf("\nAliquot Calculator\n");


    do {
        printf("\n\tp : Perfectness\n");
        printf("\ti : Inverse perfectness\n");
        printf("\td : Destiny\n");
        printf("\tc : Cycles\n");
        printf("\tt : Test\n");
        printf("\tx : Exit\n");
        printf("\tEnter your choice: ");
        ch = getchar();
        //fflush(stdin);

        switch (ch) {
            case 'p':
                perfect();
                //fflush(stdin);
                break;
            case 'i':
                inverse();
                break;
            case 'd':
                destiny();
                //fflush(stdin);
                break;
            case 'c':
                cycles();
                //fflush(stdin);
                break;
            case 't':
                test();
                break;
            case 'x':
                break;
            default:
                printf("\n\tNo such choice\n\n");
                fflush(stdin);
                break;
        }
    } while (ch != 'x');
//    system("PAUSE");
    return 0;
}

