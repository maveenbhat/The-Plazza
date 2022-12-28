#ifndef ENGINE_KITCHEN_HPP_
    #define ENGINE_KITCHEN_HPP_

    // # Lib Imports

    #include <iostream>
    #include <vector>
    #include <unistd.h>
    #include <pthread.h>
    #include <mutex>

    // # Local Imports

    #include "Engine_Cooks.hpp"
    #include "Engine_Stock.hpp"
    #include "../Shell.hpp"
    #include "../Engine.hpp"

    class Engine;
    typedef struct order_s order_t;

    // # Class

    enum KitchenState {
        Full,
        Work,
        Waiting
    };

    class Kitchen {
        public:
            Kitchen(Engine *);
            ~Kitchen();

            Engine *engine;
            std::vector<Cooks *> cooks;
            Stock *stock;
            int state;
            int active;
            bool running;
            pthread_t thread;

            std::vector<std::pair<int, int>> pizzasToCook;
            std::mutex pizzasCoooked_mutex;
            std::vector<std::pair<int, int>> pizzasCooked;

            void display_cooks(void);
            order_t prepare_order(order_t);
            void refresh_stock(void);
            void start_work(void);
            void stop_work(void);
            bool check_step(void);
            void assign_if_empty(void);
            void pizza_ready(int);
            int get_pizza_mult(int);
        private:
            void prepare_cooks(void);
    };

#endif /* !ENGINE_KITCHEN_HPP_ */