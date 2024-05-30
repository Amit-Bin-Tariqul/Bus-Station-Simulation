#include "Simulator.hpp"

Simulator::Simulator(int id_): eventList(Heap<Event*>(Event::earlier))
{
    reset(id_);
}

Simulator::~Simulator()
{
    terminate();
}

void Simulator::reset(int id_)
{
    terminal[0]=NULL;
    terminal[1]=NULL;
    terminate();

    id=id_;
    clock=0;
    passengerCount=0;

    int i;
    terminal[0]=new Terminal(this, "Mogbazar", 0.5);
    terminal[1]=new Terminal(this, "Mohakhali", 0.8);
    terminal[0]->setDestination(terminal[1]);
    terminal[1]->setDestination(terminal[0]);
    for(i=0; i<20; i++) bus.push_back(new BUS(terminal[i/10], 1.27, 1+i));

    for(i=0; i<2; i++) schedule(new Arrival(terminal[i]), RandomNumber::exponential(terminal[i]->getArrivalMean()));

    BUSstream.open("trace/BUS-record-day-"+std::to_string(id)+".csv");
    passengerStream.open("trace/passenger-record-day-"+std::to_string(id)+".csv");

    BUSstream << "ID" << ',' << "Policy" << ',' << "Passenger Count" << ',' << "Trip Count" << ',';
    BUSstream << "Profit" << ',' << "Fuel Efficiency" << '\n';

    passengerStream << "ID" << ',' << "BUS ID" << ',' << "Source" << ',' << "Destination" << ',';
    passengerStream << "Arrival Time" << ',' << "Boarding Time" << ',' << "Trip Start Time" << ',' << "Departure Time" << ',';
    passengerStream << "Queue Delay" << ',' << "Halting Delay" << ',' << "Road Delay" << ',' << "Waiting Time" << ',' << "Total Delay" << '\n';
}

void Simulator::run()
{
    std::cout << "Running simulation for day " << id << '\n';
    Event *event;

    while(!eventList.isEmpty())
    {
        event=eventList.pop();
        clock=event->time;
        event->handle();
        if(event) delete event;
    }

    int i, n=bus.size();
    for(i=0; i<n; i++) if(bus[i]) bus[i]->write();
}

void Simulator::schedule(Event *event, double interval)
{
    event->setTime(clock+interval);
    eventList.push(event);
}

void Simulator::terminate()
{
    while(!eventList.isEmpty()) delete (eventList.pop());

    int i, n=bus.size();
    for(i=0; i<n; i++) if(bus[i]) delete bus[i];

    if(terminal[0]) delete terminal[0];
    if(terminal[1]) delete terminal[1];

    if(BUSstream) BUSstream.close();
    if(passengerStream) passengerStream.close();
}

double Simulator::now() { return clock; }
int Simulator::countPassenger() { return ++passengerCount; }
int Simulator::countBUS() { return bus.size()+1; }
