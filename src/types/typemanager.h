#pragma once

#include "core/dictionary.h"
#include "core/string.h"
#include "core/variant/variant.h"

#define TYPEMAN TypeManager::get_singleton()
#define GETTYPE TYPEMAN->get_type
#define GETNAME TYPEMAN->get_name

class VariantType;

struct ObjectType {
    ObjectType() {}
    ObjectType(const ObjectType& p_objecttype) = default;

    StringName name = "";
    String path = "";
    void* ptr = nullptr;

    template <typename T>
    bool is_of_type() const {
        return ptr == T::get_type_ptr_static();
    }
};

typedef const ObjectType* ObjectTypeRef;

class TypeManager {
   public:
    TypeManager();
    ~TypeManager();

    template <typename T>
    void add_object_type() {
        ObjectType type;
        type.name = T::get_type_name_static();
        type.path = T::get_type_path_static();
        type.ptr = T::get_type_ptr_static();

        set_object_type(type);
    }

    void add_type(const StringName& name);

    VariantType get_type(const StringName& name);
    ObjectType get_object_type(const StringName& name);
    VariantType get_type(void* ptr);
    StringName get_name(void* ptr);

    bool type_exists(const StringName& name) const;

    // get singleton
    static TypeManager* get_singleton();
    static void init();

    Dictionary<StringName, VariantType> types;
    Dictionary<StringName, ObjectType> object_types;
    Dictionary<void*, StringName> names;

   private:
    void set_object_type(const ObjectType& p_object_type);
    static TypeManager* singleton;
};

// helper structs for returning the type name of a type

template <typename T>
inline String GetType() {
    return std::remove_pointer<T>::type::get_type_name_static();
}

#ifndef GET_TYPE
#define GET_TYPE
#define REGISTER_GETTYPE(X)             \
    template <>                         \
    inline String GetType<X>() {        \
        return String(#X);              \
    }                                   \
    template <>                         \
    inline String GetType<const X>() {  \
        return String(#X);              \
    }                                   \
    template <>                         \
    inline String GetType<const X&>() { \
        return String(#X);              \
    }                                   \
    template <>                         \
    inline String GetType<X&>() {       \
        return String(#X);              \
    }                                   \
    template <>                         \
    inline String GetType<X*>() {       \
        return String(#X);              \
    }

REGISTER_GETTYPE(bool)
REGISTER_GETTYPE(unsigned)
REGISTER_GETTYPE(int)
REGISTER_GETTYPE(float)
REGISTER_GETTYPE(double)
REGISTER_GETTYPE(String)
REGISTER_GETTYPE(Transform)
REGISTER_GETTYPE(Array<Variant>)
REGISTER_GETTYPE(vec2)
REGISTER_GETTYPE(vec3)
REGISTER_GETTYPE(vec4)
REGISTER_GETTYPE(mat4)
REGISTER_GETTYPE(Color)
#endif
