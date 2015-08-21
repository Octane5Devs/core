#include "../../common/File.h"
#include "../include/applicationmanager.h"

#include "cefwrapper/client_app.h"
#include "cefwrapper/client_scheme.h"

#include "cefclient/browser/main_context_impl.h"
#include "cefclient/browser/main_message_loop_multithreaded_win.h"
#include "cefclient/browser/main_message_loop_std.h"

class CApplicationCEF_Private
{
public:
    CefRefPtr<client::ClientApp> m_app;
    scoped_ptr<client::MainContextImpl> context;
    scoped_ptr<client::MainMessageLoop> message_loop;

    CApplicationCEF_Private()
    {
    }
    ~CApplicationCEF_Private()
    {
        message_loop.reset();
        context.reset();
    }
};

CApplicationCEF::CApplicationCEF()
{
    m_pInternal = new CApplicationCEF_Private();
}

void CApplicationCEF::Init_CEF(CAscApplicationManager* pManager)
{
    // Enable High-DPI support on Windows 7 or newer.
    CefEnableHighDPISupport();

    void* sandbox_info = NULL;

#if defined(CEF_USE_SANDBOX)
    // Manage the life span of the sandbox information object. This is necessary
    // for sandbox support on Windows. See cef_sandbox_win.h for complete details.
    CefScopedSandboxInfo scoped_sandbox;
    sandbox_info = scoped_sandbox.sandbox_info();
#endif

#ifdef WIN32

    // Parse command-line arguments.
    CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
    command_line->InitFromString(::GetCommandLineW());

    // Create a ClientApp of the correct type.
    client::ClientApp::ProcessType process_type = client::ClientApp::GetProcessType(command_line);
    if (process_type == client::ClientApp::BrowserProcess)
        m_pInternal->m_app = new CAscClientAppBrowser();
    else if (process_type == client::ClientApp::RendererProcess)
        m_pInternal->m_app = new CAscClientAppRenderer();
    else if (process_type == client::ClientApp::OtherProcess)
        m_pInternal->m_app = new CAscClientAppOther();

    CefMainArgs main_args((HINSTANCE)GetModuleHandle(NULL));
#else
    CefMainArgs main_args;
#endif

#if 1
    // Execute the secondary process, if any.
    int exit_code = CefExecuteProcess(main_args, m_pInternal->m_app.get(), sandbox_info);
    if (exit_code >= 0)
    {
        // ERROR!!!
    }
#endif

    // Parse command line arguments. The passed in values are ignored on Windows.
    //AppInitCommandLine(0, NULL);

    CefSettings settings;
    //settings.command_line_args_disabled = true;

#if !defined(CEF_USE_SANDBOX)
    settings.no_sandbox = true;
#endif

#if 0
    settings.single_process = 1;
#endif

    // Populate the settings based on command line arguments.
    //AppGetSettings(settings);
    m_pInternal->context.reset(new client::MainContextImpl(command_line, true));
    m_pInternal->context->PopulateSettings(&settings);

#if 1
    settings.multi_threaded_message_loop = 1;
    //settings.windowless_rendering_enabled = 1;
#endif

    if (settings.multi_threaded_message_loop)
        m_pInternal->message_loop.reset(new client::MainMessageLoopMultithreadedWin);
    else
        m_pInternal->message_loop.reset(new client::MainMessageLoopStd);

    std::string sCommandLine = GetCommandLineA();
    if (sCommandLine.find("--ascdesktop-support-debug-info") != std::string::npos)
        pManager->SetDebugInfoSupport(true);

    std::wstring sCachePath = pManager->m_oSettings.cache_path;

    cef_string_t _cache;
    memset(&_cache, 0, sizeof(_cache));
    cef_string_from_wide(sCachePath.c_str(), sCachePath.length(), &_cache);
    settings.cache_path = _cache;

    // Initialize CEF.
    bool bInit = CefInitialize(main_args, settings, m_pInternal->m_app.get(), sandbox_info);
    bool bIsInitScheme = asc_scheme::InitScheme();

    pManager->SetApplication(this);
    return;
}

CApplicationCEF::~CApplicationCEF()
{
    Close();
}

void CApplicationCEF::Close()
{
    if (NULL != m_pInternal)
    {
        // Shut down CEF.
        CefShutdown();

        RELEASEOBJECT(m_pInternal);
    }
}