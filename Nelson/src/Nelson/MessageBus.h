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

	class MessageBus
	{
	public:
		template<typename T>
		[[nodiscard]] static Subscription Subscribe(std::function<void(const T&)> handler)
		{
			uint64_t id = s_NextId++;
			s_Handlers[std::type_index(typeid(T))].push_back({ id,
				[h = std::move(handler)](const void* message) { h(*static_cast<const T*>(message)); } });
			return Subscription(id);
		}

		template<typename T>
		static void Publish(const T& message)
		{
			Dispatch(std::type_index(typeid(T)), &message);
		}

		template<typename T>
		static void Post(T message)
		{
			s_Queue.push_back([m = std::move(message)]() { Publish<T>(m); });
		}


		static void Flush();
		static bool HasPending() { return !s_Queue.empty(); }
		static void Clear();

	private:
		friend class Subscription;

		struct Handler
		{
			uint64_t Id;
			std::function<void(const void*)> Callback;
		};

		static void Dispatch(std::type_index type, const void* message);
		static void Unsubscribe(uint64_t id);
		static bool IsSubscribed(std::type_index type, uint64_t id);

		static std::unordered_map<std::type_index, std::vector<Handler>> s_Handlers;
		static std::vector<std::function<void()>> s_Queue;
		static uint64_t s_NextId;
	};
}