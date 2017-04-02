#include "numberPainter.hpp"

int main(){

	int  n;
	cin >> n;
	
	int values[n];

	for(int i = 0; i < n; i++){
		cin >> values[i];
	}

	NumberPainter painter(n,values);
	painter.paint_with(DYNAMIC);

	cout << painter << endl;

	return 0;
}