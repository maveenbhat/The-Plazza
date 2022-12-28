// # Local Imports

#include "../../include/Engine/Engine_Stock.hpp"
#include "../../include/Engine/Engine_Data.hpp"

// # Builder Destructor

Stock::Stock(void)
{
    for (int i = 0; i < 9; i++) {
        std::pair<int, int> pair = { i, 5};
        products[i] = pair;
    }
}

Stock::~Stock(void) { }

// # Methods

void Stock::display_stock(void)
{
    std::cout << "\tAvailable stock: (Len=9) {\n\t\t";
    for (int i = DOE; i <= CHIEF_LOVE; i++) {
        std::cout << ElemsNames[i].first << ": " << products[i].second << " units; ";
        if (i != 0 && i % 5 == 0) {
            std::cout << std::endl << "\t\t";
        }
    }
    std::cout << std::endl << "\t}" << std::endl;
}

void Stock::update_stock(void)
{
    for (int i = 0; i < 9; i++)
        add_elem(i, 1);
}

int Stock::check_stock(int elem)
{
    if (elem >= 0 && elem <= 8)
        return (products[elem].second);
    else
        return (-1);
}

bool Stock::get_stock_for_pizza(int type)
{
    bool can = true;
    pizzaRecipe_t recipe = { Nil };

    for (int i = 0; PizzaRecipeList[i].Type != Nil; i++)
        if (PizzaRecipeList[i].Type == type) {
            recipe = PizzaRecipeList[i];
            break;
        }
    if (recipe.Type == Nil)
        return (false);
    for (int i = 0; recipe.Elems[i] != EMPTY; i++)
        if (check_stock(recipe.Elems[i]) <= 0)
            can = false;
    if (!can)
        return (false);
    for (int i = 0; recipe.Elems[i] != EMPTY; i++)
        del_elem(recipe.Elems[i], 1);
    return (true);
}

bool Stock::available_for_pizza(int type)
{
    bool can = true;
    pizzaRecipe_t recipe = { Nil };

    for (int i = 0; PizzaRecipeList[i].Type != Nil; i++)
        if (PizzaRecipeList[i].Type == type) {
            recipe = PizzaRecipeList[i];
            break;
        }
    if (recipe.Type == Nil)
        return (false);
    for (int i = 0; recipe.Elems[i] != EMPTY; i++)
        if (check_stock(recipe.Elems[i]) <= 0)
            can = false;
    return (can);
}

void Stock::add_elem(int elem, int qty)
{
    if (elem >= 0 && elem <= 8)
        products[elem].second += qty;
}

void Stock::del_elem(int elem, int qty)
{
    if (elem >= 0 && elem <= 8)
        products[elem].second -= qty;
}