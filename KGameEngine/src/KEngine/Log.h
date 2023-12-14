#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace KEngine {

	class KENGINE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Log
#define KE_CORE_ERROR(...)	::KEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KE_CORE_WARN(...)	::KEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KE_CORE_INFO(...)	::KEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KE_CORE_TRACE(...)	::KEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KE_CORE_TRACE(...)	::KEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log
#define KE_ERROR(...)	::KEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define KE_WARN(...)	::KEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KE_INFO(...)	::KEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define KE_TRACE(...)	::KEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KE_TRACE(...)	::KEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)
