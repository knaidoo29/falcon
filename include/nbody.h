#include <iostream>
#include <cmath>
#include "fftw3.h"

using namespace std;

template<typename TYPE>
TYPE get_min(TYPE array[], int size){
  TYPE minimum;
  minimum = array[0];
  for(int i = 1; i < size; i++){
    if(array[i] < minimum){
      minimum = array[i];
    }
  }
  return minimum;
}

template<typename TYPE>
TYPE get_max(TYPE array[], int size){
  TYPE maximum;
  maximum = array[0];
  for(int i = 1; i < size; i++){
    if(array[i] > maximum){
      maximum = array[i];
    }
  }
  return maximum;
}

template<typename TYPE>
TYPE get_min(vector<TYPE> &array){
  TYPE minimum;
  minimum = array[0];
  for(int i = 1; i < array.size(); i++){
    if(array[i] < minimum){
      minimum = array[i];
    }
  }
  return minimum;
}

template<typename TYPE>
TYPE get_max(vector<TYPE> &array){
  TYPE maximum;
  maximum = array[0];
  for(int i = 1; i < array.size(); i++){
    if(array[i] > maximum){
      maximum = array[i];
    }
  }
  return maximum;
}

template<typename TYPE>
void nearest_grid_point(vector<TYPE> &x, vector<TYPE> &y, vector<TYPE> &z,
  vector<TYPE> &xgrid, vector<TYPE> &ygrid, vector<TYPE> &zgrid,
  vector<TYPE> &density, float dl, int ngrid);

template<typename TYPE>
void cloud_in_cell(vector<TYPE> &x, vector<TYPE> &y, vector<TYPE> &z,
  vector<TYPE> &xgrid, vector<TYPE> &ygrid, vector<TYPE> &zgrid,
  vector<TYPE> &density, float dl, int ngrid);

template<typename TYPE>
void build_space(vector<TYPE> &xgrid, vector<TYPE> &ygrid, vector<TYPE> &zgrid,
  float lbox, int ngrid, float l0 = 0.){
  TYPE dl;
  dl = (TYPE) lbox / (TYPE) ngrid;
  for(int i = 0; i < ngrid; i++){
    for(int j = 0; j < ngrid; j++){
      for(int k = 0; k < ngrid; k++){
        xgrid[k + ngrid*(j + ngrid*i)] = l0 + dl*(0.5 + (TYPE)i);
        ygrid[k + ngrid*(j + ngrid*i)] = l0 + dl*(0.5 + (TYPE)j);
        zgrid[k + ngrid*(j + ngrid*i)] = l0 + dl*(0.5 + (TYPE)k);
      }
    }
  }
}

template<typename TYPE>
void particle2grid(vector<TYPE> &x, vector<TYPE> &y, vector<TYPE> &z,
  vector<TYPE> &xgrid, vector<TYPE> &ygrid, vector<TYPE> &zgrid,
  vector<TYPE> &density, string mode){
  TYPE dl;
  float ngrid;
  ngrid = pow((float) xgrid.size(), 1./3.);
  for(int i = 0; i < density.size(); i++){
    density[i] = 0.;
  }
  if(mode == "NGP"){
    nearest_grid_point(x, y, z, xgrid, ygrid, zgrid, density, dl, ngrid);
  }
  if(mode == "CIC"){
    cloud_in_cell(x, y, z, xgrid, ygrid, zgrid, density, dl, ngrid);
  }
}

template<typename TYPE>
void nearest_grid_point(vector<TYPE> &x, vector<TYPE> &y, vector<TYPE> &z,
  vector<TYPE> &xgrid, vector<TYPE> &ygrid, vector<TYPE> &zgrid,
  vector<TYPE> &density, float dl, int ngrid){
  float ii, jj, kk, lbox, dx, dy, dz, wx, wy, wz;
  lbox = get_max(xgrid) - get_min(xgrid);
  dl = lbox / ((float) ngrid-1.);
  lbox += dl;
  for(int i = 0; i < x.size(); i++){
    ii = x[i]/dl;
    jj = y[i]/dl;
    kk = z[i]/dl;
    dx = abs(x[i] - xgrid[(int) kk + ngrid*((int) jj + ngrid*((int) ii))]);
    dy = abs(y[i] - ygrid[(int) kk + ngrid*((int) jj + ngrid*((int) ii))]);
    dz = abs(z[i] - zgrid[(int) kk + ngrid*((int) jj + ngrid*((int) ii))]);
    if(dx == dl/2.){
      wx = 1./(2.*dl);
    }
    else{
      wx = 1./dl;
    }
    if(dy == dl/2.){
      wy = 1./(2.*dl);
    }
    else{
      wy = 1./dl;
    }
    if(dz == dl/2.){
      wz = 1./(2.*dl);
    }
    else{
      wz = 1./dl;
    }
    density[(int) kk + ngrid*((int) jj + ngrid*((int) ii))] += wx*wy*wz;
  }
}


