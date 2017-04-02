#include <iostream>
using namespace std;

enum AlgorithmType {BACKTRACKING, BACKTRACKING_WITH_BOUNDS, DYNAMIC};
enum Color { RED, BLUE, NO_COLOR };

class NumberPainter {
private:
	int n;
	int* values;
	int colorless_values_q;
	int bb_partial_solution;

	void backtracking_solve(bool use_bounds);
	int backtracking(int index, int lastRedIndex, int lastBlueIndex, int colorless_q, bool use_bounds);


	int min(int a,int b,int c);


public:

	NumberPainter(){}
	NumberPainter(int n, int* values);

	~NumberPainter();

	int get_colorless_q();
	void paint_with(AlgorithmType a);

    friend ostream& operator<< (std::ostream& os, const NumberPainter& np);


};