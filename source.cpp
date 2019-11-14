#include<iostream>
#include<vector>
using namespace std;

struct Crate {
	long long int height = 0;
	bool permanant = false;
};

//Precondition: All of the vectors must be sized correctly prior to being passed
//Postcondition: The crate configuration is set. The row and column maxes are set. The sum is set to the value of all the crates except one from each non zero spot
void initializeLayout(vector<vector<long long int>>& configuration, vector<Crate>& rMax, vector<Crate>& cMax, const int& numRows, const int& numCols, long long int &sum) {
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			cin >> configuration[r][c];
			if (configuration[r][c] >= 1)/*Adds to sum if height is greater than 1. Decrements to leave 1 crate to satisfy top camera*/
				sum = sum + (configuration[r][c]) - 1;
			if (configuration[r][c] > rMax[r].height)/*Updates rowMax if current is greater than max*/
				rMax[r].height = configuration[r][c];
			if (configuration[r][c] > cMax[c].height)/*Updates colMax if current is greater than max*/
				cMax[c].height = configuration[r][c];
		}
	}
}
 
//Precondition: initializeLayout must be called before this function
//Postcondition: The column maxes are all satisfied. Some rowmaxes may be satisfied
void optimizeColumns(const vector<vector<long long int>>& configuration, vector<Crate>& rMax, vector<Crate>& cMax, const int& numRows, const int& numCols, long long int &sum) {
	bool keepGoing;
	int i;
	for (int j = 0; j < numCols; j++) {
		keepGoing = true;
		i = 0;
		while (keepGoing && i < numRows) {
			if (cMax[j].height == rMax[i].height)
				if (configuration[i][j] != 0)
					if (rMax[i].permanant == false) {
						rMax[i].permanant = true;
						keepGoing = false;
					}
			i++;
		}
		i--;
		cMax[j].permanant = true;
		if(cMax[j].height != 0)
			sum -= cMax[j].height - 1;
	}
}

//Precondition: optimizeColumns must be called before this function
//Postcondition: all cameras are satisfied. The number stored in sum is the optimum number of crates that may be removed
void optimizeRows(vector<Crate>& rMax, const int& numRows, long long int &sum) {
	for (int i = 0; i < numRows; i++)
		if (rMax[i].permanant == false)
			if(rMax[i].height != 0)
				sum -= rMax[i].height - 1;
}

int main() {
	int numRows, numCols;
	long long int sum = 0;
	cin >> numRows >> numCols;
	vector<vector<long long int>> layout(numRows);
	vector<Crate>rowMax(numRows);
	vector<Crate>colMax(numCols);
	for (int i = 0; i < numRows; i++)
		layout[i].resize(numCols);
	
	initializeLayout(layout, rowMax, colMax, numRows, numCols, sum);
	optimizeColumns(layout, rowMax, colMax, numRows, numCols, sum);
	optimizeRows(rowMax, numRows, sum);
	
	cout << sum << endl;
	return 0;
}
