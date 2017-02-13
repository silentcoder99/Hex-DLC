#include "WorkerThread.h"

WorkerThread::WorkerThread(ThreadSafeStack<std::function<void()> >& taskStack) :
	mTaskStack(taskStack) {

	mThread = boost::thread([this]() {
		while (mTaskStack.size() != 0) {
			std::function<void()> task = mTaskStack.pop();
			task();
		}

		mThreadRunning = false;
	});
}

void WorkerThread::join() {
	mThread.join();
}

bool WorkerThread::isRunning() {
	return mThreadRunning;
}