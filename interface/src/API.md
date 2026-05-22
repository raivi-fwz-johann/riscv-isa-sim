# interface/src 接口说明

本文档只描述 `thirdparty/riscv-isa-sim/interface/src/` 中公开头文件里的主要接口。

约定：

- 每个函数单独列出完整签名。
- 每个函数均按“作用 / 入参 / 出参”分行说明。
- 多个参数逐项展开。
- 以公开 API 为主，不展开私有实现细节。

## 状态导出层

### 模块定位
`spike_state_exporter_t` 负责把 Spike runtime hook 收集成可查询的快照、trap 状态、MMU trace 和访存日志。

### 关键数据结构

- `void spike_observed_insn_t::reset()`
  作用：清空一条观测到的指令状态。
  入参：无。
  出参：无。

- `spike_observed_insn_t`
  作用：保存单条“当前观测指令”的结构化字段。
  关键字段：
  `valid`：该观测条目是否有效。
  `pc / npc`：当前 PC 与 next PC。
  `bits`：指令位。
  `paddr / paddr2`：物理地址信息。
  `in_trap / cause / tval / tval2 / has_tval2`：trap 相关信息。

- `spike_state_snapshot_t`
  作用：保存某个 hart 的单份快照。
  关键字段：
  `observed`：所有 observe hook 共用的单份指令快照，最后写入者生效。
  `in_trap`：当前 hart 是否在 trap。
  `epc`：trap PC。
  `trap_npc`：trap handler PC。
  `cause / tval / tval2 / has_tval2`：trap 附加信息。
  `mmu_trace`：最近一次页表遍历的结构化结果。

- `spike_state_exporter_t::MemLogItem`
  作用：保存一条访存日志。
  关键字段：
  `addr`：虚拟地址。
  `val`：访存值；对普通 load 预记录通常为 `0`。
  `size`：访存字节数。
  `paddr`：物理地址；翻译失败时可能回退为虚拟地址。

### `SpikeStateExporter.hpp`

- `void spike_state_exporter_t::reset(size_t nprocs)`
  作用：按 hart 数量初始化状态导出器内部数组。
  入参：
  `nprocs`：hart 数量。
  出参：无。

- `void spike_state_exporter_t::observe_exec(size_t hart_id, insn_fetch_t* in, reg_t pc, reg_t npc)`
  作用：记录指令执行完成后的状态。
  入参：
  `hart_id`：hart 编号。
  `in`：取指对象指针。
  `pc`：当前 PC。
  `npc`：执行完成后的 next PC。
  出参：无。

- `void spike_state_exporter_t::observe_pre_exec(size_t hart_id, insn_fetch_t* in, reg_t pc)`
  作用：记录指令执行前状态；页面异常场景下也可用。
  入参：
  `hart_id`：hart 编号。
  `in`：取指对象指针。
  `pc`：当前 PC。
  出参：无。

- `reg_t spike_state_exporter_t::observe_trap(size_t hart_id, void* in, reg_t pc, trap_t& t)`
  作用：记录 trap 状态。
  入参：
  `hart_id`：hart 编号。
  `in`：取指对象指针。
  `pc`：trap PC。
  `t`：trap 对象。
  出参：返回值用于上层 trap 处理。

- `void spike_state_exporter_t::observe_trap_target(size_t hart_id, reg_t npc)`
  作用：记录 trap 目标 PC。
  入参：
  `hart_id`：hart 编号。
  `npc`：trap handler 入口 PC。
  出参：无。

- `void spike_state_exporter_t::observe_mmu_walk(const spike_mmu_walk_observe_t& event)`
  作用：记录 MMU 页表遍历。
  入参：
  `event`：页表 walk 事件。
  出参：无。

- `void spike_state_exporter_t::observe_fetch(size_t hart_id, reg_t vaddr, reg_t paddr, reg_t paddr2, insn_bits_t bits, unsigned length)`
  作用：记录一次 icache refill 取指事件。
  入参：
  `hart_id`：hart 编号。
  `vaddr`：虚拟取指地址。
  `paddr`：第一 parcel 的物理地址。
  `paddr2`：最后 parcel 的物理地址。
  `bits`：第一 parcel 刚取回时的原始指令位。
  `length`：指令长度。
  出参：无。

