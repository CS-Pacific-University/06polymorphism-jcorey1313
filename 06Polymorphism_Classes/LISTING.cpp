//############################################################################
//Letter.h 
//############################################################################
//****************************************************************************
// File name:	  Letter.h
// Author:		  James Corey
// Date:		    05/03/2021
// Class:		    CS250
// Assignment:  Polymorphism
// Purpose:		  header for class that represents a letter
//****************************************************************************
#pragma once
#include "Parcel.h"

class Letter : public Parcel {
	public:
		Letter ();

		int getDeliveryDay () const;
		void setCost ();

		double addInsurance ();
		double addRush ();
};   
  
 
//############################################################################
//Overnight.h 
//############################################################################
//****************************************************************************
// File name:	  Overnight.h
// Author:		  James Corey
// Date:		    05/03/2021
// Class:		    CS250
// Assignment:  Polymorphism
// Purpose:		  header for class that represents an overnight package
//****************************************************************************

#pragma once
#include "Parcel.h"

class Overnight : public Parcel {
	public:
		Overnight ();

		bool read (istream&);
		void print (ostream&) const;

		int getDeliveryDay () const;
		void setCost ();

		double addInsurance ();
		double addRush ();

	private:
		double mVolume;
}; 
   
  
 
//############################################################################
//Parcel.h 
//############################################################################
//****************************************************************************
// File name:	  Parcel.h
// Author:		  James Corey
// Date:		    05/03/2021
// Class:		    CS250
// Assignment:  Polymorphism
// Purpose:		  header that represents a parcel to be mailed
//****************************************************************************
#pragma once

#include <iostream>

using namespace std;

class Parcel {
  public:
	  Parcel ();

    virtual bool read (istream& rcIn);
    virtual void print (ostream& rcOut) const;

    double getCost () const;

    virtual int getDeliveryDay () const = 0;
    virtual void setCost () = 0;

    virtual double addInsurance() = 0;
    virtual double addRush() = 0; 

  protected:
    int mWeight;
    int mDistance;
    int mTrackingID;
    bool mbInsured = false;
    bool mbRushed = false;
    bool mbDelivered = false;
    string mFrom;
    string mTo;
    double mCost;
};   
  
 
//############################################################################
//Postcard.h 
//############################################################################
//****************************************************************************
// File name:	  Postcard.h
// Author:		  James Corey
// Date:		    05/03/2021
// Class:		    CS250
// Assignment:  Polymorphism
// Purpose:		  header for class that represents a postcard
//****************************************************************************

#pragma once
#include "Parcel.h"

class Postcard : public Parcel {
public:
	Postcard ();

	bool read (istream&);
	void print (ostream&) const;

	int getDeliveryDay () const;
	void setCost ();

	double addInsurance ();
	double addRush ();

private:
	string mMessage;
};   
  
 
//############################################################################
//Letter.cpp 
//############################################################################
//****************************************************************************
// File name:	  Letter.cpp
// Author:		  James Corey
// Date:		    05/03/2021
// Class:		    CS250
// Assignment:  Polymorphism
// Purpose:		  defines the letter class
//****************************************************************************
#include "Letter.h"

#include <iostream>

Letter::Letter () : Parcel () {
}

//****************************************************************************
// Function:			getDeliveryDay
//
// Description:		calculates the number of days until the letter is delivered
//
// Parameters:		none
//
// Returned:			number of days until the letter is delivered
//****************************************************************************
int Letter::getDeliveryDay () const {
	const int MIN_DAYS = 1;
	const int MILES_PER_DAY = 100;

	int numDays = mDistance / MILES_PER_DAY;
	if (mDistance % MILES_PER_DAY != 0) {
		numDays++;
	}
	if (mbRushed) {
		if (numDays != MIN_DAYS) {
			numDays--;
		}
	}
	return numDays;
}

//****************************************************************************
// Function:			setCost
//
// Description:		sets the cost of the letter to the base cost
//
// Parameters:		none
//
// Returned:			none
//****************************************************************************
void Letter::setCost () {
	const double DOLLAR_PER_OUNCE = 0.45;
	mCost = mWeight * DOLLAR_PER_OUNCE;
}

//****************************************************************************
// Function:			addInsurance
//
// Description:		calculates the cost of adding insurance to a letter, adds 
//                the cost to the total cost
//
// Parameters:		None
//
// Returned:			The cost of adding insurance
//****************************************************************************
double Letter::addInsurance () {
	double insuranceCost = 0;
	const double INSURANCE_COST = 0.45;

	if (!mbInsured) {
		mCost += INSURANCE_COST;
		mbInsured = true;
		insuranceCost = INSURANCE_COST;
	}
	return insuranceCost;
}

