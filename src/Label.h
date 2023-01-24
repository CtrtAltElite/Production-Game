#pragma once
#ifndef __LABEL__
#define __LABEL__

#include <string>

#include "UIControl.h"
#include "FontManager.h"

class Label final : public UIControl
{
public:
	explicit Label(const std::string& text = "Default Label Text", const std::string& font_name = "lazy", int size = 20, SDL_Color colour = {0, 0, 0, 255}, b2Vec2 position = b2Vec2(), int font_style = TTF_STYLE_NORMAL, bool is_centered = true);
	~Label() override;

	// Inherited via GameObject
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	void InitRigidBody(b2Vec2 position);

	void SetText(const std::string& new_text);
	void SetColour(SDL_Color new_colour) const;
	void SetSize(int new_size);

private:
	std::string m_fontPath;
	std::string m_fontID;
	SDL_Color m_fontColour;
	std::string m_fontName;
	std::string m_text;
	bool m_isCentered = true;
	int m_fontSize;
	int m_fontStyle;
	b2Body* m_rigidBody;

	void BuildFontID();
};

#endif /* defined (__LABEL__) */