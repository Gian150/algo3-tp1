#include <iostream>
using namespace std;

enum AlgorithmType {BACKTRACKING, BACKTRACKING_WITH_BOUNDS, DYNAMIC_ALGORITHM};
enum Color { RED, BLUE, NO_COLOR };

class NumberPainter {
private:
	int n;
	int* values;
	int colorless_values_q;

	int backtracking(int index, int lastRedIndex, int lastBlueIndex, int colorless_q);
	int backtracking_bound();

	void backtracking_solve();
	void backtracking_bounds_solve();

	int min(int a,int b,int c);


public:

	NumberPainter(){}
	NumberPainter(int n, int* values);
	NumberPainter(const NumberPainter& other);

	~NumberPainter();

	int get_colorless_q();
	void paint_with(AlgorithmType a);

    friend ostream& operator<< (std::ostream& os, const NumberPainter& np);


};