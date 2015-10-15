// This is a practice program practicing using functions as variables
// Written 20150711

#include <iostream>
// literally just returns 5
int return5()
{
	return 5;
}

// inform stdout of a function jump
void jump()
{
	std::cout<<"We're outside of main()."<<std::endl;
	std::cout<<"Going back. . ."<<std::endl;
}

// starting main().
int main()
{
	std::cout<<"We'll run a few functions now."<<std::endl;
	std::cout<<return5()<<std::endl;
	std::cout<<"And now let's throw in a little math."<<std::endl;
	std::cout<<return5() * 4<<std::endl;
	std::cout<<return5()<<return5()<<std::endl;
	std::cout<<return5() + 10<<std::endl;
	jump();
	return 0;
}
