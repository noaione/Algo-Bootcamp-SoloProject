#include <stdio.h>
#include "../controllers/controllers.h"

int main() {
    char name[255];
    int dd, yyyy;
    char mm[10];
    int total, cures;
    scanf("%d %d", &total, &cures);
    for (int i = 0; i < total; i++) {
        scanf("%d %s %d - %[^\n]", &dd, mm, &yyyy, name);
        getchar();
        addNewPatients((char*)name, dd, (char*)mm, yyyy);
    }
    // printExistingPatients();
    int copy_of_cures = cures;
    int cured_patient = 0;
    if (total == cures) {
        for (int i = 0; i < cures; i++) {
            removePatient();
            copy_of_cures--;
            cured_patient++;
        }
    } else if (total > cures) {
        for (int i = 0; i < cures; i++) {
            removePatient();
            copy_of_cures--;
            cured_patient++;
        }
    } else if (cures > total) {
        for (int i = 0; i < total; i++) {
            removePatient();
            copy_of_cures--;
            cured_patient++;
        }
    }
    if (total > cured_patient) {
        printf("Need %d more cure\n", total - cured_patient);
        printExistingPatients();
    } else {
        printf("All patients get the cure, %d cure left", copy_of_cures);
    }
    return 0;
}