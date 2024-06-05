#pragma once
#include <cstdlib>
#include <Engine/API.hpp>

namespace Engine
{
	class UUID
	{
		uint64_t m_UUID = 0;

	public:
		EngineAPI UUID();
		EngineAPI UUID(uint64_t uuid);
		EngineAPI UUID(const UUID&) = default; // Copy constructor

		operator uint64_t() const { return m_UUID; }
	};

	const UUID InvalidUUID = 0;
}

namespace std
{
	// template<typename T> struct hash;

	template<>
	struct hash<Engine::UUID>
	{
		std::size_t operator()(const Engine::UUID& uuid) const
		{
			return (uint64_t)uuid;
		}
	};
}