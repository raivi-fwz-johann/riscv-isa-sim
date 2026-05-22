# extensions 接口说明

本文档只描述 `thirdparty/riscv-isa-sim/extensions/` 中公开头文件里的主要接口。

约定：

- 每个函数单独列出完整签名。
- 每个函数均按“作用 / 入参 / 出参”分行说明。
- 多个参数逐项展开。
- 以公开 API 为主，不展开私有实现细节。

## runtime

### 模块定位
`runtime/` 是 Spike 运行时扩展总线。它把 hook、日志、兼容策略、host 策略和 checkpoint 控制器统一挂到 `sim_t` 上。

### `runtime_context.h`

- `spike_runtime_context_t::spike_runtime_context_t()`
  作用：构造默认运行时上下文，并创建默认的 hook dispatcher、log manager、model compat、host policy、checkpoint controller。
  入参：无。
  出参：构造完成的 `spike_runtime_context_t` 对象。

- `spike_hook_dispatcher_t* spike_runtime_context_t::hook_dispatcher() const`
  作用：获取当前安装的 hook 分发器。
  入参：无。
  出参：当前 `spike_hook_dispatcher_t` 的裸指针；未安装时返回 `nullptr`。

- `void spike_runtime_context_t::set_hook_dispatcher(std::unique_ptr<spike_hook_dispatcher_t> hook)`
  作用：替换当前 hook 分发器。
  入参：
  `hook`：新的 hook dispatcher；所有权转入 `spike_runtime_context_t`。
  出参：无。

- `spike_log_manager_t* spike_runtime_context_t::log_manager() const`
  作用：获取日志配置管理器。
  入参：无。
  出参：当前 `spike_log_manager_t` 的裸指针；未安装时返回 `nullptr`。

- `void spike_runtime_context_t::set_log_manager(std::unique_ptr<spike_log_manager_t> log_manager)`
  作用：替换日志配置管理器。
  入参：
  `log_manager`：新的日志管理对象；所有权转入 `spike_runtime_context_t`。
  出参：无。

- `spike_model_compat_t* spike_runtime_context_t::model_compat() const`
  作用：获取模型兼容策略对象。
  入参：无。
  出参：当前 `spike_model_compat_t` 的裸指针；未安装时返回 `nullptr`。

- `void spike_runtime_context_t::set_model_compat(std::unique_ptr<spike_model_compat_t> model_compat)`
  作用：替换模型兼容策略对象。
  入参：
  `model_compat`：新的兼容策略对象；所有权转入 `spike_runtime_context_t`。
  出参：无。

- `spike_host_policy_t* spike_runtime_context_t::host_policy() const`
  作用：获取 host 策略对象。
  入参：无。
  出参：当前 `spike_host_policy_t` 的裸指针；未安装时返回 `nullptr`。

- `void spike_runtime_context_t::set_host_policy(std::unique_ptr<spike_host_policy_t> host_policy)`
  作用：替换 host 策略对象。
  入参：
  `host_policy`：新的 host policy 对象；所有权转入 `spike_runtime_context_t`。
  出参：无。

- `checkpoint_controller_t* spike_runtime_context_t::checkpoint_controller() const`
  作用：获取 checkpoint 控制器。
  入参：无。
  出参：当前 `checkpoint_controller_t` 的裸指针；未安装时返回 `nullptr`。

- `void spike_runtime_context_t::set_checkpoint_controller(std::unique_ptr<checkpoint_controller_t> controller)`
  作用：替换 checkpoint 控制器。
  入参：
  `controller`：新的 checkpoint controller；所有权转入 `spike_runtime_context_t`。
  出参：无。

### `spike_hook_dispatcher.h`

- `virtual void spike_hook_dispatcher_t::on_decode(void* instr, reg_t pc, reg_t npc)`
  作用：在指令 decode 完成、执行前提供观察点。
  入参：
  `instr`：解码后的指令对象指针。
  `pc`：当前指令的虚拟地址。
  `npc`：候选下一条 PC。
  出参：无。