- `const spike_state_snapshot_t* spike_state_exporter_t::snapshot(size_t hart_id) const`
  作用：读取某个 hart 的当前快照。
  入参：
  `hart_id`：hart 编号。
  出参：该 hart 的 `spike_state_snapshot_t` 指针；无效时返回 `nullptr`。

- `MmuTrace spike_state_exporter_t::get_mmu_trace(size_t hart_id) const`
  作用：读取某个 hart 的 MMU trace。
  入参：
  `hart_id`：hart 编号。
  出参：`MmuTrace`。

- `bool spike_state_exporter_t::in_trap(size_t hart_id) const`
  作用：查询某个 hart 是否处于 trap。
  入参：
  `hart_id`：hart 编号。
  出参：`true` 表示处于 trap；`false` 表示不在 trap 中。

- `void spike_state_exporter_t::reset_observed(size_t hart_id)`
  作用：清空某个 hart 的单份 `observed` 快照与相关状态。
  入参：
  `hart_id`：hart 编号。
  出参：无。

- `void spike_state_exporter_t::add_mem_log(size_t hart_id, reg_t addr, uint64_t val, uint8_t size, reg_t paddr, bool is_store)`
  作用：追加一条访存日志。
  入参：
  `hart_id`：hart 编号。
  `addr`：虚拟地址。
  `val`：访存值。
  `size`：访存字节数。
  `paddr`：物理地址。
  `is_store`：`true` 表示 store，`false` 表示 load。
  出参：无。

- `void spike_state_exporter_t::clear_mem_log(size_t hart_id)`
  作用：清空某个 hart 的访存日志。
  入参：
  `hart_id`：hart 编号。
  出参：无。

- `const std::vector<spike_state_exporter_t::MemLogItem>& spike_state_exporter_t::mem_loads(size_t hart_id) const`
  作用：读取某个 hart 的 load 日志。
  入参：
  `hart_id`：hart 编号。
  出参：load 日志数组的常量引用。

- `const std::vector<spike_state_exporter_t::MemLogItem>& spike_state_exporter_t::mem_stores(size_t hart_id) const`
  作用：读取某个 hart 的 store 日志。
  入参：
  `hart_id`：hart 编号。
  出参：store 日志数组的常量引用。

补充语义：

- `on_mem_log(..., is_store=false)` 在普通 load 前会触发一次。
- load fault 场景下，这条记录也会在异常继续抛出前补发一次，因此 `mem_loads()` 中仍可能看到 fault 前的 load 请求。

## Hook 桥接层

### 模块定位
`SpikeSimObjHooker` 是 `spike_hook_dispatcher_t` 的具体实现，把 Spike runtime hook 转发给状态导出器和 ROI 状态机。

### `SpikeSimObjHooker.hpp`

- `SpikeSimObjHooker::SpikeSimObjHooker(spike_state_exporter_t* state_exporter, spike_roi_state_t* roi_state, std::function<void()> stop_fn)`
  作用：构造 hook 转发器。
  入参：
  `state_exporter`：状态导出器指针。
  `roi_state`：ROI 状态机指针。
  `stop_fn`：停止仿真的回调。
  出参：构造完成的 `SpikeSimObjHooker` 对象。

- `bool SpikeSimObjHooker::on_exit(int code) override`
  作用：处理退出事件。
  入参：
  `code`：退出码。
  出参：`true` 表示继续退出；`false` 表示拦截并交给外层收尾。

- `void SpikeSimObjHooker::on_exec_observe(uint32_t hart_id, insn_fetch_t* in, reg_t pc, reg_t npc) override`
  作用：把执行完成事件转给 `spike_state_exporter_t`。
  入参：
  `hart_id`：hart 编号。
  `in`：取指对象指针。
  `pc`：当前 PC。
  `npc`：执行完成后的 next PC。
  出参：无。

- `void SpikeSimObjHooker::on_pre_exec(uint32_t hart_id, insn_fetch_t* in, reg_t pc) override`
  作用：把执行前事件转给 `spike_state_exporter_t`。
  入参：
  `hart_id`：hart 编号。
  `in`：取指对象指针。
  `pc`：当前 PC。
  出参：无。

