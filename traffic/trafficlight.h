#pragma once

#include "tset.h"
#include <iostream>

using namespace std;

class Traffic_light {
protected: 
	int number_of_colors;
	TSet color = TSet(1);
public:
	virtual void switch_color() = 0;
	virtual int get_color() = 0;
};

class Car : public Traffic_light {
public:
	Car();
	Car(int colour);
	void switch_color();
	int get_color();
	string gcolor();
};

class Pedestrian : public Traffic_light {
public:
	Pedestrian();
	Pedestrian(int colour);
	void switch_color();
	int get_color();
	string gcolor();
};