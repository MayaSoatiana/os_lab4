#include <cmath>
#include <vector>
#include "prime.h"

int PrimeCount(int A, int B){
    std::vector<bool> prime(B + 1, true);
    for (int p = 2; p * p <= B; p++) {
        if (prime[p] == true) {
            for (int i = p * p; i <= B; i += p)
                prime[i] = false;
        }
    }
    
    int count;
    for (int p = A; p <= B; p++){
        if (prime[p]){ 
            count ++;
        }
    }  
    return count; 
}