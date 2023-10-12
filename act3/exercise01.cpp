// =================================================================
//
// File: exercise01.cpp
// Author(s): Sergio Augusto Macias Corona
// Description: This file contains the code to count the number of
//				even numbers within an array using the OpenMP 
//				technology. To compile:
//				g++ -o app -fopenmp exercise01.cpp
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <chrono>
#include <omp.h>
#include "utils.h"

using namespace std;
using namespace std::chrono;

// array size
#define SIZE 500000000

// Implementa la función que suma los elementos pares en paralelo
long long sumEvenNumbers(int *arr, int size) {
    long long sum = 0;

    #pragma omp parallel for num_threads(6)
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }

    return sum;
}

int main(int argc, char* argv[]) {
    int *array;
    long long result;
    // Estas variables se utilizan para realizar un seguimiento del tiempo de ejecución.
    high_resolution_clock::time_point start, end;
    double timeElapsed;

    array = new int[SIZE];
    fill_array(array, SIZE);
    display_array("array", array);

    cout << "Starting...\n";
    timeElapsed = 0;
    for (int j = 0; j < 1; j++) {
        start = high_resolution_clock::now();

        // Llama a la función que suma los elementos pares en paralelo
        result = sumEvenNumbers(array, SIZE);

        end = high_resolution_clock::now();
        timeElapsed += 
            duration<double, std::milli>(end - start).count();
    }
    cout << "result = " << result << "\n";
    cout << "avg time = " << fixed << setprecision(3) 
         << (timeElapsed / N) <<  " ms\n";

    delete [] array;
    return 0;
}