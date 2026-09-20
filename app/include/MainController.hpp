//
// Created by matija on 20. 9. 2026..
//

#ifndef MATF_RG_PROJECT_MAINCONTROLLER_HPP
#define MATF_RG_PROJECT_MAINCONTROLLER_HPP
#include<engine/core/Controller.hpp>

namespace app {
    class MainController : public engine::core::Controller {
        void initialize() override;

        bool loop() override;

        void draw_japaneseTemple();

        void update_camera();

        void update() override;

        void begin_draw() override;

        void draw() override;

        void end_draw() override;

    public:
        std::string_view name() const override {
            return "app::MainController";
        }
    };
} // app

#endif //MATF_RG_PROJECT_MAINCONTROLLER_HPP
