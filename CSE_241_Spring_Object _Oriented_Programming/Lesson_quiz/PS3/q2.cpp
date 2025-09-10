#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>


using namespace std;

int main(){

	srand(time(0));

	vector<int> suitors;
	
	int num_suitors;
	cout << "Please enter the number of suitors" << endl;
	cin >> num_suitors;

	for(int i=0; i < num_suitors; i++){
		suitors.push_back(i+1);
	}

	cout << "Vector size = " << suitors.size() << endl;
	// suitors.erase(suitors.begin()+3);

	// cout << "Vector size = " << suitors.size() << endl;

		
	



int ind=0;
int count = 0;
	while(suitors.size() != 1 && count < 15){

		for(int i=0; i < suitors.size(); i++){
			cout << suitors[i];
		}
		cout << " initial list of suitors, start counting from" << suitors[ind] << endl;

		if(ind >= suitors.size() - 1){
			ind = ind - suitors.size();
		}
		ind += 2;
		if (suitors.size() > 1)
			suitors.erase(suitors.begin() + ind);
		
		for(int i=0; i < suitors.size(); i++){
			cout << suitors[i];
		}

		if(suitors.size() == 1){
			cout << " suitor " << suitors[ind] - 1 << " eliminated" << " , winner " << suitors[0] << endl;
			break;
		}
		cout << " suitor " << suitors[ind]-1 << " eliminated" << " , continue counting" << suitors[ind] << endl;

		cout << " suitor " << suitors[ind]-1 << " eliminated" << " , continue counting" << suitors[ind] << endl;

		count ++;

	}




	return 0;
}