#include "plugin.hpp"


struct MCXIV_Logic_3 : Module {
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
        OUT_NAND_OUTPUT,
        OUT_NOR_OUTPUT,
        OUT_XNOR_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    MCXIV_Logic_3() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(IN_T_INPUT, "Threshold");
        configInput(IN_A_INPUT, "Input A");
        configInput(IN_B_INPUT, "Input B");
        configOutput(OUT_NAND_OUTPUT, "Nand");
        configOutput(OUT_NOR_OUTPUT, "Nor");
        configOutput(OUT_XNOR_OUTPUT, "Xnor");
    }

    void process(const ProcessArgs &args) override {
        float threshold = inputs[IN_T_INPUT].getVoltage();
        float a = inputs[IN_A_INPUT].getVoltage();
        float b = inputs[IN_B_INPUT].getVoltage();
        if (fabsf(a) < threshold) a = 0;
        else a = 1;
        if (fabsf(b) < threshold) b = 0;
        else b = 1;
        if (outputs[OUT_NAND_OUTPUT].isConnected())
            outputs[OUT_NAND_OUTPUT].setVoltage(a * b == 0);
        if (outputs[OUT_NOR_OUTPUT].isConnected())
            outputs[OUT_NOR_OUTPUT].setVoltage(a + b == 0);
        if (outputs[OUT_XNOR_OUTPUT].isConnected())
            outputs[OUT_XNOR_OUTPUT].setVoltage(a != 0);
    }

};


struct MCXIV_Logic_3Widget : ModuleWidget {
    MCXIV_Logic_3Widget(MCXIV_Logic_3 *module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Logic_3.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 11.662)), module, MCXIV_Logic_3::IN_T_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 30.243)), module, MCXIV_Logic_3::IN_A_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 48.824)), module, MCXIV_Logic_3::IN_B_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 67.405)), module, MCXIV_Logic_3::OUT_NAND_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 85.985)), module, MCXIV_Logic_3::OUT_NOR_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 104.566)), module, MCXIV_Logic_3::OUT_XNOR_OUTPUT));
    }
};


Model *modelMCXIV_Logic_3 = createModel<MCXIV_Logic_3, MCXIV_Logic_3Widget>("MCXIV_Logic_3");