#include "SpikeSimObjAsync.hpp"

#include <iostream>
#include <type_traits>
#include "utility/PerfTimer.hpp"

static_assert(std::is_abstract_v<FuncSimAdapter>,
              "FuncSimAdapter must remain an abstract interface");
static_assert(std::is_base_of_v<FuncSimAdapter, SpikeSimObjAsync>,
              "SpikeSimObjAsync must derive from FuncSimAdapter");

class SpikeSimObjAsyncTest {
public:
  void test(const std::string &cmd, const std::string &isa) {
    SpikeSimObjAsync SimObj;
    SimObj.init(cmd);
    (void)isa;
    SimObj.start();
    while (not SimObj.done()) {
      SimObj.step(1);
      std::shared_ptr<InstTrace> Inst;
      Inst = SimObj.takeInst();
      if (Inst) {
        // std::cout << "pc: " << Inst->getPc() << "pc paddr: " << Inst->getPcPAddr() << " bits: " << Inst->getBits() << std::endl;
        // if (Inst->isLoad() or Inst->isStore()) {
        //   for (auto iter = Inst->getMemRs(); not iter.end(); ++iter) {
        //     std::cout << (*iter).vAddr() << " " << (*iter).pAddr() << " " << (*iter).size() << std::endl;
        //   }
        //   for (auto iter = Inst->getMemWs(); not iter.end(); ++iter) {
        //     std::cout << (*iter).vAddr() << " " << (*iter).pAddr() << " " << (*iter).size() << " " << (*iter).value() << std::endl;
        //   }
        // }
      }
    }
    SimObj.waitStop();
  }
};

int main(int argc, char **argv) {
  if (argc != 4) {
    exit(-1);
  }
  std::string dtb = argv[1];
  std::string isa = argv[2];
  std::string elf = argv[3];
  std::string cmd = "./spike --log-commits --priv=msu --dtb=";
  cmd += dtb + " --isa=";
  cmd += isa + " " + elf;
  std::cout << "cmd: " << cmd << std::endl;

  SpikeSimObjAsyncTest().test(cmd, isa);

  return 0;
}
