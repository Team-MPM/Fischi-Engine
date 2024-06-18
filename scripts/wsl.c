#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_help() {
    printf("Usage: program <command> [options]\n");
    printf("Commands:\n");
    printf("  build      Build the project\n");
    printf("  run <exe>  Run the specified executable\n");
    printf("  help       Display this help message\n");
    printf("Options:\n");
    printf("  -t config  Set the configuration for the build (default: debug)\n");
}

int main(int argc, char *argv[]) {
    const char *config = "debug";  // Default config
    const char *platform = "linux-x86_64";  // Platform

    if (argc < 2) {
        print_help();
        return 1;
    }

    if (strcmp(argv[1], "help") == 0) {
        print_help();
        return 0;
    } else if (strcmp(argv[1], "build") == 0) {
        // Check for optional configuration flag
        if (argc == 4 && strcmp(argv[2], "-t") == 0) {
            config = argv[3];
        } else if (argc != 2) {
            print_help();
            return 1;
        }

        printf("Generating project files\n");
        system("./dependencies/premake/linux/premake5 gmake2");

        printf("Building project with config: %s\n", config);
        char build_command[256];
        snprintf(build_command, sizeof(build_command), "make config=%s all", config);
        system(build_command);

        return 0;
    } else if (strcmp(argv[1], "run") == 0) {
        if (argc != 3) {
            print_help();
            return 1;
        }

        const char *executable = argv[2];
        printf("Running the executable: %s\n", executable);
        char run_command[512];
        snprintf(run_command, sizeof(run_command), "./bin/%s-%s/%s", config, platform, executable);
        system(run_command);

        return 0;
    } else {
        print_help();
        return 1;
    }
}
