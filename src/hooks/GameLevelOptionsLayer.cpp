#include <Geode/modify/GameLevelOptionsLayer.hpp>
#include "../managers/SettingsManager.h"
#include "../utils/Utils.h"

using namespace geode::prelude;

class $modify(GameLevelOptionsLayer) {
    void setupOptions() {
        GameLevelOptionsLayer::setupOptions();

        if (!SettingsManager::DisableLdmButton)
            return;

        auto* layer = m_mainLayer->getChildByType<CCLayer>(-1);
        if (!layer) return;

        auto* label = layer->getChildByType<CCLabelBMFont>(0);
        if (!label) return;
        auto* toggle = m_buttonMenu->getChildByType<CCMenuItemToggler>(0);
        if (!toggle) return;

        if (!SettingsManager::LegacyLdmCheck) {
            async::spawn(
                Utils::LevelHasLdm(m_level->m_levelString),
                [label = Ref<CCLabelBMFont>(label), toggle = Ref<CCMenuItemToggler>(toggle)](bool hasLdm) {
                    if (hasLdm)
                        return;

                    toggle->toggle(false);
                    toggle->setClickable(false);

                    label->setOpacity(0.5f * 255);
                    toggle->setCascadeOpacityEnabled(true);
                    toggle->setOpacity(0.5f * 255);
                }
            );
        } else {
            if (m_level->m_lowDetailMode)
                return;

            toggle->toggle(false);
            toggle->setClickable(false);

            label->setOpacity(0.5f * 255);
            toggle->setCascadeOpacityEnabled(true);
            toggle->setOpacity(0.5f * 255);
        }
    };
};