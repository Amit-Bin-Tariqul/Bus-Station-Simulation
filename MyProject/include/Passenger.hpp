#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include <bits/stdc++.h>
class Simulator;
class Terminal;

class Passenger
{
protected:
    int id, BUSID;
    Simulator *simulator;
    Terminal *source, *destination;
    double arrivalTime, boardingTime, tripStartTime, departureTime;

public:
    Passenger(Simulator*, Terminal*, Terminal*, double);

    void setBUSid(int id);
    void setThreshold(int id);
    void setBoardingTime(double time);
    void setTripStartTime(double time);
    void setDepartureTime(double time);

    std::string getSource();
    std::string getDestination();

    double queueDelay();
    double haltingDelay();
    double roadDelay();

    double waitingTime();
    double totalDelay();

    void write();
};

#endif
