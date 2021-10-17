#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

class Gui
{
private:
	GLFWwindow* m_window;
public:
	Gui();
	
	bool isOpen();
	void pollEvents();
	void clear(ImVec4 clear_color);
	void swapBuffers();
	GLFWwindow* GetWindow() const;
	~Gui();
	
	const char * glsl_version;
};
