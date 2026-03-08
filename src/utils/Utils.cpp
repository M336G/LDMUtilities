#include "Utils.h"
#include <asp/iter.hpp>

using namespace geode::prelude;

arc::Future<bool> Utils::LevelHasLdm(std::string levelString) {
    co_return co_await async::runtime().spawnBlocking<bool>([levelString = std::move(levelString)] {
        auto decompressed = ZipUtils::decompressString(levelString, false, 0);

        for (auto object : asp::iter::split(decompressed, ';')) {
            if (object.find(",103,1,") != std::string::npos || object.ends_with(",103,1"))
                return true;
        }

        return false;
    });
};