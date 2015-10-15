// this is the separate main()
// created 20150712

#include <iostream>

int add(int x, int y);

int main()
{
    int x, y;
    std::cout<<"Running simple function as a separate file..."<<std::endl;
    std::cout<<"Enter a number: ";
    std::cin>>x;
    std::cout<<"One more: ";
    std::cin>>y;
    std::cout<<"The sum of those numbers is: "<<add(x,y)<<std::endl;
    return 0;
}
