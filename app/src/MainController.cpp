//
// Created by matija on 20. 9. 2026..
//

#include "../include/MainController.hpp"

#include "engine/core/Controller.hpp"
#include "engine/platform/Input.hpp"
#include<MainController.hpp>
#include<spdlog/spdlog.h>

namespace app {
    void MainController::initialize() {
        spdlog::info("Maincontrolor initialized");
    }

    /* bool MainController::loop() {
         auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
         if (platform->key(engine::platform::KeyId::KEY_ESCAPE).is_down()) {
             return false;
         }
         return true;
     }*/
} // app
