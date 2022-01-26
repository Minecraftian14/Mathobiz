#include "plugin.hpp"
#include "math.h"

struct MCXIV_Math_3 : Module {
    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        IN_A_INPUT,
        IN_B_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        OUT_MAX_OUTPUT,
        OUT_MIN_OUTPUT,
        OUT_GRET_OUTPUT,
        OUT_LESS_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    MCXIV_Math_3() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(IN_A_INPUT, "");
        configInput(IN_B_INPUT, "");
        configOutput(OUT_MAX_OUTPUT, "");
        configOutput(OUT_MIN_OUTPUT, "");
        configOutput(OUT_GRET_OUTPUT, "");
        configOutput(OUT_LESS_OUTPUT, "");
    }

    void process(const ProcessArgs &args) override {
        float a = inputs[IN_A_INPUT].getVoltage();
        float b = inputs[IN_B_INPUT].getVoltage();
        bool g = a > b;
        bool l = a < b;
        if (outputs[OUT_MAX_OUTPUT].isConnected())
            outputs[OUT_MAX_OUTPUT].setVoltage(g ? a : b);
        if (outputs[OUT_MIN_OUTPUT].isConnected())
            outputs[OUT_MIN_OUTPUT].setVoltage(l ? a : b);
        if (outputs[OUT_GRET_OUTPUT].isConnected())
            outputs[OUT_GRET_OUTPUT].setVoltage(g ? a : 0);
        if (outputs[OUT_LESS_OUTPUT].isConnected())
            outputs[OUT_LESS_OUTPUT].setVoltage(l ? a : 0);
    }
};


struct MCXIV_Math_3Widget : ModuleWidget {
    MCXIV_Math_3Widget(MCXIV_Math_3 *module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Math_3.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 11.662)), module, MCXIV_Math_3::IN_A_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 30.243)), module, MCXIV_Math_3::IN_B_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 48.824)), module, MCXIV_Math_3::OUT_MAX_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 67.405)), module, MCXIV_Math_3::OUT_MIN_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 85.985)), module, MCXIV_Math_3::OUT_GRET_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 104.566)), module, MCXIV_Math_3::OUT_LESS_OUTPUT));
    }
};


Model *modelMCXIV_Math_3 = createModel<MCXIV_Math_3, MCXIV_Math_3Widget>("MCXIV_Math_3");