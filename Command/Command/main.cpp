#include <iostream>
#include <fstream>
/*
class Task
{
public:
    virtual ~Task() = default;
    virtual void execute() = 0;
    virtual void cancel() = 0;
};

class GameField
{
public:
    void setPause(bool pause_)
    {}
    void addUnit(int x_, int y_)
    {}
private:

};

class Command
{
public:
    virtual ~Command() = default;
    virtual void execute(GameField* game_field) = 0;
};

class PauseCommand : public Command //ќстанавливаем или возобновл€ем игру в зависимости от параметра pause
{
public:
    explicit PauseCommand(bool pause) : pause_(pause) {}
    void execute(GameField* game_field) override {
        game_field->setPause(pause_);
    }
private:
    bool pause_ = false;
};

class AddUnitCommand : public Command //ƒобавл€ем нового юнита на игровое поле по координатам x, y
{
public:
    AddUnitCommand(int x, int y) : x_(x), y_(y) {}
    void execute(GameField* game_field) override {
        game_field->addUnit(x_, y_);
    }
private:
    int x_ = 0;
    int y_ = 0;
};
*/


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

    }
private:
    std::string path = "";
};

void print(LogCommand& command, const std::string& message)
{
    command.print(message);
}


int main(int argc, char** argv)
{
//    GameField* gameField = new GameField();
//    AddUnitCommand addUnitCommand(0, 0);
//    addUnitCommand.execute(gameField);
 
    //вывод сообщени€ message в консоль
    LogToConsoleCommand logToConsole;
    print(logToConsole, "log to console");

    //вывод сообщени€ в файл, по указанному пути.
    LogToFileCommand logToFile(".\Command\log.txt");
    print(logToFile, "log to file");
    return 0;
}