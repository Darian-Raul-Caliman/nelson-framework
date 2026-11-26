#include "nspch.h"
#include "MessageBus.h"

#include <algorithm>

namespace Nelson {

	std::unordered_map<std::type_index, std::vector<MessageBus::Handler>> MessageBus::s_Handlers;
	std::vector<std::function<void()>> MessageBus::s_Queue;
	uint64_t MessageBus::s_NextId = 1;

	void Subscription::Reset()
	{
		if (m_Id != 0)
		{
			MessageBus::Unsubscribe(m_Id);
			m_Id = 0;
		}
	}

	void MessageBus::Dispatch(std::type_index type, const void* message)
	{
		auto it = s_Handlers.find(type);
		if (it == s_Handlers.end())
			return;

		std::vector<Handler> handlers = it->second;
		for (const Handler& handler : handlers)
		{

			if (IsSubscribed(type, handler.Id))
				handler.Callback(message);
		}
	}
	bool MessageBus::IsSubscribed(std::type_index type, uint64_t id)
	{

		auto it = s_Handlers.find(type);
		if (it == s_Handlers.end())
			return false;
		return std::any_of(it->second.begin(), it->second.end(),
			[id](const Handler& h) { return h.Id == id; });
	}

	void MessageBus::Unsubscribe(uint64_t id) 
	{
		for (auto& [type, handlers] : s_Handlers)
		{
			handlers.erase(std::remove_if(handlers.begin(), handlers.end(),
				[id](const Handler& h) { return h.Id == id; }), handlers.end());
		}
	}

	void MessageBus::Flush()
	{

		std::vector<std::function<void()>> queue = std::move(s_Queue);
		s_Queue.clear();
		for (auto& deliver : queue)
			deliver();

	}

	void MessageBus::Clear() {

		s_Handlers.clear();
		s_Queue.clear();

	}
}