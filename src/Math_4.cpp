#include "plugin.hpp"
#include "math.h"


struct MCXIV_Math_4 : Module {
    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        IN_A_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        OUT_MOD_OUTPUT,
        OUT_ROOT_OUTPUT,
        OUT_SQR_OUTPUT,
        OUT_CRT_OUTPUT,
        OUT_CUBE_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    MCXIV_Math_4() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(IN_A_INPUT, "");
        configOutput(OUT_MOD_OUTPUT, "");
        configOutput(OUT_ROOT_OUTPUT, "");
        configOutput(OUT_SQR_OUTPUT, "");
        configOutput(OUT_CRT_OUTPUT, "");
        configOutput(OUT_CUBE_OUTPUT, "");
    }

    void process(const ProcessArgs &args) override {
        float a = inputs[IN_A_INPUT].getVoltage();
        if (outputs[OUT_MOD_OUTPUT].isConnected())
            outputs[OUT_MOD_OUTPUT].setVoltage(a < 0 ? -a : a);
        if (outputs[OUT_ROOT_OUTPUT].isConnected())
            outputs[OUT_ROOT_OUTPUT].setVoltage(sqrtf(a));
        if (outputs[OUT_SQR_OUTPUT].isConnected())
            outputs[OUT_SQR_OUTPUT].setVoltage(a * a);
        if (outputs[OUT_CRT_OUTPUT].isConnected())
            outputs[OUT_CRT_OUTPUT].setVoltage(cbrtf(a));
        if (outputs[OUT_CUBE_OUTPUT].isConnected())
            outputs[OUT_CUBE_OUTPUT].setVoltage(a * a * a);
    }
};


struct MCXIV_Math_4Widget : ModuleWidget {
    MCXIV_Math_4Widget(MCXIV_Math_4 *module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Math_4.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 11.662)), module, MCXIV_Math_4::IN_A_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 30.243)), module, MCXIV_Math_4::OUT_MOD_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 48.824)), module, MCXIV_Math_4::OUT_ROOT_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 67.405)), module, MCXIV_Math_4::OUT_SQR_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 85.985)), module, MCXIV_Math_4::OUT_CRT_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 104.566)), module, MCXIV_Math_4::OUT_CUBE_OUTPUT));
    }
};


Model *modelMCXIV_Math_4 = createModel<MCXIV_Math_4, MCXIV_Math_4Widget>("MCXIV_Math_4");