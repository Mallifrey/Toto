#include "sprite.h"

namespace toto { namespace graphics {

	Sprite::Sprite(float x, float  y, float width, float height, unsigned int color)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), color, 0), position(m_Position)
	{

	}

	Sprite::Sprite(float x, float  y, float width, float height, Texture* texture)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), 0xffffffff, 0), position(m_Position)
	{
		m_Texture = texture;
	}

}}