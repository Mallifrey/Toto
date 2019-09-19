
#include <time.h>

#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"

#include "src/utils/timer.h"
#include "src/utils/arrayutils.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"

#include "src/graphics/layers/group.h"

#include "src/other/globaldata.h"

#include "src/graphics/texture.h"

#include "src/graphics/label.h"
#include "src/graphics/font.h"
#include "src/graphics/font_manager.h"

#include "ext/gorilla-audio/ga.h"
#include "ext/gorilla-audio/gau.h"

#include "src/audio/sound.h"
#include "src/audio/sound_manager.h"

#include "src/toto.h"


//dvere
#if 0
int main()
{

	using namespace toto;
	using namespace graphics;
	using namespace maths;
	using namespace audio;


	Window window("Toto!", 920, 560);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");

	Shader& shader = *s;
	shader.enable();
	shader.setUniform2f("light_pos", vec2(0, 0));

	Layer layer = Layer(new BatchRenderer2D(), &shader, maths::mat4::orthographic(LEFTB, RIGHTB, BOTTOMB, TOPB, NEARB, FARB));

	Texture* textures[] = {
		new Texture("resources/img/test.png"),
		new Texture("resources/img/test2.png"),
		new Texture("resources/img/test3.png")
	};

	srand(time(NULL));

	for (int y = -3; y <= 3; y++){
		layer.add(new Sprite(2, y, 1.0f, 1.0f, textures[0]));
	}

	for (int y = -3; y <= 3; y++){
		layer.add(new Sprite(-2, y, 1.0f, 1.0f, textures[0]));
	}

	for (int x = -1; x <= 1; x++){
		layer.add(new Sprite(x, 3, 1.0f, 1.0f, textures[0]));
	}


	Group* door = new Group(maths::mat4::translation(vec3(0,0,0)));
	door->add(new Sprite(-1, -3, 3, 6, textures[1]));
	layer.add(door);

	FontManager::add(new Font("Blade", "resources/fonts/bladrmf.ttf", 32));

	Group* g = new Group(maths::mat4::translation(maths::vec3(-15.5f, 7.0f, 0.0f)));
	Group* f = new Group(maths::mat4::scale(maths::vec3(0.4f, 0.4f, 1.0f)));

	Label* fps = new Label("", 0.4, 0.4f, 0xffffffff); //hashColor(maths::vec4(0.8f, 0.8f, 0.8f, 1.0f))
	Sprite* fps_bg = new Sprite(0, 0, 5, 1.5f, hashColor(maths::vec4(0.2f, 0.2f, 0.2f, 0.8f)));

	f->add(fps);

	g->add(fps_bg);
	g->add(fps);

	layer.add(g);


	//SoundManager::add(new Sound("sound0", "resources/audio/Journey - Don t Stop Believin Audio.wav"));
	SoundManager::add(new Sound("sound0", "resources/audio/Glenn Leroi & Bbone6512 - SCP-173 song Ogg Vorbis.ogg"));
	SoundManager::add(new Sound("sound1", "resources/audio/David Bowie - Space Oddity.wav"));
	SoundManager::add(new Sound("sound2", "resources/audio/Refining.wav"));

	float gain = 0.5f;

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




	shader.enable();
	GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
	shader.setUniform1iv("textures", 32, texIDs);
	shader.setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -10.0f, 10.0f));

	Timer time, odraz;
	int t = 0;
	float tim = 0;
	unsigned int frames = 0;
	float elap = 0;

	float rot = 0.0f;

	vec2 mousePosition;
	double x, y;

	float c = 0;
	while (!window.closed()){
		elap = odraz.elapsed();
		odraz.reset();


		frames++;
		if (time.elapsed() - t > 1.0f) {
			t += 1;
			fps->text = std::to_string(frames) + "fps";
			printf("%d: %d fps\n", t, frames);
			frames = 0;
		}

		if (t != 0){
			tim += (2.0f * elap * M_PI) / 2.0f;
		}


		/*
		mat4 mat = mat4::rotation(t, vec3(0, 0, 1));
		mat = mat * mat4::translation(vec3());
		*/
		vec3 dp = vec3(-1, -3, 0); //door->getPosition();
		vec2 ds = vec2(3, 6); //door->getSize();

		mat4 mat;
		mat = mat4::translation(vec3(dp.x, dp.y + ds.y / 2.0f, 0));
		mat = mat * mat4::rotation(time.elapsed() * 15.0f, vec3(0, 1, 0));
		mat = mat * mat4::translation(vec3(-dp.x, -dp.y - ds.y / 2.0f, 0));

		//shader.setUniformMat4("ml_matrix", mat);
		door->transformationMatrix = mat;



		window.clear();

		window.getMousePosition(x, y);
		mousePosition = maths::vec2(x * WIDTH / window.getWidth() - WIDTH / 2, HEIGHT / 2 - y * HEIGHT / window.getHeight());

		shader.enable();
		shader.setUniform2f("light_pos", vec2(mousePosition.x, mousePosition.y));

		const std::vector<toto::graphics::Renderable2D*>& rs = layer.getRenderables();
		for (int i = 0; i < layer.size(); i++){
			float c = sin(tim) / 2 + 0.5f;
			rs[i]->setColor(maths::vec4(1, c / 2, c, 1));
		}

		layer.render();


		if (window.isKeyTyped(GLFW_KEY_P)) {
			SoundManager::get("sound0")->play();
		}

		if (window.isKeyTyped(GLFW_KEY_L)) {
			SoundManager::get("sound0")->loop();
		}

		if (window.isKeyTyped(GLFW_KEY_S)) {
			SoundManager::get("sound0")->stop();
		}

		if (window.isKeyTyped(GLFW_KEY_KP_0)) {
			SoundManager::get("sound0")->pause();
		}

		if (window.isKeyTyped(GLFW_KEY_KP_1)) {
			SoundManager::get("sound0")->resume();
		}


		if (window.isKeyPressed(GLFW_KEY_C)) std::cout << "pressed" << std::endl;
		if (window.isKeyTyped(GLFW_KEY_C)) std::cout << "typed" << std::endl;


		window.update();

	}

	for (int i = 0; i < 3; i++){
		delete textures[i];
	}


	//system("PAUSE");
	return 0;
}
#endif

