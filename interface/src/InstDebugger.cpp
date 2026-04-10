#include "InstTrace.hpp"

#include "disasm.h"
#include "processor.h"
#include <cassert>

InstDebugger::InstDebugger(const InstTrace &Inst) : m_Inst(Inst) {}

uint64_t InstDebugger::getStatePc() const {
  return ERROR_PC_ADDR;
}

auto InstDebugger::getRegWs() const
    -> std::vector<std::tuple<std::string, int, size_t *>> {
  std::vector<std::tuple<std::string, int, size_t *>> res;

  for (auto iter = m_Inst.getRegWs(); not iter.end(); ++iter) {
    char prefix = ' ';
    int rd = iter->getRegnum() >> 4;
    bool is_vec = false;
    bool is_vreg = false;
    switch (iter->getRegnum() & 0xf) {
    case 0:
      prefix = 'x';
      break;
    case 1:
      prefix = 'f';
      break;
    case 2:
      prefix = 'v';
      is_vreg = true;
      break;
    case 3:
      is_vec = true;
      break;
    case 4:
      prefix = 'c';
      break;
    default:
      assert("can't been here" && 0);
      break;
    }

    if (!is_vec) {
      size_t bytes = iter->size();
      std::string reg_name;
      size_t *v = (size_t *)malloc(bytes);

      if (is_vreg) {
        memcpy(v, iter->getVRegData(), bytes);
      } else {
        memcpy(v, &iter->getData(), bytes);
      }

      if (prefix == 'c')
        reg_name = csr_name(rd);
      else
        reg_name = std::string(1, prefix) + std::to_string(rd);

      res.push_back(std::make_tuple(reg_name, bytes, v));
    }
  }
  return res;
}

std::vector<std::tuple<size_t, int, size_t>> InstDebugger::getMemRs() const {
  std::vector<std::tuple<size_t, int, size_t>> res;
  for (auto iter = m_Inst.getMemRs(); not iter.end(); ++iter) {
    res.push_back(std::make_tuple(iter->vAddr(), iter->size(), iter->pAddr()));
  }
  return res;
}

auto InstDebugger::getMemWs() const
    -> std::vector<std::tuple<size_t, int, size_t *, size_t>> {
  std::vector<std::tuple<size_t, int, size_t *, size_t>> res;

  for (auto iter = m_Inst.getMemWs(); not iter.end(); ++iter) {
    size_t bytes = iter->size();
    size_t *v = (size_t *)malloc(bytes);
    auto value = iter->value();
    memcpy(v, &value, bytes);

    res.push_back(std::make_tuple(iter->vAddr(), bytes, v, iter->pAddr()));
  }

  return res;
}