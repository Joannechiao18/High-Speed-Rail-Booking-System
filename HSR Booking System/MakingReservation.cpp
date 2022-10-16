// MakingReservation.cpp
// Member-function definitions for class MakingReservation.
#include <iostream>
#include <iomanip>
#include "MakingReservation.h" // MakingReservation class definition

extern int inputAnInteger(int begin, int end);

extern string departureTimes[37];

// MakingReservation constructor
MakingReservation::MakingReservation(ReservationDatabase& theReservationDatabase,
    SouthboundTimetable& theSouthboundTimetable,
    NorthboundTimetable& theNorthboundTimetable)
    : reservationDatabase(theReservationDatabase),
    southboundTimetable(theSouthboundTimetable),
    northboundTimetable(theNorthboundTimetable)
{
}

void MakingReservation::execute()
{
    if (chooseTrain()) // displays timetables for 10 coming trains, then let user choose a train
    {
        inputReservationDetails();

        inputContactPersonInfo();

        reservationDatabase.addReservation(reservation);

        cout << "\nReservation Completed!\n\n";

        //reservationDatabase.~ReservationDatabase();   
    }
    else
        cout << "\nSorry! No train is available!\n\n";
}

bool MakingReservation::chooseTrain()
{
    int OK = 1;
    if (OK == 1)
    {
        int choice;
        string ch;
        do {
            cout << "Origin Station\n";
            cout << "1. Nangang\n";
            cout << "2. Taipei\n";
            cout << "3. Banqiao\n";
            cout << "4. Taoyuan\n";
            cout << "5. Hsinchu\n";
            cout << "6. Miaoli\n";
            cout << "7. Taichung\n";
            cout << "8. Changhua\n";
            cout << "9. Yunlin\n";
            cout << "10. Chiayi\n";
            cout << "11. Tainan\n";
            cout << "12. Zuoying\n";
            cout << "? ";
        } while ((choice = inputAnInteger(1, 12)) == -1);
        cout << endl;

        reservation.setOriginStation(choice);

        do {
            cout << "Destination Station\n";
            cout << "1. Nangang\n";
            cout << "2. Taipei\n";
            cout << "3. Banqiao\n";
            cout << "4. Taoyuan\n";
            cout << "5. Hsinchu\n";
            cout << "6. Miaoli\n";
            cout << "7. Taichung\n";
            cout << "8. Changhua\n";
            cout << "9. Yunlin\n";
            cout << "10. Chiayi\n";
            cout << "11. Tainan\n";
            cout << "12. Zuoying\n";
            cout << "? ";
        } while ((choice = inputAnInteger(1, 12)) == -1);
        cout << endl;

        reservation.setDestinationStation(choice);

        do {
            for (int i = 1; i < 37; i++)
                cout << i << ". " << departureTimes[i] << endl;
            cout << "? ";
        } while ((choice = inputAnInteger(1, 36)) == -1);
        cout << endl;

        int time;
        time = choice;

        if (reservation.getDestinationStation() > reservation.getOriginStation())
        {
            if (southboundTimetable.trainsAvailable(time, reservation.getOriginStation(), reservation.getDestinationStation()))
            {
                southboundTimetable.displayComingTrains(time, reservation.getOriginStation(), reservation.getDestinationStation());
                //return true;
            }
            else
                return false;
        }
        else if (reservation.getOriginStation() > reservation.getDestinationStation())
        {
            if (northboundTimetable.trainsAvailable(time, reservation.getOriginStation(), reservation.getDestinationStation()))
            {
                northboundTimetable.displayComingTrains(time, reservation.getOriginStation(), reservation.getDestinationStation());
                //return true;
            }
            else
                return false;
        }


        string trainNum;
        cout << endl << "Enter Train Number: ";
        cin >> trainNum;
        cout << endl;
        reservation.setTrainNumber(trainNum);

    }
    return true;
}

void MakingReservation::inputReservationDetails()
{
    cout << "\nCar Class\n" << "1. Standard Car\n" << "2. Business Car";

    int carClass;
    do cout << "\n? ";
    while ((carClass = inputAnInteger(1, 2)) == -1);
    reservation.setCarClass(carClass);

    cout << "\nDeparture Date: ";

    char date[12];
    cin >> date;
    reservation.setDate(date);
    cin.ignore();

    cout << "\nHow many adult tickets? ";

    int adultTickets;
    cin >> adultTickets;
    reservation.setAdultTickets(adultTickets);

    cout << "\nHow many concession tickets? ";

    int concessionTickets;
    cin >> concessionTickets;
    reservation.setConcessionTickets(concessionTickets);

    cout << "\nTrip Details\n";
    reservation.displayReservationDetails();
    cout << endl;
}

void MakingReservation::inputContactPersonInfo()
{
    cout << "\nEnter Contact Person Information\n\n";

    cout << "ID Number: ";
    string id;
    cin >> id;
    reservation.setIdNumber(id);
    //cout << idNumber;

    cout << "\nPhone: ";
    string phone;
    cin >> phone;
    cin.ignore();
    reservation.setPhone(phone);

    srand(static_cast<unsigned int>(time(0)));
    char reservationNumber[12];
    for (int i = 0; i < 8; i++)
        reservationNumber[i] = rand() % 10 + '0';
    reservationNumber[8] = '\0';
    reservation.setReservationNumber(reservationNumber);

    cout << "\nReservation Number: " << reservationNumber << endl;
}