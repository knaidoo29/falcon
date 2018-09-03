#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "falcon.h"

using namespace std;

int main(){

  int size = 20;
  int data[size];
  float data2[size];
  float data3[size];
  double data4[size];

  cout << "- Create INT, FLOAT, FLOAT & DOUBLE" << endl;

  for(int i = 0; i < size; i++){
    data[i] = (int) i;
    data2[i] = 2.1 * (float) i;
    data3[i] = 3.2 * (float) i;
    data4[i] = 0.25 * (double) i;
  }

  cout << "- Write to file:" << endl;

  string filename;
  filename = "test_5.txt";
  Writer wr;
  wr.add2header("random header.");
  wr.add2header("more random header.");
  wr.add2header("even more random header.");
  wr.store(data, size, "test", "int");
  wr.store(data2, size, "test2");
  wr.store(data3, size, "test3");
  wr.store(data4, size, "test4", "double");
  wr.write2file(filename);

  cout << "\t Read data in:" << endl;

  print_file(filename);

  Reader re;

  re.readfile(filename);

  vector<int>array1;
  vector<float>array2;
  vector<float>array3;
  vector<double>array4;

  re.extract("test", array1);
  print_vector(array1);

  re.extract("test2", array2);
  print_vector(array2);

  re.extract("test3", array3);
  print_vector(array3);

  re.extract("test4", array4);
  print_vector(array4);

  return 0;
}
