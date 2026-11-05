#include "gui-helper.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// 给已创建的原生窗口设置小图标（标题栏）和大图标（Alt+Tab / 任务栏）。
// 使用 libui 公开的 uiControlHandle，而不是不稳定的 FindWindow 标题查找。
void GuiHelper::setWindowIcon(uiWindow* window) {
#ifdef _WIN32
    HWND hwnd = reinterpret_cast<HWND>(uiControlHandle(uiControl(window)));
    if (!hwnd) return;

    HINSTANCE instance = GetModuleHandleW(nullptr);
    if (!instance) return;

    // 与 win_resources.rc 中 RT_GROUP_ICON ID=101 保持一致。
    const auto loadIcon = [instance](int width, int height) -> HICON {
        return static_cast<HICON>(LoadImageW(
            instance, MAKEINTRESOURCEW(101), IMAGE_ICON,
            width, height, LR_DEFAULTCOLOR | LR_SHARED));
    };

    HICON small = loadIcon(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON));
    HICON big = loadIcon(GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON));
    if (small) SendMessageW(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(small));
    if (big) SendMessageW(hwnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(big));
#else
    (void)window;
#endif
}


vector<GuiHelper::Thing> GuiHelper::elements_;
vector<void*> GuiHelper::to_disable_;

void GuiHelper::setSpacedThing(Thing& t, bool spaced) {
	size_t j, n;
	void* p = t.ptr;

	switch (t.type) {
		case window:
			uiWindowSetMargined(uiWindow(p), spaced);
			break;
		case box:
			uiBoxSetPadded(uiBox(p), spaced);
			break;
		case tab:
			n = uiTabNumPages(uiTab(p));
			for (j = 0; j < n; j++)
				uiTabSetMargined(uiTab(p), j, spaced);
			break;
		case group:
			uiGroupSetMargined(uiGroup(p), spaced);
			break;
		case form:
			uiFormSetPadded(uiForm(p), spaced);
			break;
		case grid:
			uiGridSetPadded(uiGrid(p), spaced);
			break;
	}
}

void GuiHelper::setSpaced(bool spaced) {
	for (Thing& t : elements_)
		setSpacedThing(t, spaced);
}

void GuiHelper::setDisabled(bool disable) {
	if (disable)
		for (void* c : to_disable_)
			uiControlDisable(uiControl(c));
	else
		for (void* c : to_disable_)
			uiControlEnable(uiControl(c));
}

uiWindow* GuiHelper::newWindow(const char* title, int width, int height,
                               int hasMenubar) {
	auto w = uiNewWindow(title, width, height, hasMenubar);
	append(w, window);
	return w;
}

uiBox* GuiHelper::newHorizontalBox(void) {
	auto b = uiNewHorizontalBox();
	append(b, box);
	return b;
}

uiBox* GuiHelper::newVerticalBox(void) {
	auto b = uiNewVerticalBox();
	append(b, box);
	return b;
}

uiTab* GuiHelper::newTab(void) {
	auto t = uiNewTab();
	append(t, tab);
//	GuiHelper::to_disable_.emplace_back(t);
	return t;
}

uiGroup* GuiHelper::newGroup(const char* text) {
	auto g = uiNewGroup(text);
	append(g, group);
	return g;
}

uiForm* GuiHelper::newForm(void) {
	auto f = uiNewForm();
	append(f, form);
	return f;
}

uiGrid* GuiHelper::newGrid(void) {
	auto g = uiNewGrid();
	append(g, grid);
	return g;
}

uiButton* GuiHelper::newButton(const char* text) {
	auto b = uiNewButton(text);
	GuiHelper::to_disable_.emplace_back(b);
	return b;
}

uiEntry* GuiHelper::newEntry(void) {
	auto e = uiNewEntry();
	GuiHelper::to_disable_.emplace_back(e);
	return e;
}

void GuiHelper::append(void* ptr, int type) {
	elements_.emplace_back(ptr, type);

	// TODO: trigger update/rerender correctly
	#ifdef __MINGW32__
	setSpaced(true);
	#endif
}


GuiHelper::Thing::Thing(void* ptr, int type) : ptr(ptr), type(type) {}