- `reg_t SpikeSimObjHooker::on_trap(uint32_t hart_id, void* in, reg_t pc, trap_t& t) override`
  作用：把 trap 事件转给 `spike_state_exporter_t`。
  入参：
  `hart_id`：hart 编号。
  `in`：取指对象指针。
  `pc`：trap PC。
  `t`：trap 对象。
  出参：返回值用于上层 trap 处理。

- `void SpikeSimObjHooker::on_trap_target(uint32_t hart_id, reg_t epc, reg_t npc) override`
  作用：把 trap 目标事件转给 `spike_state_exporter_t`。
  入参：
  `hart_id`：hart 编号。
  `epc`：原 trap PC。
  `npc`：trap handler 入口 PC。
  出参：无。

- `void SpikeSimObjHooker::on_device_uart_tx(abstract_device_t* device, uint8_t byte) override`
  作用：把 UART 输出转给 ROI 状态机。
  入参：
  `device`：UART 设备对象。
  `byte`：输出字节值。
  出参：无。

- `void SpikeSimObjHooker::on_mmu_walk(const spike_mmu_walk_observe_t& event) override`
  作用：把 MMU 页表遍历转给 `spike_state_exporter_t`。
  入参：
  `event`：页表 walk 事件。
  出参：无。

- `void SpikeSimObjHooker::on_fetch_observe(uint32_t hart_id, reg_t vaddr, reg_t paddr, reg_t paddr2, insn_bits_t bits, unsigned length) override`
  作用：把 icache refill 事件转给 `spike_state_exporter_t`。
  入参：
  `hart_id`：hart 编号。
  `vaddr`：虚拟地址。
  `paddr`：第一 parcel 物理地址。
  `paddr2`：最后 parcel 物理地址。
  `bits`：第一 parcel 原始指令位。
  `length`：指令长度。
  出参：无。

- `void SpikeSimObjHooker::on_mem_log(uint32_t hart_id, reg_t addr, uint64_t val, uint8_t size, reg_t paddr, bool is_store) override`
  作用：把访存日志转给 `spike_state_exporter_t`。
  入参：
  `hart_id`：hart 编号。
  `addr`：虚拟地址。
  `val`：访存值。
  `size`：访存字节数。
  `paddr`：物理地址。
  `is_store`：是否为 store。
  出参：无。

- `void SpikeSimObjHooker::on_commit_log_reset(uint32_t hart_id) override`
  作用：通知 `spike_state_exporter_t` 清空每条指令的访存日志。
  入参：
  `hart_id`：hart 编号。
  出参：无。

## RawSpike

### 模块定位
`RawSpike` 是最接近底层 Spike 的接口封装，负责创建/驱动模拟器、记录指令、执行地址转换、控制日志和 ROI 状态。

### `RawSpike.hpp`

- `RawSpike::RawSpike()`
  作用：构造 `RawSpike` 实例并准备内部资源。
  入参：无。
  出参：构造完成的 `RawSpike` 对象。

- `RawSpike::~RawSpike()`
  作用：释放 `RawSpike` 持有的模拟器、状态导出器和 ROI 状态等资源。
  入参：无。
  出参：无。

- `void RawSpike::init(const std::string& ArgsStr) override`
  作用：按命令行参数字符串初始化 Spike。
  入参：
  `ArgsStr`：启动参数字符串。
  出参：无。

- `void RawSpike::start() override`
  作用：启动模拟器运行。
  入参：无。
  出参：无。

- `void RawSpike::stop() override`
  作用：停止模拟器运行。
  入参：无。
  出参：无。

- `bool RawSpike::done() const override`
  作用：查询模拟器是否结束。
  入参：无。
  出参：`true` 表示已结束；`false` 表示仍在运行。

- `size_t RawSpike::step(size_t n, uint32_t CId) override`
  作用：推进指定 core 的执行步数。
  入参：
  `n`：要执行的步数。
  `CId`：核心编号。
  出参：实际执行的步数。

- `int RawSpike::record(InstTrace& data, uint32_t CId) override`
  作用：从当前快照与访存日志拼装一条 `InstTrace`。
  入参：
  `data`：待写入的指令轨迹对象。
  `CId`：核心编号。
  出参：记录结果码。

