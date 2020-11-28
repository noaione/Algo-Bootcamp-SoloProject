#ifndef MTE_MODELS_H
#define MTE_MODELS_H

struct PatientNode {
    char name[255];
    int yyyy;
    int mm;
    char mms[10];
    int dd;
    long long int secs;
    PatientNode *prev, *next;
};

#endif