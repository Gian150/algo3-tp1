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

	int min_value = painter.paint_with(BACKTRACKING);
	cout << min_value << endl;

	return 0;
}