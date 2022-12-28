// # Lib Imports

#include <unistd.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

// # Local Imports

#include "../../include/Engine/Engine_Data.hpp"
#include "../../include/Engine/Engine_Stock.hpp"
#include "../../include/Engine/Engine_Kitchen.hpp"
#include "../../include/Engine.hpp"

// # Builder Destructor

Kitchen::Kitchen(Engine *eng)
{
    active = 0;
    engine = eng;
    state = Waiting;
    stock = new Stock();
}

Kitchen::~Kitchen(void)
{
    for (int i = 0; i < cooks.size(); i++)
        if (cooks[i])
            free(cooks[i]);
    cooks.clear();
    if (stock)
        free(stock);
}

// # Private Methods

void Kitchen::pizza_ready(int type)
{
    pizzasCoooked_mutex.lock();
    if (!pizzasCooked.empty() && pizzasCooked.at(0).first == type)
        pizzasCooked.at(0).second++;
    else
        pizzasCooked.insert(pizzasCooked.begin(), { type - 1, 1 } );
    pizzasCoooked_mutex.unlock();
}

bool Kitchen::check_step(void)
{
    int needSteps;
    bool doing = false;

    if (!cooks.size()) {
        active++;
        return (false);
    }
    for (int i = 0; i < cooks.size(); i++) {
        if (!cooks[i]->state)
            continue;
        doing = true;
        needSteps = engine->multiplier * get_pizza_mult(cooks[i]->type);
        cooks[i]->next_step();
        if (cooks[i]->step == needSteps) {
            //std::cout << "Cooks n°" << i << " baked pizza " << cooks[i]->type << " in " << cooks[i]->step << " step(s)." << std::endl;
            cooks[i]->cook_ready(needSteps);
        }
    }
    return (doing);
}

void Kitchen::assign_if_empty(void)
{
    if (!cooks.size())
        return;
    for (int i = 0; i < cooks.size() && pizzasToCook.size() && pizzasToCook.at(0).second; i++) {
        if (cooks[i]->state)
            continue;
        if (!stock->available_for_pizza(pizzasToCook.at(0).first))
            continue;
        pizzasToCook.at(0).second--;
        stock->get_stock_for_pizza(pizzasToCook.at(0).first);
        cooks[i]->assign_work(pizzasToCook.at(0).first);
    }
}

void Kitchen::refresh_stock(void)
{
    stock->update_stock();
}

int Kitchen::get_pizza_mult(int type)
{
    for (int i = 0; i < 4; i++)
        if (type == PizzaRecipeList[i].Type)
            return (PizzaRecipeList[i].Time);
    return (1);
}

void Kitchen::prepare_cooks(void)
{
    for (int i = 0; i < engine->cooks; i++)
        cooks.push_back(new Cooks(this));
}

static void *task(void *kitch)
{
    Kitchen *kitchen = (Kitchen *)kitch;
    int stepRefresh = 0;
    int stepCook = 0;

    while (kitchen->running) {
        // Pizzas queue
        if (!kitchen->pizzasToCook.empty() && kitchen->pizzasToCook.at(0).second <= 0)
            kitchen->pizzasToCook.erase(kitchen->pizzasToCook.begin());
        if (!kitchen->pizzasToCook.empty() && kitchen->pizzasToCook.at(0).second > 0)
            kitchen->assign_if_empty();
        // Wait
        usleep(10000);
        stepCook += 10;
        stepRefresh += 10;
        // Manage time for pizzas ingredient
        if (kitchen->engine->refresh <= stepRefresh) {
            kitchen->refresh_stock();
            stepRefresh = 0;
        }
        // Manage time for pizzas cook, step each 1s
        if (stepCook >= 1000) {
            if (kitchen->check_step())
                kitchen->active = 0;
            else if (kitchen->active <= 5)
                kitchen->active++;
            else
                kitchen->running = false;
                stepCook = 0;
        }
    }
    return (NULL);
}

// # Public Methods

void Kitchen::display_cooks(void)
{
    std::cout << "\tPizza(s) queue: {";
    for (int i = 0; i < pizzasToCook.size(); i++) {
        std::cout << "\n\t\t{ ";
        std::cout << PizzaNames[pizzasToCook[i].first - 1].first;
        std::cout << " units=" << PizzaNames[pizzasToCook[i].first - 1].second;
        std::cout << " }";
    }
    std::cout << std::endl << "\t}" << std::endl;
    
    std::cout << "\tCook(s) (Len=" << cooks.size() << "): {";
    for (int i = 0; i < cooks.size(); i++) {
        std::cout << "\n\t\tCook n°" << i << " { ";
        cooks[i]->display();
        std::cout << " }";
    }
    std::cout << std::endl << "\t}" << std::endl;
}

order_t Kitchen::prepare_order(order_t order)
{
    std::pair<int, int> pair;
    int possiblePizzas = engine->cooks * 2;

    for (int i = 0; i < 4 && possiblePizzas; i++) {
        if (!order.pizzaLeft[i].second)
            continue;
        if (possiblePizzas && possiblePizzas >= order.pizzaLeft[i].second) {
            pair = { order.pizzaLeft[i].first, order.pizzaLeft[i].second };
            possiblePizzas -= order.pizzaLeft[i].second;
            order.pizzaLeft[i].second -= order.pizzaLeft[i].second;
            pizzasToCook.insert(pizzasToCook.begin(), pair);
        } else if (possiblePizzas) {
            pair = { order.pizzaLeft[i].first, possiblePizzas };
            order.pizzaLeft[i].second -= possiblePizzas;
            possiblePizzas = 0;
            pizzasToCook.insert(pizzasToCook.begin(), pair);
        }
    }
    return (order);
}

void Kitchen::start_work(void)
{
    prepare_cooks();
    running = true;
    pthread_create(&this->thread, NULL, task, (void *)this);
    pthread_detach(this->thread);
}

void Kitchen::stop_work(void)
{
    running = false;
}