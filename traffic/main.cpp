#include "crossroad.h"

int main() {
	Crossroad example;
	for (int i = 0; i < 7; i++) {
		example.print();
		example.color_switch();
	}
	return 0;
}