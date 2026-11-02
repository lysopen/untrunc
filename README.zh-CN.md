# Untrunc Windows 简体中文 GUI

本分支基于 [anthwlock/untrunc](https://github.com/anthwlock/untrunc) 开发，保留原有修复引擎，仅汉化 `src/gui/gui.cpp` 中的可见界面文本及相关 GUI 提示。

## 下载安装

从 [GitHub Releases](../../releases) 选择适合自己的版本：

- 安装版：`Untrunc-zhCN-x64-Setup-v2026.11.02.2.exe`，支持中文安装向导、开始菜单、可选桌面快捷方式、当前用户安装及卸载。
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
