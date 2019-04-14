#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

int main () 
{
        char buffer[256];
        ifstream examplefile("t.txt");
        if (! examplefile.is_open())
		{ cout << "Error opening file"; exit (1); }

	while (! examplefile.eof() ) {
		examplefile.getline (buffer,100);
		cout << buffer << endl;
        }
        return 0;
}
 