#include "numberPainter.hpp"

int main(){

	int  n;
	cin >> n;
	
	int values[n];

	for(int i = 0; i < n; i++){
		cin >> values[i];
	}

	NumberPainter painter(n,values);
	int min_Value = painter.paint_with(BACKTRACKING_WITH_BOUNDS);

	cout << min_Value << endl;

	return 0;
}