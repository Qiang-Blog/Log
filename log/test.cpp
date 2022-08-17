#include <iostream>
#include "Logging.h"
#define LOG_NUM 1000000
int main() {

    clock_t start = clock();
    for(int i = 1; i <= LOG_NUM; i++) {
        LOG << i << "this is log !!!!";
    }
    clock_t end = clock();
    printf("time: %f s\n", ((double)(end - start)) / CLOCKS_PER_SEC );
    return 0;
}