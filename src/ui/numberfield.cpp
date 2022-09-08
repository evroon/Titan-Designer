#include "numberfield.h"

#include "canvas.h"

NumberField::NumberField(const Real &number)
    : EditableLabel(number.to_string()) {}

NumberField::NumberField() : NumberField(0.0f) {}

NumberField::~NumberField() {}

vec2 NumberField::get_required_size() const {
    return EditableLabel::get_required_size() + vec2(0, 8);
}

void NumberField::notification(int p_notification) {
    switch (p_notification) {
        case NOTIFICATION_READY:
        case NOTIFICATION_RESIZED:
        case NOTIFICATION_TRANSLATED:

            update_value();

            break;

        case NOTIFICATION_DRAW:

            draw_frame(area, Color::DarkGrey);

            EditableLabel::notification(NOTIFICATION_DRAW);

            if (get_focused())
                draw_frame(CanvasData::get_singleton()
                               ->get_default_theme()
                               ->get_highlight(),
                           area, Color::Green);

            break;
    }
}

void NumberField::handle_input(char c) { insert_at_selection(c); }

void NumberField::set_text(const String &p_text) {
    text = p_text;
    value_set(Real(p_text));

    emit_signal("value_changed", Real(p_text));
    update();
}

void NumberField::value_changed() {
    Variant v = get_value();

    set_text(v.ToString());
}

#undef CLASSNAME
#define CLASSNAME NumberField

void NumberField::bind_methods() {
    REG_CSTR(0);
    REG_CSTR_OVRLD_1(int);
    REG_CSTR_OVRLD_1(float);
}
