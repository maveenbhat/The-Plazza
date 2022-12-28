#include "../../include/Engine/Engine_Data.hpp"
#include "../../include/Engine/Engine_Cooks.hpp"
#include "../../include/Engine/Engine_Kitchen.hpp"

// # Builder Destructor

Cooks::Cooks(Kitchen *kitch)
{
    kitchen = kitch;
    state = 0;
    type = -1;
    step = -1;
}

Cooks::~Cooks(void) { }

// # Public Methods

void Cooks::display()
{
    if (state == Sleeping)
        std::cout << "Waiting";
    else {
        int remain = kitchen->get_pizza_mult(type) - step;
        std::cout << "Cooking a " << PizzaNames[type - 1].first << ", Remain=" << remain << "s, Elapsed=" << step << "s";
    }
}

void Cooks::assign_work(int _type)
{
    type = _type;
    state = Cooking;
    step = 0;
}

void Cooks::next_step(void)
{
    step++;
}

void Cooks::cook_ready(int mult)
{
    kitchen->pizza_ready(type);
    step = 0;
    type = -1;
    state = 0;
}