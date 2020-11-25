#ifndef MOD_DISH_H
#define MOD_DISH_H

#include "customers.h"

typedef struct Dishes {
    char *name;
    long int price;
    int quantity;
} Dishes;

struct DishNode {
    Dishes *dish;
    DishNode *next, *prev;
};

void tambahMenuBaru();
void hapusMenu();

bool anyAvailableDishes();
Dishes *searchDishes(char *dish_name);
void orderDishes(char *dish_name, int order_amount);

void freeDishesNode();

#endif /* MOD_DISH_H */