#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int sieve_of_eratosthenes(int limit){
    int memorySize = (limit - 1) / 2; // Considering all odd numbers are prime
    bool *isPrime = (bool *)malloc((memorySize + 1) * sizeof(bool)); // Allocate memory
    for (int i = 0; i <= memorySize; i++){
        isPrime[i] = true; //assuming it as a prime
    }

    isPrime[0] = false; 

    // Mark non-prime numbers
    for (int i = 3; i * i <= limit; i += 2){ 
        if (isPrime[i / 2]){
            for (int j = i * i; j <= limit; j += 2 * i){
                isPrime[j / 2] = false; // Mark multiples of i
            }
        }
    }
    int found = limit >= 2 ? 1 : 0;
    for (int i = 1; i <= memorySize; i++){
        if (isPrime[i])
        {
            found++;
        }
    }

    free(isPrime); // Free allocated memory
    return found;
}

int main(int argc, char const *argv[])
{
    FILE *sfptr;
    sfptr = fopen("limit.txt", "r");
    if (sfptr == NULL)
    {
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
    printf("Time taken for sequential approach: %f seconds\n", time_taken);

    return 0;
}
