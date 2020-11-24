#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dish.h"
#include "utils.h"

struct DishNode {
    Dishes *dish;
    DishNode *next, *prev;
} *dishHead, *dishTail, *dishCurr;

void tambahMenuBaru() {
    Dishes *temp_dish = (Dishes*)malloc(sizeof(Dishes));
    temp_dish->name = (char*)malloc(sizeof(char));
    bool break_name = false;
    while (!break_name) {
        printf("Insert the name of the dish [Lowercase letters]: ");
        scanf("%[^\n]", temp_dish->name);
        getchar();
        bool dont_break = false;
        for (int i = 0; temp_dish->name[i] != '\0'; i++) {
            if (temp_dish->name[i] >= 65 && temp_dish->name[i] <= 90) {
                dont_break = true;
            }
        }
        if (!dont_break) {
            break_name = true;
        }
    }

    temp_dish->quantity = 0;
    temp_dish->price = 0;
    while (temp_dish->price < 1000 || temp_dish->price > 50000) {
        printf("Insert the price of the dish [1000..50000]: ");
        scanf("%ld", &temp_dish->price);
        getchar();
    }
    while (temp_dish->quantity < 1 || temp_dish->quantity > 999) {
        printf("Insert the price of the dish [1..999]: ");
        scanf("%d", &temp_dish->quantity);
        getchar();
    }

    DishNode *temp_node = (DishNode*)malloc(sizeof(DishNode));
    temp_node->dish = temp_dish;
    temp_node->next = temp_node->prev = NULL;

    // pushTail()
    if (!dishHead) {
        dishHead = dishTail = temp_node;
    } else {
        dishTail->next = temp_node;
        temp_node->prev = dishTail;
        dishTail = temp_node;
    }
}

void popDishHead() {
    if (dishHead && dishHead == dishTail) {
        dishHead = dishTail = NULL;
        free(dishHead);
    } else {
        DishNode *headC = dishHead->next;
        dishHead->next = headC->prev = NULL;
        free(dishHead);
        dishHead = headC;
    }
}

void popDishTail() {
    if (dishHead && dishHead == dishTail) {
        dishHead = dishTail = NULL;
        free(dishHead);
    } else {
        DishNode *tailC = dishTail->prev;
        dishTail->prev = tailC->next = NULL;
        free(dishTail);
        dishTail = tailC;
    }
}

void printHeader(int longest_name, int extra_count) {
    int max_length = longest_name + 22 + extra_count;
    printalot(' ', (max_length - 11) / 2);
    printf("Bude's Menu");
    printalot(' ', (max_length - 11) / 2, true);
    printalot('=', max_length, true);
    printf("No. ");
    printalot(' ', (longest_name - 4) / 2);
    printf("Name");
    printalot(' ', (longest_name - 4) / 2);
    printf(" Quantity");
    printf("   Price\n");
}

void printDish(Dishes *dish, int menu_pos, int longest_menu) {
    int name_len = strlen(dish->name);
    printf("%d. ", menu_pos + 1);
    int name_diff = longest_menu - name_len;
    printalot(' ', name_diff / 2);
    printf(" %s ", dish->name);
    printf("   %03d    ", dish->quantity);
    if (dish->price >= 10000) {
        printf(" Rp%ld", dish->price);
    } else {
        printf("  Rp%ld", dish->price);
    }
    printf("\n");
}

// An implementation of popMid.
bool searchAndPerformDelete(char *name) {
    if (!dishHead) {
        return false;
    } else if (strcmp(name, dishHead->dish->name) == 0) {
        popDishHead();
        return true;
    } else if (strcmp(name, dishTail->dish->name) == 0) {
        popDishTail();
        return true;
    } else {
        dishCurr = dishHead;

        while (dishCurr && strcmp(name, dishCurr->dish->name) != 0) {
            dishCurr = dishCurr->next;
        }

        // final check to make sure.
        if (strcmp(name, dishCurr->dish->name) != 0) {
            return false;
        }

        dishCurr->prev->next = dishCurr->next;
        dishCurr->next->prev = dishCurr->prev;

        dishCurr->prev = dishCurr->next = NULL;
        free(dishCurr);
        return true;
    }
    return false;
}

void hapusMenu() {
    // print menu
    int menu_cnt = 0;
    dishCurr = dishHead;
    if (!dishCurr) {
        puts("No menu available to be deleted.");
        puts("Press enter to continue...");
        getchar();
        return;
    }

    int longest_name = 0;
    while (dishCurr) {
        int clen = strlen(dishCurr->dish->name);
        if (clen > longest_name) {
            longest_name = clen;
        }
        dishCurr = dishCurr->next;
        menu_cnt++;
    }

    int extra_count = 0;
    if (menu_cnt > 99) {
        do {
            extra_count++;
            menu_cnt /= 10;
        } while (menu_cnt != 0);
        extra_count -= 2;
    }

    menu_cnt = 0;
    dishCurr = dishHead;
    printHeader(longest_name, extra_count);

    while (dishCurr) {
        printDish(dishCurr->dish, menu_cnt, longest_name);
        dishCurr = dishCurr->next;
        menu_cnt++;
    }
    puts("");
    bool is_success = false;
    char *temp_name_hold = (char*)malloc(sizeof(char));
    while (!is_success) {
        printf("Insert dish's name to be deleted: ");
        scanf("%[^\n]", temp_name_hold);
        getchar();
        is_success = searchAndPerformDelete(temp_name_hold);
    }
    puts("The dish has been removed!");
    puts("Press enter to continue...");
    getchar();
    return;
}