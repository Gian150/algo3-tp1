#include <iostream>
using namespace std;

enum AlgorithmType {BACKTRACKING, BACKTRACKING_WITH_BOUNDS, DYNAMIC};
enum Color { RED, BLUE, NO_COLOR };

class NumberPainter {
private:
	int n;
	int* values;
	int bestActualValue;
	int** solutionsMatrix;

	int backtracking(int index, int lastRedIndex, int lastBlueIndex, int colorlessNumbers, bool useBounds);
	int dynamicAlgorithm();

	int min(int a,int b,int c);


public:

	NumberPainter(){}
	NumberPainter(int n, int* values);

	~NumberPainter();

	int paintWith(AlgorithmType a);

    friend ostream& operator<< (std::ostream& os, const NumberPainter& np);


};