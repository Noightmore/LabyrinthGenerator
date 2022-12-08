#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"
#include <iostream>


int main(int argc, char** argv)
{
    int * width = new int(std::stoi(argv[1]));
    int * height = new int(std::stoi(argv[2]));
    int * seed = new int(std::stoi(argv[3]));

    std::cout << "Width: " << *width << std::endl;
    std::cout << "Height: " << *height << std::endl;
    std::cout << "seed: " << *seed << std::endl;

    srand(* seed); // seed the random number generator
    // generate random number between 0 and 5
    int random_variable = rand() % 6;
    // print seed values
    std::cout << random_variable << std::endl;
    random_variable = rand() % 6;
    std::cout << random_variable << std::endl;
    random_variable = rand() % 6;
    std::cout << random_variable << std::endl;
    random_variable = rand() % 6;
    std::cout << random_variable << std::endl;
    return 0;
}

#pragma clang diagnostic pop