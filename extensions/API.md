# Extensions API

## spike_runtime_context_t

运行时服务总线。`sim_t` 持有它，通过 getter/setter 挂接各扩展模块。

```
spike_runtime_context_t
├─ hook_dispatcher()       → spike_hook_dispatcher_t*
├─ set_hook_dispatcher()   ← unique_ptr<spike_hook_dispatcher_t>
├─ log_manager()           → spike_log_manager_t*
├─ set_log_manager()       ← unique_ptr<spike_log_manager_t>
├─ model_compat()          → spike_model_compat_t*
├─ set_model_compat()      ← unique_ptr<spike_model_compat_t>
├─ host_policy()           → spike_host_policy_t*
├─ set_host_policy()       ← unique_ptr<spike_host_policy_t>
├─ checkpoint_controller() → checkpoint_controller_t*
└─ set_checkpoint_controller() ← unique_ptr<checkpoint_controller_t>
```

## spike_hook_dispatcher_t

统一 hook 抽象接口。外部通过继承此类注入 `runtime_context` 来接收执行事件。
所有虚方法默认空实现，无 hook 时零开销退化。

### 指令生命周期

```
on_decode(instr, pc, npc)           // 指令解码后
on_commit() → bool                  // 提交日志前
on_next_pc(candidate_npc) → reg_t   // 覆盖下一条 PC
```

### 陷阱/中断

```
on_trap(hart_id, fetch, epc, t) → reg_t   // trap 发生时
on_trap_target(hart_id, epc, npc)          // trap handler PC 确定后
```

### 执行流控制

```
should_continue() → bool            // 暂停 Hart
on_fake_step(instret, prev_instret) // 伪步进
```

### 内存访问

```
on_pre_store(addr, val, size, real_store)  // store 前回调
on_mem_log(hart_id, addr, val, size, paddr, is_store)  // 访存记录（含 paddr）
on_commit_log_reset(hart_id)                // 指令开始时的状态重置
```

### CSR 访问

```
allow_csr_write(csr, val) → bool    // CSR 写入前检查
on_pre_csr(csr, val, allow)          // CSR 写入前回调
```

### 退出

```
on_exit(code) → bool                // 退出回调，false 阻止硬退出
```

### 观测

```
on_exec_observe(hart_id, fetch, pc, npc)    // 指令执行后
on_pre_exec(hart_id, fetch, pc)             // 指令执行前（页面异常时仍触发）
on_fetch_observe(hart_id, vaddr, paddr, paddr2, bits, length)  // 取指时（指令缓存 miss）
```

### 设备/MMU

```
on_device_uart_tx(device, byte)     // UART 发送字节
on_mmu_walk(event)                  // 页表遍历
```

## spike_log_manager_t

```
spike_log_config_t:
  enable_commit_log_stant   bool   // 标准 commit log
  enable_fast_commit_log    bool   // 快速 commit log
  enable_fast_mem_log       bool   // 快速访存 log
  enable_raw_commit_log     bool   // 原始格式 commit log

方法:
  config()                    → const spike_log_config_t&
  set_config(config)          ← const spike_log_config_t&
  enable_commit_log_stant()   → bool
  set_enable_commit_log_stant(bool)
  enable_fast_commit_log()    → bool
  set_enable_fast_commit_log(bool)
  enable_fast_mem_log()       → bool
  set_enable_fast_mem_log(bool)
```

## checkpoint_controller_t

快照存取抽象接口。

```
enabled() → bool                    // 是否启用
has_load_target() → bool            // 是否有加载目标
has_save_target() → bool            // 是否有保存目标
prepare_restore(sim, has_elf)       // 准备恢复流程
on_post_reset(sim)                  // reset 后回调
request_save()                      // 请求保存快照
save_requested() → bool             // 是否有待处理的保存请求
save(sim)                           // 执行保存
```

工厂函数: `make_checkpoint_controller(config) → unique_ptr<checkpoint_controller_t>`

## spike_model_compat_t

```
preserve_lr_sc_reservation_across_interleave() → bool
set_preserve_lr_sc_reservation_across_interleave(bool)
```

自由函数:

```
spike_resolve_boot_isa_override(dtb_file, dtb_isa) → const char*
spike_should_yield_load_reservation_on_interleave(sim) → bool
```

## spike_host_policy_t

```
disable_host() → bool
set_disable_host(bool)
```

## spike_device_observe_registry

```
spike_register_device_runtime_context(device, runtime_context)
spike_unregister_device_runtime_context(device)
spike_find_device_runtime_context(device) → spike_runtime_context_t*
```
