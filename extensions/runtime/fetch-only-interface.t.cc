#include "../../riscv/mmu.h"
#include <type_traits>

int main()
{
  static_assert(
    std::is_invocable_r<insn_fetch_t, decltype(&mmu_t::ext_fetch_insn), mmu_t*, reg_t>::value,
    "mmu_t::ext_fetch_insn must return insn_fetch_t via reg_t");

  insn_fetch_t dummy;
  return dummy.pc_ppn == 0 ? 0 : 0;
}