- `InstTrace RawSpike::fetchInstOnly(uint64_t Pc, uint32_t CId, uint64_t IId) override`
  作用：只取一条指令轨迹，不推进完整执行流程。
  入参：
  `Pc`：目标 PC。
  `CId`：核心编号。
  `IId`：期望的指令 ID。
  出参：构造好的 `InstTrace`。

- `uint64_t RawSpike::vaddr2paddr(uint64_t vaddr, uint32_t CId)`
  作用：将虚拟地址转换为物理地址。
  入参：
  `vaddr`：虚拟地址。
  `CId`：核心编号。
  出参：对应的物理地址。

- `MmuTrace RawSpike::getMmuTrace(uint32_t CId)`
  作用：读取指定核心的 MMU trace。
  入参：
  `CId`：核心编号。
  出参：`MmuTrace`。

- `void RawSpike::setupROI(bool val) override`
  作用：开启或关闭 ROI 识别。
  入参：
  `val`：是否启用 ROI。
  出参：无。

- `bool RawSpike::inROI(uint32_t cid) const override`
  作用：查询指定核心是否位于 ROI 中。
  入参：
  `cid`：核心编号。
  出参：`true` 表示在 ROI 中；`false` 表示不在。

- `size_t RawSpike::nproc() const override`
  作用：查询处理器数量。
  入参：无。
  出参：处理器数量。

- `uint64_t RawSpike::getCurrPc(uint32_t cid) const override`
  作用：读取指定核心当前 PC。
  入参：
  `cid`：核心编号。
  出参：当前 PC。

- `bool RawSpike::inTrap(uint32_t CId) const override`
  作用：查询指定核心是否处于 trap 状态。
  入参：
  `CId`：核心编号。
  出参：`true` 表示在 trap 中；`false` 表示不在。

- `bool RawSpike::inWFI(uint32_t CId) const override`
  作用：查询指定核心是否处于 WFI 状态。
  入参：
  `CId`：核心编号。
  出参：`true` 表示在 WFI 中；`false` 表示不在。

- `void RawSpike::setInterleave(size_t val)`
  作用：设置 hart 交错步进粒度。
  入参：
  `val`：interleave 值。
  出参：无。

- `void RawSpike::setLogCommits(bool LogCommits, bool IsFast, uint32_t cid)`
  作用：设置 commit log 模式。
  入参：
  `LogCommits`：是否启用 commit log。
  `IsFast`：是否启用 fast 路径。
  `cid`：核心编号。
  出参：无。

- `void RawSpike::setLogMem(bool val)`
  作用：设置是否记录 memory log。
  入参：
  `val`：是否启用 memory log。
  出参：无。

- `void RawSpike::setCycle(uint64_t Value, uint32_t cid = 0) override final`
  作用：设置指定核心的 cycle 值。
  入参：
  `Value`：新的 cycle 值。
  `cid`：核心编号，默认 `0`。
  出参：无。

- `sim_t* RawSpike::getSpikeSimulator()`
  作用：获取底层 Spike 模拟器对象。
  入参：无。
  出参：`sim_t` 裸指针。

## SpikeSimObjSync

### 模块定位
`SpikeSimObjSync` 是同步模式的功能模拟适配器，负责把 `RawSpike` 包装成上层可直接消费的同步接口。

### `SpikeSimObjSync.hpp`

- `static SpikeSimObjSync& SpikeSimObjSync::globalInstance()`
  作用：获取全局单例对象。
  入参：无。
  出参：全局 `SpikeSimObjSync` 引用。

- `SpikeSimObjSync::SpikeSimObjSync()`
  作用：构造同步接口对象。
  入参：无。
  出参：构造完成的对象。

- `SpikeSimObjSync::~SpikeSimObjSync() override`
  作用：释放同步接口对象持有的资源。
  入参：无。
  出参：无。

- `void SpikeSimObjSync::init(const std::string& ArgsStr) override`
  作用：按字符串参数初始化接口。
  入参：
  `ArgsStr`：参数字符串。
  出参：无。

- `void SpikeSimObjSync::init(const std::vector<std::string>& Args) override`
  作用：按参数列表初始化接口。
  入参：
  `Args`：参数列表。
  出参：无。

- `void SpikeSimObjSync::initROICount(int num) override`
  作用：设置 ROI 计数器。
  入参：
  `num`：ROI 计数数量。
  出参：无。

