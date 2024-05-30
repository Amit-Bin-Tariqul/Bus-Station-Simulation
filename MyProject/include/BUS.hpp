#ifndef BUS_HPP
#define BUS_HPP

#include <bits/stdc++.h>
#include "Passenger.hpp"
class Simulator;
class Terminal;

class BUS
{
protected:
    int id;
    Simulator *simulator;
    Terminal *terminal;
    std::vector<Passenger*> seat;

    int meanCost, perPassengerEarning, threshold;
    double tripDurationMean;

    int passengerCount, tripCount;
    double totalCost;

public:
    BUS(Terminal*, double, int);
    ~BUS();

    bool free();
    void addPassenger(Passenger*);
    void startTrip();
    void departureHandler();

    int profit();
    double fuelEfficiency();

    void write();
};

#endif
