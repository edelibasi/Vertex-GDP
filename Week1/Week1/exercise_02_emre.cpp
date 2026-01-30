#include <iostream>
#include <vector>

int getHighestNumber(const std::vector<int>& numbers) {
	if (numbers.empty()) {
		throw std::invalid_argument("The input vector is empty.");
	}
	int highest = numbers[0];
	for (const int& number : numbers) {
		if (number > highest) {
			highest = number;
		}
	}
	return highest;
}

void printDoubledNumbers(const std::vector<int>& Numbers) {
	for (int i = 0; i < Numbers.size() - 1; ++i) {
		std::cout << "You entered: " << Numbers.at(i) * 2 << std::endl;
		i++;
	}
}

void promptExercise1() {
	std::vector<int> Numbers;

	for (int count = 1; count <= 5; ++count) {
		std::cout << "Please insert number #" << count << ": " << std::endl;
		int number;
		std::cin >> number;
		Numbers.push_back(number);
	}

	std::cout << "The highest number is: " << getHighestNumber(Numbers) << std::endl;
}

void promptExercise2() {
	int Number = -1;
	std::vector<int> Numbers;
	
	while (Number != 0) {
		std::cout << "Please insert a number: " << std::endl;
		std::cin >> Number;
		Numbers.push_back(Number);
	} 

	printDoubledNumbers(Numbers);
}

void promptExercise3() {
	std::vector<int> Numbers;

	for (int count = 1; count <= 5; ++count) {
		std::cout << "Please insert number #" << count << ": " << std::endl;
		int number;
		std::cin >> number;
		Numbers.push_back(number);
	}

	std::reverse(Numbers.begin(), Numbers.end());

	for(const int& num : Numbers) {
		std::cout << num << " ";
	}
}

void promptExercise4() {
	float Height = -1.f;
	float Width = -1.f;
	float TotalArea = 0.f;

	while (Height != 0.f && Width != 0.f) {
		std::cout << "Please insert width: " << std::endl;
		std::cin >> Width;

		if (Width == 0.f) {
			break;
		}

		std::cout << "Please insert height: " << std::endl;
		std::cin >> Height;
		TotalArea += Width * Height;
	}

	std::cout << "Total Square Meters is: " << TotalArea << std::endl;
}

int main() {
	promptExercise4();
	return 0;
}



