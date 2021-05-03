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

