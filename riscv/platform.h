// See LICENSE for license details.
#ifndef _RISCV_PLATFORM_H
#define _RISCV_PLATFORM_H

#include <cstdint>

struct platform_cfg_t {
  enum cfg_mode_t {
    MEMSIZE_2G,
    MEMSIZE_4G,
    MEMSIZE_8G,
  };

  platform_cfg_t() {
    reinit(MEMSIZE_2G);
  }

  void reinit(cfg_mode_t mode) {
    switch (mode) {
      case MEMSIZE_2G:
        rstvec = 0x00001000;
        clintbs = 0x02000000;
        clintsz = 0x000c0000;
        plicbs = 0x0c000000;
        plicsz = 0x01000000;
        plic_ndev = 31;
        plic_prio_bits = 4;
        ns16550_base = 0x10000000;
        ns16550_size = 0x100;
        ns16550_reg_shift = 0;
        ns16550_reg_io_width = 4;
        ns16550_interrupt_id = 1;
        ext_io_base = 0x40000000;
        dram_base = 0x80000000;
        checkpoint_mainram_base = 0x80000000;
        break;

      case MEMSIZE_4G:
        rstvec = 0x100000000;
        clintbs = 0x02000000;
        clintsz = 0x000c0000;
        plicbs = 0x0c000000;
        plicsz = 0x01000000;
        plic_ndev = 31;
        plic_prio_bits = 4;
        ns16550_base = 0x110000000;
        ns16550_size = 0x100;
        ns16550_reg_shift = 0;
        ns16550_reg_io_width = 4;
        ns16550_interrupt_id = 1;
        ext_io_base = 0x140000000;
        dram_base = 0x00020000;
        checkpoint_mainram_base = 0x00020000;
        break;

      case MEMSIZE_8G:
      default:
        rstvec = 0x1000;
        clintbs = 0x02000000;
        clintsz = 0x000c0000;
        plicbs = 0x0c000000;
        plicsz = 0x01000000;
        plic_ndev = 31;
        plic_prio_bits = 4;
        ns16550_base = 0xd0087000;
        ns16550_size = 0x1000;
        ns16550_reg_shift = 0;
        ns16550_reg_io_width = 4;
        ns16550_interrupt_id = 1;
        ext_io_base = 0x40000000;
        dram_base = 0x4000000000;
        checkpoint_mainram_base = 0x4000000000;
        break;
    }
  }

  uint64_t rstvec;
  uint64_t clintbs;
  uint64_t clintsz;
  uint64_t plicbs;
  uint64_t plicsz;
  uint64_t plic_ndev;
  uint64_t plic_prio_bits;
  uint64_t ns16550_base;
  uint64_t ns16550_size;
  uint64_t ns16550_reg_shift;
  uint64_t ns16550_reg_io_width;
  uint64_t ns16550_interrupt_id;
  uint64_t ext_io_base;
  uint64_t dram_base;
  uint64_t checkpoint_mainram_base;
};

inline platform_cfg_t s_platform_cfg = platform_cfg_t();

#define DEFAULT_KERNEL_BOOTARGS "console=ttyS0 earlycon"
#define DEFAULT_RSTVEC     s_platform_cfg.rstvec
#define DEFAULT_ISA        "rv64imafdc_zicntr_zihpm"
#define DEFAULT_PRIV       "MSU"
#define CLINT_BASE         s_platform_cfg.clintbs
#define CLINT_SIZE         s_platform_cfg.clintsz
#define PLIC_BASE          s_platform_cfg.plicbs
#define PLIC_SIZE          s_platform_cfg.plicsz
#define PLIC_NDEV          s_platform_cfg.plic_ndev
#define PLIC_PRIO_BITS     s_platform_cfg.plic_prio_bits
#define NS16550_BASE       s_platform_cfg.ns16550_base
#define NS16550_SIZE       s_platform_cfg.ns16550_size
#define NS16550_REG_SHIFT  s_platform_cfg.ns16550_reg_shift
#define NS16550_REG_IO_WIDTH s_platform_cfg.ns16550_reg_io_width
#define NS16550_INTERRUPT_ID s_platform_cfg.ns16550_interrupt_id
#define EXT_IO_BASE        s_platform_cfg.ext_io_base
#define DRAM_BASE          s_platform_cfg.dram_base
#define DEBUG_START        0x118100000
#define DEBUG_SIZE         0x4000

#endif
