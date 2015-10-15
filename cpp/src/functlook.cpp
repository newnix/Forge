// practice pseudocode on functions
// function_practice.cpp 20150711

#include <iostream>

// this function does nothing but prove it's been called
void exfunct()
{
	std::cout<<"In the function exfunct()."<<std::endl;
	std::cout<<"Returning to main(). . . "<<std::endl<<std::endl;
}

// again, this function only proves that it's been called
void prefunct()
{
	std::cout<<"Entered function prefunct()."<<std::endl;
	std::cout<<"Calling function exfunct(). . ."<<std::endl;
	exfunct();
}

// now we need main() to do anything
int main()
{
	std::cout<<"This is main(), I'm the one needed to do anything"<<std::endl;
	std::cout<<"Calling function prefunct(). . ."<<std::endl;
	prefunct();
	std::cout<<"Ending the program. . . "<<std::endl;
	std::cin.clear();
	std::cin.get();
	return 0;
}