- `virtual bool spike_hook_dispatcher_t::on_commit()`
  作用：在 commit log 即将输出时参与控制。
  入参：无。
  出参：`true` 表示调用方可据此抑制默认 commit 处理；`false` 表示保持默认行为。

- `virtual reg_t spike_hook_dispatcher_t::on_next_pc(reg_t candidate_npc)`
  作用：允许 hook 覆盖下一条 PC。
  入参：
  `candidate_npc`：执行单元给出的候选 next PC。
  出参：最终应使用的 next PC。

- `virtual reg_t spike_hook_dispatcher_t::on_trap(uint32_t hart_id, void* fetch, reg_t epc, trap_t& t)`
  作用：在 trap 进入常规处理前提供拦截点。
  入参：
  `hart_id`：触发 trap 的 hart 编号。
  `fetch`：触发 trap 的取指信息指针。
  `epc`：trap 指令的 PC。
  `t`：trap 对象，包含 cause、tval 等信息。
  出参：非零返回值可让调用方跳过常规 trap 流程。

- `virtual void spike_hook_dispatcher_t::on_trap_target(uint32_t hart_id, reg_t epc, reg_t npc)`
  作用：在 trap 目标 PC 确定后提供观察点。
  入参：
  `hart_id`：hart 编号。
  `epc`：原 trap PC。
  `npc`：trap handler 入口 PC。
  出参：无。

- `virtual bool spike_hook_dispatcher_t::should_continue()`
  作用：轮询式控制 hart 是否继续执行。
  入参：无。
  出参：`true` 表示继续执行；`false` 表示暂停。

- `virtual void spike_hook_dispatcher_t::on_fake_step(size_t instret, size_t prev_instret)`
  作用：处理 instret 前进但没有执行真实指令的场景。
  入参：
  `instret`：当前 instret 值。
  `prev_instret`：前一个 instret 值。
  出参：无。

- `virtual void spike_hook_dispatcher_t::on_pre_store(reg_t addr, reg_t val, uint32_t size, std::shared_ptr<bool> real_store)`
  作用：在 store 真正落存前提供拦截点。
  入参：
  `addr`：目标虚拟地址。
  `val`：准备写入的值。
  `size`：写入字节数。
  `real_store`：共享控制位；可被改写为 `false` 以阻止真实 store。
  出参：无；是否执行真实 store 通过 `real_store` 间接反馈。

- `virtual void spike_hook_dispatcher_t::on_mem_log(uint32_t hart_id, reg_t addr, uint64_t val, uint8_t size, reg_t paddr, bool is_store)`
  作用：统一观察 architecturally visible 的 load/store 访存事件。
  入参：
  `hart_id`：hart 编号。
  `addr`：虚拟地址。
  `val`：访存值；对普通 load 预记录通常为 `0`，对 store 为待写入值。
  `size`：访存字节数。
  `paddr`：物理地址；若翻译失败，调用方可能回退为虚拟地址。
  `is_store`：`true` 表示 store，`false` 表示 load。
  出参：无。
  额外语义：
  `on_mem_log(..., is_store=false)` 在普通 load 前会触发一次。
  load fault 场景下，该回调也会在异常继续抛出前补发一次，因此模型侧仍可保留 fault 前的 load 请求。

- `virtual void spike_hook_dispatcher_t::on_commit_log_reset(uint32_t hart_id)`
  作用：在每条指令开始前重置与 commit log 相关的扩展状态。
  入参：
  `hart_id`：hart 编号。
  出参：无。

- `virtual bool spike_hook_dispatcher_t::allow_csr_write(int csr, reg_t val)`
  作用：判定 CSR 写入是否允许。
  入参：
  `csr`：CSR 编号。
  `val`：准备写入的值。
  出参：`true` 表示允许写入；`false` 表示阻止写入。

- `virtual void spike_hook_dispatcher_t::on_pre_csr(int csr, reg_t val, std::shared_ptr<bool> allow)`
  作用：在 CSR 写入前提供观察与拦截点。
  入参：
  `csr`：CSR 编号。
  `val`：准备写入的值。
  `allow`：共享控制位；可被改写为 `false` 以阻止写入。
  出参：无；允许/禁止结果通过 `allow` 间接反馈。

