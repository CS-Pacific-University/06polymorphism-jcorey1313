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