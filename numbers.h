
#ifndef _NUMBERS_H_
#define _NUMBERS_H_

typedef struct {
    int *items;
    int count;
    int capacity;
} Numbers;
typedef Numbers *NumbersRef;

typedef struct {
    char *description;
    void (*run)(NumbersRef);
} OptionItem;

#endif
