/**
 * CS2106 AY21/22 Semester 1 - Lab 2
 *
 * This file contains function definitions. Your implementation should go in
 * this file.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include "myshell.h"

typedef enum STATUS {
    INVALID = 0,
    RUNNING = 1,
    EXITED = 2,
    TERMINATING = 3,
    STOPPED = 4
} status;

static const char *STATUS_STRINGS[] = {"Invalid", "Running", "Exited", "Terminating", "Stopped"};

typedef struct PROCESS {
    pid_t pid;
    status status;
    int result;
} process;

static pid_t waiting_process;
static process *processes[MAX_PROCESSES];
static int num_process;

// Function declarations
static void my_stop_handler(int signo);
static void my_interrupt_handler(int signo);
static void my_info();
static void my_wait();
static void my_terminate();
static void my_fg();
static void my_run_program();

static void my_stop_handler(int signo) {
    (void) signo;
    if (waiting_process != -1) {
        killpg(waiting_process, SIGTSTP);
    }
}

static void my_interrupt_handler(int signo) {
    (void) signo;
    if (waiting_process != -1) {
        killpg(waiting_process, SIGINT);
    }
}

void my_init(void) {
    // Initialize what you need here
    if (signal(SIGTSTP, my_stop_handler) == SIG_ERR) {
        printf("Failed to attach stop handler");
    }
    if (signal(SIGINT, my_interrupt_handler) == SIG_ERR) {
        printf("Failed to attach interrupt handler");
    }
    num_process = 0;
    waiting_process = -1;
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        processes[i] = (process *)malloc(sizeof(process));
        processes[i]->pid = 0;
        processes[i]->status = INVALID;
        processes[i]->result = -1;
    }
}

static void my_info() {
    // Perform non-blocking wait
    for (int i = 0; i < num_process; ++i) {
        // Only do wait on RUNNING or TERMINATING processes in case of pid reuse
        if (processes[i]->status == RUNNING || processes[i]->status == TERMINATING) {
            int child_result;
            if (waitpid(processes[i]->pid, &child_result, WNOHANG) > 0) {
                processes[i]->result = child_result;
                processes[i]->status = EXITED;
            }
        }
    }
    // Print status of all processes
    for (int i = 0; i < num_process; ++i) {
        printf("[%i] %s", processes[i]->pid, STATUS_STRINGS[processes[i]->status]);
        // A process has a result iff it has exited
        if (processes[i]->status == EXITED) {
            printf(" %i", WEXITSTATUS(processes[i]->result));
        }
        printf("\n");
    }
}

static void my_wait(pid_t pid_to_wait) {
    for (int i = 0; i < num_process; ++i) {
        // Only do wait on RUNNING or TERMINATING processes in case of pid reuse
        if ((processes[i]->status == RUNNING || processes[i]->status == TERMINATING) && processes[i]->pid == pid_to_wait) {
            waiting_process = pid_to_wait;
            int child_result;
            waitpid(pid_to_wait, &child_result, WUNTRACED);
            waiting_process = -1;
            if (processes[i]->status == TERMINATING) {
                processes[i]->status = EXITED;
                processes[i]->result = child_result;
            } else if (WIFSTOPPED(child_result)) {
                processes[i]->status = STOPPED;
                printf("\n[%i] stopped\n", pid_to_wait);
            } else if (WIFSIGNALED(child_result)) {
                processes[i]->status = EXITED;
                processes[i]->result = child_result;
                printf("\n[%i] interrupted\n", pid_to_wait);
            } else {
                processes[i]->status = EXITED;
                processes[i]->result = child_result;
            }
        }
    }
}

static void my_terminate(pid_t pid_to_terminate) {
    for (int i = 0; i < num_process; ++i) {
        if (processes[i]->status == RUNNING && processes[i]->pid == pid_to_terminate) {
            killpg(pid_to_terminate, SIGTERM);
            processes[i]->status = TERMINATING;
        }
    }
}

static void my_fg(pid_t pid_to_fg) {
    for (int i = 0; i < num_process; ++i) {
        if (processes[i]->status == STOPPED && processes[i]->pid == pid_to_fg) {
            killpg(pid_to_fg, SIGCONT);

            waiting_process = pid_to_fg;
            int result;
            waitpid(pid_to_fg, &result, WUNTRACED);
            waiting_process = -1;
            if (WIFSTOPPED(result)) {
                processes[i]->status = STOPPED;
                printf("\n[%i] stopped\n", pid_to_fg);
            } else if (WIFSIGNALED(result)) {
                processes[i]->status = EXITED;
                processes[i]->result = result;
                printf("\n[%i] interrupted\n", pid_to_fg);
            } else {
                processes[i]->status = EXITED;
                processes[i]->result = result;
            }
        }
    }
}

static void my_run_program(size_t num_tokens, char **tokens) {
    bool run_in_bg = false;
    // Check if we need to run the program in the background
    if (num_tokens >= 3 && strcmp(tokens[num_tokens - 2], "&") == 0) {
        run_in_bg = true;
        // Set the ampersand to NULL so that we don't pass it into execv
        tokens[num_tokens - 2] = NULL;
        // Treat our array as if it's of length num_tokens - 1
        --num_tokens;
    }
    char *redirect_in = NULL;
    char *redirect_out = NULL;
    char *redirect_err = NULL;
    size_t s_index = 0;
    for (size_t index = 0; index < num_tokens; ++index) {
        // We've reached the end of a command
        if (index == num_tokens - 1 || strcmp(tokens[index], "&&") == 0) {
            /**
            * We perform file existence checks here before fork and exec due to the specifications
            * in our writeup. In real usage, this might cause problems like ToCToU.
            *
            * A better practice would be to leave it to the syscalls (open/exec) and check the error
            * codes returned (if any).
            */

            struct stat statbuf;
            int status = stat(tokens[s_index], &statbuf);
            // Check if program does not exist or if program is not a regular file
            if (status == -1 || !S_ISREG(statbuf.st_mode)) {
                printf("%s not found\n", tokens[s_index]);
                break;
            }

            // Check if redirect_in file exists
            if (redirect_in != NULL && access(redirect_in, F_OK) != 0) {
                printf("%s does not exist\n", redirect_in);
                break;
            }

            pid_t child_pid = fork();
            if (child_pid == 0) {
                // For signal handling
                setpgid(0, 0);

                // Check if there's redirections
                bool has_redirection = false;
                if (redirect_in != NULL) {
                    has_redirection = true;
                    int fd = open(redirect_in, O_RDONLY);
                    dup2(fd, fileno(stdin));
                    close(fd);
                }
                if (redirect_out != NULL) {
                    has_redirection = true;
                    int fd = open(redirect_out, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                    dup2(fd, fileno(stdout));
                    close(fd);
                }
                if (redirect_err != NULL) {
                    has_redirection = true;
                    int fd = open(redirect_err, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                    dup2(fd, fileno(stderr));
                    close(fd);
                }

                size_t e_index = index;
                if (has_redirection) {
                    e_index = s_index;
                    while (strcmp(tokens[e_index], "<") != 0 && strcmp(tokens[e_index], ">") != 0 && strcmp(tokens[e_index], "2>") != 0) {
                        ++e_index;
                    }
                }

                // No need to free this as malloc-ed data will just be replaced after execv
                char **args = (char **)malloc((e_index - s_index + 1) * sizeof(*tokens));
                memcpy(args, &tokens[s_index], (e_index - s_index + 1) * sizeof(*tokens));
                args[e_index - s_index] = NULL;

                execv(tokens[s_index], args);

                // Just in case execv fails
                free(args);
                exit(1);
            }
            if (run_in_bg) {
                process *p = processes[num_process++];
                p->status = RUNNING;
                p->pid = child_pid;
                printf("Child[%i] in background\n", child_pid);
            } else {
                waiting_process = child_pid;
                int child_result;
                waitpid(child_pid, &child_result, WUNTRACED);
                waiting_process = -1;
                process *p = processes[num_process++];
                p->pid = child_pid;
                if (WIFSTOPPED(child_result)) {
                    p->status = STOPPED;
                    printf("\n[%i] stopped\n", child_pid);
                    break;
                } else if (WIFSIGNALED(child_result)) {
                    p->status = EXITED;
                    p->result = child_result;
                    printf("\n[%i] interrupted\n", child_pid);
                } else {
                    p->status = EXITED;
                    p->result = child_result;
                }
                if (!WIFSTOPPED(child_result) && WEXITSTATUS(child_result) != 0 && index != num_tokens - 1) {
                    printf("%s failed\n", tokens[s_index]);
                    break;
                }
            }
            s_index = index + 1;
            redirect_in = NULL;
            redirect_out = NULL;
            redirect_err = NULL;
        } else if (strcmp(tokens[index], "<") == 0) {
            redirect_in = tokens[++index];
        } else if (strcmp(tokens[index], ">") == 0) {
            redirect_out = tokens[++index];
        } else if (strcmp(tokens[index], "2>") == 0) {
            redirect_err = tokens[++index];
        }
    }
}

