#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <bits/stdc++.h>
#include "BUS.hpp"
class Simulator;

class Terminal
{
protected:
    std::string name;
    Simulator *simulator;
    Terminal *destination;
    double arrivalMean;

    std::queue<Passenger*> queue;
    std::vector<BUS*> bus;

public:
    Terminal(Simulator*, std::string, double);
    ~Terminal();
    void setDestination(Terminal*);

    Simulator* getSimulator();
    Terminal* getDestination();
    std::string getName();
    double getArrivalMean();

    void passengerArrivalHandler();
    void BUSarrivalHandler(BUS* c);
    void BUSdepartureHandler(BUS* c);

    int findBUSpos(BUS* c);
    int getFreeBUSpos();
    bool boardBUS();
};

#endif
