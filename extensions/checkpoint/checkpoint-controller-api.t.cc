#include "checkpoint/checkpoint_controller.h"
#include "runtime/runtime_context.h"
#include "sim.h"
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
  static_assert(std::is_same_v<
      decltype(std::declval<sim_t&>().runtime_context()->checkpoint_controller()),
      checkpoint_controller_t*>);

  auto controller = make_checkpoint_controller({});
  if (controller == nullptr) return 30;
  if (controller->enabled()) return 31;

  spike_runtime_context_t runtime_context;
  checkpoint_controller_t* runtime_controller = runtime_context.checkpoint_controller();
  if (!runtime_controller) {
    return 1;
  }
  if (runtime_controller->enabled()) {
    return 2;
  }
  return 0;
}