//playground
#if 0
int main()
{

#define TEST_50K_SPRITES 0

	using namespace toto;
	using namespace graphics;
	using namespace maths;
	using namespace audio;


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

	Layer layer = Layer(new BatchRenderer2D, &shader, maths::mat4::orthographic(LEFTB, RIGHTB, BOTTOMB, TOPB, NEARB, FARB));

	Texture* textures[] = {
		new Texture("resources/img/test.png"),
		new Texture("resources/img/test2.png"),
		new Texture("resources/img/test3.png")
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

	FontManager::add(new Font("Blade", "resources/fonts/bladrmf.ttf", 32));

	Group* g = new Group(maths::mat4::translation(maths::vec3(-15.5f, 7.0f, 0.0f)));

	Label* fps = new Label("v", 0.4, 0.4f, "Blade", hashColor(maths::vec4(0.8f, 0.8f, 0.8f, 1.0f))); 
	Sprite* fps_bg = new Sprite(0, 0, 5, 1.5f, hashColor(maths::vec4(0.2f, 0.2f, 0.2f, 0.8f)));

	g->add(fps_bg);
	g->add(fps);

	layer.add(g);


	//SoundManager::add(new Sound("sound0", "resources/audio/Journey - Don t Stop Believin Audio.wav"));
	SoundManager::add(new Sound("sound0", "resources/audio/Glenn Leroi & Bbone6512 - SCP-173 song Ogg Vorbis.ogg"));
	SoundManager::add(new Sound("sound1", "resources/audio/David Bowie - Space Oddity.wav"));
	SoundManager::add(new Sound("sound2", "resources/audio/Refining.wav"));

	float gain = 0.5f;

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
	



	shader.enable();
	GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
	shader.setUniform1iv("textures", 32, texIDs);
	shader.setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	Timer time, odraz;
	int t = 0;
	float tim = 0;
	unsigned int frames = 0;
	float elap = 0;

	vec2 mousePosition;
	double x, y;

	float c = 0;
	while (!window.closed()){
		elap = odraz.elapsed();
		odraz.reset();


		frames++;
		if (time.elapsed() - t > 1.0f) {
			t += 1;
			fps->text = std::to_string(frames) + "fps";
			printf("%d: %d fps\n", t, frames);
			frames = 0;
		}
		
		if (t != 0){
			tim += (2.0f * elap * M_PI) / 2.0f;
		}


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

		//gainl->text = std::to_string(roundf(SoundManager::get("journey")->getGain() * 100) / 100);

		//std::cout << SoundManager::get("journey")->getGain() << std::endl;

		layer.render();



		if (window.isKeyTyped(GLFW_KEY_P)) {
			SoundManager::get("sound0")->play();
		}

		if (window.isKeyTyped(GLFW_KEY_L)) {
			SoundManager::get("sound0")->loop();
		}

		if (window.isKeyTyped(GLFW_KEY_S)) {
			SoundManager::get("sound0")->stop();
		}

		if (window.isKeyTyped(GLFW_KEY_KP_0)) {
			SoundManager::get("sound0")->pause();
		}

		if (window.isKeyTyped(GLFW_KEY_KP_1)) {
			SoundManager::get("sound0")->resume();
		}


		if (window.isKeyTyped(GLFW_KEY_DOWN)) {
			if (gain > 0.0f){
				gain -= 0.05f;
				SoundManager::get("sound0")->setGain(gain);
				std::cout << "Sound gain: " << gain * 100 << "%" << std::endl;
			}
		}

		if (window.isKeyTyped(GLFW_KEY_UP)) {
			if (gain < 1.0f){
				gain += 0.05f;
				SoundManager::get("sound0")->setGain(gain);
				std::cout << "Sound gain: " << gain * 100 << "%" << std::endl;
			}
		}
		
		


		window.update();

	}

	for (int i = 0; i < 3; i++){
		delete textures[i];
	}


	//system("PAUSE");
	return 0;
}
#endif

//testobrazky
#if 0
int main()
{

#define TEST_50K_SPRITES 0

	using namespace toto;
	using namespace graphics;
	using namespace maths;


	Window window("Toto!", 920, 560);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

#if SHADER_COMPILED
	Shader* s = new Shader("basic.vert", "basic.frag");
#else
	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
#endif

	Shader& shader = *s; /*
	shader.enable();
	shader.setUniform2f("light_pos", vec2(0, 0));
	*/

	Layer layer = Layer(new BatchRenderer2D, &shader, maths::mat4::orthographic(LEFTB, RIGHTB, BOTTOMB, TOPB, NEARB, FARB));
	


	Texture* textures[] = {
		new Texture("resources/img/test.png"),
		new Texture("resources/img/test2.png"),
		new Texture("resources/img/test3.png")
	};

	/*
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		//std::cout << "OpenGL Error: " << error << std::endl;
		std::printf("OpenGL Error: %d\n", error);
	}
	*/

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

			//layer.add(new Sprite(x, y, 1.0f, 1.0f, textures[rand() % 3]));
		}
	}
