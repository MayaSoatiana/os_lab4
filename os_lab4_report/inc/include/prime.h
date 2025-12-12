#pragma once

#if defined(_WIN32)
    #ifdef MATHLIB_EXPORTS
        #define PRIME_API __declspec(dllexport)
    #else
        #define PRIME_API __declspec(dllimport)
    #endif
#endif

// Подсчёт количества простых чисел на отрезке [A, B] (A, B - натуральные)
extern "C"{
    int PrimeCount(int A, int B);
}
