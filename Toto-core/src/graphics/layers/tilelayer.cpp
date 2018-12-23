#include "tilelayer.h"
#include "../../other/globaldata.h"

namespace toto {
	namespace graphics {

		TileLayer::TileLayer(Shader* shader)
			: Layer(new BatchRenderer2D(), shader, maths::mat4::orthographic(LEFTB, RIGHTB, BOTTOMB, TOPB, NEARB, FARB)) {

		}

		TileLayer::~TileLayer() {

		}

	}
}