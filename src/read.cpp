#include "../include/falcon.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void read_ascii_table(string filename, int rows, int columns, int array[]){

    string line;
    int i = 0;

    ifstream _file (filename);
    cout << "\nReading ascii file: '" << filename << "':" << endl;
    if(_file.is_open()){
      while(getline(_file, line)){
        replace(line.begin(), line.end(), '\t', ' ');
        stringstream str2float(line);
        float temp_float;
        while(str2float >> temp_float){
          array[i] = temp_float;
          i++;
        }
      }
      _file.close();
    }
    else{
      cout << "Unable to open file " << filename << endl;
    }
}

void read_ascii_table(string filename, int rows, int columns, float array[]){

    string line;
    int i = 0;

    ifstream _file (filename);
    cout << "\nReading ascii file: '" << filename << "':" << endl;
    if(_file.is_open()){
      while(getline(_file, line)){
        replace(line.begin(), line.end(), '\t', ' ');
        stringstream str2float(line);
        float temp_float;
        while(str2float >> temp_float){
          array[i] = temp_float;
          i++;
        }
      }
      _file.close();
    }
    else{
      cout << "Unable to open file " << filename << endl;
    }
}


void read_ascii_table(string filename, int rows, int columns, double array[]){

    string line;
    int i = 0;

    ifstream _file (filename);
    cout << "\nReading ascii file: '" << filename << "':" << endl;
    if(_file.is_open()){
      while(getline(_file, line)){
        replace(line.begin(), line.end(), '\t', ' ');
        stringstream str2float(line);
        float temp_float;
        while(str2float >> temp_float){
          array[i] = temp_float;
          i++;
        }
      }
      _file.close();
    }
    else{
      cout << "Unable to open file " << filename << endl;
    }
}

int read_ascii_table(string filename, vector<int> &array){

    string line;
    int count_col, count_rows;
    count_col = 0;
    count_rows = 0;

    ifstream _file (filename);
    cout << "\nReading ascii file: '" << filename << "':" << endl;
    if(_file.is_open()){
      while(getline(_file, line)){
        if(line[0] != '#'){
          replace(line.begin(), line.end(), '\t', ' ');
          stringstream str2float(line);
          float temp_float;
          while(str2float >> temp_float){
            array.push_back(temp_float);
            if(count_col == 0){
              count_rows++;
            }
          }
          count_col++;
        }
      }
      cout << "---> Number of columns = " << count_col << endl;
      cout << "---> Number of rows = " << count_rows << endl;
      _file.close();
    }
    else{
      cout << "Unable to open file " << filename << endl;
    }
    return count_rows;
}

int read_ascii_table(string filename, vector<float> &array){

    string line;
    int count_col, count_rows;
    count_col = 0;
    count_rows = 0;

    ifstream _file (filename);
    cout << "\nReading ascii file: '" << filename << "':" << endl;
    if(_file.is_open()){
      while(getline(_file, line)){
        if(line[0] != '#'){
          replace(line.begin(), line.end(), '\t', ' ');
          stringstream str2float(line);
          float temp_float;
          while(str2float >> temp_float){
            array.push_back(temp_float);
            if(count_col == 0){
              count_rows++;
            }
          }
          count_col++;
        }
      }
      cout << "---> Number of columns = " << count_col << endl;
      cout << "---> Number of rows = " << count_rows << endl;
      _file.close();
    }
    else{
      cout << "Unable to open file " << filename << endl;
    }
    return count_rows;
}

int read_ascii_table(string filename, vector<double> &array){

    string line;
    int count_col, count_rows;
    count_col = 0;
    count_rows = 0;

    ifstream _file (filename);
    cout << "\nReading ascii file: '" << filename << "':" << endl;
    if(_file.is_open()){
      while(getline(_file, line)){
        if(line[0] != '#'){
          replace(line.begin(), line.end(), '\t', ' ');
          stringstream str2float(line);
          float temp_float;
          while(str2float >> temp_float){
            array.push_back(temp_float);
            if(count_col == 0){
              count_rows++;
            }
          }
          count_col++;
        }
      }
      cout << "---> Number of columns = " << count_col << endl;
      cout << "---> Number of rows = " << count_rows << endl;
      _file.close();
    }
    else{
      cout << "Unable to open file " << filename << endl;
    }
    return count_rows;
}
