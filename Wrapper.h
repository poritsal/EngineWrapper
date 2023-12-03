#pragma once
#include <unordered_map>
#include <string>
#include <functional>


class WrapperBase {
public:
    virtual int execute(const std::unordered_map<std::string, int>& params) = 0;
};


template <typename T, typename... Args>
class Wrapper : public WrapperBase {
public:
    Wrapper(T* obj_, int (T::* method_)(Args...), const std::unordered_map<std::string, int>& args_ = {});
    int execute(const std::unordered_map<std::string, int>& params) override; 

private:
    T* obj;
    std::function<int(Args...)> method;
    std::unordered_map<std::string, int> args;

    template <std::size_t... Is>
    auto vectorToTuple(const std::vector<int>& vec, std::index_sequence<Is...>); 
    std::vector<int> validateKeys(const std::unordered_map<std::string, int>& params); 
};

#include "Wrapper.cpp"