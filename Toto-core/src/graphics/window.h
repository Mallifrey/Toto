#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace toto {namespace graphics {

#define MAX_KEYS	1024
#define MAX_BUTTONS	32

	class Window {
	private:
		const char *m_Title;
		int m_Width, m_Height;
		GLFWwindow *m_Window;
		bool m_Closed;

		static bool m_Keys[MAX_KEYS];
		static bool m_KeyState[MAX_KEYS];
		static bool m_KeyTyped[MAX_KEYS];
		static bool m_MouseButtons[MAX_BUTTONS];
		static bool m_MouseClicked[MAX_BUTTONS];
		static bool m_MouseState[MAX_BUTTONS];
		static double mx, my;
	public:
		Window(const char *title, int width, int height);
		~Window();
		void clear() const;
		void update();
		bool closed() const;

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }

		static bool isKeyDown(unsigned int keycode);
		static bool isKeyTyped(unsigned int keycode);
		static bool isMouseButtonDown(unsigned int button);
		static bool isMouseButtonClicked(unsigned int button);
		static void getMousePosition(double& x, double& y);
		static bool testCursor(float x, float y);
	private:
		bool init();
		friend void window_resize(GLFWwindow* m_Window, int width, int height);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};

}}