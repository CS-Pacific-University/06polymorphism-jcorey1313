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