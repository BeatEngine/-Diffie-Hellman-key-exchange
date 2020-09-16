#include <stdio.h>

#include <math.h>

#include <time.h>

long gcd(long a, long b)
{
    long x = a;
    long y = b;
    do
    {
        x = y;
        y = x % y;
    } while (y > 0);
    return x;
}

bool isPrime(long x)
{
    int a = 3;
    if(x % 2 == 0)
    {
        return false;
    }
    while (a < x)
    {
        if(x % a == 0)
        {
            return false;
        }
        a+=2;
    }
    return true;
}

long genPrim(int len)
{
    long p = pow(10,len);
    //p = (long)(p/log(p));
    p = (log(p)*p-p) - (log(2)*2-2) - (long)(p/log(p));
    //p += log(p)*2.99977340;
    long a = p;
    if(p % 2 == 0)
    {
        p++;
    }
    while(!isPrime(p))
    {
        p += 2;
    }
    printf("Abs: %d\n", p - a);
    return p;
}


const char* toChar(bool x)
{
    if(x)
    {
        return "true";
    }
    return "false";
}

long lpow(long a, long b, long mod)
{
    if(mod == 1)
    {
        return 0;
    }
    long t = a;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            a = (a*t) % mod;
        }
        b = b >> 1;
        t = (t*t) % mod;
    }
    return a;
}

long generatePublicKey(int digits, long* retP, long* reta, long* retA)
{
    long p = genPrim(digits);
    long a = (5*powf(10,digits)) + rand() % (long)(5*powf(10,digits));
    long A = rand() % (long)(10*powf(10,digits)) + 15.38273*powf(10,digits);
    *retP = p;
    *reta = a;
    *retA = A;
    return lpow(A, a, p);
}

long generatePublicKey(int digits, long P, long G, long pair, long* retb)
{
    long b = 5*powf(10,digits) + rand() % (long)(5*powf(10,digits));
    *retb = b;
    return lpow(G, b, P);
}
//#include "bigcalc.h"
int main()
{
    srand(clock());
    long p, a, G;
    long pair1 = generatePublicKey(7, &p, &a, &G);
    long b;
    long pair2 = generatePublicKey(7, p, G, pair1, &b);
    long key_1 = lpow(pair2, a, p);
    long key_2 = lpow(pair1, b, p);
    printf("Key: %d == %d\n", key_1, key_2);

    //BC::Integer k;
    //k = key_1;
    //k.cprint();

    return 0;
}


