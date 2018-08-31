#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "falcon.h"

using namespace std;

int main(){

  string filename = "test4_file.txt";

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

  rows = read_asci_table(filename, array);
  columns = array.size()/rows;

  print_vector(array, true);
  return 0;
}
