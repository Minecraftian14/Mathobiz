#include "plugin.hpp"


struct MCXIV_Steps : Module {
    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        IN_A_INPUT,
        IN_STEPS_INPUT,
        IN_SLOPE_RISE_INPUT,
        IN_SLOPE_CRUISE_INPUT,
        IN_DOT_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        OUT_O_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    MCXIV_Steps() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(IN_A_INPUT, "Input");
        configInput(IN_STEPS_INPUT, "Steps");
        configInput(IN_SLOPE_RISE_INPUT, "Rise Slope");
        configInput(IN_SLOPE_CRUISE_INPUT, "Cruise Slope");
        configInput(IN_DOT_INPUT, "Dot");
        configOutput(OUT_O_OUTPUT, "Output");
    }

    void process(const ProcessArgs &args) override {
        float a = inputs[IN_A_INPUT].getVoltage();
//        a = a / 2 + 0.5f;
        if (a < 0) {
            outputs[OUT_O_OUTPUT].setVoltage(-1);
            return;
        } else if (a > 1) {
            outputs[OUT_O_OUTPUT].setVoltage(1);
            return;
        }

        float steps = inputs[IN_STEPS_INPUT].getVoltage();

        // Width of one step
        float w = 1 / (steps + 1);
        // Height of one step
//      float h = 1 / steps;

        if (a < w) /* If a is on the first platform */ {
            outputs[OUT_O_OUTPUT].setVoltage(-1);
            return;
        } else if (a > 1 - w)
            /* If a is on the platform after last platform */
            /* If a is on the platform with value 1 */ {
            outputs[OUT_O_OUTPUT].setVoltage(1);
            return;
        }

        float mRise = inputs[IN_SLOPE_RISE_INPUT].getVoltage();
        float mCrui = inputs[IN_SLOPE_CRUISE_INPUT].getVoltage();
        float dot = inputs[IN_DOT_INPUT].getVoltage();
        dot = clamp(dot, 0.f, 1.f);

        // Number of complete steps a has crossed
        // I believe the only range possible here is [0, 4]
        // In that range too, 0 is impossible because of the ifs above
        float comp = floorf(a * (steps + 1));

        if (mRise == 0 && mCrui == 0) {
            outputs[OUT_O_OUTPUT].setVoltage(comp / steps * 2 - 1);
            return;
        }

        // In the step where it lies on, how much away is it from the next step ona scale of [0, 1]
        // or Had the width of one step been 1, where does a lye on it with respect to that step.
        float devi = a * (steps + 1) - comp;

        // Currently, the pair (mCrui, mRise) represent to point of deflex from top left corner.
        // Converting it to represent the point from bottom left (ie aka first quadrant)
        mRise = 1 - mRise;

        float o;

        if (devi < mCrui) /* That is, we are in a Rise */ {
            o = devi * mRise / mCrui;
        } else /* That is, we are in a Cruise */ {
            // With respect to the upper right triangle
            //   devi - mCrui       o - mRise
            //  --------------  =  -----------
            //     1 - mCrui        1 - mRise
            o = (devi - mCrui) * (1 - mRise) / (1 - mCrui) + mRise;
        }

        o = (o + comp - 1) / steps;
        o = (o + (a - 0.5f) * dot) / (1 + dot);

        outputs[OUT_O_OUTPUT].setVoltage(o * 2 - 1);

    }
};


struct MCXIV_StepsWidget : ModuleWidget {
    MCXIV_StepsWidget(MCXIV_Steps *module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Steps.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 11.662)), module, MCXIV_Steps::IN_A_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 30.243)), module, MCXIV_Steps::IN_STEPS_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 48.824)), module, MCXIV_Steps::IN_SLOPE_RISE_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 67.405)), module, MCXIV_Steps::IN_SLOPE_CRUISE_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 85.985)), module, MCXIV_Steps::IN_DOT_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 104.566)), module, MCXIV_Steps::OUT_O_OUTPUT));
    }
};


Model *modelMCXIV_Steps = createModel<MCXIV_Steps, MCXIV_StepsWidget>("MCXIV_Steps");