- `void SpikeSimObjSync::start() override`
  作用：启动同步模拟。
  入参：无。
  出参：无。

- `void SpikeSimObjSync::stop() override`
  作用：停止同步模拟。
  入参：无。
  出参：无。

- `void SpikeSimObjSync::waitStop() override`
  作用：等待停止完成；同步模式下为空实现。
  入参：无。
  出参：无。

- `bool SpikeSimObjSync::done() const override`
  作用：查询仿真是否结束。
  入参：无。
  出参：`true` 表示结束；`false` 表示仍在运行。

- `size_t SpikeSimObjSync::step(size_t n, uint32_t CId = 0) override`
  作用：推进指定核心执行。
  入参：
  `n`：步数。
  `CId`：核心编号，默认 `0`。
  出参：实际执行步数。

- `void SpikeSimObjSync::resetNPc(uint64_t NPc, uint32_t CId = 0) override`
  作用：重置指定核心的 next PC。
  入参：
  `NPc`：新的 next PC。
  `CId`：核心编号，默认 `0`。
  出参：无。

- `InstUserPtr SpikeSimObjSync::reqInst(uint32_t CId = 0) override`
  作用：申请一条待处理指令。
  入参：
  `CId`：核心编号，默认 `0`。
  出参：指令句柄。

- `InstUserPtr SpikeSimObjSync::requestInst(uint64_t expected_pc, uint32_t CId = 0) override`
  作用：按期望 PC 申请一条指令。
  入参：
  `expected_pc`：期望的 PC。
  `CId`：核心编号，默认 `0`。
  出参：指令句柄。

- `void SpikeSimObjSync::freeInst(InstUserPtr& InstPtr, uint32_t CId = 0) override`
  作用：释放指令句柄。
  入参：
  `InstPtr`：待释放的指令句柄。
  `CId`：核心编号，默认 `0`。
  出参：无。

- `void SpikeSimObjSync::freeInst(uint64_t IId, uint32_t CId = 0) override`
  作用：按指令 ID 释放指令。
  入参：
  `IId`：指令 ID。
  `CId`：核心编号，默认 `0`。
  出参：无。

- `std::shared_ptr<InstTrace>& SpikeSimObjSync::takeInst(uint32_t CId = 0) override`
  作用：取走当前生成的指令轨迹。
  入参：
  `CId`：核心编号，默认 `0`。
  出参：指向 `InstTrace` 的共享指针引用。

- `void SpikeSimObjSync::resolve(uint64_t InstUId, uint32_t CId = 0) override`
  作用：标记某条指令已 resolve。
  入参：
  `InstUId`：指令唯一 ID。
  `CId`：核心编号，默认 `0`。
  出参：无。

- `void SpikeSimObjSync::replay(uint64_t InstUId, uint32_t CId = 0) override`
  作用：回放某条指令。
  入参：
  `InstUId`：指令唯一 ID。
  `CId`：核心编号，默认 `0`。
  出参：无。

- `InstTrace SpikeSimObjSync::fetchInstOnly(uint64_t Pc, uint32_t CId = 0, uint64_t IId = INVALID_INST_ID) override`
  作用：仅获取一条指令轨迹。
  入参：
  `Pc`：目标 PC。
  `CId`：核心编号，默认 `0`。
  `IId`：期望指令 ID，默认 `INVALID_INST_ID`。
  出参：`InstTrace`。

- `RawSim* SpikeSimObjSync::getRawSim() override`
  作用：获取底层 `RawSim`。
  入参：无。
  出参：`RawSim` 裸指针。

- `uint64_t SpikeSimObjSync::vaddr2paddr(uint64_t vaddr, uint32_t CId) const override`
  作用：虚拟地址转物理地址。
  入参：
  `vaddr`：虚拟地址。
  `CId`：核心编号。
  出参：物理地址。

- `void SpikeSimObjSync::setCycle(uint64_t value, uint32_t CId = 0) override`
  作用：设置 cycle。
  入参：
  `value`：cycle 值。
  `CId`：核心编号，默认 `0`。
  出参：无。

- `bool SpikeSimObjSync::inROI(uint32_t cid = 0) const override`
  作用：查询是否在 ROI 中。
  入参：
  `cid`：核心编号，默认 `0`。
  出参：布尔值。

