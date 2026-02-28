#include <Geode/modify/PlayLayer.hpp>
#include "../SettingsManager.h"

class $modify(PlayLayer) {
    struct Fields {
        bool m_previousLdmToggle;
    };

    bool init(GJGameLevel *level, bool useReplay, bool dontCreateObjects) {
        if (level->m_lowDetailMode && SettingsManager::AutoLdm) {
            m_fields->m_previousLdmToggle = level->m_lowDetailModeToggled;

            if (!level->m_lowDetailModeToggled)
                level->m_lowDetailModeToggled = true;
        }

        return PlayLayer::init(level, useReplay, dontCreateObjects);
    };

    void onQuit() {
        if (m_level->m_lowDetailMode && SettingsManager::AutoLdm)
            m_level->m_lowDetailModeToggled = m_fields->m_previousLdmToggle;

        PlayLayer::onQuit();
    };
};