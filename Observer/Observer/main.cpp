#include <iostream>
#include <string>
//#include <filesystem>
//#include <fstream>
#include <memory>
#include <algorithm>
#include <vector>

class Observed
{
public:
	virtual ~Observed() = default;
	virtual void Warning(const std::string& message) const;
	virtual void Error(const std::string& message) const;
	virtual void FatalError(const std::string& message) const;
};

class ObservedChild : public Observed
{
public:
	~ObservedChild() override
	{}

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




class Observer
{
public:
	virtual ~Observer() = default;
	virtual void onWarning(const std::string& message) {}
	virtual void onError(const std::string& message) {}
	virtual void onFatalError(const std::string& message) {}
};

class ObserverChild : public Observer
{
public:
	virtual ~ObserverChild() override
	{}

	void onWarning(const std::string& message)
	{
		for (auto observed : observed_) {
			if (auto strong_ptr = observed.lock()) {
				strong_ptr->Warning(message);
			}
		}
	}

	void onError(const std::string& message)
	{
		for (auto observed : observed_) {
			if (auto strong_ptr = observed.lock()) {
				strong_ptr->Error(message);
			}
		}
	}

	void onFatalError(const std::string& message)
	{
		for (auto observed : observed_) {
			if (auto strong_ptr = observed.lock()) {
				strong_ptr->FatalError(message);
			}
		}
	}

	void AddObserver(std::weak_ptr<Observed> observed)
	{
		observed_.push_back(observed);
	}

private:
	std::vector<std::weak_ptr<Observed>> observed_;
};


int main(int argc, char** argv)
{
	ObserverChild observer;

	ObservedChild observed;
	std::shared_ptr<ObservedChild> ptr_observed = std::make_shared<ObservedChild>(observed);//std::shared_ptr<ObservedChild> ptr_observed(&observed);	
	std::weak_ptr<ObservedChild> weak_ptr(ptr_observed);
	observer.AddObserver(weak_ptr);
	
	observer.onWarning("Everybody dance now");

	return 0;

	

	return 0;
}








/*
class Subscriber
{
public:
	virtual ~Subscriber() = default;
	virtual void DidStartLoading() {}
	virtual void DidStopLoading() {}
};

class SubscriberChild : public Subscriber
{
public:
	~SubscriberChild() override
	{

	}

	void DidStartLoading() override
	{
		std::cout << "start loading" << std::endl;
	}

	void DidStopLoading() override
	{
		std::cout << "stop loading" << std::endl;
	}
};

class ObserverGroup
{
public:
	void StartLoading()
	{
		for (auto observer : subscribers_) {
			if (auto strong_ptr = observer.lock()) {
				strong_ptr->DidStartLoading();
			}
		}
	}

	void StopLoading()
	{
		for (auto observer : subscribers_) {
			if (auto strong_ptr = observer.lock()) {
				strong_ptr->DidStopLoading();
			}
		}
	}

	void AddObserver(std::weak_ptr<Subscriber> subscriber)
	{
		subscribers_.push_back(subscriber);
	}
private:
	std::vector<std::weak_ptr<Subscriber>> subscribers_;
};

int main(int argc, char** argv)
{
	std::shared_ptr<SubscriberChild> ptr_subscriber = std::make_shared<SubscriberChild>();
	std::weak_ptr<SubscriberChild> weak_ptr_subscriber(ptr_subscriber);
	ObserverGroup group;
	group.AddObserver(weak_ptr_subscriber);
	group.StartLoading();
	group.StopLoading();
	return 0;
}
*/





