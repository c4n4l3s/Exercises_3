#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main() {
    std::vector<double> numbers;
    double input;
    char choice;

    std::cout << "Enter numbers (type 'q' to stop):" << std::endl;
    while (std::cin >> input) {
        numbers.push_back(input);
    }

    //Errorsss
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (numbers.empty()) {
        std::cout << "No numbers were entered." << std::endl;
        return 1;
    }

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(0)));

    //Create a random index
    int randomIndex = std::rand() % numbers.size();

    std::cout << "Random number: " << numbers[randomIndex] << std::endl;

    return 0;
}