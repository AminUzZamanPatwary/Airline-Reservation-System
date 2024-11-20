#ifndef AIRLINERESERVATION_H
#define AIRLINERESERVATION_H

#include <iostream>
#include <string>
using namespace std;

class Passenger {
public:
    string name;    
    Passenger* next; 

    Passenger(const string& name);
};

class Flight {
public:
    string flightName;  
    Passenger* passengerHead; 
    Flight* next;           

    Flight(const string& flightName);

    void addPassenger(const string& name);
    bool removePassenger(const string& name);
    bool isPassengerPresent(const string& name);
    void displayPassengers();
};
class AirlineReservationSystem {
private:
    Flight* flightHead;

public:
    AirlineReservationSystem();

    void addFlight(const string& flightName);
    void removeFlight(const string& flightName);
    Flight* findFlight(const string& flightName);
    void reserveTicket(const string& flightName, const string& passengerName);
    void cancelTicket(const string& flightName, const string& passengerName);
    void checkReservation(const string& flightName, const string& passengerName);
    void displayPassengers(const string& flightName);
    void menu();
};

#endif 
