#include "../include/falcon.h"
#include <vector>

using namespace std;

void get_index(int index[], int size){
    // get index.
    for (int i = 0; i < size; i++)
    {
        index[i] = i;
    }
}


void get_index(vector<int> &index, int size){
    // get index.
    for (int i = 0; i < size; i++)
    {
        index[i] = i;
    }
}
