; Windows 简体中文 GUI 安装版，保留原视频修复内核
; 上游 https://github.com/anthwlock/untrunc
#ifndef AppVersion
  #define AppVersion "2026.11.05.4"
#endif
#define AppName "Untrunc 视频修复"

[Setup]
AppId={{7FE478A0-E50B-4057-B8B0-1915C6C602E6}
AppName={#AppName}
AppVersion={#AppVersion}
AppVerName={#AppName} {#AppVersion}
AppPublisher=lysopen (Unofficial zh-CN localization)
AppPublisherURL=https://github.com/lysopen/untrunc
AppSupportURL=https://github.com/lysopen/untrunc/issues
AppUpdatesURL=https://github.com/lysopen/untrunc/releases
DefaultDirName={localappdata}\Programs\Untrunc-zhCN
DefaultGroupName={#AppName}
PrivilegesRequired=lowest
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible
UninstallDisplayName={#AppName}
UninstallDisplayIcon={app}\untrunc-gui.exe
LicenseFile=..\COPYING
OutputDir=..\dist
OutputBaseFilename=Untrunc-zhCN-x64-Setup-v{#AppVersion}
Compression=lzma
SolidCompression=yes
WizardStyle=modern
SetupIconFile=..\src\gui\app_icon.ico
DisableProgramGroupPage=yes

[Languages]
Name: "chinesesimplified"; MessagesFile: "ChineseSimplified.isl"

[Tasks]
Name: "desktopicon"; Description: "创建桌面快捷方式"; GroupDescription: "其他选项："; Flags: unchecked

[Files]
Source: "ChineseTranslation-LICENSE-MIT.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\untrunc_zh-CN_x64\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[InstallDelete]
; 在原 AppId 内升级时移除旧版带“（简体中文）”的开始菜单/桌面快捷方式。
Type: files; Name: "{autoprograms}\Untrunc 视频修复（简体中文）.lnk"
Type: files; Name: "{autodesktop}\Untrunc 视频修复（简体中文）.lnk"

[Icons]
Name: "{autoprograms}\{#AppName}"; Filename: "{app}\untrunc-gui.exe"; WorkingDir: "{app}"
Name: "{autodesktop}\{#AppName}"; Filename: "{app}\untrunc-gui.exe"; WorkingDir: "{app}"; Tasks: desktopicon

[Run]
Filename: "{app}\untrunc-gui.exe"; Description: "运行 {#AppName}"; Flags: nowait postinstall skipifsilent
