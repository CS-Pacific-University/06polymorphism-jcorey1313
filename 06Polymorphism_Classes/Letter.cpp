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