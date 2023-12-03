# EngineWrapper
This code implements a command engine in C++ that allows registering and executing commands through wrappers. It is designed to work with class methods that accept and return integers

# Classes
1. Subject
The Subject class serves as an example class with methods that can be used as commands. In this example, it includes three methods: f1(), f2(int arg1, int arg2), and f3(int arg1, int arg2, int arg3).

2. WrapperBase
The abstract WrapperBase class defines the interface for command wrappers. It declares a pure virtual function execute, which is implemented by its derived class Wrapper.

3. Wrapper
The Wrapper class is a template class that acts as a wrapper for a method of the Subject class. It takes the object (T* obj_), method pointer (int (T::* method_)(Args...)), and a map of default arguments (std::unordered_map<std::string, int> args_). The execute function applies the method with the provided parameters.

4. Engine
The Engine class manages the registration and execution of commands. It uses a map (std::unordered_map<std::string, WrapperBase*> commands) to store registered commands and their corresponding wrappers. The register_command function adds a new command to the map, and the execute function runs a specified command with given parameters.
