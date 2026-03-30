/**
 * @file option_configure_ext.cc
 * @author qiubinglin (qiubinglin@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-02-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "option_configure_ext.h"

#include "easy_args.h"

void option_configure_ext(option_parser_t &parser, cfg_t &cfg) {
  parser.option(0, "deepctrl", 1, [&](const char* s){cfg.deepctrl = strtoull(s, nullptr, 10);});
  parser.option(0, "waddr", 1, [&](const char* s){cfg.watch_addr = strtoull(s, nullptr, 16);});
  parser.option(0, "misaligned_mode", 1, [&](const char* s){cfg.misaligned_mode = strtoull(s, nullptr, 10);});
  parser.option(0, "term_log", 1, [&](const char* s){g_easy_args.term_log = s;});
  parser.option(0, "pmpcsr_num", 1, [&](const char* s){cfg.pmpcsr_num = strtoll(s, nullptr, 10);});
  parser.option(0, "debug_info", 0, [&](const char *s){cfg.debug_info = true;});
}