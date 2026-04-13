#include "RawSpike.hpp"

#include <iostream>
#include <string>

namespace {

void dump_inst(const InstTrace& inst)
{
  const auto& trace = inst.newTrace;
  std::cout << std::hex
            << "vpc=0x" << trace.vpc
            << " ppc=0x" << trace.ppc
            << " instr_raw=0x" << trace.instr_raw
            << " next_vpc=0x" << trace.next_vpc
            << " branch_taken=" << std::dec << trace.branch_taken
            << " exception=" << trace.exception
            << " fetch_ptw=" << trace.fetch_ptw.size()
            << " src_regs=" << trace.src_regs.size()
            << " dst_regs=" << trace.dst_regs.size()
            << " mem_ops=" << trace.mem_ops.size()
            << " vtype=0x" << std::hex << trace.vtype
            << " vl=" << std::dec << trace.vl
            << " vstart=" << trace.vstart
            << " active_mask=0x" << std::hex << trace.active_mask
            << std::endl;
}

}  // namespace

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cerr << "usage: TraceStructDumpMain \"spike <args> <elf>\"" << std::endl;
    return 1;
  }

  RawSpike sim;
  sim.init(argv[1]);
  sim.start();
  sim.setLogMem(true);

  size_t printed = 0;
  while (!sim.done() && printed < 80) {
    InstTrace inst(0);
    sim.step(1, 0);
    if (sim.record(inst, 0) == 0 && inst.perfect() && inst.newTrace.vpc >= 0x80000000) {
      dump_inst(inst);
      ++printed;
    }
  }

  sim.stop();
  return 0;
}
