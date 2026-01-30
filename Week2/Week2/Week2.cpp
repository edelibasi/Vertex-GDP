#include <iostream>
#include <string>
#include "Phone.h"
#include <vector>

int main()
{
	Phone IPhone("iPhone", 123456);
	Phone Samsung("Samsung", 654321);
	Phone GooglePixel("Google Pixel", 112233);
	std::vector<Phone> Phones = { IPhone, Samsung, GooglePixel };

	for (Phone Phone: Phones) {
		std::cout << "Phone Serial Number: " << Phone.GetSerialNumber() << std::endl;
		std::cout << "Phone Name: " << Phone.GetName() << std::endl;
		std::cout << "Phone Battery Life: " << Phone.GetBatteryLife() << std::endl;
	}

    return 0;
}
