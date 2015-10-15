// practicing reuse of variables.
// created 20150712
// adding extra comments for help defining scope for future reference



#include <iostream>

// function getvar() will read a value from stdin, and store it in a var for later use.
// all functions declared here are accessible to any other function. normally only used in main() though.
int getvar()
{
    std::cout<<"Enter an integer: ";
	int a; // create a var only available in this function
	std::cin>>a; 
	return a;
} //as of here, 'a' is destroyed

int add(int x, int y)
{
	return x + y; 
} // 'x' and 'y' are destroyed here

int multiply(int x, int y)
{
	return x * y;
}

int subtract(int x, int y)
{
	return x - y;
}

int doublenum(int x)
{
	return x * 2;
}


int main()
{
	// these vars are only useable here.
	int x = getvar();
	int y = getvar();
	std::cout<<x<<" + "<<y<<" = "<< x + y <<std::endl;
	std::cout<<"The sum of your integers is: "<<add(x,y)<<std::endl;
	std::cout<<"The product of your integers is: "<<multiply(x,y)<<std::endl;
	std::cout<<"The difference between them is: "<<subtract(x,y)<<std::endl;
	std::cout<<"Doubling both ints... "<<std::endl;
	std::cout<<x<<" doubled is: "<<doublenum(x)<<std::endl;
	std::cout<<y<<" doubled is: "<<doublenum(y)<<std::endl;
	std::cout<<"Exiting..."<<std::endl;
	return 0;
}
