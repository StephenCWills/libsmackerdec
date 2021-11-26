#include "Profiler.h"
#include <algorithm>
#include <unordered_map>

std::unordered_map<std::string, TimingInfo> timings;

FunctionProfiler::FunctionProfiler(std::string name)
    : _name(name)
{
    osTickCounterStart(&_tickCounter);
}

FunctionProfiler::~FunctionProfiler()
{
	osTickCounterUpdate(&_tickCounter);

	TimingInfo& timing = timings[_name];
	timing.Ticks += osTickCounterRead(&_tickCounter);
	timing.Count++;
}

static bool CompareTiming(const TimingInfo &a, const TimingInfo &b)
{
	return a.Ticks > b.Ticks;
}

std::vector<TimingInfo> FunctionProfiler::Dump()
{
	std::vector<TimingInfo> timingList;
	for (auto it = timings.begin(); it != timings.end(); ++it) {
        it->second.Name = it->first;
		timingList.push_back(it->second);
    }
	std::sort(timingList.begin(), timingList.end(), CompareTiming);
	return timingList;
}
