#include <iostream>

using namespace std;

template<typename TYPE>
void progress_bar(TYPE i, TYPE size, bool include_index = false){
  TYPE bar_length = 50;
  double j, sizej;
  if(i != 0){
    if((bar_length*i)/size != (bar_length*(i+1))/size or i==size){
      cout.flush();
      cout << "\r|";
      for(int j = 0; j < (bar_length*(i+1))/size; j++){
        cout << "#";
      }
      for(int j = (bar_length*(i+1))/size; j < bar_length; j++){
        cout << "-";
      }
      cout << "|  ";
      j = (double) i+1;
      sizej = (double) size;
      cout << 100.*(j / sizej) << "%";
      if(include_index == true){
        cout << "  [" << i+1 << "/" << size << "]";
      }
      if(i+1 == size){
        cout << "  " << endl;
      }
    }
  }
}
