#pragma once

#include "../renderable2d.h"
#include "../../maths/maths.h"

namespace toto { namespace graphics {

	class Group : public Renderable2D {
	private:
		std::vector<Renderable2D*> m_Renderables;
	public:
		maths::mat4 transformationMatrix;
		float& x = transformationMatrix.elements[12];
		float& y = transformationMatrix.elements[13];
		float& z = transformationMatrix.elements[14];
		Group(const maths::mat4& transform);
		Group(const maths::mat4& transform, const maths::vec2 size);
		~Group();

		void add(Renderable2D* renderable);
		void remove(Renderable2D* renderable);
		void submit(Renderer2D* renderer) const override;

		void enable(Renderable2D* renderable);
		void disable(Renderable2D* renderable);
		void enable();
		void disable();
		bool const getStatus() const { return this->m_Enabled; };


		//bool testCursor(maths::vec2 cursor);
	};

}}