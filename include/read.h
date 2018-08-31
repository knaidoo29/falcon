#include <iostream>

using namespace std;

void read_ascii_table(string filename, int rows, int columns, int array[]);
void read_ascii_table(string filename, int rows, int columns, float array[]);
void read_ascii_table(string filename, int rows, int columns, double array[]);

int read_ascii_table(string filename, vector<int> &array);
int read_ascii_table(string filename, vector<float> &array);
int read_ascii_table(string filename, vector<double> &array);
