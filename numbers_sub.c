#include "numbers_processor.h"

void process_numbers(NumbersRef numbers) {
    for (int index = 0; index < numbers->count; index++) {
        numbers->items[index] -= 5;
    }
}
