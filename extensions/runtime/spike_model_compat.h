#pragma once

#include <cstdint>
#include <optional>
#include <string>

class mmu_t;
class sim_t;

class spike_model_compat_t {
public:
  bool preserve_lr_sc_reservation_across_interleave() const
  {
    return preserve_lr_sc_reservation_across_interleave_;
  }

  void set_preserve_lr_sc_reservation_across_interleave(bool value)
  {
    preserve_lr_sc_reservation_across_interleave_ = value;
  }

private:
  bool preserve_lr_sc_reservation_across_interleave_ = false;
};

class spike_explicit_isa_scope_t {
public:
  explicit spike_explicit_isa_scope_t(const std::optional<std::string>& isa);
  ~spike_explicit_isa_scope_t();

  spike_explicit_isa_scope_t(const spike_explicit_isa_scope_t&) = delete;
  spike_explicit_isa_scope_t& operator=(const spike_explicit_isa_scope_t&) = delete;

private:
  bool had_previous_ = false;
  std::optional<std::string> previous_;
};

const char* spike_resolve_boot_isa_override(const char* dtb_file, const char* dtb_isa);
bool spike_should_yield_load_reservation_on_interleave(const sim_t* sim);
void spike_note_fetch_paddr(const mmu_t* mmu, uint64_t paddr);
uint64_t spike_fetch_paddr(const mmu_t* mmu, uint64_t fallback_paddr);
void spike_forget_fetch_paddr(const mmu_t* mmu);
