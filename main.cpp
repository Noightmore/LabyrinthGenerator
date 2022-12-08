#include <iostream>

extern "C" unsigned long long rnd_by_seed(unsigned long long seed);

int main()
{
    std::cout << "Hello, World!" << std::endl;
    // call rnd_rnd_by_seed function
    auto val = rnd_by_seed(12);
    printf("val = %llu", val);
    return 0;
}
