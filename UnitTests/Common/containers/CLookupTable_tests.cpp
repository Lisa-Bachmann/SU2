/*!
 * \file CLookupTable_tests.cpp
 * \brief Unit tests for the lookup table.
 * \author N. Beishuizen
 * \version 8.0.1 "Harrier"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2024, SU2 Contributors (cf. AUTHORS.md)
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#include "catch.hpp"

#include <sstream>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "../../../Common/include/CConfig.hpp"
#include "../../../Common/include/containers/CTrapezoidalMap.hpp"
#include "../../../Common/include/containers/CLookUpTable.hpp"
#include "../../../Common/include/containers/CFileReaderLUT.hpp"

TEST_CASE("LUTreader", "[tabulated chemistry]") {
  /*--- smaller and trivial lookup table ---*/

  CLookUpTable look_up_table("/home/bal1dev/simulations/00_2D_Validation/lut/multicomponent_SetupwithworkingTemp/LUT_TableGeneration.drg", "ProgressVariable", "EnthalpyTot");

  /*--- string names of the controlling variables ---*/

  string name_CV1 = "ProgressVariable";
  string name_CV2 = "EnthalpyTot";

  /*--- look up a single value for density ---*/
  su2double temp = 300;
  su2double pv = 0;
  string look_up_tag = "EnthalpyTot";
  unsigned long idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
  su2double look_up_dat;
  look_up_table.LookUp_XY(idx_tag, &look_up_dat, temp, pv);
  CHECK(look_up_dat == Approx(2200));
  std::cout << look_up_dat << std::endl;

  su2double enth = 2200;
  pv = 0;
  look_up_tag = "Temperature";
  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
  look_up_table.LookUp_XY(idx_tag, &look_up_dat, enth, pv);
  CHECK(look_up_dat == Approx(300));
  std::cout << look_up_dat << std::endl;

  /*enth = 2228;
  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
  look_up_table.LookUp_XY(idx_tag, &look_up_dat, enth, pv);
  CHECK(look_up_dat == Approx(300));
  std::cout << look_up_dat << std::endl;*/
  /*--- look up a single value for viscosity ---*/

/*  prog = 0.6;
  enth = 0.9;
  look_up_tag = "Viscosity";
  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
  look_up_table.LookUp_XY(idx_tag, &look_up_dat, prog, enth);
  CHECK(look_up_dat == Approx(0.0000674286));
*/
  /* find the table limits */

  /*auto limitsEnth = look_up_table.GetTableLimitsY();
  CHECK(SU2_TYPE::GetValue(*limitsEnth.first) == Approx(-1.0));
  CHECK(SU2_TYPE::GetValue(*limitsEnth.second) == Approx(1.0));

  auto limitsProgvar = look_up_table.GetTableLimitsX();
  CHECK(SU2_TYPE::GetValue(*limitsProgvar.first) == Approx(0.0));
  CHECK(SU2_TYPE::GetValue(*limitsProgvar.second) == Approx(1.0));

  /* lookup value outside of lookup table */

  /*prog = -0.57414;
  su2double enth = 2228;
  look_up_tag = "Temperature";
  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
  look_up_table.LookUp_XY(idx_tag, &look_up_dat, prog, enth);
  CHECK(look_up_dat == Approx(300));*/
}

TEST_CASE("LUTreader_3D", "[tabulated chemistry]") {
  /*--- smaller and trivial lookup table ---*/

  CLookUpTable look_up_table("LUT_TableGeneration.drg", "ProgressVariable", "EnthalpyTot");


  /*--- string names of the controlling variables ---*/

  string name_CV1 = "ProgressVariable";
  string name_CV2 = "EnthalpyTot";
  string name_CV3 = "MixtureFraction";

  /*--- look up a single value for density ---*/

  su2double prog = -0.57;
  su2double enth = 2200;
  su2double mfrac = 0.01446;

  /*--- setting up .txt file ---*/

  std::ofstream file("/home/bal1dev/simulations/PINNTraining/output_LUT_multicomponent.txt", std::ios::trunc);
   if (file.is_open()) {
  	file << "Mixture Fraction Z=" << mfrac<< "	Enthalpy h=" << enth<< std::endl;
	file << "ProgressVariable,Temperature,Conductivity,ViscosityDyn,Cp,MolarWeightMix,DiffusionCoefficient,Beta_ProgVar, Beta_Enth,Beta_Enth_Thermal,Beta_MixFrac,ProdRateTot_PV,Y-H,Y_dot_net-NOx"<< std::endl;

	// Iterate and save the new values of x and y
     	for (prog; prog < 0.036; prog +=0.001) {

	  string look_up_tag = "Temperature";
  	  unsigned long idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
  	  su2double look_up_dat;
  	  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
	  float temperature = look_up_dat;

	  look_up_tag = "Conductivity";
	  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
	  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
	  float conductivity = look_up_dat;

	  look_up_tag = "ViscosityDyn";
	  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
	  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
	  float viscosity = look_up_dat;

	  look_up_tag = "Cp";
	  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
	  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
	  float cp = look_up_dat;

	  look_up_tag = "MolarWeightMix";
	  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
	  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
	  float molarweightmix = look_up_dat;

	  look_up_tag = "DiffusionCoefficient";
	  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
	  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
	  float diffusion = look_up_dat;

	  look_up_tag = "Beta_ProgVar";
	  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
	  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
	  float beta_progvar = look_up_dat;

	  look_up_tag = "Beta_Enth_Thermal";
	  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
	  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
	  float beta_enth_thermal = look_up_dat;

	  look_up_tag = "Beta_Enth";
	  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
	  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
	  float beta_enth = look_up_dat;

	  look_up_tag = "Beta_MixFrac";
	  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
	  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
	  float beta_mixfrac = look_up_dat;

	  look_up_tag = "ProdRateTot_PV";
	  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
	  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
	  float prodratetot = look_up_dat;

	  /*look_up_tag = "Y-H";
	  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
	  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
	  float yh = look_up_dat;

	  look_up_tag = "Y_dot_net-NOx";
	  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
	  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
	  float ydotnetnox = look_up_dat;*/

	  file << prog << "," << temperature << "," << conductivity << "," << viscosity << "," << cp << "," << molarweightmix << "," << diffusion << "," << beta_progvar << "," << beta_enth_thermal << "," << beta_enth << "," << beta_mixfrac << "," << prodratetot<< std::endl;
	}
	     // Close the file
     	file.close();
   } else {
     // Print an error message if the file couldn't be opened
     std::cout << "Error: Unable to create or open the file for writing" << std::endl;
   }

}

