#include "plugin.hpp"
#include "math.h"

struct MCXIV_Math_2 : Module {
    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        IN_A_INPUT,
        IN_B_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        OUT_POW_OUTPUT,
        OUT_ROOT_OUTPUT,
        OUT_MAGN_OUTPUT,
        OUT_HYPOT_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    MCXIV_Math_2() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(IN_A_INPUT, "");
        configInput(IN_B_INPUT, "");
        configOutput(OUT_POW_OUTPUT, "");
        configOutput(OUT_ROOT_OUTPUT, "");
        configOutput(OUT_MAGN_OUTPUT, "");
        configOutput(OUT_HYPOT_OUTPUT, "");
    }

    void process(const ProcessArgs &args) override {
        float a = inputs[IN_A_INPUT].getVoltage();
        float b = inputs[IN_B_INPUT].getVoltage();
        if (outputs[OUT_POW_OUTPUT].isConnected())
            outputs[OUT_POW_OUTPUT].setVoltage(powf(a, b));
        if (outputs[OUT_ROOT_OUTPUT].isConnected())
            outputs[OUT_ROOT_OUTPUT].setVoltage(powf(a, 1 / b));

        float magn = 0;
        if (outputs[OUT_MAGN_OUTPUT].isConnected() || outputs[OUT_HYPOT_OUTPUT].isConnected())
            magn = a * a + b * b;
        outputs[OUT_MAGN_OUTPUT].setVoltage(magn);

        if (outputs[OUT_HYPOT_OUTPUT].isConnected())
            outputs[OUT_HYPOT_OUTPUT].setVoltage(sqrtf(magn));
    }
};


struct MCXIV_Math_2Widget : ModuleWidget {
    MCXIV_Math_2Widget(MCXIV_Math_2 *module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Math_2.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 11.662)), module, MCXIV_Math_2::IN_A_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 30.243)), module, MCXIV_Math_2::IN_B_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 48.824)), module, MCXIV_Math_2::OUT_POW_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 67.405)), module, MCXIV_Math_2::OUT_ROOT_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 85.985)), module, MCXIV_Math_2::OUT_MAGN_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 104.566)), module, MCXIV_Math_2::OUT_HYPOT_OUTPUT));
    }
};


Model *modelMCXIV_Math_2 = createModel<MCXIV_Math_2, MCXIV_Math_2Widget>("MCXIV_Math_2");