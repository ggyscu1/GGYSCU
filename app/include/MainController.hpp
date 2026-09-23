//
// Created by matija on 20. 9. 2026..
//

#ifndef MATF_RG_PROJECT_MAINCONTROLLER_HPP
#define MATF_RG_PROJECT_MAINCONTROLLER_HPP
#include <engine/core/Controller.hpp>

namespace app {
class MainController : public engine::core::Controller {
    void initialize() override;

    bool loop() override;

    void draw_japanese_temple();

    void update_camera();

    void update() override;

    void begin_draw() override;

    //void draw_skybox();

    void draw() override;

    void end_draw() override;

    bool m_event_started = false;
    bool m_event_a_done = false;
    bool m_event_b_done = false;
    float m_event_timer = 0.0f;

public:
    std::string_view name() const override {
        return "app::MainController";
    }
};
}// namespace app

#endif//MATF_RG_PROJECT_MAINCONTROLLER_HPP