- `virtual bool spike_hook_dispatcher_t::on_exit(int code)`
  作用：在 Spike 退出前决定是否执行硬退出。
  入参：
  `code`：退出码。
  出参：`true` 表示继续执行硬退出；`false` 表示交给上层做受控退出。

- `virtual void spike_hook_dispatcher_t::on_exec_observe(uint32_t hart_id, insn_fetch_t* fetch, reg_t pc, reg_t npc)`
  作用：在指令执行完成后提供观察点。
  入参：
  `hart_id`：hart 编号。
  `fetch`：解码后的取指对象。
  `pc`：当前 PC。
  `npc`：执行完成后的 next PC。
  出参：无。

- `virtual void spike_hook_dispatcher_t::on_pre_exec(uint32_t hart_id, insn_fetch_t* fetch, reg_t pc)`
  作用：在 `fetch.func()` 执行前提供观察点；页面异常场景下仍会触发。
  入参：
  `hart_id`：hart 编号。
  `fetch`：解码后的取指对象。
  `pc`：当前 PC。
  出参：无。

- `virtual void spike_hook_dispatcher_t::on_fetch_observe(uint32_t hart_id, reg_t vaddr, reg_t paddr, reg_t paddr2, insn_bits_t bits, unsigned length)`
  作用：在 icache refill 时观察取指信息。
  入参：
  `hart_id`：hart 编号。
  `vaddr`：虚拟取指地址。
  `paddr`：第一 parcel 的物理地址。
  `paddr2`：最后一个 parcel 的物理地址；跨页指令时与 `paddr` 可能不同。
  `bits`：第一 parcel 刚取回时的原始指令位。
  `length`：指令长度，单位字节。
  出参：无。

- `virtual void spike_hook_dispatcher_t::on_device_uart_tx(abstract_device_t* device, uint8_t byte)`
  作用：观察 UART 输出字节。
  入参：
  `device`：UART 设备对象。
  `byte`：输出字节值。
  出参：无。

- `virtual void spike_hook_dispatcher_t::on_mmu_walk(const spike_mmu_walk_observe_t& event)`
  作用：观察一次 MMU 页表遍历。
  入参：
  `event`：页表 walk 元数据，包含 hart、虚拟地址、物理地址、PTE 地址和翻译标志。
  出参：无。

### `spike_log_manager.h`

- `const spike_log_config_t& spike_log_manager_t::config() const`
  作用：读取当前整包日志配置。
  入参：无。
  出参：`spike_log_config_t` 常量引用。

- `void spike_log_manager_t::set_config(const spike_log_config_t& config)`
  作用：整包替换日志配置。
  入参：
  `config`：新的日志配置对象。
  出参：无。

- `bool spike_log_manager_t::enable_commit_log_stant() const`
  作用：读取普通 commit log 开关。
  入参：无。
  出参：当前是否启用普通 commit log。

- `void spike_log_manager_t::set_enable_commit_log_stant(bool value)`
  作用：设置普通 commit log 开关。
  入参：
  `value`：新的开关值。
  出参：无。

- `bool spike_log_manager_t::enable_fast_commit_log() const`
  作用：读取 fast commit log 开关。
  入参：无。
  出参：当前是否启用 fast commit log。

- `void spike_log_manager_t::set_enable_fast_commit_log(bool value)`
  作用：设置 fast commit log 开关。
  入参：
  `value`：新的开关值。
  出参：无。

- `bool spike_log_manager_t::enable_fast_mem_log() const`
  作用：读取 fast memory log 开关。
  入参：无。
  出参：当前是否启用 fast memory log。

- `void spike_log_manager_t::set_enable_fast_mem_log(bool value)`
  作用：设置 fast memory log 开关。
  入参：
  `value`：新的开关值。
  出参：无。

- `bool spike_log_manager_t::enable_raw_commit_log() const`
  作用：读取 raw commit log 开关。
  入参：无。
  出参：当前是否启用 raw commit log。

