#include "FuncSimAdapter.hpp"
#include <iostream>

#include "RawSpike.hpp"
#include "Disassembler.hpp"

class SimObjTest {
public:
  static void testInRange(const std::string &cmd, const std::string &isa, size_t beg,
                   size_t end) {
    FuncSimAdapter SimObj;
    SimObj.setFuncSim(new RawSpike());
    SimObj.init(cmd);
    SimObj.start();

    size_t StepCnt = 0;
    Disassembler DisasmObj(isa, "msu");

    while (not SimObj.done()) {
      SimObj.step(1);
      StepCnt++;
      auto Inst = SimObj.reqInst();
      if (StepCnt >= beg and StepCnt < end) {
        if (Inst) {
          std::cout << "StepCnt: " << StepCnt << " pc: 0x" << std::hex
                    << Inst->getPc() << " "
                    << DisasmObj.disassemble(Inst->getBits()) << std::dec
                    << std::endl;
        } else {
          std::cout << "StepCnt: " << StepCnt << " no inst" << std::endl;
        }
      }

      if (StepCnt >= end) {
        break;
      }
    }
  }
};

int main(int argc, char **argv) {
  if (argc != 4) {
    exit(-1);
  }
  std::string params = argv[1];
  std::string isa = argv[2];
  std::string cmd = "./spike --log-commits ";
  cmd += params;
  std::cout << "cmd: " << cmd << std::endl;

  SimObjTest::testInRange(cmd, isa, 0, 0);

  return 0;
}