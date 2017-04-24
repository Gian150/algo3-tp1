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
	int bestActualValue;
	int** dMatrix;

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