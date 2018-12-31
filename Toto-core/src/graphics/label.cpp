#include "label.h"

namespace toto { namespace graphics {

	Label::Label(std::string text, float x, float y, maths::vec4 color)
		: Renderable2D(), text(text), position(m_Position)
	{
		
		m_Position = maths::vec3(x, y, 0);
		m_Color = color;

	}

	void Label::submit(Renderer2D* renderer) const {
		renderer->drawString(text, m_Position, m_Color);
	}

}}