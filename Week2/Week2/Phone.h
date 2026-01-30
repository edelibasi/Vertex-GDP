#pragma once

#include <string>

class Phone
{
	public:
		Phone(std::string Name, int SerialNumber);
		void PrintBatteryLife();
		void TakePhoto();
		void SetFactoryDefaults();
		void ChargeBattery(int charge);
		void MakeCall();
		void SetSerialNumber(int serialNumber);
		std::string GetName();
		int GetSerialNumber();
		int GetBatteryLife();

	private:
		std::string Name;
		int SerialNumber;
		float BatteryLife;
		float InternalTemperature;
};

