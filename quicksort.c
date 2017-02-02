#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int T;

int limited_rand(int low, int high) {
   return rand() % (high - low + 1) + low;
}

void print_array(T* data, int len) {
    for(int i = 0; i < len; i++) { printf("%d ", data[i]); }
    printf("\n");
}

void swap(T* data, int from, int to) {
    T tmp = data[to];
    data[to] = data[from];
    data[from] = tmp;
}

void quick_sort(T* data, int len) {
    int ref = data[0]; // same as middle
    int left = 0; //i
    int right = len; //j

    if (len <= 1)
        return;

    for (;;) {
        while (data[++left] < ref && left < len) {}
        while (data[--right] > ref) {}
        if (left >= right) break;
        swap(data, left, right);
    }

    swap(data, 0, left-1);
    quick_sort(data, left-1);
    quick_sort(data+left, len - left);
}

void main(int argc, const char * argv[]) {
	int i;
	int len = 100000;
	int data[len];
    clock_t begin, end;
    double time_spent;
	srand(time(NULL));

	for (i = 0; i < len; i++) {
		data[i] = limited_rand(0, len);
	}

	printf("Hello world!\n");

//    print_array(data, len);

    begin = clock();
    quick_sort(data, len);
    end = clock();


    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time taken: %fms\n", time_spent*1000);
    printf("Elements per second: %f\n", len / time_spent);
//    print_array(data, len);
}
