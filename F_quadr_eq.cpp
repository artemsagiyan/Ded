#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "H_quadr_eq.h"

const static double noRoots =    -1; 
const static double EXP     = 10E-4;

//------------------------------------------------------------------------------------------- 

void readKoefQuadr(double *pa, double *pb, double *pc) {
    assert(pa != NULL);
    assert(pb != NULL);
    assert(pc != NULL);
    
    printf("Enter koefficients of quadratik equation\n");

    while ((scanf("%lf %lf %lf", pa, pb, pc)) != 3) {
        printf("Your data are wrong! Can you repeat, please?\n");
        fflush(stdin);
    }
}

//------------------------------------------------------------------------------------------- 

int solveSquare(const double a, const double b, const double c, double *px_1, double *px_2) {
    assert(px_1 != NULL);
    assert(px_2 != NULL);

    if (isZero(a)) return linearSolve(b, c, px_1, px_2);
    if (isZero(c)) {
        *px_2 = noRoots;
        return linearSolve(a, b, px_1, px_2);
    }
    else {
        double dsk = NAN;
        dsk = b * b - 4 * a * c; 
        assert(isfinite(dsk));   //проверка на бесконечный дискриминант     
        
        if (dsk < 0) return 0;
        if (isZero(dsk)) {
            *px_1 = -b / (2 * a);
            *px_1 = isZero(*px_1) ? 0 : *px_1;
            return 1;
        }  
        double sq = sqrt(dsk);
        *px_1 = (-b + sq) / (2 * a),
        *px_2 = (-b - sq) / (2 * a);
        
        return 2; 
    }
} 

//------------------------------------------------------------------------------------------- 

void printAnswer(const int count, double x_1, double x_2) {
    
    switch (count) {
        case 0:   printf("The equation doesn't have real numbers\n");
                  break;
        
        case 1:   printf("The equation has 1 number:\nx = %.3lf\n", x_1); 
                  break;
        
        case 2:   printf("The equation has 2 numbers:\nx_1 = %.3lf\nx_2 = %.3lf\n", x_1,
                                                                                    x_2);
                  break;
        
        case -1:  printf("The equation has infinite number\n");
                  break;
        default: printf("Warning!!!");
    }  
}

//------------------------------------------------------------------------------------------- 

int linearSolve(const double b, const double c, double *px_1, double *px_2) {
    assert(px_1 != NULL);
    assert(px_2 != NULL);

    if (isZero(b))
        if (isZero(c)) return -1;
        else return 0;
    *px_1 = -c/b;
    *px_1 = isZero(*px_1) ? 0 : *px_1;  
    if(isZero(*px_2)) return 2;
    return 1;
}

//------------------------------------------------------------------------------------------- 

bool isZero(const double num) { 
    if (fabs(num) < EXP) return 1;
    return 0;
}

//------------------------------------------------------------------------------------------- 

void TestSolveSquare() {
    #define Test(testNum, a, b, c, rightNumRoots, Right_x_1, Right_x_2) {                             \
        double x_1 = 0,                                                                               \
               x_2 = 0;                                                                               \
        int countRoots = solveSquare(a, b, c, &x_1, &x_2);                                            \
                                                                                                      \
        if(countRoots != rightNumRoots)                                                               \
            printf("Test %d is BAD\nRight answer is rightCount = %d\nYour ans is count = %d\n",       \
                                                              testNum, rightNumRoots, countRoots);    \
        if (!isZero(Right_x_1 - x_1))                                                                 \
            printf("Test %d is BAD\nRight answer is Rx_1 = %lf\nYour answer is x_1   = %lf\n",        \
                                                          testNum, Right_x_1,       x_1);             \
                                                                                                      \
        if (!isZero(Right_x_2 - x_2))                                                                 \
            printf("Test %d is BAD\nRight answer is Rx_2 = %lf\nYour answer is x_2   = %lf\n",        \
                                                          testNum, Right_x_1, x_2);                   \
        else printf("Test %d is OK\n", testNum);                                                      \
        testNum++;                                                                                    \
}                                                                                                 

                                                                                                  
        int testNum = 1;                                                                           
                                                                                                     
        Test (testNum,  0,  0,   0, -1,  0.0,  0.0)                                                            
        Test (testNum,  1,  2,   2,  0,  0.0,  0.0)                                                            
        Test (testNum,  1,  2,   1,  1, -1.0,  0.0)                                                            
        Test (testNum,  1,  2, 1.1,  0,  0.0,  0.0)                                                            
        Test (testNum,  1,  1,   1,  0,  0.0,  0.0) 
                                                           
        Test (testNum,  1,   2,   -1, 2,  0.414214,  -2.414214)      
        Test (testNum,  EXP, 2 * EXP, EXP, 1, -1.0, 0.0)
}                                                                      
