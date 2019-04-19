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
#include "src/graphics/font.h"
#include "src/graphics/font_manager.h"

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

	Shader& shader = *s; 
	shader.enable();
	shader.setUniform2f("light_pos", vec2(0, 0));
						 
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
			layer.add(new Sprite(x, y, 0.1f, 0.1f/*0.067f, 0.067f*/, hashColor(maths::vec4(rand() % 1000 / 1000.0f, 0, 0.5f, 1))));
		}
	}
#else
	for (int x = LEFTB; x < RIGHTB; x++){
		for (int y = BOTTOMB; y < TOPB; y++){
			layer.add(new Sprite(x, y, 1.0f, 1.0f, textures[rand() % 3]));
		}
	}
#endif

	FontManager::add(new Font("Blade", "fonts/bladrmf.ttf", 32));

	Group* g = new Group(maths::mat4::translation(maths::vec3(-15.5f, 7.0f, 0.0f)));
	Group* f = new Group(maths::mat4::scale(maths::vec3(0.4f, 0.4f, 1.0f)));

	Label* fps = new Label("", 0.4, 0.4f, 0xffffffff); //hashColor(maths::vec4(0.8f, 0.8f, 0.8f, 1.0f))
	Sprite* fps_bg = new Sprite(0, 0, 5, 1.5f, hashColor(maths::vec4(0.2f, 0.2f, 0.2f, 0.8f)));

	f->add(fps);

	g->add(fps_bg);
	g->add(fps);

	layer.add(g);

	/*
	Group* button = new Group(maths::mat4::translation(maths::vec3(-15.5f, -8.5f, 0.0f)), maths::vec2(4, 1.5f));
	Sprite* button_pozadi = new Sprite(0, 0, 4, 1.5f, hashColor(maths::vec4(0, 0.2f, 0, 0.8)));
	Sprite* button_vnitrek = new Sprite(0.125f, 0.125f, 3.75f, 1.25f, hashColor(maths::vec4(0, 0.8f, 0, 1)));
	Label* button_text = new Label("Text", 0.9f, 0.4f, hashColor(maths::vec4(0, 0.5f, 0, 1)));

	button->add(button_pozadi);
	button->add(button_vnitrek);
	button->add(button_text);

	layer.add(button);


	Sprite* rotate = new Sprite(-4, 0, 1, 1, hashColor(maths::vec4(1, 1, 1, 0.9f)));
	layer.add(rotate);

	layer.add(new Sprite(-5, -5, 1, 10, hashColor(maths::vec4(1, 0, 1, 1))));
	layer.add(new Sprite(5, -5, 1, 10, hashColor(vec4(1, 0, 1, 1))));
	*/


	GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

	shader.enable();
	shader.setUniform1iv("textures", 32, texIDs);
	shader.setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	Timer time, deltaTime;
	float t = 0;
	float tim = 0;
	unsigned int frames = 0;
	float timeset;

	vec2 mousePosition;
	double x, y;

	//float& buttonX = button->x;

	float c = 0;
	while (!window.closed()){
		tim += 0.001f;
		//std::cout << window.getWidth() << ", " << window.getHeight() << std::endl;

		window.clear();

		window.getMousePosition(x, y);
		mousePosition = maths::vec2(x * WIDTH / window.getWidth() - WIDTH / 2, HEIGHT / 2 - y * HEIGHT / window.getHeight());

		shader.enable();
		shader.setUniform2f("light_pos", vec2(mousePosition.x, mousePosition.y));

#if !TEST_50K_SPRITES
		const std::vector<toto::graphics::Renderable2D*>& rs = layer.getRenderables();
		for (int i = 0; i < layer.size(); i++){
			float c = sin(tim) / 2 + 0.5f;
			rs[i]->setColor(maths::vec4(1, c/2, c, 1));
		}
#endif

		layer.render();

		window.update();

		frames++;
		if (time.elapsed() - t > 1.0f) {
			t += 1.0f;
			fps->text = std::to_string(frames) + "fps";
			printf("%d ftp\n", frames);
			frames = 0;
		}

		deltaTime.reset();


	}

	for (int i = 0; i < 3; i++){
		delete textures[i];
	}


	//system("PAUSE");
	return 0;
}
#endif

