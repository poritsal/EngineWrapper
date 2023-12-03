#include "Subject.h"
#include "Engine.h"


int main() {
    try {
        Subject subj;

        Wrapper wrapper1(&subj, &Subject::f1);
        Wrapper wrapper2(&subj, &Subject::f2, { {"arg1", 0}, {"arg2", 0} });
        Wrapper wrapper3(&subj, &Subject::f3, { {"arg1", 0}, {"varg2", 0}, {"arg3", 0} });

        Engine engine;
        engine.register_command(&wrapper1, "command1");
        engine.register_command(&wrapper2, "command2");
        engine.register_command(&wrapper3, "command3");

        std::cout << engine.execute("command1") << std::endl;
        std::cout << engine.execute("command2", { {"arg1", 4}, {"arg2", 5} }) << std::endl;
        std::cout << engine.execute("command3", { {"varg2", 4}, {"arg1", 5}, {"arg3", 6} }) << std::endl;
        std::cout << engine.execute("command2", { {"a1", 4}, {"a2", 5} }) << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}