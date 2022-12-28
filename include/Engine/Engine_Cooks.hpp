#ifndef ENGINE_COOKS_HPP_
    #define ENGINE_COOKS_HPP_

    // # Lib Imports

    #include <iostream>
    #include <stack>

    // # Local Imports

    #include "Engine_Pizza.hpp"
    class Kitchen;

    // # Class

    enum CooksState {
        Sleeping = 0,
        Cooking
    };

    class Cooks {
        public:
            Cooks(Kitchen *);
            ~Cooks();

            Pizza *pizza;

            void display(void);
            void assign_work(int);
            void next_step(void);
            void cook_ready(int);
            Kitchen *kitchen;
            int type;
            int step;
            int state;
    };

#endif /* !ENGINE_COOKS_HPP_ */