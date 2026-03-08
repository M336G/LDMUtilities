#include "SettingsManager.h"

using namespace geode::prelude;

bool SettingsManager::AutoLdm = Mod::get()->getSettingValue<bool>("auto-ldm");
bool SettingsManager::DisableLdmButton = Mod::get()->getSettingValue<bool>("disable-ldm-button");
bool SettingsManager::LegacyLdmCheck = Mod::get()->getSettingValue<bool>("legacy-ldm-check");

$execute {
    listenForSettingChanges<bool>("auto-ldm", [](bool enabled) {
        SettingsManager::AutoLdm = enabled;
    });
    listenForSettingChanges<bool>("disable-ldm-button", [](bool enabled) {
        SettingsManager::DisableLdmButton = enabled;
    });
    listenForSettingChanges<bool>("legacy-ldm-check", [](bool enabled) {
        SettingsManager::LegacyLdmCheck = enabled;
    });
};