#include "Phone.h"
#include <string>
#include <iostream>


Phone::Phone(std::string Name, int SerialNumber) :
	Name(Name),
	SerialNumber(SerialNumber),
	BatteryLife(15.0f),
	InternalTemperature(30.0f)
{
}

void Phone::PrintBatteryLife()
{
	std::cout << "Battery Life: " << BatteryLife << " hours" << std::endl;
}

void Phone::TakePhoto()
{
	std::cout << "Photo taken!" << std::endl;
}

void Phone::SetFactoryDefaults()
{
	BatteryLife = 15.0f;
	InternalTemperature = 30.0f;
	std::cout << "Factory defaults restored." << std::endl;
}

void Phone::ChargeBattery(int charge)
{
	BatteryLife += charge;

	if (BatteryLife > 100.0f)
	{
		BatteryLife = 100.0f;
	}

	std::cout << "Battery charged. Current battery life is: " << BatteryLife << " percent" << std::endl;
}

void Phone::MakeCall()
{
	if (BatteryLife <= 5.0f)
	{
		std::cout << "Low battery, please charge!" << std::endl;
		return;
	}
	BatteryLife -= 5.0f;
	std::cout << "Making a call..." << std::endl;
}

void Phone::SetSerialNumber(int serialNumber)
{
	SerialNumber = serialNumber;
}

int Phone::GetSerialNumber()
{
	return SerialNumber;
}

int Phone::GetBatteryLife()
{
	return BatteryLife;
}

std::string Phone::GetName()
{
	return Name;
}