#endif

	
	/*
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

	
	*/


	Timer time, deltaTime;
	float t = 0;
	unsigned int frames = 0;
	float timeset;

	vec2 mousePosition;
	double x, y;

	//float& buttonX = button->x;

	float c = 0;
	while (!window.closed()){

		window.clear();

		/*
		window.getMousePosition(x, y);
		mousePosition = maths::vec2(x * WIDTH / window.getWidth() - WIDTH / 2, HEIGHT / 2 - y * HEIGHT / window.getHeight());

		shader.enable();
		shader.setUniform2f("light_pos", vec2(mousePosition.x, mousePosition.y));
		*/


		if (window.isKeyTyped(GLFW_KEY_W))
			std::cout << "Yos" << std::endl;

		if (window.isKeyTyped(GLFW_KEY_W))
			std::cout << "Chaos" << std::endl;

		if (window.isMouseButtonClicked(GLFW_MOUSE_BUTTON_1))
			std::cout << "1" << std::endl;

		if (window.isMouseButtonClicked(GLFW_MOUSE_BUTTON_1))
			std::cout << "2" << std::endl;

		/*
		timeset = deltaTime.elapsed();
		button_pozadi->setColor(maths::vec4(0, 0, 0.2f, 0.8));
		button_vnitrek->setColor(maths::vec4(0, 0, 0.8f, 1));
		button_text->setColor(maths::vec4(0, 0, 0.5f, 1));
		buttonX += timeset * 50.0f;
		rotate->setPosition(rotate->getPosition() + timeset * maths::vec3(4 * sin(c), 4 * sin(c + 90), 0));
		c += timeset;
		*/

		/*
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::cout << "OpenGL Error: " << error << std::endl;
		}
		*/

		layer.render();

		window.update();
		
		frames++;
		if (time.elapsed() - t > 1.0f) {
			t += 1.0f;
			//fps->text = std::to_string(frames) + "fps";
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

//obrazky
#if 0
int main() {

	const char* filename = "resources/img/non.png";


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
			//std::cout << +pixel[FI_RGBA_RED] << " " << +pixel[FI_RGBA_GREEN] << " " << +pixel[FI_RGBA_BLUE] << " " << +pixel[FI_RGBA_ALPHA] << std::endl;
			std::cout << +pixel[FI_RGBA_RED] << " " << +pixel[FI_RGBA_GREEN] << " " << +pixel[FI_RGBA_BLUE] << std::endl;
			pixel += bitsPerPixel / 8;
		}
		std::cout << std::endl;
		bits += pitch;
	}


	FreeImage_Unload(dib);



	system("PAUSE");

	return 0;

}
#endif

