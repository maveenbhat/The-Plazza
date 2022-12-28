#ifndef ENGINE_STOCK_HPP_
    #define ENGINE_STOCK_HPP_

    // # Lib Imports

    #include <iostream>
    #include <stack>

    // # Class

    class Stock {
        public:
            Stock();
            ~Stock();
        
        std::pair<int, int> products[9];

        void display_stock(void);
        void update_stock(void);
        int check_stock(int);
        bool get_stock_for_pizza(int);
        bool available_for_pizza(int);
        void add_elem(int, int);
        void del_elem(int, int);
    };

#endif /* !ENGINE_STOCK_HPP_ */