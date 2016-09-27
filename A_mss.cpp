/*Maximun Subsequence Sum*/

#include<iostream>
using namespace std;

int sequence[] = { -1 , 2 , 0 , 3, -6, 9 , -10 , 8 , -2 , 5 , 0 , -1}; // sequence size is 12.
int basicOpreationCounter = 0;// count the addtions times.

/*enum */
/*算法上界分析:worst case O(n^3)*/
int maxmss_enum(const int arr[], const int n){ // n is size
	int i ,j, k;
	int maxSum = arr[0];
	for(i = 0 ; i < n ; i++ ){
		for(j = i ; j < n ; j++ ){
			int sum = 0;
			for(k = i ; k < j ; k++){
				sum += arr[k];
				basicOpreationCounter++;
			}
			if(sum > maxSum)
				maxSum = sum;
		}
	}
	cout<<"enumeration method: " << basicOpreationCounter <<" times addtions"<<endl;
	basicOpreationCounter = 0;
	return maxSum;
}

/*	sequence sum:S = A1+A2+...+An
	Sj - Si = A[i]+ A[i+1] + ... + A[j-1] + A[j]
*/
int maxmss_enum2(const int arr[] , const int n){
	int i ,j, k;
	int maxSum = arr[0];
	for(i = 0 ; i < n ; i++ ){
		int sum = 0;
		for	(j = i ; j < n ; j++ ){
			basicOpreationCounter++;
			sum += arr[j];
			if(sum > maxSum)
				maxSum = sum;
		}
	}
	cout<<"modified enumeration method: " << basicOpreationCounter <<" times addtions"<<endl;
	basicOpreationCounter = 0;
	return maxSum;
}

/*devide and conquer method
either exists entirely in one half, entirely in the other half
or it /spans/ the middle, in which case it is split into two pieces
where the end of one of the pieces is fixed.
	Recursive function like left tree traverse : every recursion must find the first return exit, 
	that is, it(function)  has to find the first atomic unit.
*/
/// DC method Begin...
int maxmssDC(const int arr[] , const int lo , const int hi ){
	
	if( lo == hi) return arr[lo];	//Recursive Boundary (RB) Atomic unit.
									/** In General, RB is two boundary variables cover into one value/index (var1 == var2 -> return ) */
	
	int mid = lo + ( hi - lo)/2;	/** Binary devide , mid is the center value (odd size) or the last center value (even size)*/
	
	int maxLHs = maxmssDC(arr, lo, mid);	/** Typical binary recursion(left traverse recursion), calculate the LEFT halves*/
	int maxRhs = maxmssDC(arr, mid+1, hi);  /** Typical binary recursion(left traverse recursion), this statement lead direction for traverse, calculate the RIGHT halves*/
	
	int max_LHalves_sum = arr[mid] , lhalves_sum = 0; // initinalizaion
	for(int i = mid ; i >= lo ; i--){				  // calculate the left hand side halves. begin point is mid ,end is lo, revise direction. 
		basicOpreationCounter++;						
		lhalves_sum += arr[i];
		if( max_LHalves_sum < lhalves_sum) max_LHalves_sum = lhalves_sum;
	}	
	
	int max_RHalves_sum = arr[mid+1] , rhalves_sum = 0;
	for(int i = mid+1 ; i <= hi; i++){
		basicOpreationCounter++;
		rhalves_sum += arr[i];
		if( max_RHalves_sum < rhalves_sum) max_RHalves_sum = rhalves_sum;
	}
	int LRbigger = ( (maxLHs > maxRhs)? maxLHs:maxRhs ) ; // return bigger value of both sides 
	return   (max_LHalves_sum + max_RHalves_sum ) > LRbigger ? (max_LHalves_sum + max_RHalves_sum ) : LRbigger; // the middle halves addtion is bigger or the LRbigger  is bigger
}	

int devideConquer(const int arr[] , const int lo , const int hi ){
	int mssNum = maxmssDC( arr , lo , hi );
	cout << "method devide and conquer has " << basicOpreationCounter << " times additions." << endl;
	basicOpreationCounter = 0;
	return mssNum;
}
/// End of DC method.

int main(){
	cout << "result is: " << maxmss_enum(sequence, 12) << endl;
	cout << "result is: " << maxmss_enum2(sequence, 12) << endl;
	cout << "result is: " << devideConquer(sequence, 0, 11) << endl;
	return 0;
}
