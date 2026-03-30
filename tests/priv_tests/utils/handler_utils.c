
#include <handler_utils.h>

/*
 *  Current virtual mode
 */
enum virtual_mode v_mode = false;

/*
 *  Target core virtual mode, when switch mode
 */
enum virtual_mode target_v_mode = OFF;

/*
 *  Current core mode
 */
enum mode current_mode = MODE_M;

/*
 *  Target core mode, when switch mode
 */
enum mode target_mode = MODE_M;

/*
 *  Ecall args and retrun value
 */
reg_t ecall_args[2];

/*
 *  Exception info
 */
struct exception excpt;

/*
 *  mode handler pointer
 */
mhandler_ptr_t mhandler_ptr = &default_mhandler;
shandler_ptr_t shandler_ptr = &default_shandler;
vshandler_ptr_t vshandler_ptr = &default_vshandler;

reg_t ecall(reg_t a0, reg_t a1) {
    ecall_args[0] = a0;
    ecall_args[1] = a1;
    asm volatile("ecall" ::: "memory");
    return ecall_args[0];
}

static bool is_interrupt(enum mode trap_mode) {
    reg_t cause;
    reg_t interrupt_bit;

    switch(trap_mode){
        case MODE_M:
            cause = CSRR(mcause);
            break;
        case MODE_S:
            cause = CSRR(scause);
            break;
        default:
            ERROR("Switch mode error")
    }

    interrupt_bit = cause & (1L << (XLEN_BYTES * 8 - 1));
    interrupt_bit >>= (XLEN_BYTES * 8 - 1);

    return (bool)interrupt_bit;
}

/*
 *  Switch mode handlers
 */

void switch_mode_mhandler() {
   csr_set_field(mstatus, MSTATUS_MPP_OFF, MSTATUS_MPP_LEN, target_mode);
   current_mode = target_mode;
}

void switch_mode_none_mhandler() {
    csr_set_field(mstatus, MSTATUS_MPP_OFF, MSTATUS_MPP_LEN, MODE_M);
    current_mode = MODE_M;
}

void switch_mode_M(enum mode to_mode) {
    target_mode = to_mode;
    mhandler_ptr_t temp_mhandler_ptr = mhandler_ptr;
    set_mhandler(switch_mode_mhandler);
    ecall(0, 0);
    set_mhandler(temp_mhandler_ptr);
}

void switch_mode_S(enum mode to_mode) {
    // switch to M mode
    shandler_ptr_t temp_mhandler_ptr = mhandler_ptr;
    set_mhandler(switch_mode_none_mhandler);
    ecall(0, 0);

    // switch to target mode
    switch_mode_M(to_mode);
    set_mhandler(temp_mhandler_ptr);
}

void switch_mode(enum mode to_mode) {

    bool old_for_testing = excpt.for_testing;
    excpt.for_testing = true;
    
    switch(current_mode){
        case MODE_M:
            switch_mode_M(to_mode);
            break;
        case MODE_S:
        case MODE_U:
            switch_mode_S(to_mode);
            break;
        default:
            ERROR("Switch mode error")
    }

    excpt.for_testing = old_for_testing;
}

/*
 *  Switch mode and virtualization handlers 
 */

void switch_mode_and_vmode_mhandler() {
   csr_set_field(mstatus, MSTATUS_MPP_OFF, MSTATUS_MPP_LEN, target_mode);
   csr_set_field(mstatus, MSTATUS_MPV_OFF, MSTATUS_MPV_LEN, (unsigned long)target_v_mode);
   current_mode = target_mode;
   v_mode = target_v_mode;
}

void switch_mode_and_vmode_none_mhandler() {
    csr_set_field(mstatus, MSTATUS_MPP_OFF, MSTATUS_MPP_LEN, MODE_M);
    csr_set_field(mstatus, MSTATUS_MPV_OFF, MSTATUS_MPV_LEN, (unsigned long)OFF);
    current_mode = MODE_M;
    v_mode = OFF;
}

void switch_mode_and_vmode_M(enum mode to_mode, enum virtual_mode to_v_mode) {
    target_mode = to_mode;
    target_v_mode = to_v_mode;
    mhandler_ptr_t temp_mhandler_ptr = mhandler_ptr;
    set_mhandler(switch_mode_and_vmode_mhandler);
    ecall(0, 0);
    set_mhandler(temp_mhandler_ptr);
}

