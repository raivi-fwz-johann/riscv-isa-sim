/**
 * @file option_configure_ext.h
 * @author qiubinglin (qiubinglin@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-02-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef EXT_OPTION_CONFIGURE_EXT_H
#define EXT_OPTION_CONFIGURE_EXT_H

#include "option_parser.h"
#include "cfg.h"

#define OPTION_HELP_PRINT \
  fprintf(stderr, "  --deepctrl=<val>         Set if in deepctrl mode, val=0 or 1.\n"); \
  fprintf(stderr, "  --waddr=<hexval>         Watch access behavior in <hexval> addr.\n"); \
  fprintf(stderr, "  --misaligned_mode=<val>  Setup misaligned mode. 0: no further check; 1: 16B check. default 0.\n"); \
  fprintf(stderr, "  --term_log=<flie>        Setup canonical_terminal output file.\n"); \
  fprintf(stderr, "  --pmpcsr_num=<num>       The number of pmp csr to be created, default 64.\n"); \
  fprintf(stderr, "  --debug_info             Print debug info for MMU/PRIV/CSRS.\n");


void option_configure_ext(option_parser_t &parser, cfg_t &cfg);

#endif // EXT_OPTION_CONFIGURE_EXT_H