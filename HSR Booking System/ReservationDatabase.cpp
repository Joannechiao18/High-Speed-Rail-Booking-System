// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <fstream>
using namespace std;
#include "ReservationDatabase.h"


// ReservationDatabase default constructor loads reservations from the file Reservation details.dat
ReservationDatabase::ReservationDatabase()
{
    loadReservations();
}

// ReservationDatabase destructor stores reservations into the file Reservation details.dat
ReservationDatabase::~ReservationDatabase()
{
    storeReservations();
}

void ReservationDatabase::loadReservations()
{
    /*ifstream ioFile("Reservation details.dat", ios::in | ios::binary);
    if (!ioFile)
        cout << "File could not be opened.\n";
    else
    {
        ioFile.seekg(0, ios::end);
        int numLine = ioFile.tellg() / sizeof(Reservation);
        ioFile.seekg(0, ios::beg);

        reservations.resize(numLine);
        for (int i = 0; i < numLine; i++)
            ioFile.read(reinterpret_cast<char*>(&reservations[i]), sizeof(Reservation));
    }*/
    fstream ioFile("Reservation details.dat", ios::in | ios::out | ios::binary);
    if (!ioFile) {
        cout << "File could not be opened." << endl;
        exit(1);
    }
    ioFile.seekg(0, ios::end);
    int numLine = ioFile.tellg() / sizeof(Reservation);
    ioFile.seekg(0, ios::beg);
    reservations.resize(numLine);
    for (int i = 0; i < numLine; i++) {
        ioFile.read(reinterpret_cast<char*>(&reservations[i]), sizeof(reservations[i]));
    }
}

void ReservationDatabase::storeReservations()
{
    fstream ioFile("Reservation details.dat", ios::in | ios::out | ios::binary);
    if (!ioFile)
        cout << "File could not be opened.\n";

    /*ioFile.seekg(0, ios::end);
    int numLine = ioFile.tellg() / sizeof(Reservation);
    ioFile.seekg(0, ios::beg);*/

    for (int i = 0; i < reservations.size(); i++)
        ioFile.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(Reservation));
}

bool ReservationDatabase::exist(string idNumber, string reservationNumber)
{
    // loop through reservations searching for matching idNumber and reservationNumber
    for (vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it)
    {
        //cout << it->getIdNumber() << endl << it->getReservationNumber();
        if (it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber)
            return true; // return true if match found
    }
    return false; // if no matching reservation was found, return false
}

void ReservationDatabase::displayReservation(string idNumber, string reservationNumber)
{
    vector< Reservation >::iterator it = searchReservation(idNumber, reservationNumber);
    it->displayReservationDetails();
}

void ReservationDatabase::cancelReservation(string idNumber, string reservationNumber)
{
    vector< Reservation >::iterator it = searchReservation(idNumber, reservationNumber);
    reservations.erase(it);
    /* cout << it->getOriginStation() << endl << it->getDestinationStation() << endl;
     cout << it->getAdultTickets() << endl << it->getConcessionTickets();*/
    cout << "Reservation Cancelled.\n\n";
}

void ReservationDatabase::addReservation(Reservation reservation)
{
    reservations.push_back(reservation);
}

void ReservationDatabase::reduceSeats(string idNumber, string reservationNumber)
{
    vector< Reservation >::iterator it = searchReservation(idNumber, reservationNumber);

    int r1, r2;
    do cout << "How many adult tickets to cancel? ";
    while (cin >> r1 && r1 < 0);
    it->setAdultTickets(it->getAdultTickets() - r1);

    do cout << endl << "How many concession tickets to cancel? ";
    while (cin >> r2 && r2 < 0);
    it->setConcessionTickets(it->getConcessionTickets() - r2);

    it->displayReservationDetails();  //output the details pointed to by it
}

vector< Reservation >::iterator ReservationDatabase::searchReservation(string idNumber, string reservationNumber)
{
    // loop through reservations searching for matching idNumber and reservationNumber
    for (vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it)
        if (it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber)
            return it; // return iterator to thecurrent reservation if match found

    return reservations.end();
}