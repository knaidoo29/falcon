#include <iostream>
#include "falcon.h"

using namespace std;

int main(){

  cout << "Test 'merge_sort' function for array types float, double" << endl;

  int size = 100;

  int rands_f_ind[size];
  float rands_f[size];

  get_index(rands_f_ind, size);
  get_randoms(rands_f, size);

  cout << "\nARRAY Float randoms:" << endl;

  print_array(rands_f, size, true);

  merge_sort(rands_f, rands_f_ind, size);

  cout << "\nAfter merge sort:" << endl;

  print_array(rands_f, size, true);

  int rands_d_ind[size];
  double rands_d[size];

  get_index(rands_d_ind, size);
  get_randoms(rands_d, size);

  cout << "\nARRAY Double randoms:" << endl;

  print_array(rands_d, size, true);

  merge_sort(rands_d, rands_d_ind, size);

  cout << "\nAfter merge sort:" << endl;

  print_array(rands_d, size, true);

  cout << "\nTest 'merge_sort' function for vector types float, double" << endl;

  vector<int>rands_fv_ind;
  vector<float>rands_fv;

  rands_fv_ind = vector<int>(size);
  rands_fv = vector<float>(size);

  get_index(rands_fv_ind, size);
  get_randoms(rands_fv, size);

  cout << "\nVECTOR Float randoms:" << endl;

  print_vector(rands_fv, true);

  merge_sort(rands_fv, rands_fv_ind, size);

  cout << "\nAfter merge sort:" << endl;

  print_vector(rands_fv, true);

  vector<int>rands_dv_ind;
  vector<double>rands_dv;

  rands_dv_ind = vector<int>(size);
  rands_dv = vector<double>(size);

  get_index(rands_dv_ind, size);
  get_randoms(rands_dv, size);

  cout << "\nVECTOR Double randoms:" << endl;

  print_vector(rands_dv, true);

  merge_sort(rands_dv, rands_dv_ind, size);

  cout << "\nAfter merge sort:" << endl;

  print_vector(rands_dv, true);

  return 0;
}