//****************************************************************************
// Function:			addRush
//
// Description:		calculates the cost of rushing a letter, adds the cost to 
//                the total cost
//
// Parameters:		None
//
// Returned:			The cost of adding rush
//****************************************************************************
double Letter::addRush () {
	double rushCost = 0;
	double originalCost = mCost;
	const double RUSH_MULTIPLIER = 0.1;

	if (!mbRushed) {
		mCost *= RUSH_MULTIPLIER;
		mbRushed = true;
		rushCost = mCost - originalCost;
	}
	return rushCost;
}   
  
 
//############################################################################
//Overnight.cpp 
//############################################################################
//****************************************************************************
// File name:	  Overnight.cpp
// Author:		  James Corey
// Date:		    05/03/2021
// Class:		    CS250
// Assignment:  Polymorphism
// Purpose:		  defines the Overnight class
//****************************************************************************
#include "Overnight.h"

//****************************************************************************
// Constructor:	Overnight
//
// Description:	Default constructor for Overnight class, sets ints to 0 and 
//              strings to ""
//
// Parameters:	none
//
// Returned:		none
//****************************************************************************
Overnight::Overnight () : Parcel () {
	mVolume = 0;
}

//****************************************************************************
// Function:	  read
//
// Description:	reads in the data from an Overnight Package to a stream
//
// Parameters:	rcIn - the stream to read from 
//
// Returned:		true if the data is read in, or else false 
//****************************************************************************
bool Overnight::read (istream& rcInput) {
	bool bIsRead = Parcel::read (rcInput);
	if (bIsRead && rcInput >> mVolume) {
		bIsRead = true;
	}
	return bIsRead;
}

//****************************************************************************
// Function:			Print
//
// Description:		prints the overnight parcel to a stream
//
// Parameters:		rcOut - stream to be output to
//
// Returned:			None
//****************************************************************************
void Overnight::print (ostream& rcOutput) const {
	Parcel::print (rcOutput);
	rcOutput << "\t OVERNIGHT!";
}

//****************************************************************************
// Function:			getDeliveryDay
//
// Description:		calculates the number of days until the overnight package is 
//                delivered
//
// Parameters:		none
//
// Returned:			number of days until the package is delivered
//****************************************************************************
int Overnight::getDeliveryDay () const {
	const int MIN_DAYS = 1;
	const int MAX_DAYS = 2;
	const int MILES_PER_DAY = 1000;
	int numDays;

	if (mDistance <= MILES_PER_DAY || mbRushed) {
		numDays = MIN_DAYS;
	}
	else {
		numDays = MAX_DAYS;
	}
	return numDays;
}

//****************************************************************************
// Function:			setCost
//
// Description:		sets the cost of the overnight package to the base cost
//
// Parameters:		none
//
// Returned:			none
//****************************************************************************
void Overnight::setCost () {
	const int MIN_COST = 12;
	const int MAX_COST = 20;
	const int VOLUME_CUTOFF = 100;

	if (mVolume > VOLUME_CUTOFF) {
		mCost = MAX_COST;
	}
	else {
		mCost = MIN_COST;
	}
}

//****************************************************************************
// Function:			addInsurance
//
// Description:		calculates the cost of adding insurance to a package, adds 
//                the cost to the total cost
//
// Parameters:		None
//
// Returned:			The cost of adding insurance
//****************************************************************************
double Overnight::addInsurance () {
	double insuranceCost = 0;
	double originalCost = mCost;
	const double INSURANCE_MULTIPLIER = 0.25;

	if (!mbInsured) {
		mCost *= INSURANCE_MULTIPLIER;
		mbInsured = true;
		insuranceCost = mCost - originalCost;
	}
	return insuranceCost;
}

//****************************************************************************
// Function:			addRush
//
// Description:		calculates the cost of rushing an overnight package, adds 
//                the cost to the total cost
//
// Parameters:		None
//
// Returned:			The cost of adding rush
//****************************************************************************
double Overnight::addRush () {
	double rushCost = 0;
	double originalCost = mCost;
	const double RUSH_MULTIPLIER = 1.75;

	if (!mbRushed) {
		mCost *= RUSH_MULTIPLIER;
		mbRushed = true;
		rushCost = mCost - originalCost;
	}
	return rushCost;
}   
  
 
//############################################################################
//Parcel.cpp 
//############################################################################
//****************************************************************************
// File name:	  Parcel.cpp
// Author:		  James Corey
// Date:		    05/03/2021
// Class:		    CS250
// Assignment:  Polymorphism
// Purpose:		  defines the parcel parent class
//****************************************************************************
#pragma once
#include "Parcel.h"

//****************************************************************************
// Constructor:	Parcel
//
// Description:	Default constructor for Parcel class, sets ints to 0 and 
//              strings to "" for the variables that all 3 classes use
//
// Parameters:	none
//
// Returned:		none
//****************************************************************************
Parcel::Parcel () {
	mTrackingID = mWeight = mDistance = 0;
	mTo = mFrom = "null";
}

