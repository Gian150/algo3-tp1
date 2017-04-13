#include "numberPainter.hpp"
#include <iostream>
#include <chrono>
using namespace std;

int main(){

	int  n;
	cin >> n;
	
	int values[n];

	for(int i = 0; i < n; i++){
		cin >> values[i];
	}

	NumberPainter painter(n,values);

	painter.paint_with(BACKTRACKING);
	cout << painter.get_colorless_q() << endl;

	return 0;
}