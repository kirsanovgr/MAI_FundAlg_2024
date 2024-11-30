#include "func.h"

int main() {
    overfprintf(stdout, "Roman numeral of 42: %rO\n", 42);
    overfprintf(stdout, "Fibonacci (3 numbers) in reverse: %Zr\n", 3);
    overfprintf(stdout, "Number in hexadecimal: %C\n", 42, 16);
    overfprintf(stdout, "Memory representation of an int: %mi\n", 42);

    return SUCCESS;
}