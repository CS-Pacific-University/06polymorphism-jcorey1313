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