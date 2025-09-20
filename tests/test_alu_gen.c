#include "alu.h"
#include "log.h"
#include <stdbool.h>


bool isFailing = false;

void alu_add_test() {
	// stores the alu outputs
    OperandFormat format;
    int64_t x = 0;
    format.data = &x;
    int64_t source1;
    int64_t source2;

    // test case 0:
    source1 = 1;
    source2 = 5;
    handle_add_fn(&source1, &source2, &format);
    if (*(int64_t*)format.data != 6) {
        log_trace("alu_add_test test case: 0 failed ❌");
        isFailing = true;
    }
    else{
        log_trace("alu_add_test (test case: 0) passed ✅");
    }

    // test case 1:
    source1 = 100;
    source2 = 300;
    handle_add_fn(&source1, &source2, &format);
    if (*(int64_t*)format.data != 400) {
        log_trace("alu_add_test test case: 1 failed ❌");
        isFailing = true;
    }
    else{
        log_trace("alu_add_test (test case: 1) passed ✅");
    }

    // test case 2:
    source1 = 11231;
    source2 = 120120;
    handle_add_fn(&source1, &source2, &format);
    if (*(int64_t*)format.data != 131351) {
        log_trace("alu_add_test test case: 2 failed ❌");
        isFailing = true;
    }
    else{
        log_trace("alu_add_test (test case: 2) passed ✅");
    }
}


int main(void) {
    alu_add_test();
}
