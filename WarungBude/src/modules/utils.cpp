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