#include <iostream>
#include <vector>

using namespace std;

#define INF numeric_limits<int>::max()
#define MINUS_INF -INF

enum AlgorithmType {BACKTRACKING, BACKTRACKING_WITH_BOUNDS, DYNAMIC};


class NumberPainter {
private:
	int n;
	int* values;
	int best_actual_value;
	int** d_matrix;

	int backtracking(int index, int last_red_index, int last_blue_index, int colorless_numbers, bool use_bounds);
	int dynamic_algorithm();

	int min(int a,int b,int c);


public:

	NumberPainter(){}
	NumberPainter(int n, int* values);

	~NumberPainter();

	int paint_with(AlgorithmType a);

    friend ostream& operator<< (std::ostream& os, const NumberPainter& np);


};