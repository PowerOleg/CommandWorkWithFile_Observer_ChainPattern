#include <iostream>
#include <filesystem>
#include <fstream>

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













/*

class LogCommand
{
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class LogToConsoleCommand : public LogCommand
{
public:
    void print(const std::string& message) override
    {
        std::cout << message << std::endl;
    }
};

class LogToFileCommand : public LogCommand
{
public:
    LogToFileCommand(std::string path_) : path{ path_ }
    {}

    void print(const std::string& message) override
    {
        std::ofstream fout(path, std::ios_base::out | std::ios_base::trunc);
        if (!fout.is_open())
        {
            //work with compiler std:c++17
            int index = path.find_last_of('\\');
            std::string dir = path.substr(0, index);
            std::filesystem::create_directories(dir);// #include<windows.h> //std::CreateDirectory("C:\\Users\\morons", NULL);
            std::cout << "Created directory .\\Command\\log\\ \n";
            fout = std::ofstream(path, std::ios_base::out | std::ios_base::trunc);
        }
        //if (!fout.is_open()){ return;}
        fout << message;
        fout.close();
    }
private:
    std::string path = "";
};

void print(LogCommand& command, const std::string& message)
{
    command.print(message);
}



class LogObserverParent
{
public:
	virtual ~LogObserverParent() = default;
	virtual void Warning(const std::string& message) const;
	virtual void Error(const std::string& message) const;
	virtual void FatalError(const std::string& message) const;
};

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void onWarning(const std::string& message) {}
	virtual void onError(const std::string& message) {}
	virtual void onFatalError(const std::string& message) {}
};

*/
/*int main(int argc, char** argv)
{
	//вывод сообщения message в консоль
	LogToConsoleCommand logToConsole;
	print(logToConsole, "log to console");

	//вывод сообщения в файл, по указанному пути.
	LogToFileCommand logToFile(".\\log\\log.txt");//".\\Command\\log.txt");
	print(logToFile, "log to file");

	//В иерархии классов-наблюдателей нужно реализовать класс для работы с предупреждениями,
	//который будет печатать сообщение в консоль;

	return 0;
}*/






