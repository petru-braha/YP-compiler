#include <iostream>
#include <vector>

int main()
{
    std::size_t n = 2;
    int value = 5;
    std::allocator<int> number;
    std::vector<int> dada(n, value, number);
    if(5 != dada[0] || 5 != dada[1])
        std::cout << "error\n";
}
