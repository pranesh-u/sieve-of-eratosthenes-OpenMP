#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

int sieve_of_eratosthenes(int limit) { // 100
    omp_set_num_threads(omp_get_num_procs());
    const int limitSqrt = (int)sqrt((double)limit); // limitsqrt = 10
    int memorySize = (limit - 1) / 2; // condisering only odd numbers
    bool *isPrime = (bool *)malloc((memorySize + 1) * sizeof(bool));
#pragma omp parallel for
    for (int i = 0; i <= memorySize; i++) {
        isPrime[i] = true;
    }

#pragma omp parallel for schedule(dynamic)
    for(int i = 3;i <= limitSqrt;i++){
        if(isPrime[i/2]){
            for(int j = i*i;j <= limit;j += 2*i){
                isPrime[j/2] = false;
            }
        }
    }
    int found = limit >= 2 ? 1 : 0;
#pragma omp parallel for reduction(+:found)
    for(int i = 1;i <= memorySize;i++){
        if(isPrime[i]){
            found++;
        }
    }
        
    free(isPrime);
    return found;
}


int main(int argc, char const *argv[]) {
    FILE *sfptr;
    sfptr = fopen("limit.txt", "r");
    if (sfptr == NULL) {
        printf("Limit file not found\n");
        exit(1);
    }


    int limit;
    fscanf(sfptr, "%d", &limit);
    fclose(sfptr);

    clock_t start = clock();
    int found = sieve_of_eratosthenes(limit);
    clock_t end = clock();

    double time_taken = (double)((end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for parallel approach: %f seconds\n", time_taken);
    
    return 0;
}
