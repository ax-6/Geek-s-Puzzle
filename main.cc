// Copyright 2025 Xie Zicong, All Rights Reserved.
// This program is licensed under GPL-3.0. You can find the GPL-3.0 in
// the root directory.

#include "main.h"
<<<<<<< HEAD

#include <Windows.h>

#include "third-party/cef/include/cef_app.h"
#include "third-party/cef/include/cef_browser.h"
#include "third-party/cef/include/cef_client.h"
#include "third-party/cef/include/wrapper/cef_helpers.h"


class SimpleClient : public CefClient,
                     public CefLifeSpanHandler,  // 必须继承
                     public CefDisplayHandler {  // 必须继承
 public:
  explicit SimpleClient(bool& is_closed) : is_closed_(is_closed) {}

  // 实现Handler获取接口
  CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
  CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }

  // 生命周期处理
  void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {
    CEF_REQUIRE_UI_THREAD();
    // 窗口调整代码保持不变...
    if (!browser->GetHost()->IsWindowRenderingDisabled()) {
      RECT rect;
      GetClientRect(browser->GetHost()->GetWindowHandle(), &rect);
      browser->GetHost()->WasResized();
    }
  }

  // 标题改变处理（修复编码问题）
  void OnTitleChange(CefRefPtr<CefBrowser> browser,
                     const CefString& title) override {
    CEF_REQUIRE_UI_THREAD();
    // 使用宽字符版本API
    SetWindowTextW(browser->GetHost()->GetWindowHandle(),
                   title.ToWString().c_str());
  }

 private:
  bool& is_closed_;
  IMPLEMENT_REFCOUNTING(SimpleClient);
};

void OnBeforeClose(CefRefPtr<CefBrowser> browser) override {
  CEF_REQUIRE_UI_THREAD();
  is_closed_ = true;
}

    // 显示相关处理
    void OnTitleChange(CefRefPtr<CefBrowser> browser,
                      const CefString& title) override {
        CEF_REQUIRE_UI_THREAD();
        SetWindowText(browser->GetHost()->GetWindowHandle(),
                     std::wstring(title).c_str());
    }

   private:
    bool& is_closed_;
    IMPLEMENT_REFCOUNTING(SimpleClient);

    // 正确调用方式（补充所有必需参数）
    CefBrowserHost::CreateBrowser(
        window_info, 
        new SimpleClient(is_closed_),  // 客户端实例
        "https://example.com",        // URL
        settings,                     // 浏览器设置
        nullptr,                      // extra_info
        nullptr                       // request_context
    );
};

class CefAppInstance : public CefApp, public CefBrowserProcessHandler {
public:
    CefAppInstance() = default;

    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override {
        return this;
    }

    void OnContextInitialized() override {
        CEF_REQUIRE_UI_THREAD();

        CefWindowInfo window_info;
        window_info.SetAsPopup(nullptr, L"CEF Minimal Example");

        CefBrowserSettings settings;
        bool is_closed = false;
        CefBrowserHost::CreateBrowser(
            window_info, new SimpleClient(is_closed), 
            "https://example.com", settings, nullptr, nullptr);
    }

    IMPLEMENT_REFCOUNTING(CefAppInstance);
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int) {
    CefMainArgs args(hInstance);
    CefRefPtr<CefAppInstance> app(new CefAppInstance);

    int exit_code = CefExecuteProcess(args, app, nullptr);
    if (exit_code >= 0) return exit_code;

    CefSettings cef_settings;
    cef_settings.windowless_rendering_enabled = false;
    cef_settings.no_sandbox = true;
    cef_settings.multi_threaded_message_loop = true;

    CefInitialize(args, cef_settings, app, nullptr);
    CefRunMessageLoop();
    CefShutdown();

    return 0;
}
=======
>>>>>>> ea1d75d7cbe924bc8ae695f8d29c3ce3f53465f6
