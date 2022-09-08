#pragma once

#include "core/string.h"
#include "tmessage.h"
#include "types/methodbuilder.h"
#include "types/typemanager.h"
#include "utility/chelper.h"

#define OBJ_DEFINITION(NAME, INHERITS)                                        \
   public:                                                                    \
    bool is_type(const String& name) const override { return name == #NAME; } \
    void* get_type_ptr() const override {                                     \
        return NAME::get_type_ptr_static();                                   \
    }                                                                         \
    bool is_type_ptr(void* ptr) const override {                              \
        return ptr == get_type_ptr();                                         \
    }                                                                         \
    VariantType get_type() const override {                                   \
        return GETTYPE(StringName(#NAME));                                    \
    }                                                                         \
                                                                              \
    String get_type_path() const override {                                   \
        return INHERITS::get_type_path() + "/" + #NAME;                       \
    }                                                                         \
                                                                              \
    static void init_type() {                                                 \
        TypeManager::get_singleton()->add_object_type<NAME>();                \
    }                                                                         \
    StringName get_type_name() const override { return #NAME; }               \
    static StringName get_type_name_static() { return #NAME; }                \
    static String get_type_path_static() {                                    \
        return INHERITS::get_type_path_static() + "/" + #NAME;                \
    }                                                                         \
    static void* get_type_ptr_static() {                                      \
        static int ptr;                                                       \
        return &ptr;                                                          \
    }                                                                         \
    static bool is_type_static(void* ptr) {                                   \
        return ptr == get_type_ptr_static();                                  \
    }                                                                         \
                                                                              \
   private:

class VariantType;

class Object {
   public:
    Object() = default;
    virtual ~Object() = default;

    // Construct with a base pointer
    Object(Object* base);

    template <typename T>
    bool is_of_type() const {
        return T::get_type_ptr_static() == get_type_ptr();
    }

    template <typename T>
    bool derives_from_type() {
        return dynamic_cast<T>(this) != nullptr;
    }

    template <typename T>
    inline T cast_to_type() {
        if (derives_from_type<T>())
            return reinterpret_cast<T>(this);
        else
            return nullptr;
    }

    virtual StringName get_type_name() const;

    // virtual
    virtual String get_type_path() const;
    virtual bool is_type(const String& name) const;
    virtual void* get_type_ptr() const;
    virtual bool is_type_ptr(void* ptr) const;
    virtual VariantType get_type() const;

    // static
    static StringName get_type_name_static();
    static String get_type_path_static();
    static void* get_type_ptr_static();
    static bool is_type_static(void* ptr);
};
