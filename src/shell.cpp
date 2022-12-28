// # Lib Imports
    
#include <iostream> 
#include <stack> 
#include <string.h>

// # Local Imports

#include "../include/Engine.hpp"

// # Static Values

static const char *status_command = "status";
static const char *exit_command = "exit";

// # Methods

void *shell_loop(void *eng)
{
    const char *invalid = "Invalid command. Please check syntax.";
    const char *prompt = "> ";
    Engine *engine = (Engine *)eng;
    char *command = NULL;

    while (engine->running) {
        std::cout << prompt;
        command = shell_read_line();
        if (!command)
            break;
        if (!strcmp(command, status_command))
            engine->display();
        else if (!strcmp(command, exit_command))
            engine->running = false;
        else {
            std::stack<pizzaOrder_t> stack = shell_parser(engine, command);
            if (stack.empty())
                std::cerr << invalid << std::endl;
            else
                engine->load_orders(stack);
        }
        if (command)
            free(command);
    }
    return (NULL);
}