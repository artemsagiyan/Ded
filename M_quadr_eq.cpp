#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "H_quadr_eq.h"


int main() {
    
    TestSolveSquare();

    printf("\n");

    double a = NAN,
           b = NAN,
           c = NAN;

    readKoefQuadr(&a, &b, &c);

    double x_1   = NAN,
           x_2   = NAN;
    int    count = 0;    

    count = solveSquare(a, b, c, &x_1, &x_2);
    printAnswer(count, x_1, x_2);

    return 0;   
}
