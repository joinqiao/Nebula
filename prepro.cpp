/*
Nebula started from 2018/7/3 20:30.

Nebula is a opensource softwere.

Copyright 2018-2018, Qiao Chen-Liang, Xu He-Yong, and the Nebula contributors.

*/

#include "../include/prepro.h"

#include <string>

using namespace std;

CPrepro::CPrepro(string filename, unsigned int nDim)
{
	// Reading the mesh file.
	Read_Meshfile(filename, nDim);
	// Get all boundary conditions.
	Get_BCs();
	// Set all boundary conditions.
	Set_BCs();
	// Flow field initialization.
	Initialization();
}

CPrepro::~CPrepro() { }

void CPrepro::Read_Meshfile(string filename, unsigned int nDim)
{
	int i, j, k, n;
	int BPoints;
	double *tmp_Coord;		// 临时存放网格点坐标数组，存放方式与网格文件相同。
	meshfile.open(filename, ios::in);
	getline(meshfile, meshline);
	nBlock = stoi(meshline);
	Block_ijk = new int *[nBlock];
	if (nDim == 2)
	{
		Coord2D_X = new double **[nBlock];
		Coord2D_Y = new double **[nBlock];
	}
	else
	{
		Coord3D_X = new double ***[nBlock];
		Coord3D_Y = new double ***[nBlock];
		Coord3D_Z = new double ***[nBlock];
	}
	nPoint = 0;
	for (iBlock = 0; iBlock < nBlock; iBlock++)
	{
		getline(meshfile, meshline);
		istringstream block_line(meshline);
		Block_ijk[iBlock] = new int[3];
		if (nDim == 2)
		{
			block_line >> imax;
			block_line >> jmax;
			Block_ijk[iBlock][0] = imax;
			Block_ijk[iBlock][1] = jmax;
			Block_ijk[iBlock][2] = 1;
			Coord2D_X[iBlock] = new double *[imax];
			Coord2D_Y[iBlock] = new double *[imax];
			for (i = 0; i < imax; i++)
			{
				Coord2D_X[iBlock][i] = new double[jmax];
				Coord2D_Y[iBlock][i] = new double[jmax];
			}
			nPoint += imax * jmax;
		}
		else
		{
			block_line >> imax;
			block_line >> jmax;
			block_line >> kmax;
			Block_ijk[iBlock][0] = imax;
			Block_ijk[iBlock][1] = jmax;
			Block_ijk[iBlock][2] = kmax;
			Coord3D_X[iBlock] = new double **[imax];
			Coord3D_Y[iBlock] = new double **[imax];
			Coord3D_Z[iBlock] = new double **[imax];
			for (i = 0; i < imax; i++)
			{
				Coord3D_X[iBlock][i] = new double *[jmax];
				Coord3D_Y[iBlock][i] = new double *[jmax];
				Coord3D_Z[iBlock][i] = new double *[jmax];
				for (j = 0; j < jmax; j++)
				{
					Coord3D_X[iBlock][i][j] = new double[kmax];
					Coord3D_Y[iBlock][i][j] = new double[kmax];
					Coord3D_Z[iBlock][i][j] = new double[kmax];
				}
			}
			nPoint += imax * jmax * kmax;
		}
	}
	if (nDim == 2)
	{ tmp_Coord = new double[2 * nPoint]; }
	else
	{ tmp_Coord = new double[3 * nPoint]; }

	n = 0;
	while (getline(meshfile, meshline))
	{
		istringstream coord_line(meshline);
		coord_line >> tmp_Coord[n];
		if (!(coord_line >> tmp_Coord[n + 1]))
		{ n += 1; continue; }
		if (!(coord_line >> tmp_Coord[n + 2]))
		{ n += 2; continue; }
		if (!(coord_line >> tmp_Coord[n + 3]))
		{ n += 3; continue; }
		n += 4;
	}
	n = 0;
	if (nDim == 2)
	{
		for (iBlock = 0; iBlock < nBlock; iBlock++)
		{
			imax = Block_ijk[iBlock][0];
			jmax = Block_ijk[iBlock][1];
			BPoints = imax * jmax;
			for (j = 0; j < jmax; j++)
			{
				for (i = 0; i < imax; i++)
				{
					Coord2D_X[iBlock][i][j] = tmp_Coord[n];
					Coord2D_Y[iBlock][i][j] = tmp_Coord[n + BPoints];
					n++;
					//cout << "+++++++++++++++++++" << Coord2D_X[iBlock][i][j] << "&" << Coord2D_Y[iBlock][i][j] << endl;
				}
			}
			n += BPoints;
		}
	}
	else
	{
		for (iBlock = 0; iBlock < nBlock; iBlock++)
		{
			imax = Block_ijk[iBlock][0];
			jmax = Block_ijk[iBlock][1];
			kmax = Block_ijk[iBlock][2];
			BPoints = imax * jmax * kmax;
			for (k = 0; k < kmax; k++)
			{
				for (j = 0; j < jmax; j++)
				{
					for (i = 0; i < imax; i++)
					{
						Coord3D_X[iBlock][i][j][k] = tmp_Coord[n];
						Coord3D_Y[iBlock][i][j][k] = tmp_Coord[n + BPoints];
						Coord3D_Z[iBlock][i][j][k] = tmp_Coord[n + BPoints + BPoints];
						n++;
						//cout << "+++++++++++++++++++" << Coord3D_X[iBlock][i][j][k] << "&" << Coord3D_Y[iBlock][i][j][k] << "&" << Coord3D_Z[iBlock][i][j][k] << endl;
					}
				}
			}
			n = n + BPoints + BPoints;
		}
	}
	delete tmp_Coord;
}

void CPrepro::Get_BCs()
{

}

void CPrepro::Set_BCs()
{

}

void CPrepro::Initialization()
{

}