#include "../include/falcon.h"

#include <iostream>

int _get_split_count(int run){

    int splits_i, split_count;

    splits_i = 1;
    split_count = 1;
    while(splits_i < run){
        split_count *= 2;
        splits_i += 1;
    }

    return split_count;
}
