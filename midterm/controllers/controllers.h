#ifndef MTE_CONTROLLER_H
#define MTE_CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../models/models.h"

PatientNode *head, *tail;

int parseMonth(char *month) {
    if (strcasecmp(month, "january") == 0) {
        return 1;
    } else if (strcasecmp(month, "february") == 0) {
        return 2;
    } else if (strcasecmp(month, "march") == 0) {
        return 3;
    } else if (strcasecmp(month, "april") == 0) {
        return 4;
    } else if (strcasecmp(month, "may") == 0) {
        return 5;
    } else if (strcasecmp(month, "june") == 0) {
        return 6;
    } else if (strcasecmp(month, "july") == 0) {
        return 7;
    } else if (strcasecmp(month, "august") == 0) {
        return 8;
    } else if (strcasecmp(month, "september") == 0) {
        return 9;
    } else if (strcasecmp(month, "october") == 0) {
        return 10;
    } else if (strcasecmp(month, "november") == 0) {
        return 11;
    } else if (strcasecmp(month, "december") == 0) {
        return 12;
    }
}

bool determineLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } else {
        return false;
    }
}

int determineTotalDays(int month) {
    if (month == 2) {
        return 28; // ignore leap year
    }
    if (month >= 1 && month <= 7) {
        if (month % 2 == 0) {
            return 30;
        } else {
            return 31;
        }
    } else if (month >= 8 && month <= 12) {
        if (month % 2 == 0) {
            return 31;
        } else {
            return 30;
        }
    }
}

int countTotalDaysForMonth(int month) {
    int total_days = 0;
    for (int i = 1; i <= month; i++) {
        total_days += determineTotalDays(i);
    }
    return total_days;
}

PatientNode *createNewPatient(char *name, int dd, char *mm, int yyyy) {
    PatientNode *temp = (PatientNode*)malloc(sizeof(PatientNode));
    strcpy(temp->name, name);
    temp->dd = dd;
    strcpy(temp->mms, mm);
    temp->mm = parseMonth(mm);
    temp->yyyy = yyyy;
    long long int totalSecPassedDays = 0;
    if (temp->mm == 1) {
        totalSecPassedDays += (temp->dd) * 86400;
    } else {
        bool isLeap = determineLeapYear(yyyy);
        int totalMonthDays = countTotalDaysForMonth(temp->mm);
        if (isLeap) {
            totalMonthDays++;
        }
        int currentMonthDays = determineTotalDays(temp->mm);
        int diffMonthDaysAndCurrentDay = currentMonthDays - dd;
        totalMonthDays -= diffMonthDaysAndCurrentDay;
        totalSecPassedDays = totalMonthDays * 86400;
    }
    int tempYear = yyyy - 1;
    if (tempYear >= 0) {
        for (int i = 0; i < tempYear; i++) {
            bool leap = determineLeapYear(yyyy);
            if (leap) {
                totalSecPassedDays += 366 * 86400;
            } else {
                totalSecPassedDays += 365 * 86400;
            }
        }
    }
    temp->secs = totalSecPassedDays;
    temp->prev = temp->next = NULL;
    return temp;
}

void addNewPatients(char *name, int dd, char *mm, int yyyy) {
    PatientNode *patient = createNewPatient(name, dd, mm, yyyy);
    if (!head) {
        head = tail = patient;
    } else if (patient->secs < head->secs) {
        head->prev = patient;
        patient->next = head;
        head = patient;
    } else if (patient->secs > tail->secs) {
        patient->prev = tail;
        tail->next = patient;
        tail = patient;
    } else {
        // 50, 40, 30, 20, 10
        PatientNode *curr = head;
        // 35
        while (curr && patient->secs > curr->secs) {
            curr = curr->next;
        }

        patient->prev = curr->prev;
        patient->next = curr;
        curr->prev->next = patient;
        curr->prev = patient;
    }
}

// popHead()
void removePatient() {
    if (head && head == tail) {
        head = tail = NULL;
        free(head);
    } else {
        PatientNode *newPoint = head->next;
        head->next = newPoint->prev = NULL;
        free(head);
        head = newPoint;
    }
}

void printExistingPatients() {
    PatientNode *curr = head;
    if (!curr) {
        return;
    } else {
        while (curr) {
            printf("%d %s %d - %s\n", curr->dd, curr->mms, curr->yyyy, curr->name);
            curr = curr->next;
        }
    }
}

#endif