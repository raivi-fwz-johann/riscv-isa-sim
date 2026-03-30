
#ifndef HANDLER_UTILS_H
#define HANDLER_UTILS_H

#include <platform.h>
#include <sys_utils.h>
#include <stdbool.h>
#include <stdint.h>
#include <instructions.h>
#include <logging.h>

enum priv {PRIV_VU = 0, PRIV_HU = 1, PRIV_VS = 2, PRIV_HS = 3, PRIV_M = 4, PRIV_MAX};

enum mode {MODE_U = 0, MODE_VU = 0, MODE_HU = 0, MODE_VS = 1, MODE_HS = 1, MODE_S = 1, MODE_M = 3};

enum virtual_mode {OFF = 0, ON = 1};

typedef void (*mhandler_ptr_t)();
typedef void (*shandler_ptr_t)();
typedef void (*vshandler_ptr_t)();

static const char* priv_strs[] = {
    [PRIV_VU] = "vu",
    [PRIV_VS] = "vs",
    [PRIV_HU] = "hu",
    [PRIV_HS] = "hs",
    [PRIV_M] = "m",
};

struct exception {
    bool testing_pass;
    bool for_testing;
    bool triggered;
    enum priv priv;
    uint64_t cause;
    uint64_t epc;
    uint64_t tval;
    uint64_t tinst;
    uint64_t tval2;
    bool gva;
    bool xpv;
    uintptr_t fault_inst;
};

extern enum mode current_mode;
extern enum mode target_mode;
extern enum virtual_mode v_mode;

reg_t ecall(reg_t a0, reg_t a1); 

reg_t next_instruction(reg_t epc);

void set_epc_to_next_instruction(enum mode trap_mode);


void switch_mode(enum mode to_mode);
void switch_mode_and_vmode(enum mode to_mode, enum virtual_mode to_v_mode);
void switch_mode_supervisor(enum mode to_mode);
void switch_mode_guest(enum mode to_mode);

void set_virtial_mode_host(enum virtual_mode to_mode);
void set_virtial_mode_machine(enum virtual_mode to_mode);

void default_mhandler();

void set_mhandler(mhandler_ptr_t handler);

void default_shandler();

void set_shandler(shandler_ptr_t handler);

void default_vshandler();

void set_vshandler(vshandler_ptr_t handler);

#endif
