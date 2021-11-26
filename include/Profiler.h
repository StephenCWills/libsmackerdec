#ifndef _Profiler_h_
#define _Profiler_h_

#include <3ds.h>
#include <string>
#include <vector>

struct TimingInfo {
	std::string Name;
	double Ticks;
	int Count;
};

class FunctionProfiler {
public:
    FunctionProfiler(std::string name);
    ~FunctionProfiler();
    static std::vector<TimingInfo> Dump();
    
private:
	std::string _name;
	TickCounter _tickCounter;
};


#endif
