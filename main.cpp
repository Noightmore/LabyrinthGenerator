#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include <iostream>
#include "Models/Headers/Grid.h"


int main([[maybe_unused]] int argc, char** argv)
{
    // alokace paramatru na heap
    int * width = new int(std::stoi(argv[1]));
    int * height = new int(std::stoi(argv[2]));
    int * seed = new int(std::stoi(argv[3]));

    std::cout << "Width: " << *width << std::endl;
    std::cout << "Height: " << *height << std::endl;
    std::cout << "seed: " << *seed << std::endl;

    // grid se taky alokuje na heap
    Grid * grid = new Grid(width, height, seed);

    // vypis gridu
    grid->printGrid();

    // konec programu, jiz zadna data nepotrebujeme
    delete width;
    delete height;
    delete seed;
    grid->~Grid();

    return 0;
}

#pragma clang diagnostic pop