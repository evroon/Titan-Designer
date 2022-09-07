#pragma once

#include "button.h"

class Toggle : public Button
{
	OBJ_DEFINITION(Toggle, Button);

public:
	Toggle();
	Toggle(const String& p_text);
	Toggle(Ref<Texture2D> p_tex);
	virtual ~Toggle();

	void handle_event(UIEvent* p_event) override;
	void notification(int p_notification) override;
	vec2 get_required_size() const override;

	static void bind_methods();

private:
	Ref<Texture2D> tex;
	String text;

	bool selected;
};

class ToggleStrip : public Control
{
	OBJ_DEFINITION(ToggleStrip, Control);

public:
	ToggleStrip();
	virtual ~ToggleStrip();

	struct Toggle
	{
		Ref<Texture2D> tex = nullptr;
		String text = "";
		String tip = "";
		rect2 area = rect2();
	};

	void handle_event(UIEvent* p_event) override;
	void notification(int p_notification) override;
	vec2 get_required_size() const override;

	void add_child(const String& p_tip, Ref<Texture2D> p_tex);

	static void bind_methods();

private:
	Array<Toggle> toggles;

	float left_margin;
	float margin;
	int selected;
};