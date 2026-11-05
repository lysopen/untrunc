"""生成 Untrunc Windows 应用图标（设计稿为原创，开发时需要 Pillow）。"""
from pathlib import Path

from PIL import Image, ImageDraw

S = 1024
im = Image.new("RGBA", (S, S), (0, 0, 0, 0))
d = ImageDraw.Draw(im)

# 蓝色品牌底板，外部透明，适合 Windows 深浅两种主题。
d.rounded_rectangle((65, 65, 960, 960), radius=225, fill="#132A49")
d.rounded_rectangle((110, 110, 915, 915), radius=184, fill="#18406A")

# 放映胶片：亮色框体 + 透明胶片孔；所有形状保持在 16px 缩小时可识别。
d.rounded_rectangle((259, 274, 767, 755), radius=78, fill="#F2F8FF")
d.rounded_rectangle((333, 328, 694, 700), radius=28, fill="#18406A")
for x1 in (279, 704):
    for y1 in (350, 454, 558, 662):
        d.rounded_rectangle((x1, y1, x1 + 44, y1 + 51), radius=10, fill="#18406A")

# 视频播放符号。
d.polygon([(440, 400), (440, 632), (626, 516)], fill="#36DECF")

# 右下角金色小徽标象征“修复成功”，形成差异化视觉识别。
d.ellipse((674, 668, 874, 868), fill="#FEBB55", outline="#18406A", width=20)
d.line([(720, 765), (754, 799), (826, 731)], fill="#173453", width=30, joint="curve")
d.ellipse((707, 752, 731, 776), fill="#173453")
d.ellipse((814, 718, 838, 742), fill="#173453")

out = Path("src/gui/app_icon.ico")
im.save(
    out,
    format="ICO",
    sizes=[(16, 16), (24, 24), (32, 32), (48, 48),
           (64, 64), (128, 128), (256, 256)],
)
print(f"Created {out} ({out.stat().st_size} bytes)")
