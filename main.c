#include<stdio.h>

#define ARRAY_SIZE 10

int main(void)
{
    char string[] = "hello!";
    printf("%s\n", string);

    for (int index = 0; index < 6; index++) {
        char current_char = string[index];
        if (current_char >= 'a' && current_char <= 'z') {
            current_char -= 32;
        }
        printf("string[%d] = %c (%d)\n", index, current_char, current_char);
    }

    return 0;
    // const int ARRAY_SIZE = 5;
    int numbers[ARRAY_SIZE] = {0};
    int number_count = 0;

    numbers[number_count++] = 10;
    // number_count == 1
    numbers[number_count++] = 30;
    numbers[number_count++] = 50;
    for (int index = 0; index < number_count; index++) {
        printf("numbers[%d] = %d\n", index, numbers[index]);
    }

    printf("\n");
    number_count--;
    number_count--;
    for (int index = 0; index < number_count; index++) {
        printf("numbers[%d] = %d\n", index, numbers[index]);
    }

    printf("\n");
}
