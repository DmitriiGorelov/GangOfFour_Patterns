// pattern_command.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>

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

    MacroCommand mc;
    mc.Add(new SimpleCommand<Receiver1>(new Receiver1, &Receiver1::Handle));
    mc.Add(new SimpleCommand<Receiver2>(new Receiver2, &Receiver2::Handle));

    mc.Execute();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