void my_process_command(size_t num_tokens, char **tokens) {
    if (num_tokens == 0) {
        return;  // no-op
    }
    char *cmd = tokens[0];
    if (strcmp(cmd, "info") == 0) {
        my_info();
    } else if (strcmp(cmd, "wait") == 0 || strcmp(cmd, "terminate") == 0 || strcmp(cmd, "fg") == 0) {
        // num_tokens includes NULL, thus we need to minus one
        if (num_tokens - 1 != 2) {
            printf("Malformed %s command\n", cmd);
            return;
        }

        pid_t input_pid = atoi(tokens[1]);
        if (strcmp(cmd, "wait") == 0) {
            my_wait(input_pid);
        } else if (strcmp(cmd, "terminate") == 0) {
            my_terminate(input_pid);
        } else {
            my_fg(input_pid);
        }
    } else {
        my_run_program(num_tokens, tokens);
    }
}

void my_quit(void) {
    // Clean up function, called after "quit" is run

    // Send SIGTERM to all processes that have not exited
    for (int i = 0; i < num_process; ++i) {
        if (processes[i]->status == RUNNING || processes[i]->status == TERMINATING || processes[i]->status == STOPPED) {
            // Send SIGCONT to stopped processes first
            if (processes[i]->status == STOPPED) {
                killpg(processes[i]->pid, SIGCONT);
            }
            killpg(processes[i]->pid, SIGTERM);
        }
    }

    // Wait for all processes that we have sent SIGTERM to
    for (int i = 0; i < num_process; ++i) {
        if (processes[i]->status == RUNNING || processes[i]->status == TERMINATING || processes[i]->status == STOPPED) {
            waitpid(processes[i]->pid, NULL, 0);
        }
    }

    for (int i = 0; i < MAX_PROCESSES; ++i) {
        free(processes[i]);
    }
    printf("Goodbye!\n");
}
