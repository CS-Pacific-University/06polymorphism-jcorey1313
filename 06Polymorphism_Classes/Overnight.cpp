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