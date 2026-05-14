#pragma once

#include <cstdint>
#include <optional>
#include <string>

class mmu_t;
class sim_t;

// Controls whether LR/SC reservations are preserved when simulation
// interleaves between harts.  When false (default), reservations are
// yielded on every interleave, matching standard Spike behavior.
class spike_model_compat_t {
public:
  // Returns true if LR/SC reservations survive interleave.
  bool preserve_lr_sc_reservation_across_interleave() const {
    return preserve_lr_sc_reservation_across_interleave_;
  }
  void set_preserve_lr_sc_reservation_across_interleave(bool value) {
    preserve_lr_sc_reservation_across_interleave_ = value;
  }

private:
  bool preserve_lr_sc_reservation_across_interleave_ = false;
};

// RAII guard that temporarily overrides the ISA string derived from
// the device tree.  The override is thread-local and is automatically
// popped when the guard goes out of scope.
// Construction from an engaged std::optional installs the override;
// construction from std::nullopt clears it.
class spike_explicit_isa_scope_t {
public:
  // Installs an ISA override for the current thread.
  // |isa|  std::nullopt to clear, or the ISA string to use.
  explicit spike_explicit_isa_scope_t(const std::optional<std::string>& isa);
  ~spike_explicit_isa_scope_t();

  spike_explicit_isa_scope_t(const spike_explicit_isa_scope_t&) = delete;
  spike_explicit_isa_scope_t& operator=(const spike_explicit_isa_scope_t&) = delete;

private:
  bool had_previous_ = false;
  std::optional<std::string> previous_;
};

// Returns the ISA string to use for boot.  If a command-line ISA override
// is active (via spike_explicit_isa_scope_t), it takes precedence over
// the DTB-derived ISA.
// |dtb_file|  path to the device tree blob (may be null).
// |dtb_isa|   ISA string from the device tree.
// Returns     the effective ISA string.
const char* spike_resolve_boot_isa_override(const char* dtb_file,
                                            const char* dtb_isa);

// Returns true if the current hart's LR reservation should be yielded
// when the simulator interleaves to another hart.
// |sim|  the simulator instance (may be null).
bool spike_should_yield_load_reservation_on_interleave(const sim_t* sim);
