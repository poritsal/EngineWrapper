template<typename T, typename ...Args>
Wrapper<T, Args...>::Wrapper(T* obj_, int(T::* method_)(Args...), const std::unordered_map<std::string, int>& args_) {
    obj = obj_;
    if (sizeof...(Args) != args_.size()) {
        throw std::exception("The number of arguments passed does not match the number of arguments accepted by the function");
    }
    method = [=](Args... methodArgs) { return (obj->*method_)(methodArgs...); };
    args = args_;
}

template<typename T, typename ...Args>
int Wrapper<T, Args...>::execute(const std::unordered_map<std::string, int>& params) {
    return std::apply(method, vectorToTuple(validateKeys(params), std::index_sequence_for<Args...>()));
}

template<typename T, typename ...Args>
template<std::size_t ...Is>
auto Wrapper<T, Args...>::vectorToTuple(const std::vector<int>& vec, std::index_sequence<Is...>) {
    return std::make_tuple(vec[Is]...);
}

template<typename T, typename ...Args>
std::vector<int> Wrapper<T, Args...>::validateKeys(const std::unordered_map<std::string, int>& params) {
    if (params.size() != args.size()) {
        throw std::exception("The number of arguments passed does not match the number of arguments accepted by the function");
    }

    std::vector<int> foundValues;

    for (const auto& arg : args) {
        auto it = params.find(arg.first);
        if (it != params.end()) {
            foundValues.push_back(it->second);
        }
        else {
            throw std::runtime_error("Key '" + arg.first + "' is missing in the provided parameters.");
        }
    }

    return foundValues;
}