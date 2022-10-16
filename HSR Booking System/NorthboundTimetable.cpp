// NorthboundTimetable.cpp
// Member-function definitions for class NorthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "NorthboundTimetable.h"

extern string departureTimes[37];

// NorthboundTimetable default constructor
// loads northbound timetable from the file "Northbound timetable.dat"
NorthboundTimetable::NorthboundTimetable()
{
    loadNorthboundTimetable();
}

void NorthboundTimetable::loadNorthboundTimetable()
{
    ifstream inFile("Northbound timetable.dat", ios::in);
    if (!inFile)
        cout << "File could not be opened.\n";
    else
    {
        inFile.seekg(0, ios::end);
        int numLine = inFile.tellg() / sizeof(Train);
        inFile.seekg(0, ios::beg);

        northboundTimetable.resize(numLine);
        for (int i = 0; i < numLine; i++)
            inFile.read(reinterpret_cast<char*>(&northboundTimetable[i]), sizeof(Train));
    }
}

// returns departureTimes[ station ]
string NorthboundTimetable::getDepartureTimes(string trainNumber, int station)
{
    vector< Train >::iterator it = searchTrain(trainNumber);
    return it->getDepartureTimes(station);
}

bool NorthboundTimetable::trainsAvailable(int departureTime,
    int originStation, int destinationStation)
{
    Train train;
    for (int i = 0; i < northboundTimetable.size(); i++)
    {
        if (departureTimes[departureTime] <= northboundTimetable[i].getDepartureTimes(13 - originStation) && northboundTimetable[i].getDepartureTimes(13 - originStation) != "-" && northboundTimetable[i].getDepartureTimes(13 - destinationStation) != "-")
            return true;
    }
    return false;
}

void NorthboundTimetable::displayComingTrains(int departureTime,
    int originStation, int destinationStation)
{
    cout << endl << "Train No." << setw(11) << "Departure" << setw(9) << "Arrival" << endl;
    int count = 0;
    for (int i = 0; i < northboundTimetable.size(); i++)
    {
        if (departureTimes[departureTime] <= northboundTimetable[i].getDepartureTimes(13 - originStation) && northboundTimetable[i].getDepartureTimes(13 - originStation) != "-" && northboundTimetable[i].getDepartureTimes(13 - destinationStation) != "-")
        {
            cout << setw(9) << northboundTimetable[i].getTrainNumber() << setw(11) << northboundTimetable[i].getDepartureTimes(13 - originStation) << setw(9) << northboundTimetable[i].getDepartureTimes(13 - destinationStation) << endl;
            count++;
        }
        if (count >= 10)
            break;
    }
}

vector< Train >::iterator NorthboundTimetable::searchTrain(string trainNumber)
{
    vector< Train >::iterator it = northboundTimetable.begin();
    for (; it != northboundTimetable.end(); ++it)
        if (it->getTrainNumber() == trainNumber)
            return it;

    return northboundTimetable.end();
}