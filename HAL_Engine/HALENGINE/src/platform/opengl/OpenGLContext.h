#pragma once

#include "engine/renderer/GraphicContext.h"

struct GLFWwindow;

namespace Haleng {
	class OpenGLContext : public GraphicContext {
	public:
		OpenGLContext(GLFWwindow* window);
		virtual void Init() override;
		virtual void SwapBuffer() override;

	private:
		GLFWwindow* m_Window;
	};
}