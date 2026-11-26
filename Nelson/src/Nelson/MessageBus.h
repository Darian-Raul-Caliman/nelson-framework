#pragma once
#include <cstdint>
#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace Nelson {

	class Subscription
	{
	public:
		Subscription() = default;
		explicit Subscription(uint64_t id) : m_Id(id) {}
		~Subscription() { Reset(); }
		Subscription(const Subscription&) = delete;
		Subscription& operator=(const Subscription&) = delete;
		Subscription(Subscription&& other) noexcept : m_Id(other.m_Id) { other.m_Id = 0; }
		Subscription& operator=(Subscription&& other) noexcept
		{
			if (this != &other)
			{
				Reset();
				m_Id = other.m_Id;
				other.m_Id = 0;
			}
			return *this;
		}

		void Reset();                            
		bool IsActive() const { return m_Id != 0; }

	private:
		uint64_t m_Id = 0;
	};
}