void switch_mode_and_vmode_S(enum mode to_mode, enum virtual_mode to_v_mode) {
    // switch to M mode
    shandler_ptr_t temp_mhandler_ptr = mhandler_ptr;
    set_mhandler(switch_mode_and_vmode_none_mhandler);
    ecall(0, 0);

    // switch to target mode
    switch_mode_and_vmode_M(to_mode, to_v_mode);
    set_mhandler(temp_mhandler_ptr);
}

void switch_mode_and_vmode(enum mode to_mode, enum virtual_mode to_v_mode) {

    bool old_for_testing = excpt.for_testing;
    excpt.for_testing = true;
    
    switch(current_mode){
        case MODE_M:
            switch_mode_and_vmode_M(to_mode, to_v_mode);
            break;
        case MODE_S:
        case MODE_U:
            switch_mode_and_vmode_S(to_mode, to_v_mode);
            break;
        default:
            ERROR("Switch mode error")
    }

    excpt.for_testing = old_for_testing;
}
/*
 *  Supervisor witch mode handlers
 */

void switch_mode_shandler() {
    csr_set_field(sstatus, SSTATUS_SPP_OFF, SSTATUS_SPP_LEN, target_mode);
    current_mode = target_mode;
}

void switch_mode_none_shandler() {
    csr_set_field(sstatus, SSTATUS_SPP_OFF, SSTATUS_SPP_LEN, MODE_S);
    current_mode = MODE_S;
}

void switch_mode_S_supervisor(enum mode to_mode) {
    target_mode = to_mode;
    shandler_ptr_t temp_shandler_ptr = shandler_ptr;
    set_shandler(switch_mode_shandler);
    ecall(0, 0);
    set_shandler(temp_shandler_ptr);
}

void switch_mode_U_supervisor(enum mode to_mode) {
    // switch to S mode
    shandler_ptr_t temp_shandler_ptr = shandler_ptr;
    set_shandler(switch_mode_none_shandler);
    ecall(0, 0);
    switch_mode_S_supervisor(to_mode); // switch to target mode
    set_shandler(temp_shandler_ptr);
}

void switch_mode_supervisor(enum mode to_mode) {

    bool old_for_testing = excpt.for_testing;
    excpt.for_testing = true;
    
    switch(current_mode){
        case MODE_S:
            switch_mode_S_supervisor(to_mode);
            break;
        case MODE_U:
            switch_mode_U_supervisor(to_mode);
            break;
        default:
            ERROR("Switch mode error")
    }

    excpt.for_testing = old_for_testing;
}


/*
 *  Switch virtual mode handlers
 */

void switch_mode_vshandler() {
    csr_set_field(sstatus, SSTATUS_SPP_OFF, SSTATUS_SPP_LEN, target_mode);
    current_mode = target_mode;
}

void switch_mode_none_vshandler() {
    csr_set_field(sstatus, SSTATUS_SPP_OFF, SSTATUS_SPP_LEN, MODE_S);
    current_mode = MODE_S;
}

void switch_mode_S_guest(enum mode to_mode) {
    target_mode = to_mode;
    vshandler_ptr_t temp_vshandler_ptr = vshandler_ptr;
    set_vshandler(switch_mode_vshandler);
    // ecall can't be delegated, so use illigal instruction to trap to VS mode
    asm volatile ("unimp \n\t");
    set_vshandler(temp_vshandler_ptr);
}

void switch_mode_U_guest(enum mode to_mode) {
    // switch to VS mode
    vshandler_ptr_t temp_vshandler_ptr = vshandler_ptr;
    set_vshandler(switch_mode_none_vshandler);
    // ecall can't be delegated, so use illigal instruction to trap to VS mode
    asm volatile ("unimp \n\t");
    switch_mode_S_guest(to_mode); // switch to target mode
    set_vshandler(temp_vshandler_ptr);
}

