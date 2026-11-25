#include "nspch.h"
#include "Timer.h"

#include <algorithm>
#include <chrono>

namespace Nelson {

	std::vector<Timer::Entry> Timer::s_Timers;
	TimerId Timer::s_NextId = 1;

	double Timer::Now()
	{

		using namespace std::chrono;
		return duration<double>(steady_clock::now().time_since_epoch()).count();
	}

	TimerId Timer::Add(double seconds, bool repeat, std::function<void()> callback)
	{
		if (!callback)
			return 0;
		if (repeat && seconds < 0.001)
			seconds = 0.001;   

		TimerId id = s_NextId++;
		s_Timers.push_back({ id, seconds, Now() + seconds, repeat, std::move(callback) });
		return id;
	}

	TimerId Timer::After(double seconds, std::function<void()> callback)
	{
		return Add(seconds, false, std::move(callback));
	}

	TimerId Timer::Every(double seconds, std::function<void()> callback)
	{
		return Add(seconds, true, std::move(callback));
	}

	void Timer::Cancel(TimerId id)
	{
		s_Timers.erase(std::remove_if(s_Timers.begin(), s_Timers.end(),
			[id](const Entry& e) { return e.Id == id; }), s_Timers.end());
	}

	void Timer::CancelAll()
	{
		s_Timers.clear();
	}

	bool Timer::IsActive(TimerId id)
	{
		return std::any_of(s_Timers.begin(), s_Timers.end(),
			[id](const Entry& e) { return e.Id == id; });
	}

	void Timer::Update()
	{
		double now = Now();


		std::vector<TimerId> due;
		for (const Entry& e : s_Timers)
			if (e.Deadline <= now)
				due.push_back(e.Id);


		for (TimerId id : due)
		{
			auto it = std::find_if(s_Timers.begin(), s_Timers.end(),
				[id](const Entry& e) { return e.Id == id; });
			if (it == s_Timers.end())
				continue;   

			std::function<void()> callback = it->Callback;

			if (it->Repeat)
			{
				it->Deadline += it->Interval;
				if (it->Deadline <= now)           
					it->Deadline = now + it->Interval; 
			}
			else
			{
				s_Timers.erase(it);
			}

			callback();
		}
	}

	double Timer::GetTimeUntilNext()
	{
		if (s_Timers.empty())
			return -1.0;

		double next = s_Timers.front().Deadline;
		for (const Entry& e : s_Timers)
			next = std::min(next, e.Deadline);

		return std::max(0.0, next - Now());
	}
}