- `void spike_log_manager_t::set_enable_raw_commit_log(bool value)`
  作用：设置 raw commit log 开关。
  入参：
  `value`：新的开关值。
  出参：无。

- `bool spike_log_manager_t::log_print_enabled() const`
  作用：查询 `commit_log_print_insn()` 是否允许输出文本日志行。
  入参：无。
  出参：`true` 表示允许打印；`false` 表示直接跳过打印。

- `void spike_log_manager_t::set_log_print_enabled(bool value)`
  作用：设置 `commit_log_print_insn()` 的文本打印总开关。
  入参：
  `value`：新的打印开关值。
  出参：无。

### `spike_host_policy.h`

- `bool spike_host_policy_t::disable_host() const`
  作用：查询是否禁用 HTIF host 路径。
  入参：无。
  出参：`true` 表示禁用；`false` 表示保留默认 host 行为。

- `void spike_host_policy_t::set_disable_host(bool value)`
  作用：设置是否禁用 HTIF host 路径。
  入参：
  `value`：host 禁用开关。
  出参：无。

### `spike_model_compat.h`

- `bool spike_model_compat_t::preserve_lr_sc_reservation_across_interleave() const`
  作用：查询 hart 交错执行时是否保留 LR/SC reservation。
  入参：无。
  出参：`true` 表示保留；`false` 表示沿用 Spike 默认让出行为。

- `void spike_model_compat_t::set_preserve_lr_sc_reservation_across_interleave(bool value)`
  作用：设置 hart interleave 时的 LR/SC reservation 保留策略。
  入参：
  `value`：策略开关。
  出参：无。

- `spike_explicit_isa_scope_t::spike_explicit_isa_scope_t(const std::optional<std::string>& isa)`
  作用：以 RAII 方式为当前线程安装一个临时 ISA 覆盖。
  入参：
  `isa`：可选 ISA 字符串；传 `std::nullopt` 表示清空覆盖。
  出参：构造完成的 `spike_explicit_isa_scope_t` 对象。

- `spike_explicit_isa_scope_t::~spike_explicit_isa_scope_t()`
  作用：离开作用域时恢复上一个 ISA 覆盖状态。
  入参：无。
  出参：无。

- `const char* spike_resolve_boot_isa_override(const char* dtb_file, const char* dtb_isa)`
  作用：决定启动时最终使用的 ISA 字符串。
  入参：
  `dtb_file`：DTB 文件路径，可为空。
  `dtb_isa`：从 DTB 推导出的 ISA 字符串。
  出参：最终应使用的 ISA 字符串指针。

- `bool spike_should_yield_load_reservation_on_interleave(const sim_t* sim)`
  作用：决定 hart interleave 时是否让出 load reservation。
  入参：
  `sim`：模拟器对象指针，可为空。
  出参：`true` 表示应让出 reservation；`false` 表示保留。

### `spike_device_observe_registry.h`

- `void spike_register_device_runtime_context(abstract_device_t* device, spike_runtime_context_t* runtime_context)`
  作用：注册设备对象和 runtime context 的对应关系。
  入参：
  `device`：设备对象指针。
  `runtime_context`：所属运行时上下文指针。
  出参：无。

- `void spike_unregister_device_runtime_context(const abstract_device_t* device)`
  作用：移除设备对象和 runtime context 的对应关系。
  入参：
  `device`：设备对象指针。
  出参：无。

- `spike_runtime_context_t* spike_find_device_runtime_context(const abstract_device_t* device)`
  作用：根据设备对象反查其所属 runtime context。
  入参：
  `device`：设备对象指针。
  出参：找到时返回 runtime context 指针；未找到时返回 `nullptr`。

## checkpoint

### 模块定位
`checkpoint/` 负责 checkpoint 的保存与恢复，包括寄存器状态、主存镜像、bootrom、HTIF 状态，以及恢复流程所需的 ROM 构造逻辑。

### `checkpoint_controller.h`

