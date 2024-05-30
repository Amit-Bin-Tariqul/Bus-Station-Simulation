#include "Passenger.hpp"
#include "Terminal.hpp"
#include "Simulator.hpp"

Passenger::Passenger(Simulator *s, Terminal* src, Terminal* dest, double time):
id(src->getSimulator()->countPassenger()), simulator(s), source(src), destination(dest),
arrivalTime(time), boardingTime(-1), tripStartTime(-1), departureTime(-1)
{}

void Passenger::setBUSid(int id) { BUSID=id; }
void Passenger::setBoardingTime(double time) { boardingTime=time; }
void Passenger::setTripStartTime(double time) { tripStartTime=time; }
void Passenger::setDepartureTime(double time) { departureTime=time; }

std::string Passenger::getSource() { return source->getName(); }
std::string Passenger::getDestination() { return destination->getName(); }

double Passenger::queueDelay() { return boardingTime-arrivalTime; }
double Passenger::haltingDelay() { return tripStartTime-boardingTime; }
double Passenger::roadDelay() { return departureTime-tripStartTime; }

double Passenger::waitingTime() { return queueDelay()+haltingDelay(); }
double Passenger::totalDelay() { return departureTime-arrivalTime; }

void Passenger::write()
{
	simulator->passengerStream << id << ',' << BUSID << ',' << getSource() << ',' << getDestination() << ',';
	simulator->passengerStream << arrivalTime << ',' << boardingTime << ',' << tripStartTime << ',' << departureTime << ',';
	simulator->passengerStream << queueDelay() << ',' << haltingDelay() << ',' << roadDelay() << ',' << waitingTime() << ',' << totalDelay() << '\n';
}
