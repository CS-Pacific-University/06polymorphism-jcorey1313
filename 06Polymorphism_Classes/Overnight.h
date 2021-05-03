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
