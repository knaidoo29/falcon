#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "falcon.h"

using namespace std;

int main(){

  cout << "FLOAT TYPE" << endl;

  string filename = "test4_file_float.txt";

  ofstream _file;
  _file.open(filename);
  _file << "# Header... add stuff here about whats in the file.\n";

  int size = 10;
  float rand1[size], rand2[size], rand3[size];

  get_randoms(rand1, size);
  get_randoms(rand2, size);
  get_randoms(rand3, size);

  string line;

  for(int i = 0; i < size; i++){
    line = to_string(rand1[i]) + "\t" + to_string(2.*rand2[i]) + "\t" + to_string(3.*rand3[i]) + "\n";
    _file << line;
    cout << line;
  }
  _file.close();

  vector<float>array;

  int rows, columns;

  rows = read_ascii_table(filename, array);
  columns = array.size()/rows;

  print_vector(array, true);

  cout << "DOUBLE TYPE" << endl;

  string filename2 = "test4_file_double.txt";

  ofstream _file2;
  _file2.open(filename2);
  _file2 << "# Header... add stuff here about whats in the file.\n";

  double rand12[size], rand22[size], rand32[size];

  get_randoms(rand12, size);
  get_randoms(rand22, size);
  get_randoms(rand32, size);

  for(int i = 0; i < size; i++){
    line = to_string(rand12[i]) + "\t" + to_string(2*rand22[i]) + "\t" + to_string(3*rand32[i]) + "\n";
    _file2 << line;
    cout << line;
  }
  _file2.close();

  vector<double>array2;

  rows = read_ascii_table(filename2, array2);
  columns = array.size()/rows;

  print_vector(array2, true);

  cout << "INT TYPE" << endl;

  string filename3 = "test4_file_int.txt";

  ofstream _file3;
  _file3.open(filename3);
  _file3 << "# Header... add stuff here about whats in the file.\n";

  int rand13[size], rand23[size], rand33[size];

  get_index(rand13, size);
  get_index(rand23, size);
  get_index(rand33, size);

  for(int i = 0; i < size; i++){
    line = to_string(rand13[i]) + "\t" + to_string(2*rand23[i]) + "\t" + to_string(3*rand33[i]) + "\n";
    _file3 << line;
    cout << line;
  }
  _file3.close();

  vector<double>array3;

  rows = read_ascii_table(filename3, array3);
  columns = array.size()/rows;

  print_vector(array3, true);

  return 0;
}
