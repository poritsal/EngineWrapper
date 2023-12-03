template<typename T, typename ...Args>
void Engine::register_command(Wrapper<T, Args...>* wrapper, const std::string& command_name) {
    if (commands.count(command_name) == 1) {
        throw std::runtime_error("Recurring command: " + command_name);
    }
    commands[command_name] = wrapper;
}

template<typename ...Args>
int Engine::execute(const std::string& command_name, const std::unordered_map<std::string, int>& params) {
    auto it = commands.find(command_name);
    if (it != commands.end()) {
        return it->second->execute(params);
    }
    else {
        throw std::runtime_error("Unknown command: " + command_name);
    }
}