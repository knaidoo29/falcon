#include <iostream>
#include "falcon.h"

using namespace std;

int main(){

  cout << "Demonstrate use of progress bar for different type ints:" << endl;

  cout << "int :" << endl;

  int l = 1000000;

  for(int i = 0; i < l; i++){
    progress_bar(i, l, false);
  }

  for(int i = 0; i < l; i++){
    progress_bar(i, l, true);
  }

  cout << "long int :" << endl;

  long int l2 = 1000000;

  for(long int i2 = 0; i2 < l2; i2++){
    progress_bar(i2, l2, false);
  }

  for(long int i2 = 0; i2 < l2; i2++){
    progress_bar(i2, l2, true);
  }

  cout << "long long int :" << endl;

  long long int l3 = 1000000;

  for(long long int i3 = 0; i3 < l3; i3++){
    progress_bar(i3, l3, false);
  }

  for(long long int i3 = 0; i3 < l3; i3++){
    progress_bar(i3, l3, true);
  }

  return 0;
}
