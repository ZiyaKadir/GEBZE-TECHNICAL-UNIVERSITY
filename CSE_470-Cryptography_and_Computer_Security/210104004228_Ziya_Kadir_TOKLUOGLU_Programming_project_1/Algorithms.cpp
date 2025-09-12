#include "Algorithms.h"

using namespace std;

mutex mtx;

int moduler_exponentiation(int x, unsigned int y, int p) 
{
    int res = 1;      
    x = x % p;  

    while (y > 0)
    {
        
        if (y & 1)  
            res = (res*x) % p;
 
        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}
 

bool Miller_Rabin(int d, int n)
{
    
    int a = 2 + rand() % (n - 4);
 
    int x = moduler_exponentiation(a, d, n);
 
    if (x == 1  || x == n-1)
       return true;
 

    while (d != n-1)
    {
        x = (x * x) % n;
        d *= 2;
 
        if (x == 1)      return false;
        if (x == n-1)    return true;
    }
 
    return false;
}
 

bool Miller_Rabin_Prime(int n, int k=50)
{
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;
 
    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;
 
    for (int i = 0; i < k; i++)
         if (!Miller_Rabin(d, n))
              return false;
 
    return true;
}



bool Eratosthenes_Prime(int limit)
{

    if (limit <= 1) return false; 
    if (limit <= 3) return true; 
    if (limit % 2 == 0 || limit % 3 == 0) return false; 

    int sqrtLimit = sqrt(limit);
    vector<bool> sieve(sqrtLimit + 1, true);

    for (int i = 2; i <= sqrtLimit; ++i) {
        if (sieve[i]) { 
            for (int j = i * i; j <= sqrtLimit; j += i) {
                sieve[j] = false;
            }
            if (limit % i == 0) return false; 
        }
    }
    return true; 
}



bool Atkin_Prime(int limit)
{
    if (limit <= 1)
        return false;


    bool sieve[limit + 1];
    for (int i = 0; i <= limit; i++)
        sieve[i] = false;


    if (limit > 2)
        sieve[2] = true;
    if (limit > 3)
        sieve[3] = true;

    for (int x = 1; x * x <= limit; x++) {
        for (int y = 1; y * y <= limit; y++) {
            int n = (4 * x * x) + (y * y);
            if (n <= limit && (n % 12 == 1 || n % 12 == 5))
                sieve[n] ^= true;

            n = (3 * x * x) + (y * y);
            if (n <= limit && n % 12 == 7)
                sieve[n] ^= true;

            n = (3 * x * x) - (y * y);
            if (x > y && n <= limit && n % 12 == 11)
                sieve[n] ^= true;
        }
    }

    for (int r = 5; r * r <= limit; r++) {
        if (sieve[r]) {
            for (int i = r * r; i <= limit; i += r * r)
                sieve[i] = false;
        }
    }

    return sieve[limit];
}