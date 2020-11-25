#ifndef MOD_DISH_H
#define MOD_DISH_H

typedef struct Dishes {
    char *name;
    long int price;
    int quantity;
} Dishes;

void tambahMenuBaru();
void hapusMenu();

Dishes *searchDishes(char *dish_name);
void orderDishes(char *dish_name, int order_amount);

void freeDishesNode();

#endif /* MOD_DISH_H */