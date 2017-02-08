#include <boost/thread.hpp>
#include <stack>
#include "util/ThreadSafeStack.hpp"

class WorkerThread {
public:
	WorkerThread(ThreadSafeStack< std::function<void()> >& taskStack);
	bool isRunning();
	void join();
private:
	ThreadSafeStack< std::function<void()> >& mTaskStack;
	boost::thread mThread;
	bool mThreadRunning = true;
};
