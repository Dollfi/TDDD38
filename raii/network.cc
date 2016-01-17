#include "Connection.h"
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
int main()
try // function-try block
{
  Network_Stream ns {"SOME_HOST"};
  ns.exceptions(true);
  cout << "Enter message to server: ";
  // scoping the line-variable to the input operations
  for ( string line; getline(cin, line);  )  
  {
    ns.send(line);
    ns.recv(line);
    cout << "Server answer: " << line << endl;
  }
  return 0;
}
catch (exception const & e )
{
  cerr << "ERROR: \"" << e.what() << "\", exiting!" << endl;
}
