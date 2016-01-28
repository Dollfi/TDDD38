// Program that shows usage of commandline arguments
// You add two arguments to the main function (always of types int and (char*)[])
// On a POSIX-system, the name used to call the runnable file is argv[0]

#include <iostream>
using namespace std;

int main(int argc, char * argv[])
{
	// Require 2 arguments
	if ( argc != 3 )
	{
		cerr << "Wrong arg count!" << endl;
	// return something else than 0 if program didn't end successfully
		return 1; 
	}
	for ( int arg {}; arg < argc; ++arg )
	{
		cout << argv[arg] << endl;
	}
	return 0; 
}
