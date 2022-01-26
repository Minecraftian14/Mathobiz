#include "plugin.hpp"


struct MCXIV_Drag : Module {

    // Current state (either one of A or B)
    float c = 0;

    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        IN_A_INPUT,
        IN_B_INPUT,
        IN_STATE_INPUT,
        IN_FACTOR_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        OUT_O_OUTPUT,
        OUT_POS_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    MCXIV_Drag() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(IN_A_INPUT, "Input A");
        configInput(IN_B_INPUT, "Input B");
        configInput(IN_STATE_INPUT, "Set State [ve-/ve+]");
        configInput(IN_FACTOR_INPUT, "Set Rate");
        configOutput(OUT_O_OUTPUT, "Output");
        configOutput(OUT_POS_OUTPUT, "Instantaneous Factor");
    }

    void process(const ProcessArgs &args) override {
        float a = inputs[IN_A_INPUT].getVoltage();
        float b = inputs[IN_B_INPUT].getVoltage();

        float f = inputs[IN_FACTOR_INPUT].getVoltage();
        f = clamp(f, 0.f, 1.f);

        float s = inputs[IN_STATE_INPUT].getVoltage();

        if (s < 0) /* Move towards A */ {
            c = lerp(c, 0, f);
        } else /* Move towards B */ {
            c = lerp(c, 1, f);
        }

        outputs[OUT_O_OUTPUT].setVoltage(lerp(a, b, c));
        outputs[OUT_POS_OUTPUT].setVoltage(c);
    }

    static float lerp(float a, float b, float f) {
        return a + (b - a) * f;
    }

};


struct MCXIV_DragWidget : ModuleWidget {
    MCXIV_DragWidget(MCXIV_Drag *module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Drag.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 11.662)), module, MCXIV_Drag::IN_A_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 30.243)), module, MCXIV_Drag::IN_B_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 48.824)), module, MCXIV_Drag::IN_STATE_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 67.405)), module, MCXIV_Drag::IN_FACTOR_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 85.985)), module, MCXIV_Drag::OUT_O_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 104.566)), module, MCXIV_Drag::OUT_POS_OUTPUT));
    }
};


Model *modelMCXIV_Drag = createModel<MCXIV_Drag, MCXIV_DragWidget>("MCXIV_Drag");