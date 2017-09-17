//===- Operator.h -----------------------------------------------*- C++ -*-===//
//
//  Copyright (C) 2017  
//
//  This file is part of Clang-Toolnumberone.
//
//  Clang-Toolnumberone is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Clang-Toolnumberone is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with Clang-Toolnumberone. If not, see <http://www.gnu.org/licenses/>.
//
//===----------------------------------------------------------------------===//
/// \file Operator.h
/// \author 
/// \brief This file contains operators definition for VPA
//===----------------------------------------------------------------------===//

#ifndef INCLUDE_IIDEAA_VPAOPERATOR_H_
#define INCLUDE_IIDEAA_VPAOPERATOR_H_

#include "Core/MutationOperator.h"

namespace toolnumberone {
namespace vpamutator{

  /// @brief VPA Operation mutator
  /// @brief Create and return the IIDEAA operator
  /// @return the IIDEAA operator
  std::unique_ptr<::toolnumberone::m_operator::MutationOperator> getVPAOperator();

}  // End namespace vpa
}  // End namespace toolnumberone
#endif /* INCLUDE_IIDEAA_VPAOPERATOR_H_ */
