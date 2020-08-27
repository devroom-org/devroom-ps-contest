#include <algorithm>
#include <iostream>
#include <iterator>

int main() {
    int lengths[3];
    for (int& l : lengths) {
        std::cin >> l;
    }
    std::sort(std::begin(lengths), std::end(lengths));

    const bool isIsosceles = lengths[0] == lengths[1] || lengths[1] == lengths[2];
    const bool isEquilateral = lengths[0] == lengths[2];
    if (isEquilateral) {
        std::cout << "Equilateral";
        return 0;
    }

    const int abSquared = lengths[0] * lengths[0] + lengths[1] * lengths[1];
    const int cSquared = lengths[2] * lengths[2];
    if (abSquared == cSquared) {
        std::cout << "Right";
    } else if (abSquared > cSquared) {
        std::cout << "Acute";
    } else {
        std::cout << "Obtuse";
    }

    if (isIsosceles) {
        std::cout << " isosceles";
    }
    std::cout << " triangle";
}