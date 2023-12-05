#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

void exCom(const std::string& com) {
    pid_t pid = fork();
    if (pid == 0) {
        // Дочерний процесс - выполняет команду
        execlp(com.c_str(), com.c_str(), nullptr);
        // Если execlp вернется, значит произошла ошибка
        std::cerr << "Ошибка выполнения команды\n";
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Родительский процесс - ожидает завершения дочернего
        int status;
        waitpid(pid, &status, 0);
    } else {
        // Ошибка при создании дочернего процесса
        std::cerr << "Ошибка создания процесса\n";
    }
}

int main() {
    std::string input;
    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, input);
        if (input == "exit" || input == "quit") {
            break;
        }
        exCom(input);
    }
    return 0;
}
