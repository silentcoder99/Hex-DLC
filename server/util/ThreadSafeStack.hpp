#include <stack>
#include <boost/thread.hpp>
#include <mutex>
#include <boost/date_time/posix_time/posix_time.hpp>

template <class Type>
class ThreadSafeStack {
	std::stack<Type> mStack;
	mutable std::mutex m_mutex;
public:
	Type pop() {
		std::lock_guard<std::mutex> lock(m_mutex);
		Type item = mStack.top();
		mStack.pop();
		return item;
	}

	int size() {
		std::lock_guard < std::mutex > lock(m_mutex);
		return mStack.size();
	}

	void push(Type item) {
		std::lock_guard< std::mutex > lock(m_mutex);
		mStack.push(item);
	}
};