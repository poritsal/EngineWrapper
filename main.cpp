#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <tuple>

class Subject {
public:
    int f1() {
        std::cout << "f1" << std::endl;
        return 0;
    }

    int f2(int arg1, int arg2) {
        std::cout << "f2: " << arg1 << ", " << arg2 << std::endl;
        return arg1 + arg2;
    }

    int f3(int arg1, int arg2, int arg3) {
        std::cout << "f3: " << arg1 << ", " << arg2 << ", " << arg3 << std::endl;
        return arg1 + arg2 + arg3;
    }
};

class WrapperBase {
public:
    virtual int execute(std::unordered_map<std::string, int> params) = 0;
};

template <typename T, typename... Args>
class Wrapper : public WrapperBase {
public:
    Wrapper(T* obj, int (T::* method)(Args...), std::unordered_map<std::string, int> args = {})
        : obj(obj), method([=](Args... methodArgs) { return (obj->*method)(methodArgs...); }), args(args) {}


    int execute(std::unordered_map<std::string, int> params) override {
        return std::apply(method, expandArgs(params, std::index_sequence_for<Args...>()));
    }

private:
    T* obj;
    std::function<int(Args...)> method;
    std::unordered_map<std::string, int> args;

    template <std::size_t... Is>
    auto expandArgs(std::unordered_map<std::string, int> params, std::index_sequence<Is...>) {
        return std::make_tuple(params["arg" + std::to_string(Is + 1)]...);
    }
};

class Engine {
public:
    template <typename T, typename... Args>
    void register_command(Wrapper<T, Args...>* wrapper, const std::string& command_name) {
        commands[command_name] = wrapper;
    }

    template <typename... Args>
    int execute(const std::string& command_name, std::unordered_map<std::string, int> params = {}) {
        auto it = commands.find(command_name);
        if (it != commands.end()) {
            return it->second->execute(params);
        }
        else {
            std::cerr << "Error: Unknown command '" << command_name << "'" << std::endl;
            return -1;
        }
    }

private:
    std::unordered_map<std::string, WrapperBase*> commands;
};

int main() {
    Subject subj;

    Wrapper wrapper1(&subj, &Subject::f1);
    Wrapper wrapper2(&subj, &Subject::f2, { {"arg1", 0}, {"arg2", 0} });
    Wrapper wrapper3(&subj, &Subject::f3, { {"arg1", 0}, {"arg2", 0}, {"arg3", 0} });

    Engine engine;
    engine.register_command(&wrapper1, "command1");
    engine.register_command(&wrapper2, "command2");
    engine.register_command(&wrapper3, "command3");


    std::cout << engine.execute("command1") << std::endl;
    std::cout << engine.execute("command2", { {"arg1", 4}, {"arg2", 5} }) << std::endl;
    std::cout << engine.execute("command3", { {"arg1", 4}, {"arg2", 5}, {"arg3", 6} }) << std::endl;
}