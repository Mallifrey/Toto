#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace toto {namespace graphics {

#define MAX_KEYS	1024
#define MAX_BUTTONS	32

	class Window {
	public:
		int m_Width, m_Height;
	private:
		const char *m_Title;
		GLFWwindow *m_Window;
		bool m_Closed;

		static bool m_Keys[MAX_KEYS];
		static bool m_MouseButtons[MAX_BUTTONS];
		static double mx, my;
	public:
		Window(const char *title, int width, int height);
		~Window();
		void clear() const;
		void update();
		bool closed() const;

		static bool isKeyPressed(unsigned int keycode);
		static bool isMouseButtonPressed(unsigned int button);
		static void getMousePosition(double& x, double& y);
	private:
		bool init();
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};

}}