TEST_CASE("LUTreader_3D_enthAndPV", "[tabulated chemistry]") {
  /*--- smaller and trivial lookup table ---*/

  CLookUpTable look_up_table("LUT_TableGeneration.drg", "ProgressVariable", "EnthalpyTot");


  /*--- string names of the controlling variables ---*/

  string name_CV1 = "ProgressVariable";
  string name_CV2 = "EnthalpyTot";
  string name_CV3 = "MixtureFraction";

  /*--- look up a single value for density ---*/

  su2double prog = -0.59;
  su2double enth = -2000000;
  su2double mfrac = 0.01446;

  /*--- setting up .txt file ---*/

  std::ofstream file("output_LUT_multicomponent.txt", std::ios::trunc);
   if (file.is_open()) {
  	file << "Mixture Fraction Z=" << mfrac<< "	Enthalpy h=" << enth<< std::endl;
	file << "ProgressVariable,TotalEnthalpy,Temperature,Conductivity,ViscosityDyn,Cp,MolarWeightMix,DiffusionCoefficient,Beta_ProgVar, Beta_Enth,Beta_Enth_Thermal,Beta_MixFrac,ProdRateTot_PV"<< std::endl;

	// Iterate and save the new values of x and y
     	 for (enth= -2000000; enth < 500000; enth +=10000) {     	
	for (prog= -0.59; prog < 0.036; prog +=0.001) {
		  string look_up_tag = "Temperature";
	  	  unsigned long idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
	  	  su2double look_up_dat;
	  	  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
		  float temperature = look_up_dat;

		  look_up_tag = "Conductivity";
		  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
		  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
		  float conductivity = look_up_dat;

		  look_up_tag = "ViscosityDyn";
		  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
		  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
		  float viscosity = look_up_dat;

		  look_up_tag = "Cp";
		  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
		  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
		  float cp = look_up_dat;

		  look_up_tag = "MolarWeightMix";
		  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
		  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
		  float molarweightmix = look_up_dat;

		  look_up_tag = "DiffusionCoefficient";
		  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
		  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
		  float diffusion = look_up_dat;

		  look_up_tag = "Beta_ProgVar";
		  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
		  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
		  float beta_progvar = look_up_dat;

		  look_up_tag = "Beta_Enth_Thermal";
		  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
		  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
		  float beta_enth_thermal = look_up_dat;

		  look_up_tag = "Beta_Enth";
		  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
		  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
		  float beta_enth = look_up_dat;

		  look_up_tag = "Beta_MixFrac";
		  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
		  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
		  float beta_mixfrac = look_up_dat;

		  look_up_tag = "ProdRateTot_PV";
		  idx_tag = look_up_table.GetIndexOfVar(look_up_tag);
		  look_up_table.LookUp_XYZ(idx_tag, &look_up_dat, prog, enth, mfrac);
		  float prodratetot = look_up_dat;

		  file << prog << ","<< enth << "," << temperature << "," << conductivity << "," << viscosity << "," << cp << "," << molarweightmix << "," << diffusion << "," << beta_progvar << "," << beta_enth_thermal << "," << beta_enth << "," << beta_mixfrac << "," << prodratetot << std::endl;
	 }
	}
	     // Close the file
     	file.close();
   } else {
     // Print an error message if the file couldn't be opened
     std::cout << "Error: Unable to create or open the file for writing" << std::endl;
   }

}

TEST_CASE("LUT_limits", "[tabulated chemistry]") {
  /*--- smaller and trivial lookup table ---*/

  CLookUpTable look_up_table("/home/bal1dev/simulations/FlameletAI_with_LUT/flameletAI_unityLewis/TestCases/HydrogenAir/hydrogen_flamelet_data_refined/LUT_hydrogen_refined.drg", "ProgressVariable", "EnthalpyTot");

  /*--- string names of the controlling variables ---*/

  string name_CV1 = "ProgressVariable";
  string name_CV2 = "EnthalpyTot";

  /* find the table limits */

  auto limitsEnth = look_up_table.GetTableLimitsY();
  std::cout << "Table Limits for Enthalpy: " << *limitsEnth.first << " to " << *limitsEnth.second << std::endl;

  auto limitsProgvar = look_up_table.GetTableLimitsX();
  std::cout << "Table Limits for Progress Variable: " << *limitsProgvar.first << " to " << *limitsProgvar.second << std::endl;
}


