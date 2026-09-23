//
// Created by matija on 20. 9. 2026..
//

#ifndef MATF_RG_PROJECT_GUICONTROLER_HPP
#define MATF_RG_PROJECT_GUICONTROLER_HPP
#include <engine/core/Controller.hpp>

namespace app {
class GUIController : public engine::core::Controller {
public:
    std::string_view name() const override {
        return "app: GUIController";
    }

private:
    void initialize() override;

    void poll_events() override;

    void draw() override;
};
}// namespace app

#endif//MATF_RG_PROJECT_GUICONTROLER_HPP
