// practice with macros being used as an object
// created 20150720

#include <iostream>
// this macro is considered fine
#define favnum
// this is not. no idea why at this point
#define FAVNUM 42

int main()
{
// here's some conditional compilation preprocessors
// they only compile if they've been defined in the past
// turns out this sort of macro needs to be in a function in order to be used.
#define PRINT_JOE
//so this will compile
#ifdef PRINT_JOE
std::cout<< "Joe" <<std::endl;
#endif
// this one will not
#ifdef PRINT_BOB
std::cout<< "Bob" <<std::endl;
#endif


    //this particular example should be avoided
    std::cout<<"My the answer to life, the universe, and everything else is: "<< FAVNUM<<std::endl;
    return 0;

}
