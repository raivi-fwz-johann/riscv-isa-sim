#include "runtime/spike_model_compat.h"

#include <optional>
#include <string>

int main()
{
  if (std::string(spike_resolve_boot_isa_override(nullptr, "rv64imac")) != "rv64imac")
    return 1;

  {
    spike_explicit_isa_scope_t scope(std::optional<std::string>{"rv64gc"});
    if (std::string(spike_resolve_boot_isa_override("/tmp/test.dtb", "rv64imac")) != "rv64gc")
      return 2;
  }

  if (std::string(spike_resolve_boot_isa_override("/tmp/test.dtb", "rv64imac")) != "rv64imac")
    return 3;

  auto* fake_mmu = reinterpret_cast<const mmu_t*>(0x1);
  spike_note_fetch_paddr(fake_mmu, 0x1234);
  if (spike_fetch_paddr(fake_mmu, 0) != 0x1234)
    return 4;

  spike_forget_fetch_paddr(fake_mmu);
  if (spike_fetch_paddr(fake_mmu, 0x88) != 0x88)
    return 5;

  if (!spike_should_yield_load_reservation_on_interleave(nullptr))
    return 6;

  return 0;
}
