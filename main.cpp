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

	NumberPainter* painter = new NumberPainter(n,values);
	painter->paint_with(BACKTRACKING);

	delete painter;

	return 0;
}