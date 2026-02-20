#define NOB_IMPLEMENTATION
#include "nob.h"

#ifdef _WIN32
bool is_windows = true;
#else 
bool is_windows = false;
#endif

typedef struct {
    const char** items;
    size_t capacity;
    size_t count;
} Flags;

int main(int argc, char* argv[]) {
    NOB_GO_REBUILD_URSELF(argc, argv);

    Nob_Cmd cmd = {0};
    Flags flags = {0};

    nob_da_append(&flags, "-std=c++17");
    nob_da_append(&flags, "-g");
    nob_da_append(&flags, "-O0");
    nob_da_append(&flags, "-fstandalone-debug");

    const char* exe = is_windows ? "main.exe" : "main";

    nob_cmd_append(&cmd, "clang++");
    nob_cmd_append(&cmd, "-o");
    nob_cmd_append(&cmd, exe);
    nob_cmd_append(&cmd, "main.cpp");
    nob_da_foreach(const char*, cmd, &flags);

    bool ok = nob_cmd_run_sync_and_reset(&cmd);

    if (!ok) { return 0; }
    nob_cmd_append(&cmd, exe);
    nob_cmd_run_sync_and_reset(&cmd);
}
