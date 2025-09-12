#ifndef ALGORITHMS_H
#define ALGORITHMS_H


#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>
#include <mutex>
#include <bits/stdc++.h>

using namespace std;

int moduler_exponentiation(int x, unsigned int y, int p);

bool Miller_Rabin(int d, int n);

bool Miller_Rabin_Prime(int n, int k);

bool Eratosthenes_Prime(int limit);

bool Atkin_Prime(int limit);




#endif // ALGORITHMS_H