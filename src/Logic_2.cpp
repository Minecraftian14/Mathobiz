#include "plugin.hpp"


struct MCXIV_Logic_2 : Module {
    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        IN_T_INPUT,
        IN_A_INPUT,
        IN_B_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        OUT_AND_OUTPUT,
        OUT_OR_OUTPUT,
        OUT_XOR_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    MCXIV_Logic_2() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(IN_T_INPUT, "Threshold");
        configInput(IN_A_INPUT, "Input A");
        configInput(IN_B_INPUT, "Input B");
        configOutput(OUT_AND_OUTPUT, "And");
        configOutput(OUT_OR_OUTPUT, "Or");
        configOutput(OUT_XOR_OUTPUT, "Xor");
    }

    void process(const ProcessArgs &args) override {
        float threshold = inputs[IN_T_INPUT].getVoltage();
        float a = inputs[IN_A_INPUT].getVoltage();
        float b = inputs[IN_B_INPUT].getVoltage();
        if (fabsf(a) < threshold) a = 0;
        else a = 1;
        if (fabsf(b) < threshold) b = 0;
        else b = 1;
        if (outputs[OUT_AND_OUTPUT].isConnected())
            outputs[OUT_AND_OUTPUT].setVoltage(a * b);
        if (outputs[OUT_OR_OUTPUT].isConnected())
            outputs[OUT_OR_OUTPUT].setVoltage(a + b > 0);
        if (outputs[OUT_XOR_OUTPUT].isConnected())
            outputs[OUT_XOR_OUTPUT].setVoltage(a == b);
    }
};


struct MCXIV_Logic_2Widget : ModuleWidget {
    MCXIV_Logic_2Widget(MCXIV_Logic_2 *module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Logic_2.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 11.662)), module, MCXIV_Logic_2::IN_T_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 30.243)), module, MCXIV_Logic_2::IN_A_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 48.824)), module, MCXIV_Logic_2::IN_B_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 67.405)), module, MCXIV_Logic_2::OUT_AND_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 85.985)), module, MCXIV_Logic_2::OUT_OR_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 104.566)), module, MCXIV_Logic_2::OUT_XOR_OUTPUT));
    }
};


Model *modelMCXIV_Logic_2 = createModel<MCXIV_Logic_2, MCXIV_Logic_2Widget>("MCXIV_Logic_2");