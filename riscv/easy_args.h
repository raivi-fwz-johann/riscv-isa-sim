#ifndef _EASY_ARGS_H_
#define _EASY_ARGS_H_

#include <stdio.h>

// todo. Remove usage from insn_template.
struct easy_args_t {
  bool vmaskone = false; // vector usage

  bool specify_proc = false; // to be removed

  const char *term_log{nullptr};
  FILE *term_log_file{nullptr};

  ~easy_args_t() {
    if (term_log_file) {
      ::fclose(term_log_file);
    }
  }
};

inline easy_args_t g_easy_args = easy_args_t();

#endif // _EASY_ARGS_H_