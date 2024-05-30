#ifndef RANDOMNUMBER_HPP
#define RANDOMNUMBER_HPP

#include <bits/stdc++.h>

class RandomNumber
{
public:
    static double uniform();
    static double uniform(double, double);
    static int uniformInt(int, int);
    static double exponential(double);
    static double normal();
    static double normal(double, double);
private:
    RandomNumber();
};

#endif
