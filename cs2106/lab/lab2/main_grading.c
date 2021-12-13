#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/syscall.h>
#include <unistd.h>

#include "myshell.h"

static void process_commands(FILE *file, const char *eoc);
static bool handle_command(const size_t num_tokens, char ***tokensp);
static size_t tokenise(char *const line, char ***tokens);

static size_t command_count = 0;

// intercept kill to stop people from kill()ing -1
int kill(pid_t pid, int sig) {
  if (pid == -1) {
    errno = EPERM;
    fprintf(stderr, "---------attempted-to-kill-(-1)---------\n");
    return -1;
  }
  return syscall(SYS_kill, pid, sig);
}

int main(int argc, char *argv[]) {
  my_init();
  setlinebuf(stdout);
  setvbuf(stderr, NULL, _IONBF, 0);
  process_commands(stdin, argc >= 2 ? argv[1] : NULL);
  my_quit();
  return 0;
}

static void process_commands(FILE *file, const char *eoc) {
  char *line = NULL;
  size_t line_size = 0;
  while (1) {
    if (eoc) {
      setvbuf(stderr, NULL, _IONBF, 0);
      fprintf(stderr, "\n----------%s-%zu-BEGIN----------\n", eoc, command_count);
    }
    if (getline(&line, &line_size, file) == -1) {
      if (feof(file)) {
        printf("End of commands; shutting down\n");
      } else {
        perror("Error while reading command; shutting down");
      }
      break;
    }
    char **tokens = NULL;
    size_t num_tokens = tokenise(line, &tokens);
    if (!tokens) {
      printf("Failed to tokenise command\n");
      exit(1);
    }

    handle_command(num_tokens, &tokens);
    if (eoc) {
      setvbuf(stderr, NULL, _IONBF, 0);
      fprintf(stderr, "\n----------%s-%zu-END----------\n", eoc, command_count);
    }
    command_count++;
    free(tokens);
  }

  if (line) {
    free(line);
  }

  if (ferror(file)) {
    perror("Failed to read line");
    exit(1);
  }
}

#define CHECK_ARGC(nargs)                                                                          \
  do {                                                                                             \
    if (num_tokens < nargs) {                                                                      \
      printf("Insufficient arguments for %s\n", cmd);                                              \
      return false;                                                                                \
    }                                                                                              \
  } while (0)

#define SCAN_SERVICE_NUMBER(into)                                                                  \
  do {                                                                                             \
    if (sscanf((*tokensp)[1], "%zu", &into) != 1) {                                                \
      printf("Invalid service number %s\n", (*tokensp)[1]);                                        \
      return false;                                                                                \
    }                                                                                              \
  } while (0)

static bool handle_command(const size_t num_tokens, char ***tokensp) {
  const char *const cmd = (*tokensp)[0];
  if (!cmd) {
    // no-op
  } else if (strcmp(cmd, "quit") == 0) {
    my_quit();
    return true;
  } else {
    *tokensp = realloc(*tokensp, (num_tokens + 1) * sizeof(char *));
    (*tokensp)[num_tokens] = NULL;
    my_process_command(num_tokens + 1, *tokensp);
  }

  return false;
}

static size_t tokenise(char *const line, char ***tokens) {
  size_t reg_argv_buf_index = 0;
  size_t ret_argv_nmemb = 8;
  size_t ret_argv_index = 0;
  char **ret = calloc(ret_argv_nmemb, sizeof(char *));
  if (!ret) {
    goto fail;
  }

  bool last_was_tok = false;
  while (1) {
    char *const cur = line + reg_argv_buf_index;
    if (*cur == '\0') {
      // if we've hit the end of the line, break
      break;
    } else if (isspace(*cur)) {
      // this is whitespace; if the the last character was part of a token,
      // write a null byte here to terminate the last token
      if (last_was_tok) {
        *cur = '\0';
      }
      last_was_tok = false;
    } else {
      // this is not whitespace (so part of a token)
      // if the previous character was not part of a token (start of line or
      // whitespace), then add this to the result
      if (!last_was_tok) {
        // + 1 for the NULL at the end
        if (ret_argv_index + 1 >= ret_argv_nmemb) {
          // our result array is full, resize it
          ret_argv_nmemb += 8;
          ret = realloc(ret, ret_argv_nmemb * sizeof(char *));
          if (!ret) {
            goto fail;
          }
        }
        ret[ret_argv_index++] = cur;
      }
      last_was_tok = true;
    }
    reg_argv_buf_index++;
  }

  // NULL-terminate the result array
  ret[ret_argv_index] = NULL;
  *tokens = ret;
  return ret_argv_index;

  // N.B. goto is idiomatic for error-handling in C
fail:
  if (ret) {
    free(ret);
  }
  *tokens = NULL;
  return 0;
}
