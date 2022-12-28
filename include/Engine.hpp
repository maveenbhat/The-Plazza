#ifndef ENGINE_HPP_
    #define ENGINE_HPP_

    // # Lib Imports
    
    #include <iostream>
    #include <stack>
    #include <vector>
    #include <mutex>

    // # Local Imports

    #include "Engine/Engine_Kitchen.hpp"

    #include "Shell.hpp"

    // # Struct

    typedef struct commu_s
    {
        int instruction;
        int val;
        int type;
        int size;
        int delay;
    } commu_t;

    typedef struct order_s
    {
        std::vector<std::pair<int, int>> pizzaToCook;
        std::vector<std::pair<int, int>> pizzaLeft;
        std::vector<std::pair<int, int>> pizzaCooked;
        std::stack<pizzaOrder_t> details;
        
    } order_t;

    // # Class

    class Engine {
        public:
            Engine(int, int, int);
            ~Engine(void);

            std::vector<Kitchen *> kitchens;
            std::vector<order_t> tasks;

            int multiplier;
            int cooks;
            int refresh;
            bool running;
            pthread_t thread;
            commu_t *commu;

            void display(void);
            void load_orders(std::stack<pizzaOrder_t>);
            void run(void);
            bool order_ready(void);
            void delete_current_order(void);
            bool check_kitchens(void);
            void clean_kitchens(void);
            void update_order(void);
    };

#endif /* !ENGINE_HPP_ */