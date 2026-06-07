#include "Utils.h"
#include <asp/iter.hpp>

using namespace geode::prelude;

arc::Future<bool> Utils::LevelHasLdm(std::string levelString) {
    co_return co_await async::runtime().spawnBlocking<bool>([levelString = std::move(levelString)] {
        auto decompressed = ZipUtils::decompressString(levelString, false, 0);
        if (decompressed.empty())
            return false;

        // For each object:
        // - If it's the level settings object, it'll check if the level has a LDM
        // - If it's just a regular object and it's marked as high detail, the level has a LDM
        for (auto object : asp::iter::split(decompressed, ';')) {
            if (object.empty()) continue;
            
            // Check if LDM is enabled in the level settings
            if (object == "kA29,1"
                || object.starts_with("kA29,1,")
                || object.ends_with(",kA29,1")
                || object.find(",kA29,1,") != std::string_view::npos)
            { return true; }
            
            // Check if the object is marked as high detail, meaning the level has a LDM
            if (object == "103,1"
                || object.starts_with("103,1,")
                || object.ends_with(",103,1")
                || object.find(",103,1,") != std::string_view::npos) 
            { return true; }
        }

        return false;
    });
};