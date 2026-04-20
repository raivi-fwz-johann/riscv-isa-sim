#include <iostream>

#include <unordered_map>
#include <chrono>

#include "SpikeSimObjSync.hpp"
#include "Disassembler.hpp"

// #include "SpikeUtils.hpp"

void testReplay(const std::string &cmd, const std::string &isa) {
  std::list<InstUserPtr> InstVec;
  std::unordered_map<uint64_t, InstUserPtr> InstSet;
  Disassembler disasm(isa, "msu");
  SpikeSimObjSync SimObj;
  SimObj.init(cmd);
  SimObj.start();
  // SimObj.setLogCommits(true, true);
  [[maybe_unused]]uint64_t prev_pc = 0;
  [[maybe_unused]]int tmpcount = 0;
  while (not SimObj.done()) {
    SimObj.step(1);
    auto Inst = SimObj.reqInst();
    if (Inst and Inst->perfect()) {
      // std::cout << "tmpcount: " << tmpcount << std::endl;
      tmpcount++;
      if (InstSet.count(Inst->getId()) == 0) {
        InstVec.push_back(Inst);
        InstSet.emplace(Inst->getId(), Inst);
      }
      // std::cout << "id: " << Inst->getId() << std::endl;
      // std::cout << "pc: " << Inst->getPc() << "pc paddr: " << Inst->getPcPAddr() << " bits: " << Inst->getBits() << std::endl;
      // if (Inst->getNPc() != SimObjDebugger(SimObj).getPc(0)) {
      //   std::cout << "pc: " << Inst->getPc() << " npc: " << Inst->getNPc() << " state pc: " << SimObjDebugger(SimObj).getPc(0) << std::endl;
      //   throw std::runtime_error("npc wrong!");
      // }
      // SimObj.resetNPc(Inst->getNPc());
      // std::cout << "disasm: " << disasm.disassemble(Inst->getBits()) << std::endl;
      // if (prev_pc != 0) {
      //   std::cout << "prev pc: " << prev_pc  << " bits: " << SimObj.fetchInstOnly(prev_pc).getBits() << std::endl;
      // }
      // prev_pc = Inst->getPc();
      // if (Inst->isLoad() or Inst->isStore()) {
      //   for (auto iter = Inst->getMemRs(); not iter.end(); ++iter) {
      //     std::cout << (*iter).vAddr() << " " << (*iter).pAddr() << " " << (*iter).size() << std::endl;
      //   }
      //   for (auto iter = Inst->getMemWs(); not iter.end(); ++iter) {
      //     std::cout << (*iter).vAddr() << " " << (*iter).pAddr() << " " << (*iter).size() << " " << (*iter).value() << std::endl;
      //   }
      // }

      // if (tmpcount % 1000 == 0) {
      //   tmpcount = 0;
      //   // std::cout << "------" << std::endl;
      //   auto riter = InstVec.rbegin();
      //   int i = 0;
      //   while (i < 10) {
      //     ++riter;
      //     ++i;
      //   }
      //   SimObj.rollback((*riter)->getId());
      // }

      if (InstVec.size() > 1000) {
        InstSet.erase(InstVec.front()->getId());
        SimObj.freeInst(InstVec.front());
        InstVec.pop_front();
      }
    }
  }
  SimObj.stop();
}

void testReplayWithMiss(const std::string &cmd, const std::string &isa) {
  std::list<InstUserPtr> InstVec;
  std::unordered_map<uint64_t, InstUserPtr> InstSet;
  Disassembler disasm(isa, "msu");
  SpikeSimObjSync SimObj;

  SimObj.init(cmd);
  SimObj.start();
  [[maybe_unused]]uint64_t prev_pc = 0;
  [[maybe_unused]]int tmpcount = 0;
  while (not SimObj.done()) {
    SimObj.step(1);
    auto Inst = SimObj.reqInst();
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
      tmpcount++;
      // if (InstSet.count(Inst->getId()) == 0) {
      //   InstVec.push_back(Inst);
      //   InstSet.emplace(Inst->getId(), Inst);
      // }
      // if (not path.inCorrectId()) {
      //   SimObj.resetNPc(Inst->getPc() + Inst->getInstLen());
      // } else {
      //   SimObj.resetNPc(Inst->getNPc());
      // }
      // if (tmpcount == 1000) {
      //   uint64_t NPc = Inst->getNPc() + Inst->getInstLen() * 10;
      //   SimObj.resetNPc(NPc);
      // }

      // if (tmpcount == 1100) {
      //   uint64_t rpc = 0;
      //   {
      //     auto riter = InstVec.rbegin();
      //     int i = 0;
      //     while (i < 100) {
      //       ++riter;
      //       ++i;
      //     }
      //     SimObj.resolve((*riter)->getId());
      //     rpc = (*riter)->getNPc();
      //   }
      //   {
      //     int i = 0;
      //     while (i < 100) {
      //       auto riter = InstVec.rbegin();
      //       InstSet.erase((*riter)->getId());
      //       InstVec.pop_back();
      //       ++i;
      //     }
      //   }
      //   SimObj.resetNPc(rpc);
      // }

      if (InstVec.size() > 1000) {
        InstSet.erase(InstVec.front()->getId());
        SimObj.freeInst(InstVec.front());
        InstVec.pop_front();
      }
    }
  }
  SimObj.stop();
}

