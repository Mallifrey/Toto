#include "group.h"

namespace toto { namespace graphics {

	Group::Group(const maths::mat4& transform)
		: transformationMatrix(transform) {
		m_Type = 3;
	}

	Group::Group(const maths::mat4& transform, const maths::vec2 size)
		: transformationMatrix(transform) {
		m_Size = size;
		m_Type = 3;
	}

	Group::~Group() {
		for(int i = 0; i < m_Renderables.size(); i++) {
			delete m_Renderables[i];
		}
	}

	void Group::add(Renderable2D* renderable){
		m_Renderables.push_back(renderable);
		renderable->m_Enabled = true;
		renderable->m_Owner = this;
	}
	
	void Group::remove(Renderable2D* renderable){
		std::vector<Renderable2D*> newr;
		for (int i = 0; i < m_Renderables.size(); i++)
			if (renderable != m_Renderables[i])
				newr.push_back(m_Renderables[i]);
		m_Renderables = newr;
		/*
		for (int i = 0; i < newr.size(); i++) {
			delete newr[i];
		}
		*/
		renderable->m_Enabled = false;
	}

	void Group::submit(Renderer2D* renderer) const {
		renderer->push(transformationMatrix);
		for (const Renderable2D* renderable : m_Renderables) {
			renderable->submit(renderer);
		}
		renderer->pop();
	}

	void Group::enable(Renderable2D* renderable) {
		if (renderable->m_Enabled == false){
			this->add(renderable);
		}
	}

	void Group::disable(Renderable2D* renderable) {
		if (renderable->m_Enabled == true){
			this->remove(renderable);
		}
	}

	void Group::enable() {
		if (this->m_Enabled == false){
			m_Owner->add(this);
		}
	}

	void Group::disable() {
		if (this->m_Enabled == true){
			m_Owner->remove(this);
		}
	}


	/*
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
	*/
	

}}