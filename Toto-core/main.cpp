#include <time.h>

#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"
#include "src/utils/timer.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"

#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/layers/group.h"

#include "src/other/globaldata.h"

#include "src/graphics/texture.h"

#include "src/graphics/label.h"

#if 1
int main()
{

#define TEST_50K_SPRITES 0

	using namespace toto;
	using namespace graphics;
	using namespace maths;

	Window window("Toto!", 920, 560);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

#if SHADER_COMPILED
	Shader* s = new Shader("basic.vert", "basic.frag");
#else
	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
#endif

	Shader& shader = *s; /*
	shader.enable();
	shader.setUniform2f("light_pos", vec2(0, 0));
	*/
	TileLayer layer(&shader);
	
	Texture* textures[] = {
		new Texture("img/test.png"),
		new Texture("img/test2.png"),
		new Texture("img/test3.png")
	};

	srand(time(NULL));
	

#if TEST_50K_SPRITES
	for (float x = LEFTB; x < RIGHTB; x += 0.1f){
		for (float y = BOTTOMB; y < TOPB; y += 0.1f){
			layer.add(new Sprite(x, y, 0.1f, 0.1f/*0.067f, 0.067f*/, maths::vec4(rand() % 1000 / 1000.0f, 0, 0.5f, 1)));
		}
	}
#else
	for (int x = LEFTB; x < RIGHTB; x++){
		for (int y = BOTTOMB; y < TOPB; y++){
			//layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4(rand() % 1000 / 1000.0f, 0, 0.5f, 1)));
			//layer.add(new Sprite(x, y, 1.0f, 1.0f, vec4(1, 1, 1, 1)));
			layer.add(new Sprite(x, y, 1.0f, 1.0f, textures[rand() % 3]));
		}
	}
#endif



	Group* g = new Group(maths::mat4::translation(maths::vec3(-15.5f, 7.0f, 0.0f)));
	Label* fps = new Label("", 0.4, 0.4f, maths::vec4(0.8f, 0.8f, 0.8f, 1.0f));

	g->add(new Sprite(0, 0, 5, 1.5f, maths::vec4(0.2f, 0.2f, 0.2f, 0.8f)));
	g->add(fps);

	layer.add(g);


	GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

	shader.enable();
	shader.setUniform1iv("textures", 32, texIDs);
	shader.setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));


	Timer time;
	float t = 0;
	unsigned int frames = 0;

	while (!window.closed()){

		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		shader.enable();
		shader.setUniform2f("light_pos", vec2((float)(x * WIDTH / window.m_Width - WIDTH / 2), (float)(HEIGHT / 2 - y * HEIGHT / window.m_Height)));

		layer.render();

		window.update();
		
		frames++;
		if (time.elapsed() - t > 1.0f) {
			t += 1.0f;
			fps->text = std::to_string(frames) + "fps";
			printf("%d ftp\n", frames);
			frames = 0;
		}
		
	}

	/*
	for (int i = 0; i < 3; i++){
		delete textures[i];
	}

	*/
	//system("PAUSE");
	return 0;
}
#endif

#if 0
int main() {

	const char* filename = "test.png";


	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return false;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		return false;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	unsigned int bitsPerPixel = FreeImage_GetBPP(dib);
	unsigned int pitch = FreeImage_GetPitch(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return false;


	for (int y = 0; y < height; y++){
		BYTE *pixel = (BYTE*)bits;;
		for (int x = 0; x < width; x++){
			std::cout << +pixel[FI_RGBA_RED] << " " << +pixel[FI_RGBA_GREEN] << " " << +pixel[FI_RGBA_BLUE] << std::endl;
			pixel += 4;
		}
		bits += pitch;
	}


	FreeImage_Unload(dib);



	system("PAUSE");

	return 0;

}
#endif

#if 0
int main() {

	using namespace toto;
	using namespace graphics;
	using namespace maths;

	Window window("Toto!", 920, 560);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	TileLayer layer(&shader);

	layer.add(new Sprite(-0.75f, -0.75f, 1.5f, 1.5f, vec4(1, 1, 1, 1)));
	layer.add(new Sprite(LEFTB+1.0f, BOTTOMB+1.0f, 1.0f, 5.0f, vec4(1, 1, 1, 1)));
	//layer.add(new Sprite(-1.0f, -1.0f, 2.0f, 2.0f, vec4(1, 1, 1, 1)));

	while (!window.closed()){

		layer.render();

		window.update();
	}

	return 0;
}
#endif