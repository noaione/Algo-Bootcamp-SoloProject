#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "customers.h"
#include "utils.h"
#include "dish.h"

#define MAX_ELEMENT 30

struct CustInfo {
    char *name;
    int index;
};

struct OrderData {
    char *name;
    long int amount;
};

CustomerNode *custHead[MAX_ELEMENT], *custTail[MAX_ELEMENT];

bool isThereSpace(char *temp) {
    int len = strlen(temp);
    for (int i = 0; i < len; i++) {
        if (temp[i] == 32) {
            return true;
        }
    }
    return false;
}

void buatPelangganBaru() {
    CustomerNode *temp = (CustomerNode*)malloc(sizeof(CustomerNode));
    temp->name = (char*)malloc(sizeof(char));
    temp->order = NULL;
    temp->next = NULL;

    bool is_space = true;
    while (is_space) {
        printf("Insert the customer's name [Without space]: ");
        scanf("%[^\n]", temp->name);
        getchar();
        is_space = isThereSpace(temp->name);
    }

    int index = DJB2(temp->name, MAX_ELEMENT);

    if (custHead[index]) {
        custTail[index]->next = temp;
        custTail[index] = temp;
    } else {
        custHead[index] = custTail[index] = temp;
    }

    puts("");
    puts("Customer has been added!");
    puts("Press enter to continue...");
    getchar();
}

CustInfo *searchCustomerData(char *target_name) {
    for (int i = 0; i < MAX_ELEMENT; i++) {
        if (custHead[i]) {
            CustomerNode *curr = custHead[i];
            while (curr) {
                if (strcmp(target_name, curr->name) == 0) {
                    CustInfo *info = (CustInfo*)malloc(sizeof(info));
                    strcpy(info->name, curr->name);
                    info->index = i;
                    return info;
                }
                curr = curr->next;
            }
        }
    }
    return NULL;
}

void lihatSeluruhDataPelanggan() {
    puts("Customer’s List");
    for (int i = 0; i < MAX_ELEMENT; i++) {
        if (custHead[i]) {
            CustomerNode *curr = custHead[i];
            while (curr) {
                printf("%d. %s\n", i, curr->name);
                curr = curr->next;
            }
        }
    }
    puts("");
    puts("Press enter to continue...");
    getchar();
}

void cariDataPelanggan() {
    bool any_space = true;
    char *search_name = (char*)malloc(sizeof(char));
    while (any_space) {
        printf("Insert the customer’s name to be searched: ");
        scanf("%[^\n]", search_name);
        getchar();
        any_space = isThereSpace(search_name);
    }

    CustInfo *search_res = searchCustomerData(search_name);
    if (!search_res) {
        printf("%s is not present.\n", search_name);
    } else {
        printf("%s is present with customer's ID %d\n", search_res->name, search_res->index);
        free(search_res);
    }
    free(search_name);
    puts("Press enter to continue...");
    getchar();
}

bool anyAddedCustomers() {
    bool any_user = false;
    for (int i = 0; i < MAX_ELEMENT; i++) {
        if (custHead[i]) {
            CustomerNode *curr = custHead[i];
            while (curr) {
                any_user = true;
                curr = curr->next;
            }
            if (any_user) {
                return any_user;
            }
        }
    }
    return any_user;
}

bool isNumber(char ch) {
    if (ch >= '0' && ch <= '9') {
        return true;
    }
    return false;
}

bool isAllNumber(char *strg) {
    int len = strlen(strg);
    for (int i = 0; i < len; i++) {
        if (!isNumber(strg[i])) {
            printf("%c\n", strg[i]);
            return false;
        }
    }
    return true;
}

// A scuffed way to parse the order format
// format: dish_name xAMOUNT
// not so much error checking because I'm lazy :^)
OrderData *parseOrderInfo(char *text_data) {
    OrderData *order = (OrderData*)malloc(sizeof(OrderData));
    order->name = (char*)malloc(sizeof(char));
    char *amount = (char*)malloc(sizeof(char));
    int len = strlen(text_data);
    int valid_num = 0; // used to add null terminator
    int valid_name_len = 0; // used to add null terminator
    for (int i = 0; i < len; i++) {
        if (text_data[i] == ' ' && text_data[i + 1] == 'x' && isNumber(text_data[i + 2])) {
            int min_num = i + 2;
            for (int j = i + 2; j < len; j++) {
                if (isNumber(text_data[j])) {
                    amount[j - min_num] = text_data[j];
                    valid_num++;
                }
            }
            break;
        } else {
            order->name[i] = text_data[i];
            valid_name_len++;
        }
    }
    order->name[valid_name_len] = '\0';
    amount[valid_num] = '\0';
    order->amount = 0;
    if (strlen(amount) < 1) {
        return order;
    }
    if (!isAllNumber(amount)) {
        // just fail immediatly, I'm too lazy to proper check it.
        return order;
    }
    sscanf(amount, "%ld", &order->amount);
    return order;
}

void iterAndAddOrder(CustomerOrder *mainHead, CustomerOrder *temp_node) {
    CustomerOrder *curr = mainHead;
    CustomerOrder *lastKnown = NULL;
    while (curr) {
        lastKnown = curr;
        curr = curr->next;
    }
    lastKnown->next = temp_node;
}

