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