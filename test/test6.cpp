#include <iostream>
#include <cmath>
#include "falcon.h"
#include "fftw3.h"

using namespace std;

int main(){

  int ngrid;
  float lbox;

  vector<float> x;
  vector<float> y;
  vector<float> z;
  vector<float> data;

  vector<float> xgrid;
  vector<float> ygrid;
  vector<float> zgrid;

  vector<float> dngp;
  vector<float> dcic;

  int col;
  string filename;

  filename = "/Users/krishna/Research/github/falcon/reference/levy_flight.txt";
  col = read_ascii_table(filename, data);

  extract_from_table(data, 0, col, x);
  extract_from_table(data, 1, col, y);
  extract_from_table(data, 2, col, z);

  lbox = 75.;
	ngrid = 256;

  xgrid = vector<float>(ngrid*ngrid*ngrid);
  ygrid = vector<float>(ngrid*ngrid*ngrid);
  zgrid = vector<float>(ngrid*ngrid*ngrid);

  build_space(xgrid, ygrid, zgrid, lbox, ngrid);

  dngp = vector<float>(ngrid*ngrid*ngrid);
  dcic = vector<float>(ngrid*ngrid*ngrid);

  particle2grid(x, y, z, xgrid, ygrid, zgrid, dngp, "NGP");
  particle2grid(x, y, z, xgrid, ygrid, zgrid, dcic, "CIC");

  filename = "density.txt";
  Writer wr;
  wr.store(xgrid, xgrid.size(), "x_grid");
  wr.store(ygrid, xgrid.size(), "y_grid");
  wr.store(zgrid, xgrid.size(), "z_grid");
  wr.store(dngp, xgrid.size(), "NGP");
  wr.store(dcic, xgrid.size(), "CIC");
  wr.write2file(filename);

  get_density_contrast(dcic);

  vector<float> kh;
  vector<float> pk;
  int k_max = 500;

  get_power_spectra(ngrid, lbox, dcic, kh, pk, k_max);

  filename = "pofk.txt";

  Writer wr1;
  wr1.store(kh, kh.size(), "kk");
  wr1.store(pk, pk.size(), "P(k)");
  wr1.write2file(filename);

  return 0;
}