void switch_mode_guest(enum mode to_mode) {

    bool old_for_testing = excpt.for_testing;
    excpt.for_testing = true;
    
    switch(current_mode){
        case MODE_S:
            switch_mode_S_guest(to_mode);
            break;
        case MODE_U:
            switch_mode_U_guest(to_mode);
            break;
        default:
            ERROR("Switch mode error")
    }

    excpt.for_testing = old_for_testing;
}

void virtual_mode_on_shandler() {
   csr_set_field(hstatus, HSTATUS_SPV_OFF, HSTATUS_SPV_LEN, 1);
   v_mode = ON;
}

void virtual_mode_off_shandler() {
   csr_set_field(hstatus, HSTATUS_SPV_OFF, HSTATUS_SPV_LEN, 0);
   v_mode = OFF;
}

void virtual_mode_on_mhandler() {
   csr_set_field(mstatus, MSTATUS_MPV_OFF, MSTATUS_MPV_LEN, 1L);
   v_mode = ON;
}

void virtual_mode_off_mhandler() {
   csr_set_field(mstatus, MSTATUS_MPV_OFF, MSTATUS_MPV_LEN, 0L);
   v_mode = OFF;
}

void set_virtial_mode_host(enum virtual_mode to_mode) {

    bool old_for_testing = excpt.for_testing;
    excpt.for_testing = true;
    
    shandler_ptr_t temp_shandler_ptr = shandler_ptr;

    if (to_mode == ON) {
        set_shandler(virtual_mode_on_shandler);
    }
    else {
        set_shandler(virtual_mode_off_shandler);
    }

    ecall(0, 0);
    set_shandler(temp_shandler_ptr);

    excpt.for_testing = old_for_testing;
}

void set_virtial_mode_machine(enum virtual_mode to_mode) {

    bool old_for_testing = excpt.for_testing;
    excpt.for_testing = true;
    
    mhandler_ptr_t temp_mhandler_ptr = mhandler_ptr;

    if (to_mode == ON) {
        set_mhandler(virtual_mode_on_mhandler);
    }
    else {
        set_mhandler(virtual_mode_off_mhandler);
    }

    ecall(0, 0);
    set_mhandler(temp_mhandler_ptr);

    excpt.for_testing = old_for_testing;
}



/*
 *  Helper functions
 */

inline reg_t next_instruction(reg_t epc){
    if(((*(uint16_t*)epc) & 0b11) == 0b11) return epc + 4;
    else return epc + 2;
}

inline void set_epc_to_next_instruction(enum mode trap_mode) {
    reg_t epc;

    switch (trap_mode) {
        case MODE_M:
            epc = CSRR(mepc);
            CSRW(mepc, next_instruction(epc));
            break;
        case MODE_S:
            epc = CSRR(sepc);
            CSRW(sepc, next_instruction(epc));
            break;
        default:
            ERROR("invalid current mode");
    }
}

void set_mhandler(mhandler_ptr_t handler){
    mhandler_ptr = handler;
}

void __attribute__((weak)) mhandler_trampoline(){
    if (!excpt.for_testing){
        ERROR("Unexcpected exception");
    }
    mhandler_ptr();
    if ( !is_interrupt(MODE_M) ){
        set_epc_to_next_instruction(MODE_M);
    }
}

void __attribute__((weak)) default_mhandler(){
    ERROR("Default mhandler. Please use set_mhandler()");
}


void set_shandler(shandler_ptr_t handler){
    shandler_ptr = handler;
}

void __attribute__((weak)) shandler_trampoline(){
    if (!excpt.for_testing){
        ERROR("Unexcpected exception");
    }
    shandler_ptr();
    if ( !is_interrupt(MODE_S) ){
        set_epc_to_next_instruction(MODE_S);
    }
}

void __attribute__((weak)) default_shandler(){
    ERROR("Default shandler. Please use set_shandler()");
}


void set_vshandler(vshandler_ptr_t handler){
    vshandler_ptr = handler;
}

void __attribute__((weak)) vshandler_trampoline(){
    if (!excpt.for_testing){
        ERROR("Unexcpected exception");
    }
    vshandler_ptr();
    if ( !is_interrupt(MODE_S) ){
        set_epc_to_next_instruction(MODE_S);
    }
}

void __attribute__((weak)) default_vshandler(){
    ERROR("Default shandler. Please use set_vshandler()");
}
