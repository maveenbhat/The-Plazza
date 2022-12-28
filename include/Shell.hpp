#ifndef SHELL_HPP_
    #define SHELL_HPP_
    
    // # Lib Imports

    #include <string.h>
    #include <iostream>
    #include <stack>
    
    // # Local Imports

    class Engine;

    #include "Shell/Shell_Reader.hpp"

    // # Struct

    typedef struct pizzaOrder_s
    {
        int type;
        int size;
        int quantity;
    } pizzaOrder_t;

    // # Methods

    bool shell_syntax(char *);
    std::stack<pizzaOrder_t> shell_parser(Engine *, char *);
    void *shell_loop(void *);

#endif /* !SHELL_HPP_ */