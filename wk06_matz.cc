//This code I can not guarantee 80% correct.

#include <iostream>
#include <sstream>

using std::cin; 
using std::cout;
using std::cerr;
using std::endl;
using std::ofstream;
using std::ostringstream;
using std::string;

#include <math.h>
#include <stdlib.h>

typedef struct {
  double value;
  int row;
  int column;
} Trinity;


int main(int argc, char *argv[])
{
  int row = atoi(argv[1]);
  int column = atoi(argv[2]);

  if (row != column)
  {
    cerr<< "Matrix dimensions mismatch; exiting.\n";
    exit(-1);
  }

  double d_unit;
  int input_counter = 1;
  int uzNum = 0;
  ostringstream oss; 
  Trinity tri_list[column];
  int lineIndex = 0;
  string str;
  
  cout << column << endl;
while( cin >> d_unit )
{
    if( d_unit ) //if this is not zero
    {                 
      tri_list[lineIndex].value = d_unit;
      tri_list[lineIndex].row = input_counter / column ;
      if( !(input_counter % column) ) // input_counter % column == 0
	tri_list[lineIndex++].column = column ;
      else
	tri_list[lineIndex++].column = input_counter % column ;   
    }

    if(input_counter % column == 0) // if end of a line.
     {
       	oss.str("");
        oss << lineIndex;
        str = oss.str();
	uzNum += lineIndex;  // count this line non-zero number and added into uzNum .
        for(int i=0; i<lineIndex; i++)
	{
	  str += " ";
	  
	  oss.str("");
	  oss << tri_list[i].column;
	  str += oss.str();
	  
	  str += " ";
	  
	  oss.str("");
	  oss << tri_list[i].value;
	  str += oss.str();
	}
         str += '\n';
   	 lineIndex = 0; 
	 cout << str;
     } 
    // if( input_counter % column == 0 && 0 == lineIndex) // if end of a line.&& No nznum
    //  {
    //	cout <<"0"<< endl;
    //    break;
    //  }
      
   input_counter++;
}  
 cout << uzNum ;
 
  return 0;
}
                                  // d_unit is non-zero number;    if( input_counter++ % column == 0){
                                   //      cout << d_unit << endl;
                                   //    }
                                   //    else
                                   //       cout << d_unit << ' ';
