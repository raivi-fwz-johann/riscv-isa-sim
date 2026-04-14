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
  if (controller->has_load_target()) return 32;
  if (controller->has_save_target()) return 33;
  controller->request_save();
  if (controller->save_requested()) return 34;

  auto load_controller = make_checkpoint_controller(
      checkpoint_legacy_config_t{.snapshot_load_name = "snap-load"});
  if (load_controller == nullptr) return 35;
  if (!load_controller->enabled()) return 36;
  if (!load_controller->has_load_target()) return 37;
  if (load_controller->has_save_target()) return 38;
  load_controller->request_save();
  if (load_controller->save_requested()) return 39;

  auto save_controller = make_checkpoint_controller(
      checkpoint_legacy_config_t{.snapshot_save_name = "snap-save"});
  if (save_controller == nullptr) return 40;
  if (!save_controller->enabled()) return 41;
  if (save_controller->has_load_target()) return 42;
  if (!save_controller->has_save_target()) return 43;
  if (save_controller->save_requested()) return 44;
  save_controller->request_save();
  if (!save_controller->save_requested()) return 45;

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
