#include "runtime/spike_model_compat.h"

#include "runtime/runtime_context.h"
#include "sim.h"

#include <iostream>
#include <mutex>
#include <unordered_map>

namespace {

thread_local std::optional<std::string> g_explicit_isa_override;

std::mutex g_fetch_paddr_mu;
std::unordered_map<const mmu_t*, uint64_t> g_fetch_paddr;

}  // namespace

spike_explicit_isa_scope_t::spike_explicit_isa_scope_t(const std::optional<std::string>& isa)
{
  had_previous_ = g_explicit_isa_override.has_value();
  previous_ = g_explicit_isa_override;
  g_explicit_isa_override = isa;
}

spike_explicit_isa_scope_t::~spike_explicit_isa_scope_t()
{
  if (had_previous_) {
    g_explicit_isa_override = previous_;
  } else {
    g_explicit_isa_override.reset();
  }
}

const char* spike_resolve_boot_isa_override(const char* dtb_file, const char* dtb_isa)
{
  if (dtb_file == nullptr || !g_explicit_isa_override.has_value()) {
    return dtb_isa;
  }

  std::cout << "***Warnning*** Replace dtb isa: [" << dtb_isa
            << "] by command line isa: [" << *g_explicit_isa_override << "]" << std::endl;
  return g_explicit_isa_override->c_str();
}

bool spike_should_yield_load_reservation_on_interleave(const sim_t* sim)
{
  if (!sim) {
    return true;
  }

  auto* runtime = sim->runtime_context();
  auto* compat = runtime ? runtime->model_compat() : nullptr;
  return !compat || !compat->preserve_lr_sc_reservation_across_interleave();
}

void spike_note_fetch_paddr(const mmu_t* mmu, uint64_t paddr)
{
  std::lock_guard<std::mutex> lock(g_fetch_paddr_mu);
  g_fetch_paddr[mmu] = paddr;
}

uint64_t spike_fetch_paddr(const mmu_t* mmu, uint64_t fallback_paddr)
{
  std::lock_guard<std::mutex> lock(g_fetch_paddr_mu);
  auto it = g_fetch_paddr.find(mmu);
  return it == g_fetch_paddr.end() ? fallback_paddr : it->second;
}

void spike_forget_fetch_paddr(const mmu_t* mmu)
{
  std::lock_guard<std::mutex> lock(g_fetch_paddr_mu);
  g_fetch_paddr.erase(mmu);
}
