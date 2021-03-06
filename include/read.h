#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void print_file(string filename);

template<typename TYPE>
void read_ascii_table(string filename, int rows, int columns, TYPE array[],
   bool printout=true){

    string line;
    int i = 0;

    ifstream _file (filename);
    if(printout == true){
      cout << "\nReading ascii file: '" << filename << "':" << endl;
    }
    if(_file.is_open()){
      while(getline(_file, line)){
        replace(line.begin(), line.end(), '\t', ' ');
        stringstream str2float(line);
        TYPE temp_float;
        while(str2float >> temp_float){
          array[i] = temp_float;
          i++;
        }
      }
      _file.close();
    }
    else{
      if(printout == true){
        cout << "Unable to open file " << filename << endl;
      }
    }
}

template<typename TYPE>
int read_ascii_table(string filename, vector<TYPE> &array, bool printout=true){

    string line;
    int count_col, count_row;
    count_col = 0;
    count_row = 0;

    ifstream _file (filename);
    if(printout == true){
      cout << "\nReading ascii file: '" << filename << "':" << endl;
    }
    if(_file.is_open()){
      while(getline(_file, line)){
        if(line[0] != '#'){
          replace(line.begin(), line.end(), '\t', ' ');
          stringstream str2float(line);
          TYPE temp_float;
          while(str2float >> temp_float){
            array.push_back(temp_float);
            if(count_row == 0){
              count_col++;
            }
          }
          count_row++;
        }
      }
      if(printout == true){
        cout << "---> Number of columns = " << count_col << endl;
        cout << "---> Number of rows = " << count_row << endl;
      }
      _file.close();
    }
    else{
      if(printout == true){
        cout << "Unable to open file " << filename << endl;
      }
    }
    return count_col;
}


template<typename TYPE>
void extract_from_table(vector<TYPE> &table, int col, int total_col, vector<TYPE> &array){
  for(int i = 0; i < table.size()/total_col; i++){
    array.push_back(table[i*total_col + col]);
  }
}

class Reader{
  public:
    void readfile(string filename);
    template<typename TYPE>
    void extract(string description, TYPE array[]);
    template<typename TYPE>
    void extract(string description, vector<TYPE> &array);
    vector<string> header;
    vector<string> types;
  private:
    int isfalconfile;
    int rows, cols;
    string store_as;
    vector<int> data_int;
    vector<float> data_float;
    vector<double> data_double;
    void readheader(string filename);
};

template<typename TYPE>
void Reader::extract(string description, vector<TYPE> &array){
  int j=0;
  bool found;
  while(header[j] != description && j<header.size()){
    j++;
  }
  if(header[j] == description){
    found = true;
  }
  else{
    found = false;
    cout << "ERROR: Variable does not exist" << endl;
    cout << "Variables that are stored are :";
  }
  if(store_as == "int"){
    for(int i=0; i < data_int.size()/header.size(); i++){
      array.push_back((TYPE) data_int[header.size()*i + j]);
    }
  }
  if(store_as == "float"){
    for(int i=0; i < data_float.size()/header.size(); i++){
      array.push_back((TYPE) data_float[header.size()*i + j]);
    }
  }
  if(store_as == "double"){
    for(int i=0; i < data_double.size()/header.size(); i++){
      array.push_back((TYPE) data_double[header.size()*i + j]);
    }
  }
}
