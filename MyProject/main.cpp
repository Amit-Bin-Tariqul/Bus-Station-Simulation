#include <bits/stdc++.h>
#include "Simulator.hpp"
#include "RandomNumber.hpp"

int main()
{
    srand(time(0));

    for(int i=1; i<=10; i++)
    {
        Simulator s(i);
        s.run();
    }

    return 0;
}
