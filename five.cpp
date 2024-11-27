#include <iostream>
#include <vector>
#include <algorithm> // For std::find

int main() {
    std::vector<int> numbers;
    int input;
    int searchNumber;

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

    std::cout << "Enter the number to find its position: ";
    std::cin >> searchNumber;

    auto it = std::find(numbers.begin(), numbers.end(), searchNumber);
    if (it != numbers.end()) {
        int index = std::distance(numbers.begin(), it);
        std::cout << "The number " << searchNumber << " is at position " << index << " in the list." << std::endl;
    } else {
        std::cout << "The number " << searchNumber << " is not in the list." << std::endl;
    }

    return 0;
}