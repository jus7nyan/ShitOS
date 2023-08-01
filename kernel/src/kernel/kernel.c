#include "print.h"


void prnt_check(){
    char* mytest = "XYN";
    print_clear();
    print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLACK);
    print_str(mytest);
}

void kernel_main() {
    prnt_check();
}