- `bool SpikeSimObjSync::inWFI(uint32_t cid = 0) const override`
  作用：查询是否在 WFI 中。
  入参：
  `cid`：核心编号，默认 `0`。
  出参：布尔值。

- `uint64_t SpikeSimObjSync::getCurrPc(uint32_t cid = 0) const override`
  作用：读取当前 PC。
  入参：
  `cid`：核心编号，默认 `0`。
  出参：当前 PC。

- `uint64_t SpikeSimObjSync::getConfiguredNPc(uint32_t cid = 0) const override`
  作用：读取配置的 next PC。
  入参：
  `cid`：核心编号，默认 `0`。
  出参：next PC。

- `const PathHandler& SpikeSimObjSync::getPathHandler(uint32_t CId) const override`
  作用：获取路径处理器。
  入参：
  `CId`：核心编号。
  出参：`PathHandler` 常量引用。

- `uint64_t SpikeSimObjSync::getCurrInstNPc(uint32_t CId) const override`
  作用：读取当前指令的 next PC。
  入参：
  `CId`：核心编号。
  出参：next PC。

- `void SpikeSimObjSync::setInterleave(size_t val) override`
  作用：设置 interleave。
  入参：
  `val`：interleave 值。
  出参：无。

- `void SpikeSimObjSync::setLogMem(bool val) override`
  作用：设置 memory log 开关。
  入参：
  `val`：是否开启。
  出参：无。

- `void SpikeSimObjSync::setLogCommits(bool log_commits, bool is_fast, uint32_t cid = 0) override`
  作用：设置 commit log 开关。
  入参：
  `log_commits`：是否记录 commit log。
  `is_fast`：是否使用 fast 模式。
  `cid`：核心编号，默认 `0`。
  出参：无。

- `InstInfoHolder& SpikeSimObjSync::correctHolder(uint32_t CId) override`
  作用：获取正确路径的指令缓存容器。
  入参：
  `CId`：核心编号。
  出参：`InstInfoHolder` 引用。

- `const InstInfoHolder& SpikeSimObjSync::correctHolder(uint32_t CId) const override`
  作用：获取正确路径的指令缓存容器只读视图。
  入参：
  `CId`：核心编号。
  出参：`InstInfoHolder` 常量引用。

- `InstInfoHolder& SpikeSimObjSync::missHolder(uint32_t CId) override`
  作用：获取 miss 路径的指令缓存容器。
  入参：
  `CId`：核心编号。
  出参：`InstInfoHolder` 引用。

- `const InstInfoHolder& SpikeSimObjSync::missHolder(uint32_t CId) const override`
  作用：获取 miss 路径的指令缓存容器只读视图。
  入参：
  `CId`：核心编号。
  出参：`InstInfoHolder` 常量引用。

- `uint64_t& SpikeSimObjSync::missIdCursor(uint32_t CId) override`
  作用：获取 miss 路径的指令 ID 游标。
  入参：
  `CId`：核心编号。
  出参：游标引用。

- `uint64_t SpikeSimObjSync::backendCurrPc(uint32_t CId) const override`
  作用：读取后端当前 PC。
  入参：
  `CId`：核心编号。
  出参：后端 PC。

## SpikeSimObjAsync

### 模块定位
`SpikeSimObjAsync` 在同步接口基础上加入后台线程和指令缓冲，用于异步生产/消费指令轨迹。

### `SpikeSimObjAsync.hpp`

- `SpikeSimObjAsync::SpikeSimObjAsync()`
  作用：构造异步接口对象。
  入参：无。
  出参：构造完成的对象。

- `SpikeSimObjAsync::~SpikeSimObjAsync() override`
  作用：释放异步线程和缓冲资源。
  入参：无。
  出参：无。

- `void SpikeSimObjAsync::initROICount(int num) override`
  作用：设置 ROI 计数器。
  入参：
  `num`：ROI 计数数量。
  出参：无。

- `void SpikeSimObjAsync::start() override`
  作用：启动异步工作线程。
  入参：无。
  出参：无。

- `void SpikeSimObjAsync::stop() override`
  作用：停止异步工作线程。
  入参：无。
  出参：无。

