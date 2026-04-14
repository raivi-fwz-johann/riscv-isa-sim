#include "runtime/runtime_context.h"

namespace {
class null_checkpoint_controller_t final : public checkpoint_controller_t {
public:
  bool enabled() const override { return false; }
  bool has_load_target() const override { return false; }
  bool has_save_target() const override { return false; }
  void prepare_restore(sim_t&, bool) override {}
  void on_post_reset(sim_t&) override {}
  void request_save() override {}
  bool save_requested() const override { return false; }
  void save(sim_t&) override {}
};
}  // namespace

spike_runtime_context_t::spike_runtime_context_t()
  : hook_dispatcher_(std::make_unique<spike_hook_dispatcher_t>()),
    log_manager_(std::make_unique<spike_log_manager_t>()),
    host_policy_(std::make_unique<spike_host_policy_t>()),
    checkpoint_controller_(std::make_unique<null_checkpoint_controller_t>())
{
}
