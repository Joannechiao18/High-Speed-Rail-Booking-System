#include <iostream>
#include <fstream>
#include "ReservationHistory.h" // ReservationHistory class definition

extern int inputAnInteger(int begin, int end);

// ReservationHistory default constructor
ReservationHistory::ReservationHistory(ReservationDatabase& theReservationDatabase,
    SouthboundTimetable& theSouthboundTimetable,
    NorthboundTimetable& theNorthboundTimetable)
    : idNumber(),
    reservationNumber(),
    reservationDatabase(theReservationDatabase),
    southboundTimetable(theSouthboundTimetable),
    northboundTimetable(theNorthboundTimetable)
{
} // end ReservationHistory default constructor

void ReservationHistory::execute()
{
    fstream ioFile("Reservation details.dat", ios::in | ios::binary);
    if (!ioFile)
        cout << "File could not be opened." << endl;

    string ID, num;
    cout << "Enter ID Number: ";
    cin >> ID;
    cout << endl << "Enter Reservation Number: ";
    cin >> num;

    //ReservationDatabase reserBase;
    if (reservationDatabase.exist(ID, num))
    {
        cout << endl << "Reservation Details\n";

        reservationDatabase.displayReservation(ID, num);

        cout << endl;

        int choice;
        do {
            cout << "Enter Your Choice\n";
            cout << "1. Cancellation\n";
            cout << "2. Reduce\n";
            cout << "3. End\n";
            cout << "? ";
        } while ((choice = inputAnInteger(1, 3)) == -1);
        if (choice == 3)
            return;
        cout << endl;

        switch (choice)
        {
        case 1:
            reservationDatabase.cancelReservation(ID, num);
            break;
        case 2:
            reservationDatabase.reduceSeats(ID, num);
            break;
        }
    }
    else
        cout << endl << "Reservation record not found.\n" << endl;

    //cout << "Enter ID Number: ";
    //cin >> idNumber;
    ////cout << idNumber;
    //cin.get();
    ////cin >> userID;
    ////user.setIdNumber(userID);
    //cout << endl << "Enter Reservation Number: ";
    //cin >> reservationNumber;
    //cin.get();
    ////cin >> userReservationNumber;
    ////user.setReservationNumber(userReservationNumber);
    //if (reservationDatabase.exist(idNumber, reservationNumber)) {
    //    cout << endl << "Reservation Details" << endl;
    //    reservationDatabase.displayReservation(idNumber, reservationNumber);

    //    int choice;
    //    cout << "\nEnter Your Choice\n"
    //        << "1. Cancellation\n"
    //        << "2. Reduce\n"
    //        << "3. End";

    //    do cout << "\n? ";
    //    while ((choice = inputAnInteger(1, 3)) == -1);
    //    cout << endl;

    //    switch (choice)
    //    {
    //    case 1:
    //        reservationDatabase.cancelReservation(idNumber, reservationNumber);
    //        break;

    //    case 2:
    //        reservationDatabase.reduceSeats(idNumber, reservationNumber);
    //        break;

    //    case 3:
    //        return;

    //    default:
    //        cerr << "Incorrect Choice!\n";
    //        break;
    //    }
    //}
    //else
    //    cout << endl << "Reservation record not found." << endl << endl;
}