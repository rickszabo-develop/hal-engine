#pragma once
#include "Core.h"

namespace Haleng {
	class HALENG_API Application
	{
		public:
			Application();
			virtual ~Application();

			void Run();
	};

	Application* CreateApplication();
}