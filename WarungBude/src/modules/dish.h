#ifndef MOD_DISH_H
#define MOD_DISH_H

typedef struct Dishes {
    char *name;
    long int price;
    int quantity;
} Dishes;

void tambahMenuBaru();
void hapusMenu();

void freeDishesNode();

#endif /* MOD_DISH_H */