#if 0
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
	Label* fps = new Label("", 0.4, 0.4f, hashColor(maths::vec4(0.8f, 0.8f, 0.8f, 1.0f)));

	g->add(new Sprite(0, 0, 5, 1.5f, hashColor(maths::vec4(0.2f, 0.2f, 0.2f, 0.8f))));
	g->add(fps);

	layer.add(g);




	Group* button = new Group(maths::mat4::translation(maths::vec3(-15.5f, -8.5f, 0.0f)), maths::vec2(4, 1.5f));
	Sprite* button_pozadi = new Sprite(0, 0, 4, 1.5f, hashColor(maths::vec4(0, 0.2f, 0, 0.8)));
	Sprite* button_vnitrek = new Sprite(0.125f, 0.125f, 3.75f, 1.25f, hashColor(maths::vec4(0, 0.8f, 0, 1)));
	Label* button_text = new Label("Text", 0.9f, 0.4f, hashColor(maths::vec4(0, 0.5f, 0, 1)));

	button->add(button_pozadi);
	button->add(button_vnitrek);
	button->add(button_text);

	layer.add(button);


	Sprite* rotate = new Sprite(-4, 0, 1, 1, hashColor(maths::vec4(1, 1, 1, 0.9f)));
	layer.add(rotate);

	layer.add(new Sprite(-5, -5, 1, 10, hashColor(maths::vec4(1, 0, 1, 1))));
	layer.add(new Sprite(5, -5, 1, 10, hashColor(vec4(1, 0, 1, 1))));

	


	GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

	shader.enable();
	shader.setUniform1iv("textures", 32, texIDs);
	shader.setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	

	Timer time, deltaTime;
	float t = 0;
	unsigned int frames = 0;
	float timeset;

	vec2 mousePosition;
	double x, y;

	float& buttonX = button->x;

	float c = 0;
	while (!window.closed()){
		std::cout << window.getWidth() << ", " << window.getHeight() << std::endl;

		window.clear();

		window.getMousePosition(x, y);
		mousePosition = maths::vec2(x * WIDTH / window.getWidth() - WIDTH / 2, HEIGHT / 2 - y * HEIGHT / window.getHeight());

		shader.enable();
		shader.setUniform2f("light_pos", vec2(mousePosition.x, mousePosition.y));


		if (window.isKeyTyped(GLFW_KEY_W))
			std::cout << "Yos" << std::endl;

		if (window.isKeyTyped(GLFW_KEY_W))
			std::cout << "Chaos" << std::endl;

		if (window.isMouseButtonClicked(GLFW_MOUSE_BUTTON_1))
			std::cout << "1" << std::endl;

		if (window.isMouseButtonClicked(GLFW_MOUSE_BUTTON_1))
			std::cout << "2" << std::endl;




		//if (button->testCursor(mousePosition)) {

		    timeset = deltaTime.elapsed();
			button_pozadi->setColor(maths::vec4(0, 0, 0.2f, 0.8));
			button_vnitrek->setColor(maths::vec4(0, 0, 0.8f, 1));
			button_text->setColor(maths::vec4(0, 0, 0.5f, 1));
			buttonX += timeset * 50.0f;
			rotate->setPosition(rotate->getPosition() + timeset * maths::vec3(4 * sin(c), 4 * sin(c + 90), 0));
			c += timeset;
	/*	} else {
			button_pozadi->setColor(maths::vec4(0, 0.2f, 0, 0.8));
			button_vnitrek->setColor(maths::vec4(0, 0.8f, 0, 1));
			button_text->setColor(maths::vec4(0, 0.5f, 0, 1));
		}
		
		*/

		layer.render();

		window.update();
		
		frames++;
		if (time.elapsed() - t > 1.0f) {
			t += 1.0f;
			fps->text = std::to_string(frames) + "fps";
			printf("%d ftp\n", frames);
			frames = 0;
		}

		deltaTime.reset();
		
		
	}

	for (int i = 0; i < 3; i++){
		delete textures[i];
	}

	
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

	layer.add(new Sprite(-0.75f, -0.75f, 1.5f, 1.5f, hashColor(maths::vec4(1, 1, 1, 1))));
	layer.add(new Sprite(LEFTB + 1.0f, BOTTOMB + 1.0f, 1.0f, 5.0f, hashColor(maths::vec4(1, 1, 1, 1))));
	//layer.add(new Sprite(-1.0f, -1.0f, 2.0f, 2.0f, vec4(1, 1, 1, 1)));

	while (!window.closed()){

		layer.render();

		window.update();
	}

	return 0;
}
#endif