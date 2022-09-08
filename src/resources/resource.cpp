#include "resource.h"

#undef CLASSNAME
#define CLASSNAME Resource

void Resource::set_file(const String &p_file) {
    file = File(p_file);

    file_loaded();
}

String Resource::get_file() const { return file.get_relative_path(); }

void Resource::bind_methods() { REG_PROPERTY(file); }
