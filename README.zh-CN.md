# Untrunc Windows 简体中文 GUI

本分支基于 [anthwlock/untrunc](https://github.com/anthwlock/untrunc) 开发，保留原有修复引擎，仅汉化 `src/gui/gui.cpp` 中的可见界面文本及相关 GUI 提示。

## 下载安装

从 [GitHub Releases](../../releases) 选择适合自己的版本：

- 安装版：`Untrunc-zhCN-x64-Setup-v2026.11.05.4.exe`，支持中文安装向导、开始菜单、可选桌面快捷方式、当前用户安装及卸载。
- 便携版：`untrunc_zh-CN_x64.zip`，解压后直接运行 `untrunc-gui.exe`。

两种版本使用相同修复引擎，无需同时安装。安装包未做代码签名，Windows SmartScreen 可能给出警告，请核对来源与校验值。

## 使用

1. 在“视频修复”页选择**参考视频**：同设备、同视频编码和尽可能相同录制参数的正常视频。
2. 选择**损坏视频**：需要尝试恢复的 MP4/MOV 文件。
3. 点击“修复”，等待日志出现“修复完成！”或检查错误信息。
4. 输出文件位置和命名规则沿用上游实现。建议提前备份原始视频，并先在复制文件上测试。

“分析”页提供导出样本、媒体信息、Atom 搜索等上游功能；“设置”页部分选项为高级选项，`-sv` 仍属测试功能。

## 范围与局限

- 仅 GUI 文案汉化；修复引擎输出的部分技术日志仍为英文。
- 未更改 MP4/MOV 修复算法和 FFmpeg/LibUI 依赖。
- 不能保证恢复任意损坏视频；需进行真实样本验证。
- Windows x64 工作流沿用上游 FFmpeg 3.3.4、libui alpha4.1、MSYS2/MinGW 依赖。
- 本项目保留上游 GPL-2.0 许可；分发时需遵守对应许可证。

## 构建

代码推送至 `master` 或 `feat/zh-cn-windows-gui` 时触发 `.github/workflows/release.yml`；也可以在 Actions 页面手动运行 Workflow。默认构建 Windows x64 便携 ZIP 与 Inno Setup 安装包，测试静默安装/卸载后上传两个 Artifact，不会自动覆盖 GitHub Release。

上游仓库及原许可证：<https://github.com/anthwlock/untrunc>、[COPYING](./COPYING)。


安装程序所用简体中文向导翻译来自 [kira-96/Inno-Setup-Chinese-Simplified-Translation](https://github.com/kira-96/Inno-Setup-Chinese-Simplified-Translation)（固定提交 1ff90acc4ed4aee82b1cda43253243deee3daed4，MIT 许可，见 installer/ChineseTranslation-LICENSE-MIT.txt）。


## Windows 应用图标

新增原创多尺寸应用图标（16/24/32/48/64/128/256 px），同时嵌入 `untrunc-gui.exe` 和 Setup 安装程序，用于资源管理器、任务栏、桌面及开始菜单快捷方式、卸载列表。

图标可由 `tools/generate_icon.py` 重新生成（开发时依赖 Pillow），正式构建直接使用已提交的 ICO，不增加运行时依赖。运行新版 Setup 即可沿用旧版安装位置和卸载信息。


## v2026.11.05-zhCN.4 界面修复

安装名称及主窗口标题统一为“Untrunc 视频修复”；原 AppId 与默认安装路径保持不变。升级时清理旧名称快捷方式，保留其他安装设置。主窗口通过 libui 的公开 uiControlHandle 获取 HWND，使用 WM_SETICON 显式设置标题栏与任务切换图标。“关于”页标注非官方汉化、上游原作者、lysopen 维护仓库和许可证。由于 libui alpha4.1 缺乏完整的 DPI 适配支持，未强行启用 Per-Monitor V2，避免高 DPI 显示下引入新的布局问题。
