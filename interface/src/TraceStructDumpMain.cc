#include "RawSpike.hpp"

#include <iostream>
#include <string>

namespace {

void dump_ptw_steps(const std::vector<PTWStep>& steps)
{
  std::cout << "[";
  for (size_t i = 0; i < steps.size(); ++i) {
    if (i) {
      std::cout << ",";
    }
    std::cout << "{idx:" << std::dec << i
              << ",paddr:0x" << std::hex << steps[i].paddr
              << ",pte:0x" << steps[i].pte << "}";
  }
  std::cout << "]";
}

void dump_regs(const std::vector<RegValue>& regs)
{
  std::cout << "[";
  for (size_t i = 0; i < regs.size(); ++i) {
    if (i) {
      std::cout << ",";
    }
    std::cout << "{idx:" << std::dec << i
              << ",flat_id:0x" << std::hex << regs[i].flat_id << "}";
  }
  std::cout << "]";
}

void dump_mem_ops(const std::vector<TraceMemOp>& mem_ops)
{
  std::cout << "[";
  for (size_t i = 0; i < mem_ops.size(); ++i) {
    if (i) {
      std::cout << ",";
    }
    std::cout << "{idx:" << std::dec << i
              << ",vaddr:0x" << std::hex << mem_ops[i].vaddr
              << ",paddr:0x" << mem_ops[i].paddr
              << ",size_bytes:" << std::dec << unsigned(mem_ops[i].size_bytes)
              << ",ptw_steps:";
    dump_ptw_steps(mem_ops[i].ptw_steps);
    std::cout << "}";
  }
  std::cout << "]";
}

void dump_inst(const InstTrace& inst)
{
  std::cout << std::hex
            << "vpc=0x" << inst.getPc()
            << " ppc=0x" << inst.getPcPAddr()
            << " instr_raw=0x" << inst.getBits()
            << " next_vpc=0x" << inst.getNPc()
            << " branch_taken=" << std::dec << inst.isBranchTaken()
            << " exception=" << inst.getException()
            << " fetch_ptw=" << inst.getFetchPtw().size()
            << " src_regs=" << inst.getSrcRegs().size()
            << " dst_regs=" << inst.getDstRegs().size()
            << " mem_ops=" << inst.getMemOps().size()
            << " vtype=0x" << std::hex << inst.getVType()
            << " vl=" << std::dec << inst.getVl()
            << " vstart=" << inst.getVStart()
            << " active_mask=0x" << std::hex << inst.getActiveMask();

  std::cout << " fetch_ptw_steps=";
  dump_ptw_steps(inst.getFetchPtw());
  std::cout << " src_reg_list=";
  dump_regs(inst.getSrcRegs());
  std::cout << " dst_reg_list=";
  dump_regs(inst.getDstRegs());
  std::cout << " mem_op_list=";
  dump_mem_ops(inst.getMemOps());
  std::cout
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
    if (sim.record(inst, 0) == 0 && inst.perfect() && inst.getPc() >= 0x80000000) {
      dump_inst(inst);
      ++printed;
    }
  }

  sim.stop();
  return 0;
}
