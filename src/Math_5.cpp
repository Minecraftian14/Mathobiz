#include "plugin.hpp"
#include "math.h"

struct MCXIV_Math_5 : Module {
    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        IN_A_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        OUT_LN_OUTPUT,
        OUT_LOG_OUTPUT,
        OUT_EXP_OUTPUT,
        OUT_SGN_OUTPUT,
        OUT_NEG_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    MCXIV_Math_5() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(IN_A_INPUT, "");
        configOutput(OUT_LN_OUTPUT, "");
        configOutput(OUT_LOG_OUTPUT, "");
        configOutput(OUT_EXP_OUTPUT, "");
        configOutput(OUT_SGN_OUTPUT, "");
        configOutput(OUT_NEG_OUTPUT, "");
    }

    void process(const ProcessArgs &args) override {
        float a = inputs[IN_A_INPUT].getVoltage();
        if (outputs[OUT_LN_OUTPUT].isConnected())
            outputs[OUT_LN_OUTPUT].setVoltage(logf(a));
        if (outputs[OUT_LOG_OUTPUT].isConnected())
            outputs[OUT_LOG_OUTPUT].setVoltage(log10f(a));
        if (outputs[OUT_EXP_OUTPUT].isConnected())
            outputs[OUT_EXP_OUTPUT].setVoltage(expf(a));
        if (outputs[OUT_SGN_OUTPUT].isConnected())
            outputs[OUT_SGN_OUTPUT].setVoltage(sgn(a));
        if (outputs[OUT_NEG_OUTPUT].isConnected())
            outputs[OUT_NEG_OUTPUT].setVoltage(-a);
    }
};


struct MCXIV_Math_5Widget : ModuleWidget {
    MCXIV_Math_5Widget(MCXIV_Math_5 *module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Math_5.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 11.662)), module, MCXIV_Math_5::IN_A_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 30.243)), module, MCXIV_Math_5::OUT_LN_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 48.824)), module, MCXIV_Math_5::OUT_LOG_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 67.405)), module, MCXIV_Math_5::OUT_EXP_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 85.985)), module, MCXIV_Math_5::OUT_SGN_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 104.566)), module, MCXIV_Math_5::OUT_NEG_OUTPUT));
    }
};


Model *modelMCXIV_Math_5 = createModel<MCXIV_Math_5, MCXIV_Math_5Widget>("MCXIV_Math_5");