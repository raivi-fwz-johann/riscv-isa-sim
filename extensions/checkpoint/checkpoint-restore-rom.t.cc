#include "checkpoint/checkpoint_restore_rom.h"

int main()
{
  auto rom32 = build_checkpoint_trampoline_rom(32, 0x10000);
  auto rom64 = build_checkpoint_trampoline_rom(64, 0x10000);
  if (rom32.empty()) return 10;
  if (rom64.empty()) return 11;
  if (rom32.size() != rom64.size()) return 12;
  return 0;
}
