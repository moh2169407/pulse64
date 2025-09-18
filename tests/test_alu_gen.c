#include "alu.h"
#include "log.h"
#include <stdbool.h>


bool isFailing = false;

void alu_add_test() {
    // stores the alu outputs
    OperandFormat format;
    int x = 0;
    format.data = &x;
    int source1;
    int source2;

    source1 = 1;
    source2 = 5;
    handle_add_fn(&source1, &source2, &format);

    source1 = 100;
    source2 = 300;
    handle_add_fn(&source1, &source2, &format);

    source1 = 11231;
    source2 = 120120;
    handle_add_fn(&source1, &source2, &format);
}


int main(void) {
    alu_add_test();
}
