#include <iostream>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <cstdio>
#include <fftw3.h>

/* ######################## ISW+RS Numerical Calculations ########################
 * - Numerically calculates the potential of a given LSS source from it's density
 * contrast.
 * - Author: Krishna Naidoo
 *
 * - to compile the program: 		g++ NumCal.cpp -o NumCal.exe -lfftw3 -lm
 * - to run the program: 			./NumCal.exe
 * ###############################################################################
 */

 using namespace std;

 int main()
 {
	// n should be a power of 2 to optimise the Fast Fourier Transform process used heavily later.
	int n;
	n = 256;
	cout << "	" << '\n';
	cout << "***** RUNNING: ISW+RS Numerical Calculations *****" << '\n';
	cout << "	" << '\n';
	cout << "	-> Checking n: " << n << '\n';
	cout << "	" << '\n';

	// define array size
	double *X, *Y, *Z;
	X = (double*) fftw_malloc(n*n*n * sizeof(double));
	Y = (double*) fftw_malloc(n*n*n * sizeof(double));
	Z = (double*) fftw_malloc(n*n*n * sizeof(double));

	double h, H_0, Omega_m, Mpc, c;

	Omega_m = 0.27;
	Mpc = 3.086e22;
	c = 3.e8;
	h = 0.7;
	H_0 = 100000.*(1./c)*(h/Mpc);

	// define grid edges and spacings
	double X1, X2, Y1, Y2, Z1, Z2, dx, dy, dz;
	double L1, L2, L3;
	X1 = -1000.*Mpc/h;
	X2 = 1000.*Mpc/h;

	Y1 = X1;
	Y2 = X2;
	Z1 = Y1;
	Z2 = Y2;
	dx = (X2-X1)/(n-1);
	dy = (Y2-Y1)/(n-1);
	dz = (Z2-Z1)/(n-1);
	L1 = n*dx;
	L2 = L1;
	L3 = L2;

	// define array values

	cout << "	- (1/8) Building Space: " << '\n';

	for( int i = 0; i < n; i = i+1)
		{
		for( int j = 0; j < n; j = j+1)
			{
			for( int k = 0; k < n; k = k+1)
				{
				X[k + n*(j + n*i)] = X1 + dx*i;
				Y[k + n*(j + n*i)] = Y1 + dy*j;
				Z[k + n*(j + n*i)] = Z1 + dz*k;,
				};
			};
			double L;
			L = (i+1) % 32;
			if (L == 0.)
				cout << "	---> " << i+1 << '/'<< n << '\n';
		};

	int n1;

	n1 = n/2;

	double Z0;

	Z0 = Z[n1];

	// defining density contrast and gravitational potential

	double *D;

	D = (double*) fftw_malloc(n*n*n * sizeof(double));

	cout << "	" << '\n';
	cout << "	- (2/8) D and F: " << '\n';

	double R, R0, den_contrast, d_0, adash_a0, Pdash0, X_c, Y_c;

	X_c = 1000.*Mpc/h;
	Y_c = 0.*Mpc/h;
	adash_a0 = 7.5610282998487789e-27;
	Pdash0 = 7.1947118365064552e+25;
	d_0 = 0.25;

	for( int i = 0; i < n; i = i+1)
		{
		for( int j = 0; j < n; j = j+1)
			{
			for( int k = 0; k < n; k = k+1)
				{
				R = sqrt(pow((X[k + n*(j + n*i)]-X_c), 2.0)+pow((Y[k + n*(j + n*i)]-Y_c), 2.0) + pow((Z[k + n*(j + n*i)]-Z0),2.0));
				R0 = 200.*Mpc/h;
				den_contrast = -d_0*(1.-(2./3.)*pow((R/R0),2.0))*exp(-pow((R/R0),2.0));
				D[k + n*(j + n*i)] = -((3.*Omega_m*pow(H_0,2.))/(1.-(adash_a0*Pdash0)))*den_contrast;
				};
			};
			double L;
			L = (i+1) % 32;
			if (L == 0.)
				cout << "	---> " << i+1 << '/'<< n << '\n';
		};

	cout << "	" << '\n';
	cout << "	- (3/8) Determining F:" << '\n';
	cout << "	-- FFTW: " << '\n';

	double *INFFTW, *OUTFFTW;

	INFFTW = (double*) fftw_malloc(n*n*n * sizeof(double));
	OUTFFTW = (double*) fftw_malloc(n*n*n * sizeof(double));

	fftw_plan plan_backward;
	fftw_plan plan_forward;

	plan_forward = fftw_plan_r2r_3d (n, n, n, D, INFFTW, FFTW_RODFT00, FFTW_RODFT00, FFTW_RODFT00, FFTW_MEASURE);

	fftw_execute ( plan_forward );

	fftw_destroy_plan(plan_forward);

	cout << "	---> Forward Done "<< '\n';

	cout << "	" << '\n';
	cout << "	-- Inverting Poisson Equation: " << '\n';

	double *F;
	double yy, yy1, yy2, yy3, PI;

	PI = acos(-1.);

	F = (double*) fftw_malloc(n*n*n * sizeof(double));

	for( int i = 0; i < n; i = i+1)
		{
		for( int j = 0; j < n; j = j+1)
			{
			for( int k = 0; k < n; k = k+1)
				{
				yy1 = PI*(i+1)/L1;
				yy2 = PI*(j+1)/L2;
				yy3 = PI*(k+1)/L3;
				yy = - pow(yy1,2.0)- pow(yy2,2.0)- pow(yy3,2.0);
				INFFTW[k + n*(j + n*i)] = INFFTW[k + n*(j + n*i)]/yy;
				};
			};
			double L;
			L = (i+1) % 32;
			if (L == 0.)
				cout << "	---> " << i+1 << '/'<< n << '\n';
		};

	cout << "	" << '\n';
	cout << "	-- FFTW: " << '\n';

	plan_backward = fftw_plan_r2r_3d (n, n, n, INFFTW, F, FFTW_RODFT00, FFTW_RODFT00, FFTW_RODFT00, FFTW_MEASURE);

	fftw_execute ( plan_backward );

	fftw_destroy_plan(plan_backward);

	cout << "	---> Backward Done "<< '\n';

	cout << "	" << '\n';
	cout << "	-- Normalising: " << '\n';

	for( int i = 0; i < n; i = i+1)
		{
		for( int j = 0; j < n; j = j+1)
			{
			for( int k = 0; k < n; k = k+1)
				{
				F[k + n*(j + n*i)] = (1./(pow((2*(n+1)),3)))*F[k + n*(j + n*i)];
				};
			};
			double L;
			L = (i+1) % 32;
			if (L == 0.)
				cout << "	---> " << i+1 << '/'<< n << '\n';
		};

	cout << "	" << '\n';
	cout << "	- (4/8) Differentiating F_x, F_y, F_z: " << '\n';

	double *F_x, *F_y, *F_z, *F2_r;

	F_x = (double*) fftw_malloc(n*n*n * sizeof(double));
	F_y = (double*) fftw_malloc(n*n*n * sizeof(double));
	F_z = (double*) fftw_malloc(n*n*n * sizeof(double));
	F2_r = (double*) fftw_malloc(n*n*n * sizeof(double));

	for( int i = 0; i < n; i = i+1)
		{
		for( int j = 0; j < n; j = j+1)
			{
			for( int k = 0; k < n; k = k+1)
				{
				if (i == 0 or j == 0 or k == 0)
					{
					F_x[k + n*(j + n*i)] = 0.;
					F_y[k + n*(j + n*i)] = 0.;
					F_z[k + n*(j + n*i)] = 0.;
					}
				else
					{
					F_x[k + n*(j + n*i)] = (F[k + n*(j + n*(i+1))]-F[k + n*(j + n*(i-1))])/(2.*dx);
					F_y[k + n*(j + n*i)] = (F[k + n*(j+1 + n*i)]-F[k + n*(j-1 + n*i)])/(2.*dy);
					F_z[k + n*(j + n*i)] = (F[k+1 + n*(j + n*i)]-F[k-1 + n*(j + n*i)])/(2.*dz);
					}
				F2_r[k + n*(j + n*i)] = pow(F_x[k + n*(j + n*i)],2.) + pow(F_y[k + n*(j + n*i)],2.) + pow(F_z[k + n*(j + n*i)],2.);
				};
			};
			double L;
			L = (i+1) % 32;
			if (L == 0.)
				cout << "	---> " << i+1 << '/'<< n << '\n';
		};

	cout << "	" << '\n';
	cout << "	- (5/8) Double Differentiating F_xx, F_xy, F_xz, etc...: " << '\n';

	double *F_xx, *F_xy, *F_xz, *F_yx, *F_yy, *F_yz, *F_zx, *F_zy, *F_zz, *DPsi0;

	F_xx = (double*) fftw_malloc(n*n*n * sizeof(double));
	F_xy = (double*) fftw_malloc(n*n*n * sizeof(double));
	F_xz = (double*) fftw_malloc(n*n*n * sizeof(double));
	F_yx = (double*) fftw_malloc(n*n*n * sizeof(double));
	F_yy = (double*) fftw_malloc(n*n*n * sizeof(double));
	F_yz = (double*) fftw_malloc(n*n*n * sizeof(double));
	F_zx = (double*) fftw_malloc(n*n*n * sizeof(double));
	F_zy = (double*) fftw_malloc(n*n*n * sizeof(double));
	F_zz = (double*) fftw_malloc(n*n*n * sizeof(double));
	DPsi0 = (double*) fftw_malloc(n*n*n * sizeof(double));

	for( int i = 0; i < n; i = i+1)
		{
		for( int j = 0; j < n; j = j+1)
			{
			for( int k = 0; k < n; k = k+1)
				{
				if (i == 0 or j == 0 or k == 0)
					{
					F_xx[k + n*(j + n*i)] = 0.;
					F_xy[k + n*(j + n*i)] = 0.;
					F_xz[k + n*(j + n*i)] = 0.;
					F_yx[k + n*(j + n*i)] = 0.;
					F_yy[k + n*(j + n*i)] = 0.;
					F_yz[k + n*(j + n*i)] = 0.;
					F_zx[k + n*(j + n*i)] = 0.;
					F_zy[k + n*(j + n*i)] = 0.;
					F_zz[k + n*(j + n*i)] = 0.;
					}
				else
					{
					F_xx[k + n*(j + n*i)] = (F_x[k + n*(j + n*(i+1))]-F_x[k + n*(j + n*(i-1))])/(2.*dx);
					F_xy[k + n*(j + n*i)] = (F_x[k + n*(j+1 + n*i)]-F_x[k + n*(j-1 + n*i)])/(2.*dy);
					F_xz[k + n*(j + n*i)] = (F_x[k+1 + n*(j + n*i)]-F_x[k-1 + n*(j + n*i)])/(2.*dz);
					F_yx[k + n*(j + n*i)] = (F_y[k + n*(j + n*(i+1))]-F_y[k + n*(j + n*(i-1))])/(2.*dx);
					F_yy[k + n*(j + n*i)] = (F_y[k + n*(j+1 + n*i)]-F_y[k + n*(j-1 + n*i)])/(2.*dy);
					F_yz[k + n*(j + n*i)] = (F_y[k+1 + n*(j + n*i)]-F_y[k-1 + n*(j + n*i)])/(2.*dz);
					F_zx[k + n*(j + n*i)] = (F_z[k + n*(j + n*(i+1))]-F_z[k + n*(j + n*(i-1))])/(2.*dx);
					F_zy[k + n*(j + n*i)] = (F_z[k + n*(j+1 + n*i)]-F_z[k + n*(j-1 + n*i)])/(2.*dy);
					F_zz[k + n*(j + n*i)] = (F_z[k+1 + n*(j + n*i)]-F_z[k-1 + n*(j + n*i)])/(2.*dz);
					}
				double A1, A2, A3, A4;
				A1 = pow(F_xx[k + n*(j + n*i)],2.) + pow(F_xy[k + n*(j + n*i)],2.) + pow(F_xz[k + n*(j + n*i)],2.);
				A2 = pow(F_yx[k + n*(j + n*i)],2.) + pow(F_yy[k + n*(j + n*i)],2.) + pow(F_yz[k + n*(j + n*i)],2.);
				A3 = pow(F_zx[k + n*(j + n*i)],2.) + pow(F_zy[k + n*(j + n*i)],2.) + pow(F_zz[k + n*(j + n*i)],2.);
				A4 = pow((F_xx[k + n*(j + n*i)]+F_yy[k + n*(j + n*i)]+F_zz[k + n*(j + n*i)]),2.);
				DPsi0[k + n*(j + n*i)] = A1 + A2 + A3 - A4;
				};
			};
			double L;
			L = (i+1) % 32;
			if (L == 0.)
				cout << "	--->" << i+1 << '/'<< n << '\n';
		};

	cout << "	" << '\n';
	cout << "	- (6/8) Determining Psi0:" << '\n';
	cout << "	-- FFTW: " << '\n';

	double *INFFTW1, *OUTFFTW1;

	INFFTW1 = (double*) fftw_malloc(n*n*n * sizeof(double));
	OUTFFTW1 = (double*) fftw_malloc(n*n*n * sizeof(double));

	fftw_plan plan_backward1;
	fftw_plan plan_forward1;

	plan_forward1 = fftw_plan_r2r_3d (n, n, n, DPsi0, INFFTW1, FFTW_RODFT00, FFTW_RODFT00, FFTW_RODFT00, FFTW_MEASURE);

	fftw_execute ( plan_forward1 );

	fftw_destroy_plan(plan_forward1);

	cout << "	---> Forward Done "<< '\n';

	cout << "	" << '\n';
	cout << "	-- Inverting Poisson Equation: " << '\n';

	double *Psi0;
	double yyy, yyy1, yyy2, yyy3;

	Psi0 = (double*) fftw_malloc(n*n*n * sizeof(double));

	for( int i = 0; i < n; i = i+1)
		{
		for( int j = 0; j < n; j = j+1)
			{
			for( int k = 0; k < n; k = k+1)
				{
				yyy1 = PI*(i+1)/L1;
				yyy2 = PI*(j+1)/L2;
				yyy3 = PI*(k+1)/L3;
				yyy = - pow(yyy1,2.0)- pow(yyy2,2.0)- pow(yyy3,2.0);
				INFFTW1[k + n*(j + n*i)] = INFFTW1[k + n*(j + n*i)]/yyy;
				};
			};
			double L;
			L = (i+1) % 32;
			if (L == 0.)
				cout << "	---> " << i+1 << '/'<< n << '\n';
		};

	plan_backward1 = fftw_plan_r2r_3d (n, n, n, INFFTW1, Psi0, FFTW_RODFT00, FFTW_RODFT00, FFTW_RODFT00, FFTW_MEASURE);

	cout << "	" << '\n';
	cout << "	-- FFTW: " << '\n';

	fftw_execute ( plan_backward1 );

	fftw_destroy_plan(plan_backward1);

	cout << "	---> Backward Done "<< '\n';

	cout << "	" << '\n';
	cout << "	-- Normalising: " << '\n';

	for( int i = 0; i < n; i = i+1)
		{
		for( int j = 0; j < n; j = j+1)
			{
			for( int k = 0; k < n; k = k+1)
				{
				Psi0[k + n*(j + n*i)] = (1./(pow((2*(n+1)),3)))*Psi0[k + n*(j + n*i)];
				};
			};
			double L;
			L = (i+1) % 32;
			if (L == 0.)
				cout << "	---> " << i+1 << '/'<< n << '\n';
		};

	cout << "	" << '\n';
	cout << "	- (7/8) Slicing Data: " << '\n';

	double *X2D, *Y2D, *D2D, *F2D, *Fr2D, *DPsi02D, *Psi02D;

	X2D = (double*) fftw_malloc(n*n * sizeof(double));
	Y2D = (double*) fftw_malloc(n*n * sizeof(double));
	D2D = (double*) fftw_malloc(n*n * sizeof(double));
	F2D = (double*) fftw_malloc(n*n * sizeof(double));
	Fr2D = (double*) fftw_malloc(n*n * sizeof(double));
	DPsi02D = (double*) fftw_malloc(n*n * sizeof(double));
	Psi02D = (double*) fftw_malloc(n*n * sizeof(double));

	for(int i = 0; i < n; i = i+1)
		{
		for(int j = 0; j < n; j = j+1)
			{
			X2D[j + n*i] = X[n1 + n*(j + n*i)];
			Y2D[j + n*i] = Y[n1 + n*(j + n*i)];
			D2D[j + n*i] = D[n1 + n*(j + n*i)];
			F2D[j + n*i] = F[n1 + n*(j + n*i)];
			Fr2D[j + n*i] = F2_r[n1 + n*(j + n*i)];
			DPsi02D[j + n*i] = DPsi0[n1 + n*(j + n*i)];
			Psi02D[j + n*i] = Psi0[n1 + n*(j + n*i)];
			};
			double L;
			L = (i+1) % 32;
			if (L == 0.)
				cout << "	---> " << i+1 << '/'<< n << '\n';
		};

	// write data to file
	cout << "	" << '\n';
	cout << "	- (8/8) Storing Data: " << '\n';

	cout << "	" << '\n';
	cout << "	-- 2D"<< '\n';

	ofstream outputfile;
	outputfile.open("2D_potential_values.txt");
	for( int i = 0; i < n; i = i+1)
		{
		for( int j = 0; j < n; j = j+1)
			{
			outputfile << X2D[j + n*i] << '\t' << Y2D[j + n*i] << '\t' << D2D[j + n*i] << '\t' << F2D[j + n*i] << '\t' << Fr2D[j+n*i] << '\t' << Psi02D[j + n*i] << '\n';
			};
			double L;
			L = (i+1) % 32;
			if (L == 0.)
				cout << "	---> " << i+1 << '/'<< n << '\n';
		};
	outputfile.close();

	cout << "	" << '\n';
	cout << "	-- 3D"<< '\n';

	ofstream output;
	output.open("3D_potential_values.txt");
	for( int i = 0; i < n; i = i+1)
		{
		for( int j = 0; j < n; j = j+1)
			{
			for( int k = 0; k < n; k = k+1)
				{
				output << X[k + n*(j + n*i)] << '\t' << Y[k + n*(j + n*i)] << '\t' << Z[k + n*(j + n*i)] << '\t' << D[k + n*(j + n*i)] << '\t' << F[k + n*(j + n*i)] << '\t' << F2_r[k + n*(j + n*i)] << '\t' << Psi0[k + n*(j + n*i)] << '\n';
				};
			};
			double L;
			L = (i+1) % 32;
			if (L == 0.)
				cout << "	---> " << i+1 << '/'<< n << '\n';
		};
	output.close();

	cout << "	" << '\n';
	cout << "***** ISW+RS Numerical Calculations - DONE *****" << '\n';
	cout << "	" << '\n';
 };
