#include "trafficlight.h"

Car::Car() {
	number_of_colors = 3;
	TSet _color(3);
	color = _color;
	color.InsElem(0);
}
Car::Car(int colour) {
	number_of_colors = 3;
	TSet _color(3);
	color = _color;
	color.InsElem(colour);
}
void Car::switch_color() {
	for (int i = 0; i < number_of_colors; i++) {
		if (color.IsMember(i)) {
			color.DelElem(i);
			if (i == number_of_colors - 1) {
				color.InsElem(0);
			}
			else {
				color.InsElem(i + 1);
			}
			break;
		}
	}
}
int Car::get_color() {
	for (int i = 0; i < number_of_colors; i++) {
		if (color.IsMember(i)) {
			return i;
		}
	}
}
string Car::gcolor() {
	int colour = get_color();
	switch (colour) {
	case 0: 
		return "green";
	case 1: 
		return "yellow";
	case 2: 
		return "red";
	}
}

Pedestrian::Pedestrian() {
	number_of_colors = 2;
	TSet _color(2);
	color = _color;
	color.InsElem(0);
}
Pedestrian::Pedestrian(int colour) {
	number_of_colors = 2;
	TSet _color(2);
	color = _color;
	color.InsElem(colour);
}
void Pedestrian::switch_color() {
	for (int i = 0; i < number_of_colors; i++) {
		if (color.IsMember(i)) {
			color.DelElem(i);
			if (i == number_of_colors - 1) {
				color.InsElem(0);
			}
			else {
				color.InsElem(i + 1);
			}
			break;
		}
	}
}
int Pedestrian::get_color() {
	for (int i = 0; i < number_of_colors; i++) {
		if (color.IsMember(i)) {
			return i;
		}
	}
}
string Pedestrian::gcolor() {
	int colour = get_color();
	switch (colour) {
	case 0:
		return "green";
	case 1:
		return "red";
	}
}