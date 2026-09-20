//
// Created by matija on 20. 9. 2026..
//

#include "../include/MainController.hpp"

#include "engine/core/Controller.hpp"
#include "engine/platform/Input.hpp"
#include<MainController.hpp>
#include<spdlog/spdlog.h>

#include "GUIControler.hpp"
#include "../../engine/test/app/include/app/GUIController.hpp"
#include "engine/graphics/GraphicsController.hpp"
#include "engine/graphics/OpenGL.hpp"
#include "engine/platform/PlatformController.hpp"
#include "engine/resources/ResourcesController.hpp"

namespace app {
    class MainPlatformEventObserver : public engine::platform::PlatformEventObserver {
    public:
        void on_mouse_move(engine::platform::MousePosition position) override;
    };

    void MainPlatformEventObserver::on_mouse_move(engine::platform::MousePosition position) {
        auto gui_controller = engine::core::Controller::get<GUIController>();
        if (!gui_controller->is_enabled()) {
            auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
            camera->rotate_camera(position.dx, position.dy);
        }
    }

    void MainController::initialize() {
        spdlog::info("Maincontrolor initialized");
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        platform->register_platform_event_observer(std::make_unique<MainPlatformEventObserver>());
        engine::graphics::OpenGL::enable_depth_testing();
    }

    bool MainController::loop() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        if (platform->key(engine::platform::KeyId::KEY_ESCAPE).is_down()) {
            return false;
        }
        return true;
    }

    void MainController::draw_japaneseTemple() {
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        resources->model("temple");
        engine::resources::Model *temple = resources->model("temple");

        engine::resources::Shader *shader = resources->shader("basic");

        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 1.0f, -3.0f));
        model = glm::scale(model, glm::vec3(0.3f));
        shader->set_mat4("model", model);
        shader->set_vec3("viewPos", graphics->camera()->Position);
        shader->set_vec3("dirLightDirection", glm::vec3(-0.5f, -1.0f, -0.3f));
        glm::vec3 dirLightColor(1.0f, 1.0f, 1.0f);
        if (event_b_done) {
            dirLightColor = glm::vec3(1.0f, 0.2f, 0.2f);
        }
        shader->set_vec3("dirLightColor", dirLightColor);
        shader->set_vec3("pointLightPosition", glm::vec3(2.0f, 4.0f, 1.0f));
        glm::vec3 pointLightColor(1.0f, 0.8f, 0.6f);
        if (event_a_done) {
            pointLightColor = glm::vec3(0.2f, 0.5f, 1.0f);
        }
        shader->set_vec3("pointLightColor", pointLightColor);

        temple->draw(shader);
    }

    void MainController::update_camera() {
        auto gui_controller = engine::core::Controller::get<GUIController>();
        if (gui_controller->is_enabled()) {
            return;
        }
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto camera = graphics->camera();
        float dt = platform->dt();

        if (platform->key(engine::platform::KeyId::KEY_W).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt);
        }
        if (platform->key(engine::platform::KeyId::KEY_S).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt);
        }
        if (platform->key(engine::platform::KeyId::KEY_A).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt);
        }
        if (platform->key(engine::platform::KeyId::KEY_D).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt);
        }
    }

    void MainController::update() {
        update_camera();

        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();

        if (!event_started && platform->key(engine::platform::KeyId::KEY_E).is_down()) {
            event_started = true;
            event_timer = 0.0f;
        }

        if (event_started) {
            event_timer += platform->dt();
            if (!event_a_done && event_timer >= 2.0f) {
                event_a_done = true;
            }
            if (!event_b_done && event_timer >= 5.0f) {
                event_b_done = true;
            }
        }
    }

    void MainController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();
    }

    //void MainController::draw_skybox() {
    //}

    void MainController::draw() {
        draw_japaneseTemple();
        //draw_skybox();
    }

    void MainController::end_draw() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        platform->swap_buffers();
    }
} // app
