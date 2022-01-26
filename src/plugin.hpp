#pragma once

#include <rack.hpp>


using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin *pluginInstance;

// Declare each Model, defined in each module source file

extern Model *modelMCXIV_Math_1;
extern Model *modelMCXIV_Math_2;
extern Model *modelMCXIV_Math_3;
extern Model *modelMCXIV_Math_4;
extern Model *modelMCXIV_Math_5;
extern Model *modelMCXIV_Math_6;

extern Model *modelMCXIV_Logic_1;
extern Model *modelMCXIV_Logic_2;
extern Model *modelMCXIV_Logic_3;

extern Model *modelMCXIV_ARange;
extern Model *modelMCXIV_Drag;
extern Model *modelMCXIV_Map;
extern Model *modelMCXIV_Steps;
