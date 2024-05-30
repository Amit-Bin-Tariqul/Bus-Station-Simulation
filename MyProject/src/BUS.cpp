#include "BUS.hpp"
#include "Simulator.hpp"
#include "Terminal.hpp"
#include "Passenger.hpp"
#include "Event.hpp"
#include "RandomNumber.hpp"

BUS::BUS(Terminal* t, double duration, int threshold_):
    simulator(t->getSimulator()), terminal(t), id(t->getSimulator()->countBUS()),
    tripDurationMean(duration), threshold(threshold_)
{
    terminal->BUSarrivalHandler(this);

    meanCost=6;
    totalCost=0;
    perPassengerEarning=10;
    passengerCount=0;
    tripCount=0;
}

BUS::~BUS()
{
    int i, n=seat.size();
    for(i=0; i<n; i++) delete seat[i];
}

bool BUS::free()
{
    return seat.size()<20;
}

void BUS::addPassenger(Passenger* p)
{
    p->setBoardingTime(simulator->now());
    p->setBUSid(id);
    seat.push_back(p);

    if(seat.size()==threshold) simulator->schedule(new TripStart(this), 0.1); // 0.1 for waaiting policy and 0 for waitless policy
}

void BUS::startTrip()
{
    int i=0, n=seat.size();
    for(i=0; i<n; i++) seat[i]->setTripStartTime(simulator->now());

    terminal->BUSdepartureHandler(this);
    terminal=terminal->getDestination();
    simulator->schedule(new Departure(this), RandomNumber::exponential(tripDurationMean));
}

void BUS::departureHandler()
{
    int i, n=seat.size();
    passengerCount+=n;
    tripCount++;
    totalCost+=RandomNumber::normal(meanCost, 0.25);

    for(i=0; i<n; i++)
    {
        seat[i]->setDepartureTime(simulator->now());
        seat[i]->write();

        delete seat[i];
    }

    seat.clear();

    terminal->BUSarrivalHandler(this);
}

int BUS::profit()
{
    return passengerCount*perPassengerEarning-totalCost;
}
double BUS::fuelEfficiency()
{
    return 1.0/20*passengerCount/tripCount;
}

void BUS::write()
{
    simulator->BUSstream << id << ',' << threshold << ',' << passengerCount << ',' << tripCount << ',';
    simulator->BUSstream << profit() << ',' << fuelEfficiency() << '\n';
}
