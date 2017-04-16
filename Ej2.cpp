#include "numberPainter.hpp"

int main(){

	int  n;
	cin >> n;
	
	int values[n];

	for(int i = 0; i < n; i++){
		cin >> values[i];
	}

	NumberPainter painter(n,values);
	int minValue = painter.paintWith(BACKTRACKING_WITH_BOUNDS);

	cout << minValue << endl;

	return 0;
}