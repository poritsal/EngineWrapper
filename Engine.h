#pragma once
#include "Wrapper.h"
#include <vector>
#include <tuple>
#include <stdexcept>

class Engine {
public:
    template <typename T, typename... Args>
    void register_command(Wrapper<T, Args...>* wrapper, const std::string& command_name);

    template <typename... Args>
    int execute(const std::string& command_name, const std::unordered_map<std::string, int>& params = {});

private:
    std::unordered_map<std::string, WrapperBase*> commands;
};

#include "Engine.cpp"