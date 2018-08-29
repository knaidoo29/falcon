#include <vector>

int _get_split_count(int run);

template<class TYPE>
void _sort_pair(TYPE array_pair[2], int array_pair_index[2]){
    TYPE x1, x2;
    int ind1, ind2;

    x1 = array_pair[0];
    x2 = array_pair[1];
    ind1 = array_pair_index[0];
    ind2 = array_pair_index[1];
    if(x2 < x1) {
        array_pair[0] = x2;
        array_pair[1] = x1;
        array_pair_index[0] = ind2;
        array_pair_index[1] = ind1;
    }
};

template<class TYPE>
void _merge(TYPE arr1[], int arr_in1[], int size1, TYPE arr2[], int arr_in2[],
  int size2, TYPE merged_arr[], int merged_ind[]){

    int i=0, j=0, k=0;

    while(k < size1+size2){
        if(i<size1 && j<size2){
            if(arr1[i] <= arr2[j]){
                merged_arr[k] = arr1[i];
                merged_ind[k] = arr_in1[i];
                i++;
                k++;
            }
            else{
                merged_arr[k] = arr2[j];
                merged_ind[k] = arr_in2[j];
                j++;
                k++;
            }
        }
        if(i<size1 && j==size2){
            merged_arr[k] = arr1[i];
            merged_ind[k] = arr_in1[i];
            i++;
            k++;
        }
        if(j<size2 && i==size1){
            merged_arr[k] = arr2[j];
            merged_ind[k] = arr_in2[j];
            j++;
            k++;
        }
    }
}

template<class TYPE>
void _merge(vector<TYPE> &arr1, vector<int> &arr_in1, int size1,
  vector<TYPE> &arr2, vector<int> &arr_in2, int size2, vector<TYPE> &merged_arr,
  vector<int> &merged_ind){

    int i=0, j=0, k=0;

    while(k < size1+size2){
        if(i<size1 && j<size2){
            if(arr1[i] <= arr2[j]){
                merged_arr[k] = arr1[i];
                merged_ind[k] = arr_in1[i];
                i++;
                k++;
            }
            else{
                merged_arr[k] = arr2[j];
                merged_ind[k] = arr_in2[j];
                j++;
                k++;
            }
        }
        if(i<size1 && j==size2){
            merged_arr[k] = arr1[i];
            merged_ind[k] = arr_in1[i];
            i++;
            k++;
        }
        if(j<size2 && i==size1){
            merged_arr[k] = arr2[j];
            merged_ind[k] = arr_in2[j];
            j++;
            k++;
        }
    }
}

template<class TYPE>
void merge_sort(TYPE array[], int array_index[], int size){

    int run, split_count, range1, range2, range_mid;

    run = 2;
    split_count = 2;

    for(int i = 0;  i < size/split_count; i++){
        range1 = split_count*i;
        range2 = split_count*(i+1);
        if(range2 <= size){
            float pair_ordered[2];
            int pair_index_ordered[2];
            for(int j = range1; j < range2; j++){
                pair_ordered[j - range1] = array[j];
                pair_index_ordered[j - range1] = array_index[j];
            }

            _sort_pair(pair_ordered, pair_index_ordered);

            for(int j = range1; j < range2; j++){
                array[j] = pair_ordered[j - range1];
                array_index[j] = pair_index_ordered[j - range1];
            }
        }
    }

    while(((float)size)/((float)split_count) > 2.){
        split_count = _get_split_count(run);
        for(int i = 0; i < size/split_count; i++){
            range1 = 2*split_count*i;
            range2 = 2*split_count*(i+1);
            range_mid = 2*split_count*i + split_count;
            if(range2 > size){
                range2 = size;
            }
            if(range_mid > size){
                range_mid = size;
            }
            if(range_mid != range2){
                float array1[range_mid-range1], array2[range2-range_mid], arraym[range2-range1];
                int array_index1[range_mid-range1], array_index2[range2-range_mid], array_indexm[range2-range1];
                for(int j = 0; j < range_mid-range1; j++){
                    array1[j] = array[range1 + j];
                    array_index1[j] = array_index[range1 + j];
                }
                for(int j = 0; j < range2-range_mid; j++){
                    array2[j] = array[range_mid + j];
                    array_index2[j] = array_index[range_mid + j];
                }
                _merge(array1, array_index1, range_mid-range1, array2, array_index2, range2-range_mid, arraym,
                       array_indexm);
                for(int j = 0; j < range2-range1; j++){
                    array[range1 + j] = arraym[j];
                    array_index[range1 + j] = array_indexm[j];
                }
            }
        }
        run++;
    }
}

template<class TYPE>
void merge_sort(vector<TYPE> &array, vector<int> &array_index, int size){

    int run, split_count, range1, range2, range_mid;

    run = 2;
    split_count = 2;

    for(int i = 0;  i < size/split_count; i++){
        range1 = split_count*i;
        range2 = split_count*(i+1);
        if(range2 <= size){
            float pair_ordered[2];
            int pair_index_ordered[2];
            for(int j = range1; j < range2; j++){
                pair_ordered[j - range1] = array[j];
                pair_index_ordered[j - range1] = array_index[j];
            }

            _sort_pair(pair_ordered, pair_index_ordered);

            for(int j = range1; j < range2; j++){
                array[j] = pair_ordered[j - range1];
                array_index[j] = pair_index_ordered[j - range1];
            }
        }
    }

    while(((float)size)/((float)split_count) > 2.){
        split_count = _get_split_count(run);
        for(int i = 0; i < size/split_count; i++){
            range1 = 2*split_count*i;
            range2 = 2*split_count*(i+1);
            range_mid = 2*split_count*i + split_count;
            if(range2 > size){
                range2 = size;
            }
            if(range_mid > size){
                range_mid = size;
            }
            if(range_mid != range2){

                vector<float>array1;
                vector<float>array2;
                vector<float>arraym;

                vector<int>array_index1;
                vector<int>array_index2;
                vector<int>array_indexm;

                array1 = vector<float>(range_mid - range1);
                array2 = vector<float>(range2 - range_mid);
                arraym = vector<float>(range2 - range1);

                array_index1 = vector<int>(range_mid - range1);
                array_index2 = vector<int>(range2 - range_mid);
                array_indexm = vector<int>(range2 - range1);

                for(int j = 0; j < range_mid-range1; j++){
                    array1[j] = array[range1 + j];
                    array_index1[j] = array_index[range1 + j];
                }
                for(int j = 0; j < range2-range_mid; j++){
                    array2[j] = array[range_mid + j];
                    array_index2[j] = array_index[range_mid + j];
                }
                _merge(array1, array_index1, range_mid-range1, array2, array_index2, range2-range_mid, arraym,
                       array_indexm);
                for(int j = 0; j < range2-range1; j++){
                    array[range1 + j] = arraym[j];
                    array_index[range1 + j] = array_indexm[j];
                }
            }
        }
        run++;
    }
}
