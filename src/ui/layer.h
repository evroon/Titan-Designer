#pragma once

#include "core/object.h"
#include "core/vector.h"

class WorldObject;

class Layer : public Object {
    OBJ_DEFINITION(Layer, Object)

   public:
    Layer() {}
    Layer(int p_index) : Layer() {
        depth = p_index;
        name = "Untitled";
    }
    Layer(int p_index, const String &p_name) : Layer() {
        depth = p_index;
        name = p_name;
    }

    int depth;
    String name;

    void Bind(WorldObject *o);
    void UnBind(WorldObject *o);

    Vector<WorldObject> objects;

    static void bind_methods();
};
