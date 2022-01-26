#include "plugin.hpp"


struct MCXIV_Math_1 : Module {
    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        IN_A_INPUT,
        IN_B_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        OUT_SUM_OUTPUT,
        OUT_DIFF_OUTPUT,
        OUT_PROD_OUTPUT,
        OUT_RATIO_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    MCXIV_Math_1() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(IN_A_INPUT, "Input A");
        configInput(IN_B_INPUT, "Input B");
        configOutput(OUT_SUM_OUTPUT, "Sum");
        configOutput(OUT_DIFF_OUTPUT, "Difference");
        configOutput(OUT_PROD_OUTPUT, "Product");
        configOutput(OUT_RATIO_OUTPUT, "Division");
    }

    void process(const ProcessArgs &args) override {
        float a = inputs[IN_A_INPUT].getVoltage();
        float b = inputs[IN_B_INPUT].getVoltage();
        if (outputs[OUT_SUM_OUTPUT].isConnected())
            outputs[OUT_SUM_OUTPUT].setVoltage(a + b);
        if (outputs[OUT_DIFF_OUTPUT].isConnected())
            outputs[OUT_DIFF_OUTPUT].setVoltage(a - b);
        if (outputs[OUT_PROD_OUTPUT].isConnected())
            outputs[OUT_PROD_OUTPUT].setVoltage(a * b);
        if (outputs[OUT_RATIO_OUTPUT].isConnected())
            outputs[OUT_RATIO_OUTPUT].setVoltage(a / b);
    }
};


struct MCXIV_Math_1Widget : ModuleWidget {
    MCXIV_Math_1Widget(MCXIV_Math_1 *module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Math_1.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 11.662)), module, MCXIV_Math_1::IN_A_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 30.243)), module, MCXIV_Math_1::IN_B_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 48.824)), module, MCXIV_Math_1::OUT_SUM_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 67.405)), module, MCXIV_Math_1::OUT_DIFF_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 85.985)), module, MCXIV_Math_1::OUT_PROD_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 104.566)), module, MCXIV_Math_1::OUT_RATIO_OUTPUT));
    }
};


Model *modelMCXIV_Math_1 = createModel<MCXIV_Math_1, MCXIV_Math_1Widget>("MCXIV_Math_1");