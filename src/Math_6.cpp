#include "plugin.hpp"
#include "math.h"

struct MCXIV_Math_6 : Module {
    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        IN_A_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        OUT_FLR_OUTPUT,
        OUT_CIL_OUTPUT,
        OUT_RND_OUTPUT,
        OUT_SCI_OUTPUT,
        OUT_FRC_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    MCXIV_Math_6() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(IN_A_INPUT, "");
        configOutput(OUT_FLR_OUTPUT, "");
        configOutput(OUT_CIL_OUTPUT, "");
        configOutput(OUT_RND_OUTPUT, "");
        configOutput(OUT_SCI_OUTPUT, "");
        configOutput(OUT_FRC_OUTPUT, "");
    }

    void process(const ProcessArgs &args) override {
        float a = inputs[IN_A_INPUT].getVoltage();
        if (outputs[OUT_FLR_OUTPUT].isConnected())
            outputs[OUT_FLR_OUTPUT].setVoltage(floorf(a));
        if (outputs[OUT_CIL_OUTPUT].isConnected())
            outputs[OUT_CIL_OUTPUT].setVoltage(ceilf(a));
        if (outputs[OUT_RND_OUTPUT].isConnected())
            outputs[OUT_RND_OUTPUT].setVoltage(roundf(a));
        if (outputs[OUT_SCI_OUTPUT].isConnected())
            outputs[OUT_SCI_OUTPUT].setVoltage(roundf(a * 16.f) / 16.f);
        if (outputs[OUT_FRC_OUTPUT].isConnected())
            outputs[OUT_FRC_OUTPUT].setVoltage(fractionalPart(a));
    }

    static float fractionalPart(float value) {
        float sign = value >= 0 ? 1.f : -1.f;
        float absVal = fabsf(value);
        return isinf(value) ? 0.f : sign * (absVal - floorf(absVal));
    }

};


struct MCXIV_Math_6Widget : ModuleWidget {
    MCXIV_Math_6Widget(MCXIV_Math_6 *module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Math_6.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 11.662)), module, MCXIV_Math_6::IN_A_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 30.243)), module, MCXIV_Math_6::OUT_FLR_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 48.824)), module, MCXIV_Math_6::OUT_CIL_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 67.405)), module, MCXIV_Math_6::OUT_RND_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 85.985)), module, MCXIV_Math_6::OUT_SCI_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 104.566)), module, MCXIV_Math_6::OUT_FRC_OUTPUT));
    }
};


Model *modelMCXIV_Math_6 = createModel<MCXIV_Math_6, MCXIV_Math_6Widget>("MCXIV_Math_6");