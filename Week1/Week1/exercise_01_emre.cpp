//#include <iostream>
//#include <vector>
//#include <numeric>
//#include <algorithm>
//
//float convertToFahrenheit(float celcius)
//{
//	return (celcius * 9.0f / 5.0f) + 32;
//}
//
//float convertToMiles(float kilometers)
//{
//	return kilometers / 1.6f;
//}
//
//float convertToKilograms(float pounds)
//{
//	return pounds * 0.45f;
//}
//
//float convertToEuros(float dollars)
//{
//	return dollars * 0.85f;
//}
//
//void promptExercise1() {
//	std::string UserName;
//	int UserAge = 0;
//
//	std::cout << "Enter your name: " << std::endl;
//	std::cin >> UserName;
//
//	std::cout << "Enter your age: " << std::endl;
//	std::cin >> UserAge;
//
//	std::cout << "User Name: " << UserName << std::endl;
//	std::cout << "User Age: " << UserAge << std::endl;
//}
//
//void promptExercise2() {
//	float celcius;
//	std::cout << "Enter degrees in C: " << std::endl;
//	std::cin >> celcius;
//	float fahrenheit = convertToFahrenheit(celcius);
//	std::cout << "Degrees in F: " << fahrenheit << std::endl;
//
//	float kilometers;
//	std::cout << "Enter kilometers: " << std::endl;
//	std::cin >> kilometers;
//	float miles = convertToMiles(kilometers);
//	std::cout << "Miles: " << miles << std::endl;
//
//	float pounds;
//	std::cout << "Enter pounds: " << std::endl;
//	std::cin >> pounds;
//	float kilograms = convertToKilograms(pounds);
//	std::cout << "Kilograms: " << kilograms << std::endl;
//
//	float dollars;
//	std::cout << "Enter dollars: " << std::endl;
//	std::cin >> dollars;
//	float euros = convertToEuros(dollars);
//	std::cout << "Euros: " << euros << std::endl;
//}
//
//void promptExercise3() {
//	std::vector<float> numbers = { 10.5f, 23.3f, 5.0f, 99.9f, 12.1f };
//	float sum = std::accumulate(numbers.begin(), numbers.end(), 0.0f);
//	float average = sum / numbers.size();
//	std::cout << "Average: " << average << std::endl;
//}
//
//void promptExercise4() {
//	std::vector<int> numbers;
//	int number_1, number_2, number_3, number_4, number_5;
//
//	std::cout << "Enter 5 numbers pressing Enter after each: " << std::endl;
//	std::cin >> number_1 >> number_2 >> number_3 >> number_4 >> number_5;
//
//	numbers.push_back(number_1);
//	numbers.push_back(number_2);
//	numbers.push_back(number_3);
//	numbers.push_back(number_4);
//	numbers.push_back(number_5);
//
//	int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
//	std::cout << "The sum is: " << sum << std::endl;
//
//	int largest_number = *std::max_element(numbers.begin(), numbers.end());
//	std::cout << "The largest number is: " << largest_number << std::endl;
//
//	int smallest_number = *std::min_element(numbers.begin(), numbers.end());
//	std::cout << "The smallest number is: " << smallest_number << std::endl;
//
//	int guess_number;
//	std::cout << "Enter a number: " << std::endl;
//	std::cin >> guess_number;
//	bool found = (std::find(numbers.begin(), numbers.end(), guess_number) != numbers.end());
//	if (found) {
//		std::cout << "The number " << guess_number << " is in the list." << std::endl;
//	}
//	else {
//		std::cout << "The number " << guess_number << " is not in the list." << std::endl;
//	}
//}
//
//int main()
//{
//	promptExercise4();
//}
//
//
