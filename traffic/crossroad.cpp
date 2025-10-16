#include "crossroad.h"

using namespace std;

Crossroad::Crossroad() {
	light1 = Car(2);
	light2 = Pedestrian(0);
}
void Crossroad::color_switch() {
	light1.switch_color();
	int color = light1.get_color();
	if (color != 1) {
		light2.switch_color();
	}
}
void Crossroad::print() {
	cout << "Pedestrian: " << light2.gcolor() << endl;
	cout << "Car: " << light1.gcolor() << endl << endl;
}