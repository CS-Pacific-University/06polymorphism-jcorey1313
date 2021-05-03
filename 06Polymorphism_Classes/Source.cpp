//****************************************************************************
// File name:	  Source.cpp
// Author:		  James Corey
// Date:		    05/03/2021
// Class:		    CS250
// Assignment:  Polymorphism
// Purpose:		  Using polymorphism to create a simulation of a mail service
// Hours:       9
//****************************************************************************

#include "Letter.h"
#include "Postcard.h"
#include "Overnight.h"
#include <iomanip>
#include <fstream>

void printMenu ();

int main () {

  const int PRINT = 1;
  const int INSURANCE = 2;
  const int RUSH = 3;
  const int DELIVER = 4;
  const int QUIT = 5;
  const int MAX_PARCELS = 25;
  const int TID_ADJUSTMENT = 1;
  const int DECIMAL_SPOTS = 2;
  const char LETTER = 'L';
  const char OVERNIGHT_PACKAGE = 'O';
  const char POSTCARD = 'P';
  const string INPUT_FILE = "Parcel.txt";

  ifstream inputFile;
  char whichParcel;
  Parcel* apcParcels [MAX_PARCELS] = { nullptr };
  int numParcels = 0;
  int tID, menuChoice;
  double insuranceCost, rushCost;

  cout << "Mail Simulator!" << endl;

  inputFile.open (INPUT_FILE);
  if (!inputFile.is_open ()) {
    cout << "Could not open file.";
    return EXIT_FAILURE;
  }
  else {
    while (inputFile >> whichParcel) {
      if (whichParcel == LETTER) {
        apcParcels [numParcels] = new Letter;
      }
      else if (whichParcel == OVERNIGHT_PACKAGE) {
        apcParcels [numParcels] = new Overnight;
      }
      else if (whichParcel == POSTCARD) {
        apcParcels [numParcels] = new Postcard;
      }

      apcParcels [numParcels]->read (inputFile);
      apcParcels [numParcels]->setCost ();
      numParcels++;
    }

    do {
      printMenu ();
      do {
        cout << "Choice> ";
        cin >> menuChoice;
        cout << endl;
      } 
      while (menuChoice != PRINT && menuChoice != INSURANCE 
             && menuChoice != RUSH && menuChoice != DELIVER 
             && menuChoice != QUIT);

      if (menuChoice == PRINT) {
        for (int i = 0; i < numParcels; i++) {
          if (apcParcels [i] != nullptr) {
            apcParcels [i]->print (cout);
            cout << endl;
          }
        }
      }
      else if (menuChoice == INSURANCE) {
        cout << "TID> ";
        cin >> tID;
        if (tID > 0 && tID <= numParcels) {
          insuranceCost = apcParcels [tID - TID_ADJUSTMENT]->addInsurance ();
          cout << "Added Insurance for $" << fixed 
               << setprecision (DECIMAL_SPOTS) << insuranceCost << endl;
          apcParcels [tID - TID_ADJUSTMENT]->print (cout);
          cout << endl;
        }
      }
      else if (menuChoice == RUSH) {
        cout << "TID> ";
        cin >> tID;
        if (tID > 0 && tID <= numParcels) {
          rushCost = apcParcels [tID - TID_ADJUSTMENT]->addRush ();
          cout << "Added Rush for $ " << fixed
            << setprecision (DECIMAL_SPOTS) << rushCost << endl;
          apcParcels [tID - TID_ADJUSTMENT]->print (cout);
          cout << endl;
        }
      }
      else if (menuChoice == DELIVER) {
        cout << "TID> ";
        cin >> tID;
        if (tID > 0 && tID <= numParcels) {
          cout << "Delivered!" << endl;
          cout << apcParcels [tID - TID_ADJUSTMENT]->getDeliveryDay ()
               << " Day, $" << fixed << setprecision (DECIMAL_SPOTS) 
               << apcParcels [tID - TID_ADJUSTMENT]->getCost () << endl;
          apcParcels [tID - TID_ADJUSTMENT]->print (cout);
          delete apcParcels [tID - TID_ADJUSTMENT];
          apcParcels [tID - TID_ADJUSTMENT] = nullptr;
          cout << endl;
        }
      }
    }
    while (menuChoice != QUIT);

    for (int i = 0; i < numParcels; i++) {
      delete apcParcels [i];
    }

    inputFile.close();

    return EXIT_SUCCESS;
  } 
}

void printMenu() {
  const string OPTION_1_PRINT = "1. Print All";
  const string OPTION_2_INSURANCE = "2. Add Insurance";
  const string OPTION_3_RUSH = "3. Add Rush";
  const string OPTION_4_DELIVER = "4. Deliver";
  const string OPTION_5_QUIT = "5. Quit";

  cout << endl << OPTION_1_PRINT << endl << OPTION_2_INSURANCE << endl
       << OPTION_3_RUSH << endl << OPTION_4_DELIVER << endl << OPTION_5_QUIT
       << endl << endl;
}
