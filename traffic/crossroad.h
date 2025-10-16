#pragma once

#include "trafficlight.h"

class Crossroad {
	Car light1;
	Pedestrian light2;
public:
	Crossroad();
	void color_switch();
	void print();
};