#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Mimou {

	class MIMOU_API Log
	{
	public:
		static void Init();

		// std::shared_ptr is a smart pointer that retains shared 
		// ownership of an object through a pointer. Several 
		// shared_ptr objects may own the same object.

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
			return s_CoreLogger;
		}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {
			return s_ClientLogger;
		}
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define MM_CORE_ERROR(...)	::Mimou::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MM_CORE_WARN(...)	::Mimou::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MM_CORE_INFO(...)	::Mimou::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MM_CORE_TRACE(...)	::Mimou::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MM_CORE_FATAL(...)	::Mimou::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define MM_CLIENT_ERROR(...)	::Mimou::Log::GetClientLogger()->error(__VA_ARGS__)
#define MM_CLIENT_WARN(...)		::Mimou::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MM_CLIENT_INFO(...)		::Mimou::Log::GetClientLogger()->info(__VA_ARGS__)
#define MM_CLIENT_TRACE(...)	::Mimou::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MM_CLIENT_FATAL(...)	::Mimou::Log::GetClientLogger()->fatal(__VA_ARGS__)
