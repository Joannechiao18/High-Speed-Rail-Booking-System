// FlightSchedule.cpp
// Member-function definitions for class SouthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "SouthboundTimetable.h"

extern string departureTimes[37];

// SouthboundTimetable default constructor
// loads southbound timetable from the file "Southbound timetable.dat"
SouthboundTimetable::SouthboundTimetable()
{
    loadSouthboundTimetable();
}

void SouthboundTimetable::loadSouthboundTimetable()
{
    ifstream inFile("Southbound timetable.dat", ios::in);
    if (!inFile)
        cout << "File could not be opened.\n";
    else
    {
        inFile.seekg(0, ios::end);
        int numLine = inFile.tellg() / sizeof(Train);
        inFile.seekg(0, ios::beg);

        southboundTimetable.resize(numLine);
        for (int i = 0; i < numLine; i++)
            inFile.read(reinterpret_cast<char*>(&southboundTimetable[i]), sizeof(Train));
    }
}

// returns departureTimes[ station ]
string SouthboundTimetable::getDepartureTimes(string trainNumber, int station)
{
    vector< Train >::iterator it = searchTrain(trainNumber);
    return it->getDepartureTimes(station);
}

bool SouthboundTimetable::trainsAvailable(int departureTime,
    int originStation, int destinationStation)
{
    for (int i = 0; i < southboundTimetable.size(); i++)
    {
        if (departureTimes[departureTime] < southboundTimetable[i].getDepartureTimes(originStation) && southboundTimetable[i].getDepartureTimes(originStation) != "-" && southboundTimetable[i].getDepartureTimes(destinationStation) != "-")
            return true;
    }
    return false;
}

void SouthboundTimetable::displayComingTrains(int departureTime, int originStation, int destinationStation)
{
    cout << endl << "Train No." << setw(11) << "Departure" << setw(9) << "Arrival" << endl;
    int count = 0;
    for (int i = 0; i < southboundTimetable.size(); i++)
    {
        if (departureTimes[departureTime] <= southboundTimetable[i].getDepartureTimes(originStation) && southboundTimetable[i].getDepartureTimes(originStation) != "-" && southboundTimetable[i].getDepartureTimes(destinationStation) != "-")
        {
            cout << setw(9) << southboundTimetable[i].getTrainNumber() << setw(11) << southboundTimetable[i].getDepartureTimes(originStation) << setw(9) << southboundTimetable[i].getDepartureTimes(destinationStation) << endl;
            count++;
        }
        if (count >= 10)
            break;
    }
}

vector< Train >::iterator SouthboundTimetable::searchTrain(string trainNumber)
{
    vector< Train >::iterator it = southboundTimetable.begin();
    for (; it != southboundTimetable.end(); ++it)
        if (it->getTrainNumber() == trainNumber)
            return it;

    return southboundTimetable.end();
}