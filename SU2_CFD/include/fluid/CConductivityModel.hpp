/*!
 * \file CConductivityModel.hpp
 * \brief Defines an interface class for thermal conductivity models.
 * \author S. Vitale, M. Pini, G. Gori, A. Guardone, P. Colonna, T. Economon
 * \version 7.2.1 "Blackbird"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2021, SU2 Contributors (cf. AUTHORS.md)
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

#pragma once

#include "../../../Common/include/basic_types/datatype_structure.hpp"

using namespace std;

/*!
 * \class CConductivityModel
 * \brief Interface class for defining the thermal conductivity model.
 * \author S. Vitale, M. Pini
 */
class CConductivityModel {
 public:
  CConductivityModel() = default;
  CConductivityModel(const CConductivityModel&) = delete;
  void operator=(const CConductivityModel&) = delete;
  virtual ~CConductivityModel() {}

  /*!
   * \brief return conductivity value.
   */
  virtual su2double GetConductivity(void) const = 0;

  /*!
   * \brief return conductivity partial derivative value.
   */
  virtual su2double Getdktdrho_T(void) const = 0;

  /*!
   * \brief return viscosity partial derivative value.
   */
  virtual su2double GetdktdT_rho(void) const = 0;

  /*!
   * \brief Set thermal conductivity.
   */
  virtual void SetConductivity(su2double t, su2double rho, su2double mu_lam, su2double mu_turb, su2double cp) = 0;

  /*!
   * \brief Set thermal conductivity derivatives.
   */
  virtual void SetDerConductivity(su2double t, su2double rho, su2double dmudrho_t, su2double dmudt_rho,
                                  su2double cp) = 0;
};
