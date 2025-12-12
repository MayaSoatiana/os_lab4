#pragma once 

#if defined(_WIN32)
    #ifdef MATHLIB_EXPORTS
        #define PRIME_API __declspec(dllexport)
    #else
        #define PRIME_API __declspec(dllimport)
    #endif
#endif

// Подсчет площади плоской геометрической фигуры по двум сторонам
extern "C"{
    float Square(float A, float B) ;
}
