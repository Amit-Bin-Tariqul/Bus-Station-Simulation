#include "Terminal.hpp"
#include "Simulator.hpp"
#include "BUS.hpp"
#include "Passenger.hpp"
#include "Event.hpp"
#include "RandomNumber.hpp"

Terminal::Terminal(Simulator* s, std::string name_, double mean): simulator(s), name(name_), arrivalMean(mean)
{}

Terminal::~Terminal()
{
    Passenger *p;

    while(!queue.empty())
    {
        p=queue.front();
        delete p;
        queue.pop();
    }
}

void Terminal::setDestination(Terminal* t)
{
    destination=t;
}

Simulator* Terminal::getSimulator() { return simulator; }
Terminal* Terminal::getDestination() { return destination; }
double Terminal::getArrivalMean() { return arrivalMean; }
std::string Terminal::getName() { return name; }

int Terminal::findBUSpos(BUS* c)
{
    int i, n=bus.size();
    for(i=0; i<n; i++) if(bus[i]==c) return i;

    return -1;
}

int Terminal::getFreeBUSpos()
{
    int i, n=bus.size();
    //std:: cout<<n<<'\n';
    std::vector<int> freeBUS;
    for(i=0; i<n; i++) if(bus[i]->free()) freeBUS.push_back(i);

    n=freeBUS.size();
    if(n<2) return freeBUS.size()-1;
    return freeBUS[RandomNumber::uniformInt(0, n-1)];
}

bool Terminal::boardBUS()
{
    if(queue.empty()) return false;

    int i=getFreeBUSpos();
    if(i<0) return false;

    Passenger *p=queue.front();
    queue.pop();
    bus[i]->addPassenger(p);
    return true;
}

void Terminal::passengerArrivalHandler()
{
    double now=simulator->now();
    if(now>720) return;

    Passenger *p=new Passenger(simulator, this, destination, now);
    queue.push(p);

    boardBUS();
    simulator->schedule(new Arrival(this), RandomNumber::exponential(arrivalMean));
}

void Terminal::BUSarrivalHandler(BUS* c)
{
    bus.push_back(c);

    while(boardBUS());
}

void Terminal::BUSdepartureHandler(BUS* c)
{
    int i=findBUSpos(c), n=bus.size();
    if(i<0) return;

    std::swap(bus[i], bus[n-1]);
    bus.pop_back();
}
