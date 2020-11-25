#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "customers.h"
#include "utils.h"

#define MAX_ELEMENT 30

struct CustInfo {
    char *name;
    int index;
};

struct CustomerNode {
    char *name;
    CustomerOrder *order;
    CustomerNode *next;
} *custHead[MAX_ELEMENT], *custTail[MAX_ELEMENT];

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