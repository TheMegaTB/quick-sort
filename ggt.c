#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN(a,b) ((((a)-(b))&0x80000000) >> 31)? (a) : (b)
#define MAX(a,b) ((((a)-(b))&0x80000000) >> 31)? (b) : (a)

int ggt(int a, int b) {
    int min = MIN(a,b);
    int max = MAX(a,b);
    if (min == 0) return max;
    return ggt(min, max - min);
}

int ggt2(int a, int b) {
    if (a == 0) { return b; }
    else if (a <= b) { return ggt2(a, b - a); }
    else { return ggt2(b, a); }
}

void main(int argc, const char * argv[]) {
    clock_t begin, end;
    int repetitions = 100000;
    double time_spent;

    begin = clock();
    for (int i = 0; i < repetitions; i++) {
        ggt(100, 200);
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
    printf("MINMAX: %f\n", time_spent);

    begin = clock();
    for (int i = 0; i < repetitions; i++) {
        ggt2(100, 200);
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
    printf("IF: %f\n", time_spent);
}