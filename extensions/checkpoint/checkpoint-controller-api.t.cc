#include "checkpoint/checkpoint_controller.h"
#include "runtime/runtime_context.h"
#include <type_traits>
#include <utility>

int main()
{
  static_assert(std::is_enum_v<checkpoint_restore_mode_t>);
  static_assert(std::is_same_v<
      decltype(std::declval<checkpoint_legacy_config_t>().snapshot_save_name),
      const char*>);
  static_assert(std::is_same_v<
      decltype(std::declval<checkpoint_legacy_config_t>().snapshot_compress_zstd),
      bool>);
  static_assert(std::is_same_v<
      decltype(std::declval<spike_runtime_context_t&>().checkpoint_controller()),
      checkpoint_controller_t*>);
  return 0;
}
