#pragma once
#include <cstdint>
#include <functional>
#include <vector>

namespace Nelson {

	using TimerId = uint64_t;   

	class Timer
	{
	public:

		static TimerId After(double seconds, std::function<void()> callback);

		static TimerId Every(double seconds, std::function<void()> callback);

		static void Cancel(TimerId id);
		static void CancelAll();
		static bool IsActive(TimerId id);
		static void Update();                 
		static double GetTimeUntilNext();     

	private:
		struct Entry
		{
			TimerId Id;
			double Interval;
			double Deadline;  
			bool Repeat;
			std::function<void()> Callback;
		};

		static TimerId Add(double seconds, bool repeat, std::function<void()> callback);
		static double Now();

		static std::vector<Entry> s_Timers;
		static TimerId s_NextId;
	};
}