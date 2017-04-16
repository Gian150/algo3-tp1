#include "numberPainter.hpp"
#include <iostream>
using namespace std;

int main(){

	int  n;
	cin >> n;
	
	int values[n];

	for(int i = 0; i < n; i++){
		cin >> values[i];
	}

	NumberPainter painter(n,values);

	int minValue = painter.paintWith(BACKTRACKING);
	cout << minValue << endl;

	return 0;
}