#include "plugin.hpp"


struct MCXIV_Logic_1 : Module {
    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        IN_T_INPUT,
        IN_A_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        OUT_NOT_OUTPUT,
        OUT_INV_OUTPUT,
        OUT_EVEN_OUTPUT,
        OUT_ODD_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    MCXIV_Logic_1() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(IN_T_INPUT, "Threshold");
        configInput(IN_A_INPUT, "Input");
        configOutput(OUT_NOT_OUTPUT, "Not");
        configOutput(OUT_INV_OUTPUT, "Invert");
        configOutput(OUT_EVEN_OUTPUT, "Is Even");
        configOutput(OUT_ODD_OUTPUT, "Is Odd");
    }

    void process(const ProcessArgs &args) override {
        float threshold = inputs[IN_T_INPUT].getVoltage();
        float a = inputs[IN_A_INPUT].getVoltage();
        if (outputs[OUT_NOT_OUTPUT].isConnected())
            outputs[OUT_NOT_OUTPUT].setVoltage(fabsf(a) > threshold);
        if (outputs[OUT_NOT_OUTPUT].isConnected())
            outputs[OUT_NOT_OUTPUT].setVoltage(~((int) a));
        if (outputs[OUT_EVEN_OUTPUT].isConnected())
            outputs[OUT_EVEN_OUTPUT].setVoltage(fabsf(fmodf(a, 2.f)) < threshold);
        if (outputs[OUT_ODD_OUTPUT].isConnected())
            outputs[OUT_ODD_OUTPUT].setVoltage(fabsf(fmodf(a, 2.f) - 1) < threshold);
    }
};


struct MCXIV_Logic_1Widget : ModuleWidget {
    MCXIV_Logic_1Widget(MCXIV_Logic_1 *module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Logic_1.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 11.662)), module, MCXIV_Logic_1::IN_T_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 30.243)), module, MCXIV_Logic_1::IN_A_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 48.824)), module, MCXIV_Logic_1::OUT_NOT_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 67.405)), module, MCXIV_Logic_1::OUT_INV_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 85.985)), module, MCXIV_Logic_1::OUT_EVEN_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 104.566)), module, MCXIV_Logic_1::OUT_ODD_OUTPUT));
    }
};


Model *modelMCXIV_Logic_1 = createModel<MCXIV_Logic_1, MCXIV_Logic_1Widget>("MCXIV_Logic_1");