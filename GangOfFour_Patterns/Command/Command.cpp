// pattern_command.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <memory>

class Command
{
public:
    Command() {}
    virtual ~Command() {}

    virtual void Execute() {};
};

//SimpleCommand
template<class Receiver>
class SimpleCommand : public Command
{
public:
    typedef void (Receiver::* Action)();
    SimpleCommand(Receiver* r, Action a)
        : _receiver(r)
        , _action(a)
    {}

    void Execute() override
    {
        (_receiver->*_action)();
    }
private:
    Action _action;
    Receiver* _receiver;
};

class Receiver1 {
public:
    void Handle() { std::cout << " Command HANDLED in R1" << std::endl; }
};

class Receiver2 {
public:
    void Handle() { std::cout << " Command HANDLED in R2!" << std::endl; }
};

// MacroCommand
class MacroCommand : public Command {
public:
    MacroCommand() 
    {
    
    }

    virtual ~MacroCommand() {}
    virtual void Add(Command* c) { m_cmds.push_back(c); }
    virtual void Remove(Command* c) { m_cmds.remove(c); }

    void Execute() override 
    {
        for (auto it : m_cmds)
        {
            it->Execute();
        }
    }
private:
    std::list<Command*> m_cmds;

};

int main()
{
    std::cout << "PATTERN COMMAND\n";

    std::unique_ptr<Receiver1> r1{new Receiver1};
    std::unique_ptr<Receiver2> r2{ new Receiver2 };

    std::unique_ptr<SimpleCommand<Receiver1>> sc1{new SimpleCommand<Receiver1>(r1.get(), &Receiver1::Handle)};
    std::unique_ptr<SimpleCommand<Receiver2>> sc2{new SimpleCommand<Receiver2>(r2.get(), &Receiver2::Handle) };

    MacroCommand mc;
    mc.Add(sc1.get());
    mc.Add(sc2.get());

    mc.Execute();
}
