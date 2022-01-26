#include "plugin.hpp"


Plugin *pluginInstance;


void init(Plugin *p) {
    pluginInstance = p;

    // Add modules here
    p->addModel(modelMCXIV_Math_1);
    p->addModel(modelMCXIV_Math_2);
    p->addModel(modelMCXIV_Math_3);
    p->addModel(modelMCXIV_Math_4);
    p->addModel(modelMCXIV_Math_5);
    p->addModel(modelMCXIV_Math_6);

    p->addModel(modelMCXIV_Logic_1);
    p->addModel(modelMCXIV_Logic_2);
    p->addModel(modelMCXIV_Logic_3);

    p->addModel(modelMCXIV_ARange);
    p->addModel(modelMCXIV_Drag);
    p->addModel(modelMCXIV_Map);
    p->addModel(modelMCXIV_Steps);

    // Any other plugin initialization may go here.
    // As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
