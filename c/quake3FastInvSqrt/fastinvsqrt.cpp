// fast inverse square root from Quake III
#include <chrono>
#include <math.h>
#include <iostream>


float Q_invsqrt(float number){
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                            // compileren tror at det der står på adressen er long A.K.A. modbydeligt floating point bit hack
    i  = 0x5f3759df - ( i >> 1 );                    // ???
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - (x2 * y * y ) );         // iter 1
//  y  = y * ( threehalfs - ( x2 * y* y ) );         // iter 2, optionel

    return y;
}

int main(){
    
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    float pi = 3.14159; 

    auto t11 = high_resolution_clock::now();
    float fast_foo = Q_invsqrt(pi);
    auto t12 = high_resolution_clock::now();

    auto t21 = high_resolution_clock::now();
    float foo = 1.0/sqrt(pi);
    auto t22 = high_resolution_clock::now();

    duration<double, std::milli> ms_fast = t12 - t11;
    duration<double, std::milli> ms_slow = t22 - t21;

    std::cout << "norm: " << ms_slow.count() << " ms\n";
    std::cout << "fast: " << ms_fast.count() << " ms\n\n";

    std::cout << "norm result: " << foo << "\n";
    std::cout << "fast result: " << fast_foo << "\n";

}