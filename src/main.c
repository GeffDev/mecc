#include "utility.h"

#include "options.h"
#include "lexer.h"

#include <string.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

char **environ;

int main(int argc, char* argv[]) {
    CompilerOptions options = {0};

    if (argv[1] == NULL) {
        printf("no c file provided!\n");
        return 1;
    }
    if (argv[2] != NULL) {
        if (!strcmp(argv[2], "--lex")) {
            options.only_lex = true;
        } else if (!strcmp(argv[2], "--parse")) {
            options.only_parse = true;
        } else if (!strcmp(argv[2], "--codegen")) {
            options.no_codegen = true;
        } else if (!strcmp(argv[2], "--asm")) {
            options.only_asm = true;
        }
    }

    size_t file_len = strlen(argv[1]);

    if (file_len > 256) {
        printf("file name too large! needs to be under 256 chars\n");
        return 1;
    }

    u32 ext_i = 0;
    for (u32 i = 0; i < file_len; i++, ext_i++) {
        if (argv[1][ext_i] == '.') {
            break;
        }
    }

    char preprocessed_file[256] = {0};

    snprintf(preprocessed_file, ext_i + 1, "%s", argv[1]);

    preprocessed_file[ext_i] = '.';
    preprocessed_file[ext_i + 1] = 'i';
    preprocessed_file[ext_i + 2] = '\0';

    char *gcc_args_preprocessor[] = {(char *)"gcc", (char *)"-E", (char *)"-P", argv[1], (char *)"-o", preprocessed_file, (char *)NULL};

    pid_t pid;
    pid = fork();
    switch (pid) {
        case -1:
            printf("oops! forking failed!\n");
            perror("fork");
            return 1;
        case 0:
            // TODO: add config file for gcc executable
            i32 ret = execv("/usr/bin/gcc", gcc_args_preprocessor);
            perror("exec");
            if (ret != -1) {
                return 0;
            } else {
                return 1;
            }
        default:
            i32 status;
            if (waitpid(pid, &status, 0) != -1) {
                 printf("gcc exited with return number %d\n", status);
            } else {
                perror("waitpid");
            }

            if (status != 0) {
                return 1;
            } else {
                break;
            }
    }

    FILE *pp_file = fopen(preprocessed_file, "rb+");
    if (pp_file == NULL) {
        printf("failed to open preprocessed source file!\n");
        return 1;
    }

    tokeniseSource(pp_file);

    // compile preprocessed source, generate asm file

    // assemble, remove assembly file

    return 0;
}