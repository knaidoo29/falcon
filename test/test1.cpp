#include <iostream>
#include "falcon.h"

using namespace std;

int main(){

  cout << "Test 'print_array' function for types int, float, double" << endl;

  int size = 10;

  int arri[size];
  float arrf[size];
  double arrd[size];

  for(int i = 0; i < size; i++){
    arri[i] = i;
    arrf[i] = 0.1 + (float) i;
    arrd[i] = 0.999 + (double) i;
  }

  print_array(arri, size, true);
  print_array(arrf, size, true);
  print_array(arrd, size, true);

  cout << "--> Done." << endl;

  cout << "\nTest 'get_randoms' function for array type float and double." << endl;

  size = 100;

  float rands_f[size];
  double rands_d[size];

  get_randoms(rands_f, size);
  get_randoms(rands_d, size);

  print_array(rands_f, size, true);
  print_array(rands_d, size, true);

  cout << "--> Done." << endl;

  cout << "\nTest 'get_randoms' function for vector type float and double." << endl;

  vector<float>rands_fv;
  vector<double>rands_dv;

  rands_fv = vector<float>(size);
  rands_dv = vector<double>(size);

  get_randoms(rands_fv, size);
  get_randoms(rands_dv, size);

  cout << "--> Done." << endl;

  cout << "\nTest 'print_vector' function for types float, double" << endl;

  print_vector(rands_fv, true);
  print_vector(rands_dv, true);

  cout << "--> Done." << endl;

  return 0;
}
