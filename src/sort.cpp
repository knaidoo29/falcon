#include "../include/falcon.h"

#include <iostream>
#include <cmath>

int _get_split_count(int run){
    int split_count;
    split_count = pow(2, run-1);
    return split_count;
}
