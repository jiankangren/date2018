//
// Toolnumbertwo - Design Space Exploration for Approximate Computing technique using
// Gentic Algorithm
// Copyright (C) 2017 Antonio Tammaro <ntonjeta@autistici.org>
//
// This file is part of Toolnumbertwo.
//
// Toolnumbertwo is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Toolnumbertwo is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Toolnumbertwo.  If not, see <http://www.gnu.org/licenses/>.
//

/******************************************************************************
 * @file    main.cpp
 * @author  Antonio Tammaro
 * @date    3 gen 2017
 * @brief   Toolnumbertwo main file.
 * @details Basic steps:
 *          - Execute an external function
 *          -
 ******************************************************************************/
// Tool Headers
#include "Tool/ToolnumbertwoTool.h"
#include "Core/AprxContext.h"
// Plugin Headers
#include "Plugins/FLAP/FlapAprxContext.h"
#include "Plugins/FLAP/FlapAprxTechnique.h"
#include "Plugins/LoopPerforation/LoopAprxContext.h"
#include "Plugins/LoopPerforation/LoopAprxTechnique.h"
#include "Plugins/VPA/VpaAprxTechnique.h"
#include "Plugins/VPA/VpaAprxContext.h"
// C/C++ Headers
#include <cstdlib>

using namespace std;
using namespace toolnumbertwo;
 
main(int argc, const char *argv[]) {
  tool::ToolnumbertwoTool toolnumbertwotool;

  //Register user's plugins
  toolnumbertwotool.registerAprxContext(getFlapAprxContext());
  toolnumbertwotool.registerAprxContext(getLoopAprxContext());
  toolnumbertwotool.registerAprxContext(getVpaAprxContext());
  // run tool 
  toolnumbertwotool.run(argc,argv);
  return 0;
}
