#include "plugin.hpp"


struct MCXIV_ARange : Module {

    float minA = -1, maxA = 1;
    float minB = -1, maxB = 1;

    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        IN_A_INPUT,
        IN_ARES_INPUT,
        IN_B_INPUT,
        IN_BRES_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        OUT_A_OUTPUT,
        OUT_B_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    MCXIV_ARange() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(IN_A_INPUT, "Input A");
        configInput(IN_ARES_INPUT, "Reset A");
        configInput(IN_B_INPUT, "Input B");
        configInput(IN_BRES_INPUT, "Reset B");
        configOutput(OUT_A_OUTPUT, "Output A");
        configOutput(OUT_B_OUTPUT, "Output B");
    }

    void process(const ProcessArgs &args) override {
        outputs[OUT_A_OUTPUT].setVoltage(manipulateRange(&minA, &maxA, inputs[IN_A_INPUT].getVoltage()));
        outputs[OUT_B_OUTPUT].setVoltage(manipulateRange(&minB, &maxB, inputs[IN_B_INPUT].getVoltage()));
        if (inputs[IN_ARES_INPUT].getVoltage() > 0) {
            minA = -1;
            maxA = 1;
        }
        if (inputs[IN_BRES_INPUT].getVoltage() > 0) {
            minB = -1;
            maxB = 1;
        }
    }

    static float manipulateRange(float *min, float *max, float val) {
        if (val < *min) *min = val;
        if (val > *max) *max = val;
        return (val - *min) / (*max - *min) * 2 - 1;
    }

};


struct MCXIV_ARangeWidget : ModuleWidget {
    MCXIV_ARangeWidget(MCXIV_ARange *module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/ARange.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 11.662)), module, MCXIV_ARange::IN_A_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 30.243)), module, MCXIV_ARange::IN_ARES_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 67.405)), module, MCXIV_ARange::IN_B_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 85.985)), module, MCXIV_ARange::IN_BRES_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 48.824)), module, MCXIV_ARange::OUT_A_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 104.566)), module, MCXIV_ARange::OUT_B_OUTPUT));
    }
};


Model *modelMCXIV_ARange = createModel<MCXIV_ARange, MCXIV_ARangeWidget>("MCXIV_ARange");