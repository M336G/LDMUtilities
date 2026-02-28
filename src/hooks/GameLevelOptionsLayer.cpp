#include <Geode/modify/GameLevelOptionsLayer.hpp>
#include "../SettingsManager.h"

class $modify(GameLevelOptionsLayer) {
    void setupOptions() {
        GameLevelOptionsLayer::setupOptions();

        if (!m_level->m_lowDetailMode && SettingsManager::DisableLdmButton) {
            auto *layer = m_mainLayer->getChildByType<CCLayer>(-1);
            if (!layer) return;
            auto *menu = m_mainLayer->getChildByType<cocos2d::CCMenu>(-1);
            if (!menu) return;

            auto *label = layer->getChildByType<cocos2d::CCLabelBMFont>(0);
            if (!label) return;
            auto *toggle = menu->getChildByType<CCMenuItemToggler>(0);
            if (!toggle) return;

            toggle->toggle(false);
            toggle->setClickable(false);

            label->setOpacity(0.5f * 255);
            toggle->setCascadeOpacityEnabled(true);
            toggle->setOpacity(0.5f * 255);
        }
    };
};