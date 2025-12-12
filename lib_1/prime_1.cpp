#include "prime.h"

// Проверить делимость текущего числа на все предыдущие числа
int PrimeCount(int A, int B){
    if (A > B) return 0;
    
    int count = 0;
    for(int i = A; i <= B; i++){
        if (i <= 1) continue;  
        
        bool isPrime = true;
        for(int j = 2; j * j <= i; j++){
            if (i % j == 0){
                isPrime = false;
                break;
            }    
        } 
        
        if (isPrime) count++;      
    }
    return count; 
}