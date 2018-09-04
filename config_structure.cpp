/*
Nebula started from 2018/7/3 20:30.

Nebula is a opensource softwere.

Copyright 2018-2018, Qiao Chen-Liang, Xu He-Yong, and the Nebula contributors.

*/

#include "../include/config_structure.h"

#include <string>

using namespace std;

CConfig::CConfig(char configfilename[])
{
	Read_Options(configfilename);

	Set_Options();

	map<string, COptionType *>::const_iterator it;

	for (it = setting_map.begin(); it != setting_map.end(); ++it)
	{
		cout << it->first << "=" << it->second << endl;
	}

}

void CConfig::Read_Options(char filename[])
{
	string::size_type pos, pos_end;
	//const string delimiters(" ()[]{}:,\t\n\v\f\r");
	configfile.open(filename, ios::in);
	if (configfile.fail())
	{
		cout << "not open!" << endl;
	}
	while (getline(configfile, option_line))
	{
		notoption = option_line.find_first_of("#");
		if ((notoption == 0) || (option_line.length() == 0))
		{ continue; }
		else
		{
			while ((pos = option_line.find(' ')) != string::npos)
			{ option_line.erase(pos, 1); }
			while ((pos = option_line.find('\t')) != string::npos)
			{ option_line.erase(pos, 1); }
		}
		pos = option_line.find("=");
		if (pos != string::npos)
		{
			option_name = option_line.substr(0, pos);
			option_value = option_line.substr(pos + 1, string::npos);
			option_map.insert(pair <string, string>(option_name, option_value));
		}
		else
		{
			cout << "The value of " << option_line << " is missing!" << endl;
			//return false;
		}
	}
	map<string, string>::const_iterator it;
	for (it = option_map.begin(); it != option_map.end(); ++it)
		cout << it->first << "=" << it->second << endl;
	cout << endl;
}

void CConfig::Set_Options()
{
	set_str_option("Mesh_Filename", Mesh_Filename);
	set_sel_option("Fluid_Solver", Fluid_Solver, Fluid_Solver_Map);
	set_sel_option("Dimension", Dimension, Dimension_Map);
	
	set_dbl_option("Mach_Inf", Mach_Inf);
	set_dbl_option("Reynolds", Reynolds);
	set_dbl_option("AoA", AoA);
	set_dbl_option("AoS", AoS);
	
	set_sel_option("Turbulence_Model", Turbulence_Model, Turbulence_Model_Map);

	set_dbl_option("CFL", CFL);

	set_bool_option("Restart", Restart);
	set_int_option("Save_P_Step", Save_P_Step);
	set_int_option("N_Step", N_Step);
	set_bool_option("Dual_T", Dual_T);
	set_dbl_option("Time_Step", Time_Step);
	set_int_option("Sub_Step", Sub_Step);

	set_sel_option("Fluid_Material", Fluid_Material, Fluid_Material_Map);
	
}