#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

typedef int T;

int threads = 0;

struct data_array {
    int length;
    T *data;
};

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

void *quick_sort_threaded(void* arg) {
    struct data_array *data_arr = arg;
    int len = data_arr -> length;
    T* data = data_arr -> data;
    pthread_t tid[2];

    int ref = data[0]; // same as middle
    int left = 0; //i
    int right = len; //j

    if (len <= 1) { pthread_exit(NULL); return NULL; }

    for (;;) {
        while (data[++left] < ref && left < len) {}
        while (data[--right] > ref) {}
        if (left >= right) break;
        swap(data, left, right);
    }

    swap(data, 0, left-1);

    if (threads <= 4) {
        threads += 2;
        struct data_array args1;
        args1.length = left-1;
        args1.data = data;
        struct data_array args2;
        args2.length = len-left;
        args2.data = data+left;

        pthread_create(&(tid[0]), NULL, (void*) quick_sort_threaded, (void *)&args1);
        pthread_create(&(tid[1]), NULL, (void*) quick_sort_threaded, (void *)&args2);

        pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);
    } else {
        quick_sort(data, left-1);
        quick_sort(data+left, len-left);
    }

    pthread_exit(NULL);
}

void main(int argc, const char * argv[]) {
	int i;
	int len = 100000;
    int repetitions = 10;
	int data[len];
    pthread_t tid[2];
    struct data_array args;
    clock_t begin, end;
    double times_spent[repetitions], time_spent;
	srand(time(NULL));

	for (i = 0; i < len; i++) {
		data[i] = limited_rand(0, len);
	}

	printf("Hello world!\n");

//    print_array(data, len);

    args.data = data;
    args.length = len;

    for (i = 0; i < repetitions; i++) {
        begin = clock();
        pthread_create(&(tid[0]), NULL, (void*) quick_sort_threaded, (void *)&args);
        pthread_join(tid[0], NULL);
        end = clock();
        times_spent[i] = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
    }

    time_spent = 0;
    for (i = 0; i < repetitions; i++) {
        printf("%f\n", times_spent[i]);
        time_spent += times_spent[i];
    }
    printf("%f\n", time_spent);
    time_spent = time_spent / repetitions;

    printf("Time taken: %fms\n", time_spent*1000);
    printf("Elements per second: %f\n", len / time_spent);
//    print_array(data, len);
}