//****************************************************************************
// Function:	  read
//
// Description:	reads in the data to a stream, format that all 3 child classes
//              use
//
// Parameters:	rcIn - the stream to read from 
//
// Returned:		true if the data is read in, or else false 
//****************************************************************************
bool Parcel::read (istream& rcIn) {
	bool bIsRead = false;
	if (rcIn >> mTrackingID >> mTo >> mFrom >> mWeight >> mDistance) {
		bIsRead = true;
	}
	return bIsRead;
}

//****************************************************************************
// Function:			Print
//
// Description:		format of printing the data that all 3 child classes use
//
// Parameters:		rcOut - stream to be output to
//
// Returned:			None
//****************************************************************************
void Parcel::print (ostream& rcOut) const {
	rcOut << "TID: " << mTrackingID << "	From: " << mFrom << "	To: " << mTo;
	if (mbInsured) {
		cout << "\t INSURED";
	}
	if (mbRushed) {
		cout << "\t RUSH";
	}
}

//****************************************************************************
// Function:			getCost
//
// Description:		returns the cost of the parcel
//
// Parameters:		None
//
// Returned:			mCost, the cost of the parcel
//****************************************************************************
double Parcel::getCost () const {
	return mCost;
}   
  
 
//############################################################################
//Postcard.cpp 
//############################################################################
//****************************************************************************
// File name:	  Postcard.cpp
// Author:		  James Corey
// Date:		    05/03/2021
// Class:		    CS250
// Assignment:  Polymorphism
// Purpose:		  defines the postcard class
//****************************************************************************
#include "Postcard.h"

//****************************************************************************
// Constructor:	Postcard
//
// Description:	Default constructor for Postcard class, sets ints to 0 and 
//              strings to ""
//
// Parameters:	none
//
// Returned:		none
//****************************************************************************
Postcard::Postcard () : Parcel () {
	mMessage = "null";
}

//****************************************************************************
// Function:	  read
//
// Description:	reads in the data from a Postcard to a stream
//
// Parameters:	rcIn - the stream to read from 
//
// Returned:		true if the data is read in, or else false 
//****************************************************************************
bool Postcard::read (istream& rcIn) {
	bool bIsRead = Parcel::read (rcIn);
	if (bIsRead && rcIn >> mMessage) {
		bIsRead = true;
	}
	else {
		bIsRead = false;
	}
	return (bIsRead);
}

//****************************************************************************
// Function:			Print
//
// Description:		prints the postcard to a stream
//
// Parameters:		rcOut - stream to be output to
//
// Returned:			None
//****************************************************************************
void Postcard::print (ostream& rcOut) const{
	Parcel::print (rcOut);
	rcOut << "\t" << mMessage;
}

//****************************************************************************
// Function:			setCost
//
// Description:		sets the cost of the postcard to the base cost
//
// Parameters:		none
//
// Returned:			none
//****************************************************************************
void Postcard::setCost () {
	const double BASE_COST = 0.15;
	mCost = BASE_COST;
}

//****************************************************************************
// Function:			getDeliveryDay
//
// Description:		calculates the number of days until the postcard is 
//                delivered
//
// Parameters:		none
//
// Returned:			number of days until the letter is delivered
//****************************************************************************
int Postcard::getDeliveryDay () const {
	const int MILES_PER_DAY = 10;
	const int DAYS_RUSHED = 2;
	const int MIN_DAYS = 1;
	int numDays = mDistance / MILES_PER_DAY;

	if (mDistance % MILES_PER_DAY != 0) {
		numDays++;
	}
	if (mbRushed) {
		numDays -= DAYS_RUSHED;
		if (numDays < MIN_DAYS) {
			numDays = MIN_DAYS;
		}
	}
	return numDays;
}

//****************************************************************************
// Function:			addInsurance
//
// Description:		calculates the cost of adding insurance to a postcard, adds 
//                the cost to the total cost
//
// Parameters:		None
//
// Returned:			The cost of adding insurance
//****************************************************************************
double Postcard::addInsurance () {
	double insuranceCost = 0;
	const double INSURANCE_COST = 0.15;

	if (!mbInsured) {
		mCost += INSURANCE_COST;
		mbInsured = true;
		insuranceCost = INSURANCE_COST;
	}
	return insuranceCost;
}

//****************************************************************************
// Function:			addRush
//
// Description:		calculates the cost of rushing a postcard, adds the cost to 
//                the total cost
//
// Parameters:		None
//
// Returned:			The cost of adding rush
//****************************************************************************
double Postcard::addRush () {
	double rushCost = 0;
	const double RUSH_COST = 0.25;

	if (!mbRushed) {
		mCost += RUSH_COST;
		mbRushed = true;
		rushCost = RUSH_COST;
	}
	return rushCost;
}

   
  
 
//############################################################################
//Source.cpp 
//############################################################################
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
   
  
 
