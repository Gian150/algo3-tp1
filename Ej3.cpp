#include "numberPainter.hpp"

int main(){

	int  n;
	cin >> n;
	
	int values[n+1];

	for(int i = 0; i < n; i++){
		cin >> values[i];
	}
	
	NumberPainter painter(n,values);
	int minValue = painter.paintWith(DYNAMIC);

	cout << minValue << endl;

	return 0;
}