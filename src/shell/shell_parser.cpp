// # Lib Imports

#include <string.h>
#include <iostream>
#include <stack>
#include <string>

// # Local Imports

#include "../../include/Engine/Engine_Data.hpp"
#include "../../include/Shell/Shell_Parser.hpp"
#include "../../include/Engine.hpp"

// # Static Values

// # Static Methods

char *read_quantity(std::string command)
{
    char *num = (char *)malloc(sizeof(char) * (command.size() + 1));
    int pos = 0;

    while (command[pos] && command[pos] >= '0' && command[pos] <= '9') {
        num[pos] = command[pos];
        pos++;
    }
    num[pos] = '\0';
    if (strlen(num) <= 0 || atoi(num) <= 0)
        return (NULL);
    return (num);
}

PizzaSize read_size(std::string command)
{
    for (int i = 0; i < sizeLen; i++)
        if (!strncmp(command.c_str(), SizeNames[i].first,
            strlen(SizeNames[i].first)))
            return (SizeNames[i].second);
    return (O);
}

PizzaType read_type(std::string command)
{
    for (int i = 0; i < pizzaLen; i++)
        if (!strncmp(command.c_str(), PizzaNames[i].first,
            strlen(PizzaNames[i].first)))
            return (PizzaNames[i].second);
    return (Nil);
}

// # Methods

bool shell_syntax(char *command)
{
    pizzaOrder_t elem;
    std::string s(command);

    while (s.length() != 0) {
        while (s[0] == ';' || s[0] == ' ')
            s.erase(0, 1);
        if (!s.length())
            break;
        elem.type = read_type(s);
        if (elem.type == Nil || s.length() < strlen(PizzaNames[elem.type - 1].first) + 1)
            return (false);
        s.erase(0, strlen(PizzaNames[elem.type - 1].first) + 1);
        elem.size = read_size(s);
        if (!elem.size || s.length() < strlen(SizeNames[elem.size - 1].first) + 1)
            return (false);
        s.erase(0, strlen(SizeNames[elem.size - 1].first) + 1);
        if (s[0] == 'x')
            s.erase(0, 1);
        char *qty = read_quantity(s);
        if (!qty || s.length() < strlen(qty)) {
            if (qty)
                free(qty);
            return (false);
        }
        s.erase(0, strlen(qty));
        elem.quantity = atoi(qty);
        free(qty);
    }
    return (true);
}

std::stack<pizzaOrder_t> shell_parser(Engine *eng, char *command)
{
    std::stack<pizzaOrder_t> order;
    std::stack<pizzaOrder_t> nul;
    pizzaOrder_t elem;
    std::string s(command);

    if (!shell_syntax(command))
        return (nul);
    while (s.length() != 0) {
        while (s[0] == ';' || s[0] == ' ')
            s.erase(0, 1);
        if (!s.length())
            break;
        elem.type = read_type(s);
        s.erase(0, strlen(PizzaNames[elem.type - 1].first) + 1);
        elem.size = read_size(s);
        s.erase(0, strlen(SizeNames[elem.size - 1].first) + 1);
        if (s[0] == 'x')
            s.erase(0, 1);
        char *qty = read_quantity(s);
        s.erase(0, strlen(qty));
        elem.quantity = atoi(qty);
        free(qty);
        order.push(elem);
    }
    return (order);
}