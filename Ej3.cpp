#include "numberPainter.hpp"

int main(){

	int  n;
	cin >> n;
	
	int values[n+1];

	for(int i = 0; i < n; i++){
		cin >> values[i];
	}
	
	NumberPainter painter(n,values);
	int min_value = painter.paint_with(DYNAMIC);

	cout << min_value << endl;

	return 0;
}