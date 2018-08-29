#include <iostream>
#include "falcon.h"

using namespace std;

int main(){

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

  return 0;
}
