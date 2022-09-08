#pragma once

#include "core/application.h"
#include "input/event.h"
#include "scene.h"

class GameApp : public Application {
    OBJ_DEFINITION(GameApp, Application);

   public:
    GameApp(Platform *p_platform);

    void init() override;
    void update() override;

    void draw() override;

    void resize(const vec2i &p_size) override;

    void start_scene(Scene *s);
    void handle_event(Event *e);

   private:
    Scene *activescene;
};
