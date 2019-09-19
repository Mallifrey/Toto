#include "label.h"

namespace toto { namespace graphics {

	Label::Label(std::string text, float x, float y, Font* font, unsigned int color)
		: Renderable2D(), text(text), position(m_Position), m_Font(font) {
		m_Position = maths::vec3(x, y, 0);
		m_Color = color;
		m_Type = 2;
	}

	Label::Label(std::string text, float x, float y, unsigned int color)
		: Renderable2D(), text(text), position(m_Position), m_Font(FontManager::get("SourceSansPro")) {
		m_Position = maths::vec3(x, y, 0);
		m_Color = color;
		m_Type = 2;
	}

	Label::Label(std::string text, float x, float y, const std::string& font, unsigned int color)
		: Renderable2D(), text(text), position(m_Position), m_Font(FontManager::get(font)) {
		m_Position = maths::vec3(x, y, 0);
		m_Color = color;
		m_Type = 2;
		validateFont(font);
	}

	Label::Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color)
		: Renderable2D(), text(text), position(m_Position), m_Font(FontManager::get(font, size)) {
		m_Position = maths::vec3(x, y, 0);
		m_Color = color;
		m_Type = 2;
		validateFont(font, size);
	}

	void Label::submit(Renderer2D* renderer) const {
		renderer->drawString(text, m_Position, *m_Font, m_Color);
	}

	void Label::validateFont(const std::string& name, int size) {

		if (m_Font != nullptr) {
			if (m_Font->getScale().x == 0) {
				std::cout << "[Font] Font '" << m_Font->getName() << "' does not have set scale!" << std::endl;
				m_Font->setScale(32, 32);
			}
			return;
		}
		std::cout << "[Font] Font '" << name;
		if (size > 0){
			std::cout << "' with size '" << size;
		}
		std::cout << "' is not exist!" << std::endl;

		m_Font = FontManager::get("SourceSansPro");
	}
}}