
#define BACKTRACKING 0
#define BACKTRACKING_WITH_BOUNDS 1
#define DYNAMIC_ALGORITHM 2
#define SIN_COLOR 0
#define ROJO 1
#define AZUL 2

class NumberPainter {
private:
	int n;
	int* values;
	int* colors;
	int red_values_q;
	int blue_values_q;
	int colorless_values_q;

	void backtracking(int index, int lastRedIndex, int lastBlueIndex, int colorless_q);
	void backtracking_solve();

	int min(int a,int b,int c);


public:

	NumberPainter(){}
	NumberPainter(int n, int* values);
	NumberPainter(NumberPainter& other);

	~NumberPainter();

	int get_colorless_q();
	void paint_with(int algorithm_type);


};