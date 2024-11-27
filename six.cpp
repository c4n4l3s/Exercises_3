#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<double> numbers;
    double input;

    std::cout << "Enter numbers (type 'q' to stop):" << std::endl;
    while (std::cin >> input) {
        numbers.push_back(input);
    }

    //Error fix
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (numbers.empty()) {
        std::cout << "No numbers were entered." << std::endl;
        return 1;
    }

    //Maximum number
    double maxNumber = *std::max_element(numbers.begin(), numbers.end());

    //Add number that is bigger than maximum number
    double newNumber = maxNumber + 1;
    numbers.push_back(newNumber);

    //Sort
    std::sort(numbers.begin(), numbers.end());

    //Output
    std::cout << "Sorted numbers: ";
    for (const double& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}