- `void SpikeSimObjAsync::waitStop() override`
  作用：等待异步工作线程退出。
  入参：无。
  出参：无。

- `bool SpikeSimObjAsync::done() const override`
  作用：查询是否结束。
  入参：无。
  出参：布尔值。

- `size_t SpikeSimObjAsync::step(size_t n, uint32_t CId = 0) override`
  作用：推进异步接口执行。
  入参：
  `n`：步数。
  `CId`：核心编号，默认 `0`。
  出参：实际执行步数。

- `std::shared_ptr<InstTrace>& SpikeSimObjAsync::takeInst(uint32_t CId = 0) override`
  作用：取走异步缓冲中的指令轨迹。
  入参：
  `CId`：核心编号，默认 `0`。
  出参：共享指针引用。

- `bool SpikeSimObjAsync::inROI(uint32_t cid = 0) const override`
  作用：查询是否在 ROI 中。
  入参：
  `cid`：核心编号，默认 `0`。
  出参：布尔值。

## ROI 状态层

### 模块定位
`spike_roi_state_t` 负责通过 UART 输出中的 marker 串识别 ROI 起止区间。

### `SpikeRoiState.hpp`

- `void spike_roi_state_t::set_enabled(bool enabled)`
  作用：开启或关闭 ROI 识别。
  入参：
  `enabled`：是否启用。
  出参：无。

- `bool spike_roi_state_t::enabled() const`
  作用：查询 ROI 识别是否启用。
  入参：无。
  出参：布尔值。

- `bool spike_roi_state_t::in_roi() const`
  作用：查询当前是否在 ROI 中。
  入参：无。
  出参：布尔值。

- `void spike_roi_state_t::on_device_uart_tx(abstract_device_t* device, uint8_t byte)`
  作用：根据 UART 输出更新 ROI 状态。
  入参：
  `device`：UART 设备对象。
  `byte`：输出字节。
  出参：无。

## SpikeBase / SpikeProc / ProcProxy

### 模块定位
这组接口是较老的上层封装路径：`SpikeBase` 定义通用抽象，`SpikeProc` 基于外部进程代理实现，`ProcProxy` 负责底层进程通信。

### `SpikeBase.hpp`

- `void SpikeStat::print() const`
  作用：打印当前统计信息。
  入参：无。
  出参：无。

- `static std::unique_ptr<SpikeBase> SpikeBase::create(const std::string& type)`
  作用：按类型创建具体 `SpikeBase` 实现。
  入参：
  `type`：实现类型名。
  出参：创建好的 `SpikeBase` 对象。

- `virtual ~SpikeBase() = default`
  作用：作为基类析构函数，保证派生类正确析构。
  入参：无。
  出参：无。

- `virtual void SpikeBase::init(std::vector<std::string>& args) = 0`
  作用：按参数列表初始化派生实现。
  入参：
  `args`：参数列表。
  出参：无。

- `void SpikeBase::init(const std::string& args_str)`
  作用：按字符串参数初始化，内部通常会拆分后调用向量版本。
  入参：
  `args_str`：参数字符串。
  出参：无。

- `virtual void SpikeBase::step(size_t n) = 0`
  作用：推进执行步数。
  入参：
  `n`：步数。
  出参：无。

- `const SpikeStat& SpikeBase::getStat(uint64_t proc = 0)`
  作用：读取指定处理器的统计信息。
  入参：
  `proc`：处理器编号，默认 `0`。
  出参：`SpikeStat` 常量引用。

- `virtual bool SpikeBase::isEnd() const = 0`
  作用：查询是否结束。
  入参：无。
  出参：布尔值。

### `SpikeProc.hpp`

- `SpikeProc::SpikeProc()`
  作用：构造进程代理实现。
  入参：无。
  出参：构造完成的对象。

- `SpikeProc::~SpikeProc()`
  作用：释放进程代理资源。
  入参：无。
  出参：无。

- `void SpikeProc::init(std::vector<std::string>& args) override`
  作用：按参数列表初始化进程代理。
  入参：
  `args`：参数列表。
  出参：无。

- `void SpikeProc::step(size_t n = 1) override`
  作用：推进进程代理执行。
  入参：
  `n`：步数，默认 `1`。
  出参：无。

- `bool SpikeProc::isEnd() const override`
  作用：查询是否结束。
  入参：无。
  出参：布尔值。

