#include "texteditortab.h"

#include "dock.h"
#include "seperator.h"

TextEditorTab::TextEditorTab() : TextEditorTab("") {}

TextEditorTab::TextEditorTab(const File &p_file) {
    textbox = new TextBox;
    buttons = new Container;

    save_button = new IconButton("regular/save");
    save_button->connect("clicked", this, "savebutton_pressed");

    new_button = new IconButton("solid/plus");
    new_button->connect("clicked", this, "open_file");

    open_button = new IconButton("regular/folder-open");
    open_button->connect("clicked", this, "show_dialog");

    add_child(textbox);
    add_child(buttons);

    textbox->set_anchors(ANCHOR_BEGIN, ANCHOR_BEGIN, ANCHOR_END, ANCHOR_END);
    textbox->set_margins(4, 4, 4, 42);
    textbox->set_line_numbers_enabled(true);

    buttons->set_glue_vert(false);
    buttons->set_anchors(ANCHOR_BEGIN, ANCHOR_END, ANCHOR_END, ANCHOR_END);
    buttons->set_margins(4, 4 + 34, 4, 4);

    buttons->add_child(new_button);
    buttons->add_child(open_button);
    buttons->add_child(new Seperator);
    buttons->add_child(save_button);

    if (p_file.is_file()) open_file(p_file);

    textbox_area = rect2();

    textfile = nullptr;
    dialog = nullptr;
}

TextEditorTab::~TextEditorTab() {}

vec2 TextEditorTab::get_required_size() const { return vec2(200); }

void TextEditorTab::handle_event(UIEvent *ui_event) {}

void TextEditorTab::notification(int p_notification) {
    switch (p_notification) {
        case NOTIFICATION_DRAW:

            break;

        case NOTIFICATION_TRANSLATED:
        case NOTIFICATION_RESIZED:

            break;
    }
}

void TextEditorTab::show_dialog() {
    dialog = new FileDialog;
    dialog->connect("file_chosen", this, "open_file");

    dialog->show();
}

void TextEditorTab::open_file(const String &p_path) {
    textfile = CONTENT->LoadTextFile(p_path);

    textbox->set_text(textfile->get_source());

    String extension = File(p_path).get_extension();
    textbox->handle_extension(extension);

    set_tab_title(File(textfile->get_file()).get_name());
}

void TextEditorTab::savebutton_pressed() {
    if (textfile) textfile->write(textbox->get_text());
}

#undef CLASSNAME
#define CLASSNAME TextEditorTab

void TextEditorTab::bind_methods() {
    REG_CSTR(0);

    REG_METHOD(savebutton_pressed);
    REG_METHOD(open_file);
    REG_METHOD(show_dialog);
}

ShaderEditorTab::ShaderEditorTab() : ShaderEditorTab(NULL) {}

ShaderEditorTab::ShaderEditorTab(const File &p_file) {
    String s = p_file.operator String();
    s = s.substr(0, s.find_first('.'));
    shader = CONTENT->LoadShader(s);

    open_file(p_file);

    init();
}

ShaderEditorTab::ShaderEditorTab(Shader *p_shader) {
    shader = p_shader;

    if (shader) {
        open_file(String(shader->get_file()) + ".frag");
    }

    init();
}

ShaderEditorTab::~ShaderEditorTab() {}

void ShaderEditorTab::init() {
    compile_button = new IconButton("regular/save");
    compile_button->connect("clicked", this, "compile");
    buttons->add_child(compile_button);
}

void ShaderEditorTab::compile() {
    if (shader) shader->reload();
}

#undef CLASSNAME
#define CLASSNAME ShaderEditorTab

void ShaderEditorTab::bind_methods() {
    REG_CSTR(0);

    REG_METHOD(compile);
}
