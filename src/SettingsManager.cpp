#include "SettingsManager.h"

geode::Mod *SettingsManager::Mod = geode::Mod::get();

bool SettingsManager::AutoLdm = SettingsManager::Mod->getSettingValue<bool>("auto-ldm");
bool SettingsManager::DisableLdmButton = SettingsManager::Mod->getSettingValue<bool>("disable-ldm-button");

$execute {
    geode::listenForSettingChanges<bool>("auto-ldm", [](bool enabled) {
        SettingsManager::AutoLdm = enabled;
    });
    geode::listenForSettingChanges<bool>("disable-ldm-button", [](bool enabled) {
        SettingsManager::DisableLdmButton = enabled;
    });
};