### `ProcProxy.hpp`

- `ProcProxy::ProcProxy()`
  作用：构造代理对象。
  入参：无。
  出参：构造完成的对象。

- `ProcProxy::~ProcProxy()`
  作用：释放代理资源。
  入参：无。
  出参：无。

- `void ProcProxy::launchProc(const std::vector<std::string>& args)`
  作用：按参数启动外部进程。
  入参：
  `args`：命令参数列表。
  出参：无。

- `int ProcProxy::execCmdWithRes(const char* cmd, int size, const char* end_flag)`
  作用：执行命令并读取结果。
  入参：
  `cmd`：命令字符串。
  `size`：读取大小。
  `end_flag`：结束标记。
  出参：返回结果码或读取状态。

- `int ProcProxy::execCmd(const char* cmd)`
  作用：执行命令但不显式返回结果块。
  入参：
  `cmd`：命令字符串。
  出参：返回结果码。

- `int ProcProxy::readRes(int size, const char* end_flag)`
  作用：从缓冲区读取回传结果。
  入参：
  `size`：读取大小。
  `end_flag`：结束标记。
  出参：读取状态码。

- `bool ProcProxy::exists() const`
  作用：查询代理进程是否存在。
  入参：无。
  出参：布尔值。

- `bool ProcProxy::connecting() const`
  作用：查询是否处于连接中。
  入参：无。
  出参：布尔值。

- `bool ProcProxy::isCommEnd() const`
  作用：查询通信是否结束。
  入参：无。
  出参：布尔值。

- `void ProcProxy::setCommEndFlag(const std::string& str)`
  作用：设置通信结束标记。
  入参：
  `str`：结束标记字符串。
  出参：无。

## 其他辅助接口

### `Disassembler.hpp`

- `Disassembler::Disassembler(const std::string& isa, const std::string& priv)`
  作用：按 ISA 和特权级初始化反汇编器。
  入参：
  `isa`：ISA 字符串。
  `priv`：特权级字符串。
  出参：构造完成的对象。

- `Disassembler::Disassembler()`
  作用：构造默认反汇编器。
  入参：无。
  出参：构造完成的对象。

- `Disassembler::Disassembler(const Disassembler& That) = delete`
  作用：禁止拷贝构造。
  入参：
  `That`：被拷贝对象。
  出参：无。

- `Disassembler::~Disassembler()`
  作用：释放内部反汇编器实现。
  入参：无。
  出参：无。

- `std::string Disassembler::disassemble(InsnBits Bits) const`
  作用：将指令位反汇编成字符串。
  入参：
  `Bits`：指令位。
  出参：反汇编字符串。

- `bool Disassembler::isRV64() const`
  作用：查询当前是否为 RV64 模式。
  入参：无。
  出参：布尔值。

### `run_helper.h`

- `void run_helper_t::start(sim_t* sim)`
  作用：启动模拟器。
  入参：
  `sim`：模拟器对象。
  出参：无。

- `void run_helper_t::stop(sim_t* sim)`
  作用：停止模拟器。
  入参：
  `sim`：模拟器对象。
  出参：无。

- `size_t run_helper_t::step(sim_t* sim, size_t n, size_t proc)`
  作用：推进模拟器步数。
  入参：
  `sim`：模拟器对象。
  `n`：步数。
  `proc`：处理器编号。
  出参：实际执行步数。

### `spike_init.h`

- `static std::unique_ptr<spike_boot_result_t> spike_init(int argc, char** argv, sim_t*& spike_sim, cfg_t& cfg, std::function<void(sim_t*)> callback = [](sim_t*) {})`
  作用：解析命令行、执行 bootstrap，并把结果中的 `cfg` 和 `sim` 回填给调用方。
  入参：
  `argc`：参数个数。
  `argv`：参数数组。
  `spike_sim`：输出参数，返回创建好的 `sim_t*`。
  `cfg`：输出参数，返回当前配置。
  `callback`：可选回调，在 `sim_t` 创建后执行。
  出参：持有启动结果的 `std::unique_ptr<spike_boot_result_t>`。

## 说明

`Memory.hpp` 当前只承担公共类型依赖，没有对外公开函数接口，因此不单独展开函数列表。
