param([Parameter(Mandatory = $true)][string]$ExePath)
$ErrorActionPreference = 'Stop'
$exe = (Resolve-Path -LiteralPath $ExePath).Path

# 101 对应 win_resources.rc 内的 RT_GROUP_ICON ID。
Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;
public static class UntruncIconResources {
    [DllImport("kernel32.dll", EntryPoint="LoadLibraryExW", CharSet=CharSet.Unicode, SetLastError=true)]
    public static extern IntPtr LoadLibraryEx(string name, IntPtr file, uint flags);
    [DllImport("kernel32.dll", EntryPoint="FindResourceW", SetLastError=true)]
    public static extern IntPtr FindResource(IntPtr module, IntPtr name, IntPtr type);
    [DllImport("kernel32.dll", SetLastError=true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool FreeLibrary(IntPtr module);
}
'@
$module = [UntruncIconResources]::LoadLibraryEx($exe, [IntPtr]::Zero, 2)
if ($module -eq [IntPtr]::Zero) { throw "无法加载 EXE 资源: $exe" }
try {
    $groupIcon = [UntruncIconResources]::FindResource($module, [IntPtr]101, [IntPtr]14)
    if ($groupIcon -eq [IntPtr]::Zero) { throw "找不到 RT_GROUP_ICON 101: $exe" }
    Write-Output "PASS: embedded Windows icon group (ID=101): $exe"
} finally {
    [void][UntruncIconResources]::FreeLibrary($module)
}
