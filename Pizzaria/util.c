#include <stdio.h>
#include "util.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