void testReplayWithMiss2(const std::string &cmd, const std::string &isa) {
  std::list<InstUserPtr> InstVec;
  std::unordered_map<uint64_t, InstUserPtr> InstSet;
  Disassembler disasm(isa, "msu");
  SpikeSimObjSync SimObj;

  SimObj.init(cmd);
  SimObj.start();
  [[maybe_unused]]uint64_t prev_pc = 0;
  [[maybe_unused]]int tmpcount = 0;
  // const auto &path = SimObjDebugger(SimObj).getPathHandler(0);
  while (not SimObj.done()) {
    SimObj.step(1);
    auto Inst = SimObj.reqInst();
    if (Inst) {
      // std::cout << "tmpcount: " << tmpcount << std::endl;
      tmpcount++;
      if (InstSet.count(Inst->getId()) == 0) {
        InstVec.push_back(Inst);
        InstSet.emplace(Inst->getId(), Inst);
      }
      // if (not path.inCorrectId()) {
      //   SimObj.resetNPc(Inst->getPc() + Inst->getInstLen());
      // } else {
      //   SimObj.resetNPc(Inst->getNPc());
      // }
      // if (tmpcount == 1000) {
      //   uint64_t NPc = Inst->getNPc() + Inst->getInstLen() * 10;
      //   SimObj.resetNPc(NPc);
      // }

      // if (tmpcount == 1100) {
      //   uint64_t rpc = 0;
      //   {
      //     auto riter = InstVec.rbegin();
      //     int i = 0;
      //     while (i < 100) {
      //       ++riter;
      //       ++i;
      //     }
      //     SimObj.resolve((*riter)->getId());
      //     rpc = (*riter)->getNPc();
      //   }
      //   {
      //     int i = 0;
      //     while (i < 100) {
      //       auto riter = InstVec.rbegin();
      //       InstSet.erase((*riter)->getId());
      //       InstVec.pop_back();
      //       ++i;
      //     }
      //   }
      //   SimObj.resetNPc(rpc);
      // }

      if (InstVec.size() > 1000) {
        InstSet.erase(InstVec.front()->getId());
        SimObj.freeInst(InstVec.front());
        InstVec.pop_front();
      }
    }
  }
  SimObj.stop();
}

void testSpikeSpeed(const std::string &cmd, const std::string &isa) {
  // auto start0 = std::chrono::high_resolution_clock::now();
  SpikeSimObjSync SimObj;
  SimObj.init(cmd);
  SimObj.start();
  // SimObj.setLogCommits(true, false);
  // SimObjDebugger(SimObj).setInterleave(5000);
  // LogCommitCtrl(SimObj).setLogRegW(false);
  // auto start = std::chrono::high_resolution_clock::now();
  while (not SimObj.done()) {
    SimObj.step(1);
    auto Inst = SimObj.takeInst();
    if (Inst) {
      std::cout << "pc: " << Inst->getPc() << "pc paddr: " << Inst->getPcPAddr() << " bits: " << Inst->getBits() << std::endl;
    //   if (Inst->isLoad() or Inst->isStore()) {
    //     for (auto iter = Inst->getMemRs(); not iter.end(); ++iter) {
    //       std::cout << (*iter).vAddr() << " " << (*iter).pAddr() << " " << (*iter).size() << std::endl;
    //     }
    //     for (auto iter = Inst->getMemWs(); not iter.end(); ++iter) {
    //       std::cout << (*iter).vAddr() << " " << (*iter).pAddr() << " " << (*iter).size() << " " << (*iter).value() << std::endl;
    //     }
    //   }
    }
  }
  // auto end = std::chrono::high_resolution_clock::now();
  // std::chrono::duration<double, std::milli> duration_ms = end - start;
  // std::cout << "Elapsed time: " << duration_ms.count() << " milliseconds" << std::endl;
}

int main(int argc, char **argv) {
  if (argc != 4) {
    std::cout << "Error, argc=" << argc << ", not 4!" << std::endl;
    exit(-1);
  }
  std::string dtb = argv[1];
  std::string isa = argv[2];
  std::string elf = argv[3];
  std::string cmd = "./spike --log-commits --priv=msu --dtb=";
  cmd += dtb + " --isa=";
  cmd += isa + " " + elf;
  std::cout << "cmd: " << cmd << std::endl;

  // testReplay(cmd, isa);
  // testReplayWithMiss(cmd, isa);
  // testReplayWithMiss2(cmd, isa);
  testSpikeSpeed(cmd, isa);

  return 0;
}
