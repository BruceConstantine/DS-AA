#include <iostream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
  double epsilon;
  double d_unit;
  int colCounter = 0;
  string line;
  while (getline(cin, line))
    {
       istringstream lstream(line);
       colCounter = 0;
      while (lstream >> d_unit)
	{
	  colCounter++;
	  if(argc > 1 && string(argv[1]) == "-e")
	    {
	      epsilon = fabs(strtod(argv[2], 0));
	      if(  d_unit >= epsilon || d_unit <= -epsilon )             
		cout << colCounter << " " << d_unit << " " ;
	    }
	  else if(argc == 1)
	    {
	      if(d_unit != 0)             
		cout << colCounter << " " << d_unit << " " ;
	    }
	}
      cout << endl;
    }
  return 0;
}

#if 0
why this following code cannot pass the 'Execution Test 1'?
int main(int argc, char *argv[])
{

  double epsilon;
  if (argc > 1 && string(argv[1]) == "-e")
    epsilon = fabs(strtod(argv[2], 0));
  else 
    epsilon = 0;

  double d_unit;
  int colCounter = 0;
  string line;
  while (getline(cin, line))
    {
       istringstream lstream(line);
       colCounter = 0;
      while (lstream >> d_unit)
	{
	  colCounter++;
	  if(  d_unit >= epsilon || d_unit <= -epsilon )             
	       cout << colCounter << " " << d_unit << " " ;
	}
	cout << endl;
    }
  return 0;
}
#endif
