#include "toggle.h"

//=========================================================================
// Toggle
//=========================================================================

Toggle::Toggle() : Toggle("") {}

Toggle::Toggle(const String& p_text) {
    text = p_text;
    tex = nullptr;
    selected = false;
}

Toggle::Toggle(Ref<Texture2D> p_tex) : Toggle("") { tex = p_tex; }

Toggle::~Toggle() {}

void Toggle::handle_event(UIEvent* p_event) {
    if (p_event->type == UIEvent::MOUSE_PRESS && p_event->press_type == UIEvent::DOWN) {
        if (area.is_in_box(p_event->pos)) {
            selected = !selected;
            emit_signal("toggled", selected);
            update();
            return;
        }
    }
}

#include "canvas.h"

void Toggle::notification(int p_notification) {
    Color color;
    switch (p_notification) {
        case NOTIFICATION_DRAW:

            if (selected) color = DEFAULT_THEME->get_selection_color();

            if (tex)
                draw_texture(tex, rect2(area.pos, tex->get_size() / 2.0f), color);
            else
                draw_text(text, vec2(area.get_left(), area.pos.y));

            break;

        case NOTIFICATION_TRANSLATED:
        case NOTIFICATION_RESIZED:

            update();
            break;
    }
}

vec2 Toggle::get_required_size() const {
    if (tex) return tex->get_size() + 4;

    return DEFAULT_THEME->get_font()->get_width(text);
}

#undef CLASSNAME
#define CLASSNAME Toggle

void Toggle::bind_methods() {
    REG_CSTR(0);

    REG_SIGNAL("toggled");
}

//=========================================================================
// ToggleStrip
//=========================================================================

ToggleStrip::ToggleStrip() {
    toggles = Array<Toggle>();

    selected = -1;
    margin = 4;
    left_margin = 4;
}

ToggleStrip::~ToggleStrip() {}

void ToggleStrip::handle_event(UIEvent* p_event) {
    if (p_event->type == UIEvent::MOUSE_PRESS && p_event->press_type == UIEvent::DOWN) {
        for (int c = 0; c < toggles.size(); c++) {
            if (toggles[c].area.is_in_box(p_event->pos)) {
                if (selected == c) return;

                selected = c;
                emit_signal("toggled", c);
                update();
                return;
            }
        }
    }
}

void ToggleStrip::notification(int p_notification) {
    float offset = left_margin + area.get_left();

    switch (p_notification) {
        case NOTIFICATION_DRAW:

            for (int c = 0; c < toggles.size(); c++) {
                Color color;

                if (c == selected) color = DEFAULT_THEME->get_selection_color();

                if (toggles[c].tex) {
                    vec2 tex_size = toggles[c].tex->get_size();

                    toggles[c].area =
                        rect2(offset, offset + tex_size.x, area.pos.y + tex_size.y / 2.0f,
                              area.pos.y - tex_size.y / 2.0f);

                    draw_texture(toggles[c].tex, toggles[c].area, color);
                    offset += tex_size.x;
                } else {
                    vec2 text_size = DEFAULT_THEME->get_font()->get_width(toggles[c].text);

                    toggles[c].area =
                        rect2(offset, offset + text_size.x, area.pos.y + text_size.y / 2.0f,
                              area.pos.y - text_size.y / 2.0f);

                    draw_text(toggles[c].text,
                              vec2(toggles[c].area.get_left(), toggles[c].area.pos.y));
                    offset += text_size.x;
                }
            }

            break;

        case NOTIFICATION_RESIZED:
        case NOTIFICATION_TRANSLATED:

            update();
            break;
    }
}

vec2 ToggleStrip::get_required_size() const {
    vec2 size;

    for (int c = 0; c < toggles.size(); c++) {
        if (toggles[c].tex) {
            if (toggles[c].tex->get_size().y > size.y) size.y = toggles[c].tex->get_size().y;

            size.x += toggles[c].tex->get_size().x;
            size.x += margin;
        } else {
            size.x += DEFAULT_THEME->get_font()->get_width(toggles[c].text);
            size.x += margin;
        }
    }
    return size;
}

void ToggleStrip::add_child(const String& p_tip, Ref<Texture2D> p_tex) {
    Toggle t;
    t.tip = p_tip;
    t.tex = p_tex;
    toggles.push_back(t);
    update();
    // t.tex->bind(0);
    // t.tex->set_filter(Texture::BILINEAR_FILTER);
}

#undef CLASSNAME
#define CLASSNAME ToggleStrip

void ToggleStrip::bind_methods() {
    REG_CSTR(0);

    REG_SIGNAL("toggled");
}
