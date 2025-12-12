#include "square.h"

// Реализация 2: Площадь прямоугольного треугольника
// S = (A * B) / 2
float Square(float A, float B) {
    if (A <= 0 || B <= 0) return -1.0f;  
    return (A * B) / 2.0f;
}