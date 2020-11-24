#include <stdio.h>

void printalot(char ch, int amount, bool new_line = false) {
    if (amount <= 0) {
        return;
    }
    for (int i = 0; i < amount; i++) {
        printf("%c", ch);
    }
    if (new_line) {
        printf("\n");
    }
}

unsigned long DJB2(char *str, int MAX_ELEMENT) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % MAX_ELEMENT;
}