- `std::unique_ptr<checkpoint_controller_t> make_checkpoint_controller(checkpoint_legacy_config_t config)`
  作用：根据 legacy checkpoint 配置创建具体控制器实现。
  入参：
  `config`：checkpoint 配置，主要包含 load/save 前缀和压缩选项。
  出参：具体的 `checkpoint_controller_t` 实例。

- `virtual bool checkpoint_controller_t::enabled() const`
  作用：查询 checkpoint 功能是否整体启用。
  入参：无。
  出参：`true` 表示至少存在 load/save 目标；`false` 表示 checkpoint 不生效。

- `virtual bool checkpoint_controller_t::has_load_target() const`
  作用：查询是否配置了恢复目标。
  入参：无。
  出参：`true` 表示存在 snapshot load 前缀；`false` 表示不存在。

- `virtual bool checkpoint_controller_t::has_save_target() const`
  作用：查询是否配置了保存目标。
  入参：无。
  出参：`true` 表示存在 snapshot save 前缀；`false` 表示不存在。

- `virtual void checkpoint_controller_t::prepare_restore(sim_t& sim, bool has_elf)`
  作用：在启动完成、reset 前准备恢复环境。
  入参：
  `sim`：当前模拟器对象。
  `has_elf`：是否存在 ELF/bootstrap 程序参与恢复。
  出参：无。

- `virtual void checkpoint_controller_t::on_post_reset(sim_t& sim)`
  作用：在 reset 后继续执行恢复阶段逻辑。
  入参：
  `sim`：当前模拟器对象。
  出参：无。

- `virtual void checkpoint_controller_t::request_save()`
  作用：登记一次 checkpoint 保存请求。
  入参：无。
  出参：无。

- `virtual bool checkpoint_controller_t::save_requested() const`
  作用：查询当前是否已有待处理的保存请求。
  入参：无。
  出参：`true` 表示已有保存请求；`false` 表示没有。

- `virtual void checkpoint_controller_t::save(sim_t& sim)`
  作用：执行一次完整的 checkpoint 保存流程。
  入参：
  `sim`：当前模拟器对象。
  出参：无。

### `checkpoint_files.h`

- `checkpoint_paths_t checkpoint_paths_t::from_prefix(const std::string& prefix)`
  作用：把一个 checkpoint 前缀展开成标准路径集合。
  入参：
  `prefix`：用户指定的 checkpoint 文件前缀。
  出参：包含 `bootram`、`mainram`、`mainram_zip`、`mainram_zst`、`htif`、`regs` 等路径的 `checkpoint_paths_t`。

- `std::filesystem::path select_checkpoint_mainram_for_load(const checkpoint_paths_t& paths, checkpoint_legacy_config_t& config)`
  作用：根据路径集合和压缩配置选择实际用于加载的 mainram 文件。
  入参：
  `paths`：展开后的 checkpoint 路径集合。
  `config`：checkpoint 配置；函数可能据此调整压缩选择。
  出参：最终被选中的 mainram 文件路径。

- `checkpoint_htif_state_t load_checkpoint_htif(const checkpoint_paths_t& paths)`
  作用：读取 checkpoint 中保存的 HTIF 状态。
  入参：
  `paths`：展开后的 checkpoint 路径集合。
  出参：包含 `tohost_addr` 和 `fromhost_addr` 的 `checkpoint_htif_state_t`。

- `void save_checkpoint_htif(const checkpoint_paths_t& paths, const checkpoint_htif_state_t& state)`
  作用：保存 HTIF 状态到 checkpoint 文件。
  入参：
  `paths`：展开后的 checkpoint 路径集合。
  `state`：待保存的 HTIF 状态。
  出参：无。

- `void compress_checkpoint_mainram(const std::filesystem::path& source, const checkpoint_legacy_config_t& config)`
  作用：按配置压缩 mainram 镜像。
  入参：
  `source`：原始 mainram 文件路径。
  `config`：压缩配置。
  出参：无。

