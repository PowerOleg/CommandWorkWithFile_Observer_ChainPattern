#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>

class IWatcher
{
public:
	virtual ~IWatcher() = default;
	virtual void Warning(const std::string& message) const = 0;
	virtual void Error(const std::string& message) const = 0;
	virtual void FatalError(const std::string& message) const = 0;
};

class IObserver
{
public:
	virtual ~IObserver() = default;
	virtual void onWarning(const std::string& message) = 0;
	virtual void onError(const std::string& message) = 0;
	virtual void onFatalError(const std::string& message) = 0;
};

class Watcher : public IWatcher
{
public:
	~Watcher() override {}

	void Warning(const std::string& message) const override
	{
		std::cout << "Warning: " << message << std::endl;
	}

	virtual void Error(const std::string& message) const override
	{
		std::cout << "Error: " << message << std::endl;
	}

	void FatalError(const std::string& message) const override
	{
		std::cout << "FatalError: " << message << std::endl;
	}
};

class Observer : public IObserver
{
public:
	void onWarning(const std::string& message)
	{
		for (auto watcher : watchers) {
//			if (auto strong_ptr = observed.lock()) {
			watcher->Warning(message);
		}
	}

	void onError(const std::string& message)
	{
		for (auto watcher : watchers) {
			watcher->Error(message);
		}
	}

	void onFatalError(const std::string& message)
	{
		for (auto watcher : watchers) {
			watcher->FatalError(message);
		}
	}

	void AddObserver(std::shared_ptr<IWatcher> watcher)
	{
		watchers.push_back(watcher);
	}

private:
	std::vector<std::shared_ptr<IWatcher>> watchers;
};


int main(int argc, char** argv)
{
	Observer observer;
	for (size_t i = 0; i < 4; i++)
	{
		Watcher watcher;
		auto ptr_watcher = std::make_shared<Watcher>(watcher);//std::weak_ptr<SubscriberChild> weak_ptr_subscriber(ptr_subscriber);
		observer.AddObserver(ptr_watcher);
	}
	observer.onWarning("Everybody dance now");
	observer.onError("Error dancing");
	observer.onFatalError("T_T");
	return 0;
}