void addNewOrderData(char *user_name, int user_id, Dishes *dish_data, int order_amount) {
    CustomerNode *curr = custHead[user_id];
    while (curr) {
        if (strcmp(user_name, curr->name) == 0) {
            CustomerOrder *temp_node = (CustomerOrder*)malloc(sizeof(CustomerOrder));
            temp_node->name = dish_data->name;
            temp_node->price_per_quantity = dish_data->price;
            temp_node->quantity = order_amount;
            temp_node->next = NULL;
            if (!curr->order) {
                curr->order = temp_node;
            } else {
                CustomerOrder *mainHead = curr->order;
                iterAndAddOrder(curr->order, temp_node);
            }
            return;
        }
        curr = curr->next;
    }
}

void buatOrderanBaru() {
    if (!anyAddedCustomers()) {
        puts("There's no customers currently...");
        puts("Press enter to continue...");
        getchar();
        return;
    }
    char *user_name;
    user_name = (char*)malloc(sizeof(char));
    int user_id;

    bool is_found = false;
    int total_order;
    char *find_name;
    find_name = (char*)malloc(sizeof(char));
    while (!is_found) {
        printf("Insert the customer’s name: ");
        scanf("%[^\n]", find_name);
        getchar();
        if (!isThereSpace(find_name)) {
            CustInfo *user_info = searchCustomerData(find_name);
            if (user_info) {
                user_name = user_info->name;
                // strcpy(user_name, user_info->name);
                user_id = user_info->index;
                is_found = true;
            }
        }
    }
    free(find_name);
    printf("Insert the amount of dish: ");
    scanf("%d", &total_order);
    getchar();

    char *order_string_unfmt;
    order_string_unfmt = (char*)malloc(sizeof(char));
    for (int i = 0; i < total_order; i++) {
        bool should_continue = false;
        while (!should_continue) {
            printf("[%d] Insert the dish’s name and quantity: ", i + 1);
            scanf("%[^\n]", order_string_unfmt);
            getchar();
            OrderData *ordered = parseOrderInfo(order_string_unfmt);
            if (ordered->amount > 0) {
                Dishes *dish_data = searchDishes(ordered->name);
                if (dish_data) {
                    if (ordered->amount <= dish_data->quantity) {
                        addNewOrderData(user_name, user_id, dish_data, ordered->amount);
                        orderDishes(ordered->name, ordered->amount);
                        should_continue = true;
                    }
                }
            }
        }
    }
    CustomerNode *currChain = custHead[user_id];
    while (currChain && strcmp(currChain->name, user_name)) {
        currChain = currChain->next;
    }

    free(order_string_unfmt);
    puts("Order success!");
    puts("Press enter to continue...");
    getchar();
}

void removeUserFromHashTable(int user_id, char *user_name) {
    if (custHead[user_id]) {
        CustomerNode *curr = custHead[user_id];
        int total_user = 0;
        CustomerNode *prevKnown = curr;
        while (curr && strcmp(curr->name, user_name) != 0) {
            total_user++;
            prevKnown = curr;
            curr = curr->next;
        }
        if (!curr) {
            return;
        }
        if (total_user < 1) {
            custHead[user_id] = custTail[user_id] = NULL;
        } else {
            prevKnown->next = curr->next; // cut away
            free(curr->order);
            free(curr);
        }
    }
}

void lakukanPembayaran() {
    if (!anyAddedCustomers()) {
        puts("There's no customers currently...");
        puts("Press enter to continue...");
        getchar();
        return;
    }

    int indexer = -1;
    while (indexer < 0 || indexer > MAX_ELEMENT) {
        printf("Insert the customer’s index: ");
        scanf("%d", &indexer);
        getchar();
    }

    puts("");
    if (!custHead[indexer]) {
        puts("There's no order for that customer's ID");
        puts("Press enter to continue...");
        getchar();
        return;
    }

    CustomerNode *currCustChain = custHead[indexer];
    while (currCustChain && !currCustChain->order) {
        currCustChain = currCustChain->next;
    }

    if (!currCustChain) {
        puts("There's no order for that customer's ID");
        puts("Press enter to continue...");
        getchar();
        return;
    }
    if (!currCustChain->order) {
        puts("There's no order for that customer's ID");
        puts("Press enter to continue...");
        getchar();
        return;
    }
    
    printf("%s\n", currCustChain->name);
    long long int total_price = 0;
    CustomerOrder *custOrder = currCustChain->order;
    int cntOrder = 0;
    while (custOrder) {
        printf("[%d] %s x%d\n", cntOrder + 1, custOrder->name, custOrder->quantity);
        total_price += (custOrder->price_per_quantity * custOrder->quantity);
        cntOrder++;
        custOrder = custOrder->next;
    }
    removeUserFromHashTable(indexer, currCustChain->name);
    printf("Total: Rp%lld\n", total_price);
    puts("Press enter to continue...");
    getchar();
}

void freeCustomerNode() {
    for (int i = 0; i < MAX_ELEMENT; i++) {
        if (custHead[i]) {
            CustomerNode *curr = custHead[i];
            while (curr) {
                free(curr->order);
                CustomerNode *nextAddr = curr->next;
                free(curr);
                curr = nextAddr;
            }
        }
    }
    // free(custHead);
    // free(custTail);
}