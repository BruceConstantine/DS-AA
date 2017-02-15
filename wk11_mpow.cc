#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::list;
using std::vector;
using std::istringstream;
using std::ostream;

#include <math.h>
#include <stdlib.h>
#include <memory.h>

class nz {	    // one instance for every non-zero entry in matrix
public:
  nz() { ind = 0; val = 0.0; }
  nz(int i, double v) {	// constructor when given the two items of data
	ind = i;
	val = v;
  }
  int getInd() const { return ind; } // access to ind class member
  double getVal() const { return val; } // access to val class member
private:
  int ind;
  double val;
};

typedef list<nz> sparseRow;
typedef vector<sparseRow> sparseMat;

void readMat(sparseMat&);	// read from stdin
sparseMat mat_mutil(const sparseMat, const sparseMat);
sparseMat mat_pow( sparseMat , int );

int power = 0;
int n = 0;

int main(int argc, char *argv[])
{
  sparseMat rows;
  sparseMat mat_out;    
  power = atoi(argv[1]);
  if(power < 0)
	cerr<< "Illegal exponent; exiting." << endl;
  else{
	readMat(rows);
	if(power == 0){
		for (unsigned int c = 1; c < n; c++){
			cout<< c << " 1" << endl;
		}
		cout<< n << " 1";
		return 0;
	}
	else if(power == 1)
		mat_out = rows;
	else 
	  mat_out = mat_pow( rows , power );

	for(int j = 0 ; j < n ; j++) {
		list<nz>::iterator i;
		list<nz> tempList = mat_out[j];
		if( tempList.size() != 0 )
		  for( i = tempList.begin(); i != tempList.end() ; i++)
			cout << i->getInd() << " " << i->getVal() << " " ;
		else
			cout<<0;
		cout << endl;
	}	  
  }
  return 0;
}

void readMat(sparseMat& rows)
{
	string line;
	while (getline(cin, line))	// get next full line of text; NB: text
	{
	  istringstream lstream(line) ;
	  sparseRow row;
	  int col;
	  double val;
	  while (lstream>> col>> val) 
		{
		  nz next(col, val);
		  row.push_back(next);
		}
	  n++;
	  rows.push_back(row);
	}
}

sparseMat  mat_mutil(const sparseMat A, const sparseMat B){
  sparseMat mat_out;
  for (unsigned int c = 0; c < n; c++){
		  sparseRow row;
		  mat_out.push_back(row);	// initialise every row of transpose
  }
  for(int i = 0; i < n; i++){
	  list<nz> temp_a = A[i];
	  vector<double> rowSum(n,0);
	  for(list<nz>::iterator ia = temp_a.begin(); ia != temp_a.end(); ia++){
		  list<nz> temp_b = B[ia->getInd() - 1];
		  for(list<nz>::iterator ib = temp_b.begin(); ib != temp_b.end(); ib++){
			  rowSum[ib->getInd() - 1] += ib->getVal() * ia->getVal();
		  }
	  }
	  for(int c = 0; c < n; c++){
		  if(rowSum[c] != 0){
			  nz next(c+1, rowSum[c]);
			  mat_out[i].push_back(next);
		  }
	  }
  }
  
#if 0
 // B = mat_transp(B);
  for(int i = 0; i < n ; i++){
    list<nz> templist_a = A[i];
	list<nz>::iterator ia ;
	for(int j = 0; j < n; j++){
		  ia = templist_a.begin();
		  list<nz> templist_b = B[j];
		  list<nz>::iterator ib = templist_b.begin();
		  double sum_unit = 0;
		  list<nz>::iterator ite_next;
		  while( ia != templist_a.end() && ib != templist_b.end() ){
cout<<  ia->getInd() << " " << ia->getVal() <<endl;	////////////////////////////
cout<<  ib->getInd() << " " << ib->getVal() <<endl;		////////////////////////////
			if( ia->getInd() == ib->getInd()){
				sum_unit += ia->getVal() * ib->getVal();
cout<< " result = "<< sum_unit <<endl;	////////////////////////////
				ia++;
				ib++;
			}
			else if( ia->getInd() > ib->getInd()){
				ib++;
			}
			else{
				ia++;
			}		
		  }
		  cout<<"i = "<<i<<"   j = "<< j<<" turn finished"<<endl;////////////////////////////
		  if(sum_unit != 0){
			nz next(j+1, sum_unit); 
			mat_out[i].push_back(next);
cout<< "*****************************************8"<<endl;////////////////////////////
		  }
	  }
  }
  /*
  for(int k = 0 ; k < n; k++){
		list<nz> templist_a = A[k];
		for(int j = 0; j < n; j++){
			double aSum = 0;
			for(list<nz>::iterator ia = templist_a.begin(); ia!=templist_a.end(); ia++){
				int pos = ia->getInd()-1;
				list<nz> templist_b = B[pos];
				list<nz>::iterator ib = templist_b.begin();
				double sec_pair = 0;
				for(int count = 0 ; count <= j ; count++){
					  if( ib->getInd() < j+1 ){
						ib++;
					  }
					  else if(ib->getInd() == j+1){
						sec_pair = ib->getVal();
						break;
					  }
					  else{
						sec_pair = 0;
						break;
					  }
				}
				aSum += ia->getVal() * sec_pair;
			}
			if(aSum!=0){
				nz next(j+1, aSum);
				mat_out[k].push_back(next);
			}
		}
  }
  */
#endif
  return mat_out;
}

sparseMat mat_pow(sparseMat mat_in , int power){
	if(power == 1)
		return mat_in;
	if(power == 2)
		return mat_mutil( mat_in , mat_in );
	if( power%2 == 0 )
		return mat_pow( mat_mutil( mat_in , mat_in ) , power/2);
	else{
		return mat_mutil( mat_pow( mat_mutil( mat_in , mat_in ) , power/2) , mat_in);
	}
}
