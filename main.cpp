#include <iostream>


int main()
{
    //std::cout << "Hello, World!" << std::endl;
    // call rnd_rnd_by_seed function
    //auto val = rnd_by_seed(12);
    //printf("val = %llu", val);
    srand(13); // seed the random number generator
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
