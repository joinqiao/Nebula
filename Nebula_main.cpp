/*
Nebula started from 2018/7/3 20:30.

Nebula is a opensource softwere.

Copyright 2018-2018, Qiao Chen-Liang, Xu He-Yong, and the Nebula contributors.

*/

#include "../include/Nebula_main.h"

using namespace std;

int main(int argc, char *argv[])
{
	int i, imax;
	unsigned int nDim;
	imax = 10;
	char configfilename[NAME_SIZE_LIM];
	int MPI_rank, MPI_size;
	string meshfilename;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &MPI_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &MPI_size);

	if (MPI_rank == 0)
	{
		if (argc == 2)
		{ strcpy(configfilename, argv[1]); }
		else
		{
			cout << "-------------------The configuration file is missing.-------------------" << endl;
			cout << "----Plesse type the configuration file name after the software name.----" << endl;
			exit(EXIT_FAILURE);
		}
	}
	

	CConfig *config = NULL;			// 创建设置指针
	config = new CConfig(configfilename);
	meshfilename = config->Get_Mesh_Filename();
	nDim = config->Get_Dimension();
	CPrepro *prepro = NULL;
	prepro = new CPrepro(meshfilename, nDim);
	

	

	for (i = 0; i < imax; i++)
	{
		cout << i;
		if (i == 5)
		{
			cout << "endling" << endl;
		}
	}
	cout << endl << argc << endl;
	for (i = 0; i < argc; i++)
	{
		cout << argv[i] << endl;
	}
	cout << "mesh：" << meshfilename << endl;
	//CDriver *driver = NULL;



	//if (driver != NULL) delete driver;
	//driver = NULL;

	MPI_Finalize();
	return EXIT_SUCCESS;
}



