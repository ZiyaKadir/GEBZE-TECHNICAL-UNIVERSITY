#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>
#include <mutex>
#include <bits/stdc++.h>

#include "Algorithms.h"

using namespace std;

int main() {
    
    int number;
    int numberOfTrials = 10000;
    cout << "Enter a number: ";
    cin >> number;


    cout << "Checking if " << number << " is prime using Miller-Rabin algorithm..." << endl;
    cout << "Result: " << (Miller_Rabin_Prime(number, numberOfTrials) ? "Prime" : "Not Prime") << endl;

    cout << "Checking if " << number << " is prime using Sieve of Atkin algorithm..." << endl;
    cout << "Result: " << (Atkin_Prime(number) ? "Prime" : "Not Prime") << endl;

    cout << "Checking if " << number << " is prime using Sieve of Eratosthenes algorithm..." << endl;
    cout << "Result: " << (Eratosthenes_Prime(number) ? "Prime" : "Not Prime") << endl;



    return 0;
}