//audio
#if 0

static void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
{
	gc_int32* flag = (gc_int32*)(in_context);
	*flag = 1;
	ga_handle_destroy(in_handle);
}

int main()
{
	gau_Manager* mgr;
	ga_Mixer* mixer;
	ga_Sound* sound;
	ga_Handle* handle;
	gau_SampleSourceLoop* loopSrc = 0;
	gau_SampleSourceLoop** pLoopSrc = &loopSrc;
	gc_int32 loop = 0;
	gc_int32 quit = 0;

	ga_BufferedStream* stream;
	ga_StreamManager* s_mgr;
	ga_SampleSource* s_source;
	gc_int32 s_bufferSize;

	/* Initialize library + manager */
	gc_initialize(0);
	mgr = gau_manager_create();
	mixer = gau_manager_mixer(mgr);

	/* Create and play shared sound */
	if (!loop)
		pLoopSrc = 0;
	sound = gau_load_sound_file("resources/audio/Journey - Don t Stop Believin Audio.wav", "wav"); //Journey - Don t Stop Believin Audio.wav Refining.wav
	//sound = gau_load_sound_file("http://mallifrey.borec.cz/minecraft/stop_talking.wav", "wav");
	//s_source = new ga_SampleSource("http://icecast3.play.cz/evropa2-128.mp3");
	
	s_bufferSize = 128;
	//stream = ga_stream_create(s_mgr, s_source, s_bufferSize);
	
	
	handle = gau_create_handle_sound(mixer, sound, &setFlagAndDestroyOnFinish, &quit, pLoopSrc);
	ga_handle_play(handle);

	/* Bounded mix/queue/dispatch loop */
	while (!quit)
	{
		gau_manager_update(mgr);
		printf("%d / %d\n", ga_handle_tell(handle, GA_TELL_PARAM_CURRENT), ga_handle_tell(handle, GA_TELL_PARAM_TOTAL));
		gc_thread_sleep(1);
	}

	/* Clean up sound */
	ga_sound_release(sound);

	/* Clean up library + manager */
	gau_manager_destroy(mgr);
	gc_shutdown();

	return 0;
}
#endif
