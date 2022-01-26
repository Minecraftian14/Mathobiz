#include "plugin.hpp"


struct MCXIV_Map : Module {
    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        IN_A_INPUT,
        IN_IU_INPUT,
        IN_IL_INPUT,
        IN_OU_INPUT,
        IN_OL_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        OUT_O_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    MCXIV_Map() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(IN_A_INPUT, "Input");
        configInput(IN_IU_INPUT, "Input Upper Point");
        configInput(IN_IL_INPUT, "Input Lower Point");
        configInput(IN_OU_INPUT, "Output Upper Point");
        configInput(IN_OL_INPUT, "Output Lower Point");
        configOutput(OUT_O_OUTPUT, "Output");
    }

    void process(const ProcessArgs &args) override {
        float a = inputs[IN_A_INPUT].getVoltage();
        float iu = inputs[IN_IU_INPUT].getVoltage();
        float il = inputs[IN_IL_INPUT].getVoltage();
        float ou = inputs[IN_OU_INPUT].getVoltage();
        float ol = inputs[IN_OL_INPUT].getVoltage();
//      a = a - il
//      a = a / (iu-il)
//      a = a * (ou-ol)
//      a = a + ol
        outputs[OUT_O_OUTPUT].setVoltage((a - il) * (ou - ol) / (iu - il) + ol);
    }
};


struct MCXIV_MapWidget : ModuleWidget {
    MCXIV_MapWidget(MCXIV_Map *module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Map.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 11.662)), module, MCXIV_Map::IN_A_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 30.243)), module, MCXIV_Map::IN_IU_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 48.824)), module, MCXIV_Map::IN_IL_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 67.405)), module, MCXIV_Map::IN_OU_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 85.985)), module, MCXIV_Map::IN_OL_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 104.566)), module, MCXIV_Map::OUT_O_OUTPUT));
    }
};


Model *modelMCXIV_Map = createModel<MCXIV_Map, MCXIV_MapWidget>("MCXIV_Map");