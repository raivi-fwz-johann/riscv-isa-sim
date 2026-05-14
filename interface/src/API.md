# Interface Layer API

## spike_state_exporter_t

每核独立的状态导出器。通过 hook 回调接收 Spike 执行事件，维护指令快照和访存日志。

### 状态快照

```
spike_observed_insn_t:
  valid, pc, npc, bits, paddr, paddr2

spike_state_snapshot_t:
  fetch      spike_observed_insn   // on_fetch_observe 写入（指令缓存 miss 时）
  exec       spike_observed_insn   // on_exec_observe 写入
  pre_exec   spike_observed_insn   // on_pre_exec 写入（页面异常时仍可用）
  in_trap    bool                  // on_trap 写入
  epc        reg_t                 // trap PC
  trap_npc   reg_t                 // trap handler PC
  cause      reg_t                 // trap cause
  tval       reg_t                 // trap tval
  tval2      reg_t                 // trap tval2
  has_tval2  bool
  mmu_trace  MmuTrace              // on_mmu_walk 写入
```

### 访存日志

```
MemLogItem:
  addr    reg_t      // 虚拟地址
  val     uint64_t   // 数据值（load 前为 0）
  size    uint8_t    // 访存大小
  paddr   reg_t      // 物理地址（translate 获取，失败时 fallback = addr）

mem_loads(hart_id)   → const vector<MemLogItem>&
mem_stores(hart_id)  → const vector<MemLogItem>&
```

### 方法

```
reset(nprocs)                        // 初始化 n 个核
snapshot(hart_id)                    → const spike_state_snapshot_t*
get_mmu_trace(hart_id)              → MmuTrace
in_trap(hart_id)                    → bool
reset_observed(hart_id)             // 重置快照和 mem log

// Hook 回调（由 SpikeSimObjHooker 调用）
observe_fetch(hart_id, vaddr, paddr, paddr2, bits, length)
observe_pre_exec(hart_id, fetch, pc)
observe_exec(hart_id, fetch, pc, npc)
observe_trap(hart_id, fetch, pc, t)    → reg_t
observe_trap_target(hart_id, npc)
observe_mmu_walk(event)
add_mem_log(hart_id, addr, val, size, paddr, is_store)
clear_mem_log(hart_id)
```

## SpikeSimObjHooker

`spike_hook_dispatcher_t` 的具体实现，将 hook 事件转发给 `spike_state_exporter_t`。

```
构造: SpikeSimObjHooker(spike_state_exporter_t*, spike_roi_state_t*, stop_fn)

各 on_* 方法均委托给:
  m_StateExporter->observe_*()
  m_StateExporter->add_mem_log()
  m_StateExporter->clear_mem_log()
```

## RawSpike

模型侧 Spike 封装，提供统一的仿真控制和状态读取接口。

```
init(args)                               // 初始化 Spike 实例
step(n, core_id) → size_t                // 执行 n 条指令
record(data, core_id) → int              // 记录指令状态到 InstTrace
fetchInstOnly(pc, core_id, iid) → InstTrace  // 仅取指不执行
done() → bool                            // 仿真是否结束
stop()                                   // 停止仿真
getCurrPc(core_id) → uint64_t           // 当前 PC
getConfiguredNPc(core_id) → uint64_t    // 配置的 NPC
inWFI(core_id) → bool                   // 是否在 WFI 状态
vaddr2paddr(vaddr, core_id) → uint64_t  // 虚→实地址转换
setLogCommits(log_commits, is_fast, core_id)
setLogMem(bool)
```

## 数据流

```
Spike 核心执行
  │
  ├─ refill_icache  → on_fetch_observe  → observe_fetch  → snapshot.fetch
  ├─ execute_insn   → on_pre_exec       → observe_pre_exec → snapshot.pre_exec
  │                 → on_exec_observe   → observe_exec    → snapshot.exec
  ├─ take_trap      → on_trap           → observe_trap    → snapshot.{in_trap,epc,...}
  │                 → on_trap_target    → observe_trap_target → snapshot.trap_npc
  ├─ mmu_t::walk    → on_mmu_walk       → observe_mmu_walk → snapshot.mmu_trace
  └─ mmu_t::load/store → on_mem_log     → add_mem_log    → mem_loads[]/mem_stores[]
                                          ↓
                              RawSpike::record()
                                ├─ 读 snapshot → 拼装 pc/npc/bits/paddr
                                └─ 读 mem_loads/mem_stores → 拼装 mem Rs/Ws
                                          ↓
                                     InstTrace
```
