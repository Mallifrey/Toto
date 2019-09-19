#include "window.h"
#include "../other/globaldata.h"
#include "font_manager.h"
#include "../audio/sound_manager.h"

namespace toto {namespace graphics {

	bool Window::m_Keys[MAX_KEYS];
	bool Window::m_KeyState[MAX_KEYS];
	bool Window::m_KeyTyped[MAX_KEYS];
	bool Window::m_MouseButtons[MAX_BUTTONS];
	bool Window::m_MouseState[MAX_BUTTONS];
	bool Window::m_MouseClicked[MAX_BUTTONS];
	double Window::mx;
	double Window::my;

	Window::Window(const char *title, int width, int height){
		m_Title = title;
		m_Width = width;
		m_Height = height;
		if (!init()){
			glfwTerminate();
		}

		FontManager::add(new Font("SourceSansPro", "src/default/SourceSansPro-Regular.ttf", 32));
		audio::SoundManager::init();

		for (int i = 0; i < MAX_KEYS; i++) {
			m_Keys[i] = false;
			m_KeyState[i] = false;
			m_KeyTyped[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++) {
			m_MouseButtons[i] = false;
			m_MouseState[i] = false;
			m_MouseClicked[i] = false;
		}
	}

	Window::~Window(){
		FontManager::clean();
		audio::SoundManager::clean();
		glfwTerminate();
	}

	bool Window::init() {
		if (!glfwInit()){
			std::cout << "Failed to initialize GLFW!" << std::endl;
			return false;
		}

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window) {
			std::cout << "Failed to create GLFW window!" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		//glfwSetWindowSizeCallback(m_Window, window_resize);
		glfwSetFramebufferSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSwapInterval(VSYNC); //VSYNC

		if (glewInit() != GLEW_OK){
			std::cout << "Could not initialize GLEW!" << std::endl;
			return false;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

		return true;
	}

	bool Window::isKeyDown(unsigned int keycode){
		if (keycode >= MAX_KEYS)
			return false;
		return m_Keys[keycode];
	}
	
	bool Window::isKeyTyped(unsigned int keycode){
		if (keycode >= MAX_KEYS)
			return false;
		return m_KeyTyped[keycode];
	}


	bool Window::isMouseButtonDown(unsigned int button){
		if (button >= MAX_BUTTONS)
			return false;
		return m_MouseButtons[button];
	}

	bool Window::isMouseButtonClicked(unsigned int button){
		if (button >= MAX_BUTTONS)
			return false;
		return m_MouseClicked[button];
	}

	void Window::getMousePosition(double& x, double& y) {
		x = mx;
		y = my;
	}

	bool Window::testCursor(float x, float y){
		return x<y?true:false;
	}

	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update() {

		for (int i = 0; i < MAX_KEYS; i++)
			m_KeyTyped[i] = m_Keys[i] && ! m_KeyState[i];

		for (int i = 0; i < MAX_BUTTONS; i++)
			m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];

		memcpy(m_KeyState, m_Keys, MAX_KEYS);
		memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS);
		
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::cout << "OpenGL Error: " << error << std::endl;
		}

		glfwPollEvents();
		//glfwGetWindowSize(m_Window, &m_Width, &m_Height); //navic
		glfwSwapBuffers(m_Window);
		audio::SoundManager::update();
	}

	bool Window::closed() const {
		return glfwWindowShouldClose(m_Window) == 1;
	}

	void window_resize(GLFWwindow* m_Window, int width, int height)
	{
		glViewport(0, 0, width, height);
		Window* win = (Window*)glfwGetWindowUserPointer(m_Window);
		win->m_Width = width;
		win->m_Height = height;
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window* win = (Window*) glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->mx = xpos;
		win->my = ypos;
	}
}}