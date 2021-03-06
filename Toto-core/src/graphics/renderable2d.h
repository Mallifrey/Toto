#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"

#include "renderer2d.h"
#include "texture.h"

#include "../maths/maths.h"
#include "shader.h"

namespace toto { namespace graphics {

	struct VertexData {
		maths::vec3 vertex;
		maths::vec2 uv;
		float tid;
		unsigned int color;
	};

	class Renderable2D{
	protected:
		friend class Group;
		maths::vec3 m_Position;
		maths::vec2 m_Size;
		unsigned int m_Color;
		std::vector<maths::vec2> m_UV;
		Texture* m_Texture;
		bool m_Enabled;
		unsigned int m_Type;
		Group* m_Owner;

	protected:
		Renderable2D() { setUVDefaults(); }
	public:
		Renderable2D(maths::vec3 position, maths::vec2 size, unsigned int color, unsigned int type) : m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr), m_Enabled(true), m_Type(type) { setUVDefaults(); }
		virtual ~Renderable2D() { }

		virtual void submit(Renderer2D* renderer) const{
			if(this->getStatus()==1)
				renderer->submit(this);
		}

		void setColor(unsigned int color) { m_Color = color; }
		void setColor(const maths::vec4& color ) {
			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;
			m_Color = a << 24 | b << 16 | g << 8 | r;
		}

		inline const maths::vec3& getPosition() const { return m_Position; }
		inline const maths::vec3& getOverallPosition() const{ return overallPosition(); };
		inline const maths::vec2& getSize() const { return m_Size; }
		inline const unsigned int& getColor() const { return m_Color; }
		inline const bool& getStatus() const { return m_Enabled; }
		inline const std::vector<maths::vec2>& getUV() const { return m_UV; }
		inline const unsigned int& getType() const { return m_Type; }

		void setPosition(maths::vec3& value) { m_Position = value; };
		void setSize(maths::vec2& value) { m_Size = value; }
		void enable() { m_Enabled = true; }
		void disable() { m_Enabled = false; }

		inline const GLuint GetTID() const { return m_Texture ? m_Texture->getID() : 0; }
	private:
		void setUVDefaults(){
			m_UV.push_back(maths::vec2(0, 0));
			m_UV.push_back(maths::vec2(0, 1));
			m_UV.push_back(maths::vec2(1, 1));
			m_UV.push_back(maths::vec2(1, 0));
		}
		maths::vec3 overallPosition() const{
			maths::vec3 pos = m_Position;
			//if (m_Owner != nullptr){
				//m_Owner->getStatus();
			//}
			//this->m_Owner->x;
			return pos;
		}
	};

}}