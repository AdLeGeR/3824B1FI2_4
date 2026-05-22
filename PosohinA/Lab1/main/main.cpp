#include"../lib_interface/interface.h"


int main() {
	Interface menu;
	std::cout << "Welcome to the polynomial calculator" << std::endl;
	menu.input_polyn();
	menu.actions();
}