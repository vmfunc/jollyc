#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

#define MAX_CMD_LEN 1024

int compile_output(const char* c_file, const char* exe_file) {
    char compile_cmd[MAX_CMD_LEN];
    
    snprintf(compile_cmd, MAX_CMD_LEN, "gcc -Wall -Wextra -o %s %s", exe_file, c_file);
    
    int result = system(compile_cmd);
    if (result != 0) {
        fprintf(stderr, "Compilation failed with error code: %d\n", result);
        return 0;
    }
    
    return 1;
} 