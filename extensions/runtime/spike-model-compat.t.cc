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

  if (!spike_should_yield_load_reservation_on_interleave(nullptr))
    return 4;

  return 0;
}
