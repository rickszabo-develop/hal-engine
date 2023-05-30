#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Haleng {
	class HALENG_API Log
	{
		public:
			static void Init();
			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
			inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		private:
			static std::shared_ptr<spdlog::logger> s_CoreLogger;
			static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core logs
#define HALENG_CORE_TRACE(...)	::Haleng::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HALENG_CORE_INFO(...)	::Haleng::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HALENG_CORE_WARN(...)	::Haleng::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HALENG_CORE_ERROR(...)	::Haleng::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HALENG_CORE_FATAL(...)	::Haleng::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client logs
#define HALENG_CLIENT_TRACE(...)	::Haleng::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HALENG_CLIENT_INFO(...)		::Haleng::Log::GetClientLogger()->info(__VA_ARGS__)
#define HALENG_CLIENT_WARN(...)		::Haleng::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HALENG_CLIENT_ERROR(...)	::Haleng::Log::GetClientLogger()->error(__VA_ARGS__)
#define HALENG_CLIENT_FATAL(...)	::Haleng::Log::GetClientLogger()->fatal(__VA_ARGS__)