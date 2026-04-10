/**
 * @file Disassembler.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-08
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Disassembler.hpp"

#include <iostream>

#include "disasm.h"

Disassembler::Disassembler(const std::string &isa, const std::string &priv) {
  auto isa_prefix = isa.substr(2, 2);
  if (isa_prefix == "64") {
    m_RV64 = true;
  } else if (isa_prefix == "32") {
    m_RV64 = false;
  }
  isa_parser_t IsaParser(isa.c_str(), priv.c_str());
  m_Impl = new disassembler_t(&IsaParser);
}

Disassembler::Disassembler()
  : Disassembler("rv64gcv_zicntr_zihpm_zvl512b_zk_zba_zbb_zbc_zbs_zfh_zmmul_zicbom_zicbop_zicboz_svnapot", "msu") {
}

Disassembler::~Disassembler() {
  if (m_Impl) {
    delete m_Impl;
  }
}

std::string Disassembler::disassemble(InsnBits Bits) const {
  insn_t Insn(Bits);
  return m_Impl->disassemble(Insn);
}

bool Disassembler::isRV64() const { return m_RV64; }