- `void decompress_checkpoint_mainram(const std::filesystem::path& source, const std::filesystem::path& output_dir, const checkpoint_legacy_config_t& config)`
  作用：把压缩 mainram 解压到指定目录。
  入参：
  `source`：压缩镜像路径。
  `output_dir`：解压输出目录。
  `config`：压缩配置。
  出参：无。

### `checkpoint_restore_rom.h`

- `std::vector<char> build_checkpoint_trampoline_rom(unsigned xlen, reg_t target_pc)`
  作用：构造最小 trampoline ROM，把控制流跳到目标 PC。
  入参：
  `xlen`：目标 hart 位宽。
  `target_pc`：恢复后目标 PC。
  出参：ROM 字节数组。

- `std::vector<char> build_checkpoint_restore_rom(sim_t& sim, clint_t& clint, const std::string& dtb)`
  作用：构造 checkpoint 恢复流程使用的 bootrom 内容。
  入参：
  `sim`：当前模拟器对象。
  `clint`：CLINT 设备对象。
  `dtb`：设备树二进制内容。
  出参：ROM 字节数组。

- `std::unique_ptr<rom_device_t> load_checkpoint_bootrom_file(const std::string& path)`
  作用：从 bootrom 文件直接构造 `rom_device_t`。
  入参：
  `path`：bootrom 文件路径。
  出参：构造完成的 `rom_device_t` 对象。

## integration

### 模块定位
`integration/` 负责把命令行参数、配置修正、内存构造、`sim_t` 创建、runtime 初始化、checkpoint 接入以及 cache/extension 注册这些步骤串成一次完整启动流程。

### `spike_bootstrap.h`

- `spike_boot_result_t::spike_boot_result_t()`
  作用：构造一个空的启动结果对象，用于接管后续创建出来的资源。
  入参：无。
  出参：空的 `spike_boot_result_t` 对象。

- `spike_boot_result_t::~spike_boot_result_t()`
  作用：释放 `cfg`、`sim`、cache、JTAG/RBB 等由启动流程获得的资源。
  入参：无。
  出参：无。

- `spike_boot_options_t spike_parse_argv_options(int argc, char** argv)`
  作用：把命令行参数解析成标准化的启动选项。
  入参：
  `argc`：参数个数。
  `argv`：参数数组。
  出参：填充后的 `spike_boot_options_t`。

- `void spike_prepare_boot_options(spike_boot_options_t& options)`
  作用：对启动选项做一致性检查、默认值补全和互斥关系修正。
  入参：
  `options`：待修正的启动选项对象；按引用传入并原地修改。
  出参：无。

- `spike_boot_result_t spike_bootstrap(spike_boot_options_t options, const std::function<void(sim_t*)>& on_sim_created = {})`
  作用：执行完整启动流程，创建 `sim_t`，装载内存与外设，挂接 runtime/checkpoint，并返回资源集合。
  入参：
  `options`：启动配置副本。
  `on_sim_created`：可选回调；在 `sim_t` 创建后立即调用。
  出参：包含 `cfg`、`sim`、memory、cache、JTAG/RBB 等对象的 `spike_boot_result_t`。

### 关键数据结构

- `spike_boot_options_t`
  作用：integration 模块的核心输入结构。
  关键字段：
  `debug / halted / histogram / log`：运行模式开关。
  `dtb_enabled / dtb_discovery / dtb_file`：设备树配置。
  `kernel / initrd / explicit_isa`：启动镜像与 ISA 覆写。
  `checkpoint`：checkpoint 配置。
  `plugin_device_factories / extensions`：设备与扩展工厂。
  `ic / dc / l2`：cache 模型对象。
  `htif_args`：传递给 HTIF 的目标程序参数。

- `spike_boot_result_t`
  作用：integration 模块的统一输出结构。
  关键字段：
  `cfg`：最终生效的配置对象。
  `sim`：构造完成的 Spike 模拟器。
  `mems`：主存布局。
  `ic / dc / l2`：cache 模型对象。
  `remote_bitbang / jtag_dtm`：调试接口对象。
  `dump_dts_only`：是否仅输出 DTS 后退出。