template<typename TYPE>
void cloud_in_cell(vector<TYPE> &x, vector<TYPE> &y, vector<TYPE> &z,
  vector<TYPE> &xgrid, vector<TYPE> &ygrid, vector<TYPE> &zgrid,
  vector<TYPE> &density, float dl, int ngrid){
  float ii, jj, kk, lbox, dx, dy, dz, wx, wy, wz;
  vector<int>cloud_i;
  vector<int>cloud_j;
  vector<int>cloud_k;
  lbox = get_max(xgrid) - get_min(xgrid);
  dl = lbox / ((float) ngrid-1.);
  lbox += dl;
  for(int i = 0; i < x.size(); i++){
    ii = x[i]/dl;
    jj = y[i]/dl;
    kk = z[i]/dl;
    if((int) ii > 0 && (int) ii < ngrid-1){
      cloud_i.push_back((int) ii - 1);
      cloud_i.push_back((int) ii);
      cloud_i.push_back((int) ii + 1);
    }
    else{
      if((int) ii == 0){
        cloud_i.push_back((int) ii);
        cloud_i.push_back((int) ii + 1);
      }
      if((int) ii == ngrid-1){
        cloud_i.push_back((int) ii - 1);
        cloud_i.push_back((int) ii);
      }
    }
    if((int) jj > 0 && (int) jj < ngrid-1){
      cloud_j.push_back((int) jj - 1);
      cloud_j.push_back((int) jj);
      cloud_j.push_back((int) jj + 1);
    }
    else{
      if((int) jj == 0){
        cloud_j.push_back((int) jj);
        cloud_j.push_back((int) jj + 1);
      }
      if((int) jj == ngrid-1){
        cloud_j.push_back((int) jj - 1);
        cloud_j.push_back((int) jj);
      }
    }
    if((int) kk > 0 && (int) kk < ngrid-1){
      cloud_k.push_back((int) kk - 1);
      cloud_k.push_back((int) kk);
      cloud_k.push_back((int) kk + 1);
    }
    else{
      if((int) kk == 0){
        cloud_k.push_back((int) kk);
        cloud_k.push_back((int) kk + 1);
      }
      if((int) kk == ngrid-1){
        cloud_k.push_back((int) kk - 1);
        cloud_k.push_back((int) kk);
      }
    }
    for(int i1 = 0; i1 < cloud_i.size(); i1++){
      for(int i2 = 0; i2 < cloud_j.size(); i2++){
        for(int i3 = 0; i3 < cloud_k.size(); i3++){
          dx = abs(x[i] - xgrid[cloud_k[i3] + ngrid*(cloud_j[i2] + ngrid*cloud_i[i1])]);
          dy = abs(y[i] - ygrid[cloud_k[i3] + ngrid*(cloud_j[i2] + ngrid*cloud_i[i1])]);
          dz = abs(z[i] - zgrid[cloud_k[i3] + ngrid*(cloud_j[i2] + ngrid*cloud_i[i1])]);
          if(dx < dl){
            wx = (1./dl)*(1. - dx/dl);
          }
          else{
            wx = 0.;
          }
          if(dy < dl){
            wy = (1./dl)*(1. - dy/dl);
          }
          else{
            wy = 0.;
          }
          if(dz < dl){
            wz = (1./dl)*(1. - dz/dl);
          }
          else{
            wz = 0.;
          }
          density[cloud_k[i3] + ngrid*(cloud_j[i2] + ngrid*cloud_i[i1])] += wx*wy*wz;
        }
      }
    }
    if(cloud_i.size() != 0){
      cloud_i.erase(cloud_i.begin(), cloud_i.begin() + cloud_i.size());
    }
    if(cloud_j.size() != 0){
      cloud_j.erase(cloud_j.begin(), cloud_j.begin() + cloud_j.size());
    }
    if(cloud_k.size() != 0){
      cloud_k.erase(cloud_k.begin(), cloud_k.begin() + cloud_k.size());
    }
  }
}

template<typename TYPE>
float get_mean(vector<TYPE> &array){
  float mean, sum = 0.;
  for(int i = 0; i < array.size(); i++){
    sum += array[i];
  }
  mean = sum / ((float) array.size());
  return mean;
}

template<typename TYPE>
void get_density_contrast(vector<TYPE> &density){
  float mean;
  mean = get_mean(density);
  for(int i = 0; i < density.size(); i++){
    density[i] = density[i]/mean - 1.;
  }
}

template<typename TYPE>
void get_power_spectra(int ngrid, float lbox, vector<TYPE> &density,
  vector<TYPE> &kh, vector<TYPE> &pk, int k_max){

  vector<float> delta_fftw_2;
  vector<int> n_k;
  vector<float> n_count;
  float vol = lbox*lbox*lbox;

  // set up fftw
  fftw_complex *infftw, *outfftw;
  infftw = (fftw_complex*) fftw_malloc(ngrid*ngrid*ngrid*sizeof(fftw_complex));
  outfftw = (fftw_complex*) fftw_malloc(ngrid*ngrid*ngrid*sizeof(fftw_complex));
  for(int i=0; i < ngrid*ngrid*ngrid; i++){
    infftw[i][0] = density[i];
    infftw[i][1] = 0.;
  }
  fftw_plan plan4fftw;
  plan4fftw = fftw_plan_dft_3d(ngrid, ngrid, ngrid, infftw, outfftw, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(plan4fftw);
	fftw_destroy_plan(plan4fftw);

  for(int i = 0; i < ngrid*ngrid*ngrid; i++){
    delta_fftw_2.push_back(pow(outfftw[i][0], 2.) + pow(outfftw[i][1], 2.));
  }

  fftw_free(infftw);
  fftw_free(outfftw);
  
  for(int i = 0; i < ngrid; i++){
    for(int j = 0; j < ngrid; j++){
      for(int k = 0; k < ngrid; k++){
        n_k.push_back(k + j + i);
      }
    }
  }

  for(int i = 0; i < k_max; i++){
    kh.push_back(i);
    pk.push_back(0.);
    n_count.push_back(0.);
  }

  for(int i = 0; i < n_k.size(); i++){
    if(n_k[i] < k_max){
      pk[n_k[i]] += delta_fftw_2[i];
      n_count[n_k[i]] += 1.;
    }
  }

  for(int i = 0; i < pk.size(); i++){
    pk[i] /= ((float) n_count[i]);
    pk[i] *= (vol/pow((float) ngrid, 6.));
  }
}
