#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>

unsigned char array[256 * 4096];
int main(int argc, char** argv) {
    int junk = 0;
    register uint64_t time1, time2;
    register uint64_t addr;
    volatile unsigned char* ptr;
    int k = 0;
    
    // The attacker has to ensure the memory they want to read is not cached
    for (int i = 0; i < 256; i++) {
        array[i * 4096] = 1;
    }

    // Reading a byte from the secret data
    addr = (uint64_t)(argv[1]);
    ptr = (volatile unsigned char*)addr;
    junk = *ptr;

    // Measure time taken to access array elements
    for (int i = 0; i < 256; i++) {
        time1 = __rdtscp(&junk);
        junk = array[i * 4096];
        time2 = __rdtscp(&junk) - time1;
        printf("Time for array[%d * 4096]: %lu\n", i, time2);
    }

    return 0;
}