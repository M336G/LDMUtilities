#include <Geode/modify/PlayLayer.hpp>
#include "../managers/SettingsManager.h"

class $modify(PlayLayer) {
    struct Fields {
        bool m_previousLdmToggle;
        bool m_modifiedLdm = false;
    };

    bool init(GJGameLevel *level, bool useReplay, bool dontCreateObjects) {
        if (SettingsManager::AutoLdm && level->m_lowDetailMode) {
            m_fields->m_previousLdmToggle = level->m_lowDetailModeToggled;
            
            if (!level->m_lowDetailModeToggled)
                level->m_lowDetailModeToggled = true;

            m_fields->m_modifiedLdm = true;
        }

        return PlayLayer::init(level, useReplay, dontCreateObjects);
    };

    void onQuit() {
        if (SettingsManager::AutoLdm && m_fields->m_modifiedLdm)
            m_level->m_lowDetailModeToggled = m_fields->m_previousLdmToggle;

        PlayLayer::onQuit();
    };
};