#include <iostream>

#include "Thread.hpp"

#include "RawSpike.hpp"
#include "FuncSimAdapter.hpp"
#include "utility/DTCTools.hpp"
#include "Disassembler.hpp"

class MultiThreadRunTestT {
public:
  void normalTest() {
    tools::fileDts2Dtb("/work/home/blqiu/spike/rv64_2cores.dts",
                       "./rv64_2cores.dtb");
    FuncSimAdapter SimObj;
    SimObj.setFuncSim(new RawSpike());
    SimObj.init("spike --log-commits --dtb=./rv64_2cores.dtb "
                "--priv=msu "
                "/work/home/blqiu/riscv-tests/build/benchmarks/vvadd.riscv");

    SimObj.start();
    std::thread RunProc0([&SimObj]() {
      std::list<InstUserPtr> InstVec;
      Disassembler DisasmObj("rv64imafdcv_zicntr_zihpm_zk_zba_zbb_zbc_zbs_zfh_zmmul_zicbom_zicbop_zicboz_svnapot", "msu");
      size_t StepCnt = 0;
      InstUserPtr PrevInst = nullptr;
      while (not SimObj.done()) {
        SimObj.step(1, 0);
        auto Inst = SimObj.reqInst(0);
        if (Inst and Inst != PrevInst) {
          ++StepCnt;
          std::cout << "StepCnt0: " << StepCnt << " pc: 0x" << std::hex
                    << Inst->getPc() << " "
                    << DisasmObj.disassemble(Inst->getBits()) << std::dec
                    << std::endl;
          InstVec.push_back(Inst);
          PrevInst = Inst;
        }
        if (InstVec.size() > 1000) {
          SimObj.freeInst(InstVec.front()->getId(), 0);
          InstVec.pop_front();
        }
      }
    });

    std::thread RunProc1([&SimObj]() {
      std::list<InstUserPtr> InstVec;
      Disassembler DisasmObj("rv64imafdcv_zicntr_zihpm_zk_zba_zbb_zbc_zbs_zfh_zmmul_zicbom_zicbop_zicboz_svnapot", "msu");
      size_t StepCnt = 0;
      InstUserPtr PrevInst = nullptr;
      while (not SimObj.done()) {
        SimObj.step(1, 1);
        auto Inst = SimObj.reqInst(1);
        if (Inst and Inst != PrevInst) {
          ++StepCnt;
          std::cout << "StepCnt2: " << StepCnt << " pc: 0x" << std::hex
                    << Inst->getPc() << " "
                    << DisasmObj.disassemble(Inst->getBits()) << std::dec
                    << std::endl;
          InstVec.push_back(Inst);
          PrevInst = Inst;
        }
        if (InstVec.size() > 1000) {
          SimObj.freeInst(InstVec.front()->getId(), 1);
          InstVec.pop_front();
        }
      }
    });

    RunProc0.join();
    RunProc1.join();
  }
};

int main(int argc, char **argv) {
  MultiThreadRunTestT test;
  test.normalTest();

  return 0;
}
