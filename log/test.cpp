#include <iostream>
#include "Logging.h"
int main() {

    clock_t start = clock();
    // Logger *log = new Logger("/ServerLog", 100);
    for(int i = 1; i <= 1e6; i++) {
        LOG << i << "log info error";
    }
    clock_t end = clock();
    printf("time: %f s\n", ((double)(end - start)) / CLOCKS_PER_SEC );
    return 0;
}