/**
 * @file Disassembler.hpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-01-08
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include "Memory.hpp"

#include <string>

typedef uint64_t InsnBits;

class disassembler_t;
class Disassembler {
public:
  Disassembler(const std::string &isa, const std::string &priv);
  Disassembler();
  Disassembler(const Disassembler &That) = delete;
  ~Disassembler();

  std::string disassemble(InsnBits Bits) const;

  bool isRV64() const;

private:
  disassembler_t *m_Impl = nullptr;
  bool m_RV64 = true;
};