#include <bits/stdc++.h>
#include "Event.hpp"
#include "Simulator.hpp"
#include "BUS.hpp"
#include "Terminal.hpp"

Event::Event() {}
void Event::setTime(const double _time) { time=_time; }
bool Event::earlier(Event* e1, Event* e2) { return e1->time < e2->time; }

Arrival::Arrival(Terminal* t): terminal(t) {}
void Arrival::handle() { terminal->passengerArrivalHandler(); }

Departure::Departure(BUS *c): bus(c) {}
void Departure::handle() { bus->departureHandler(); }

TripStart::TripStart(BUS *c): bus(c) {}
void TripStart::handle() { bus->startTrip(); }
