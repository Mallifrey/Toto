#include "group.h"

namespace toto { namespace graphics {

	Group::Group(const maths::mat4& transform)
		: transformationMatrix(transform) {}

	Group::Group(const maths::mat4& transform, const maths::vec2 size)
		: transformationMatrix(transform), size(size){}

	Group::~Group() {
		for(int i = 0; i < m_Renderables.size(); i++) {
			delete m_Renderables[i];
		}
	}

	void Group::add(Renderable2D* renderable){
		m_Renderables.push_back(renderable);
	}

	void Group::submit(Renderer2D* renderer) const {
		renderer->push(transformationMatrix);
		for (const Renderable2D* renderable : m_Renderables) {
			renderable->submit(renderer);
		}
		renderer->pop();
	}
	
	bool Group::testCursor(maths::vec2 cursor) {
		float cx = cursor.x, cy = cursor.y;
		float buttonX = transformationMatrix.elements[12];
		float buttonY = transformationMatrix.elements[13];

		if (buttonX < cx && cx < buttonX + size.x && buttonY < cy && cy < buttonY + size.y) {
			return true;
		}
		else {
			return false;
		}
	}
	

}}