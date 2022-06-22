
#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <Windowsx.h>

#define WIN32_DX11   (true)
#define WIN32_OPENGL (false)

#if WIN32_DX11
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#endif

#if WIN32_OPENGL
#include <GL/glew.h>
#include <GL/wglew.h>

#include <GL/gl.h>
#include <GL/glu.h>
#pragma comment(lib, "Opengl32.lib")
#pragma comment(lib, "Glu32.lib")
#endif

#endif

#include <cstdint>
#include <cstdio>
#include <exception>
#include <iostream>
#include <memory>
#include <string>

struct Vertex {
  float x;
  float y;
  float r;
  float g;
  float b;
};

class noncopyable {
public:
  noncopyable() = default;

private:
  noncopyable(const noncopyable&) = delete;

  void operator=(const noncopyable&) = delete;
};

class error_handler : public std::exception {
public:
  error_handler(const char* msg = "") {
    printf("error_handler(%s)\n", msg);
  }
};

#if WIN32_OPENGL
inline void load_shader(std::string& shader_code, const char* filename) {
  auto* shader_file = fopen(filename, "rb");
  if (!shader_file) {
    throw error_handler("cannot open the shader file");
  }

  fseek(shader_file, 0, SEEK_END);
  auto code_size = ftell(shader_file);

  fseek(shader_file, 0, SEEK_SET);

  shader_code.resize(code_size);
  if (fread(&*shader_code.begin(), code_size, 1, shader_file) < 0) {
    fclose(shader_file);
    throw error_handler("error read file");
  }

  fclose(shader_file);
}

class MSWindowFalseContext {
public:
  ~MSWindowFalseContext() {
    if (m_rc) {
      ::wglDeleteContext(m_rc);
      m_rc = nullptr;
    }

    if (m_dc) {
      ::ReleaseDC(m_hwnd, m_dc);
      m_dc = nullptr;
    }

    if (m_hwnd) {
      ::DestroyWindow(m_hwnd);
      m_hwnd = nullptr;
    }
  }

  void create() {
    auto hInstance = GetModuleHandle(nullptr);

    const wchar_t* className = L"MSWindowFalseContext";

    WNDCLASSEX wc;
    if (!GetClassInfoEx(hInstance, className, &wc)) {
      memset(&wc, 0, sizeof(wc));
      wc.cbSize        = sizeof(wc);
      wc.style         = CS_OWNDC;
      wc.lpfnWndProc   = DefWindowProc;
      wc.hInstance     = hInstance;
      wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
      wc.hbrBackground = nullptr;
      wc.lpszClassName = className;

      if (!RegisterClassEx(&wc)) {
        throw error_handler("RegisterClassEx");
      }
    }

    m_hwnd = CreateWindowExW(0, className, L"", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr, hInstance, nullptr);
    if (!m_hwnd) {
      throw error_handler("CreateWindow");
    }

    m_dc = GetDC(m_hwnd);
    if (!m_dc) {
      throw error_handler("GetDC");
    }

    PIXELFORMATDESCRIPTOR pfd;
    {
      memset(&pfd, 0, sizeof(pfd));
      pfd.nSize      = sizeof(pfd);
      pfd.nVersion   = 1;
      pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
      pfd.iPixelType = PFD_TYPE_RGBA;
      pfd.cColorBits = 32;
      pfd.cDepthBits = 32;
      pfd.iLayerType = PFD_MAIN_PLANE;
    }

    int nPixelFormat = ChoosePixelFormat(m_dc, &pfd);
    if (nPixelFormat == 0) {
      throw error_handler("ChoosePixelFormat");
    }

    BOOL bResult = SetPixelFormat(m_dc, nPixelFormat, &pfd);
    if (!bResult) {
      throw error_handler("SetPixelFormat");
    }

    m_rc = wglCreateContext(m_dc);
    if (!m_rc) {
      throw error_handler("wglCreateContext");
    }

    wglMakeCurrent(m_dc, m_rc);
  }

private:
  HWND m_hwnd = nullptr;
  HDC m_dc    = nullptr;
  HGLRC m_rc  = nullptr;
};
#endif

class Renderer {
public:
  ~Renderer() = default;

  Renderer() = default;

#if _WIN32
  Renderer(const HWND& hwnd) {
    m_hwnd = hwnd;

    m_dc = GetDC(m_hwnd);
    {
      if (!m_dc) {
        throw error_handler("GetDC");
      }
    }
#endif

#if WIN32_OPENGL
    // clang-format off
    const int formatAttrs[] = {
      WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
      WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
      WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
      WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
      WGL_COLOR_BITS_ARB,     32,
      WGL_DEPTH_BITS_ARB,     24,
      WGL_STENCIL_BITS_ARB,   8,
      0
    };

    int contextAttrs[] = {
      WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
      WGL_CONTEXT_MINOR_VERSION_ARB, 3,
#if 0 
      WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#else
      WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
#endif
      WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
      0
    };
    // clang-format on

    int format, numFormat;
    if (!wglChoosePixelFormatARB(m_dc, formatAttrs, nullptr, 1, &format, (UINT*)&numFormat)) {
      throw error_handler("wglChoosePixelFormatARB");
    }

    PIXELFORMATDESCRIPTOR pfd;
    if (!SetPixelFormat(m_dc, format, &pfd)) {
      throw error_handler("SetPixelFormat");
    }

    HGLRC sharedContext = nullptr;
    m_rc                = wglCreateContextAttribsARB(m_dc, sharedContext, contextAttrs);
    if (!m_rc) {
      throw error_handler("wglCreateContext");
    }
#endif

#if WIN32_DX11
    set_viewport_width(hwnd);
    set_viewport_height(hwnd);

    DXGI_SWAP_CHAIN_DESC swapchain               = {};
    swapchain.BufferDesc.Width                   = 0;
    swapchain.BufferDesc.Height                  = 0;
    swapchain.BufferDesc.Format                  = DXGI_FORMAT_B8G8R8A8_UNORM;
    swapchain.BufferDesc.RefreshRate.Numerator   = 0;
    swapchain.BufferDesc.RefreshRate.Denominator = 0;
    swapchain.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;
    swapchain.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapchain.SampleDesc.Count                   = 1;
    swapchain.SampleDesc.Quality                 = 0;
    swapchain.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapchain.BufferCount                        = 1;
    swapchain.OutputWindow                       = hwnd;
    swapchain.Windowed                           = TRUE;
    swapchain.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
    swapchain.Flags                              = 0;

    m_hresult = D3D11CreateDeviceAndSwapChain(nullptr,                  // DXGI Adapter
                                              D3D_DRIVER_TYPE_HARDWARE, // Driver Type
                                              nullptr,                  // Software Rasterizer
                                              0,                        // Create Flags
                                              nullptr,                  // Feature Level
                                              0,                        // Feature Level
                                              D3D11_SDK_VERSION,        // SDKVersion
                                              &swapchain,               // SwapChain
                                              &m_dxgi_swapchain,        // SwapChain
                                              &m_dx11_device,           // Device
                                              nullptr,                  // FeatureLevel
                                              &m_dx11_device_context);  // DeviceContext

    Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;

    m_hresult = m_dxgi_swapchain->GetBuffer(0,                        // zero-based buffer index
                                            __uuidof(ID3D11Resource), // REFIID
                                            &pBackBuffer);            // point to a back buffer interface

    m_hresult = m_dx11_device->CreateRenderTargetView(pBackBuffer.Get(),           // Render Target
                                                      nullptr,                     // Render Target View Description
                                                      &m_dx11_render_target_view); // Render Target View
  }
#endif

  void init(void) {
#if WIN32_OPENGL
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glClearDepth(1);
#endif
#if WIN32_DX11
#endif
  }

  void destory(void) {
#if _WIN32
    if (m_rc) {
      wglDeleteContext(m_rc);
      m_rc = nullptr;
    }

    if (m_dc) {
      ReleaseDC(m_hwnd, m_dc);
      m_dc = nullptr;
    }
#endif
  }

#if WIN32_DX11
  void VertexBufferPipeline(const Vertex (&vertices)[3]) {
    Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;

    D3D11_BUFFER_DESC bufferDescription   = {};
    bufferDescription.BindFlags           = D3D11_BIND_VERTEX_BUFFER;
    bufferDescription.Usage               = D3D11_USAGE_DEFAULT;
    bufferDescription.CPUAccessFlags      = 0;
    bufferDescription.MiscFlags           = 0;
    bufferDescription.ByteWidth           = sizeof(vertices);
    bufferDescription.StructureByteStride = sizeof(Vertex);

    D3D11_SUBRESOURCE_DATA suberSourceData = {};
    suberSourceData.pSysMem                = vertices;

    m_hresult = m_dx11_device->CreateBuffer(&bufferDescription, &suberSourceData, &pVertexBuffer);

    const UINT stride = sizeof(Vertex);
    const UINT offset = 0;
    m_dx11_device_context->IASetVertexBuffers(0,                            // input start slot
                                              1,                            // number of vertex buffers
                                              pVertexBuffer.GetAddressOf(), // vertex buffers
                                              &stride,                      // stride value for each buffer
                                              &offset);                     // offset value for each buffer
  }

  void ShaderPipeline(const wchar_t* const PixelShaderFile, const wchar_t* const VertexShaderFile) {
    Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

    Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
    {
      m_hresult = D3DReadFileToBlob(PixelShaderFile, &pBlob);

      m_hresult = m_dx11_device->CreatePixelShader(pBlob->GetBufferPointer(), //
                                                   pBlob->GetBufferSize(),    //
                                                   nullptr,                   // ID3D11ClassLinkage
                                                   &pPixelShader);            //

      m_dx11_device_context->PSSetShader(pPixelShader.Get(), // ID3D11PixelShader
                                         nullptr,            // ID3D11ClassInstance
                                         0);                 // number of instance
    }

    Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
    {
      m_hresult = D3DReadFileToBlob(VertexShaderFile, //
                                    &pBlob);          // ID3DBlob

      m_hresult = m_dx11_device->CreateVertexShader(pBlob->GetBufferPointer(), //
                                                    pBlob->GetBufferSize(),    //
                                                    nullptr,                   //
                                                    &pVertexShader);           //

      m_dx11_device_context->VSSetShader(pVertexShader.Get(), //
                                         nullptr,             //
                                         0);                  //
    }

    Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
    {
      const D3D11_INPUT_ELEMENT_DESC inputElementDescription[] = {
        {
          "Position",                  // SemanticName
          0,                           // SemanticIndex
          DXGI_FORMAT_R32G32_FLOAT,    // Format
          0,                           // InputSlot
          0,                           // AlignedByteOffset
          D3D11_INPUT_PER_VERTEX_DATA, // InputSlotClass
          0                            // InstanceDataStepRate
        },
        {
          "Color",                     //
          0,                           //
          DXGI_FORMAT_R32G32B32_FLOAT, //
          0,                           //
          8,                           //
          D3D11_INPUT_PER_VERTEX_DATA, //
          0                            //
        },
      };
      m_hresult = m_dx11_device->CreateInputLayout(inputElementDescription,                               //
                                                   static_cast<UINT>(std::size(inputElementDescription)), //
                                                   pBlob->GetBufferPointer(),                             //
                                                   pBlob->GetBufferSize(),                                //
                                                   &pInputLayout);                                        //
    }

    m_dx11_device_context->IASetInputLayout(pInputLayout.Get());
  }

  void BindTargetPipeline(void) {
    m_dx11_device_context->OMSetRenderTargets(1,                                        //
                                              m_dx11_render_target_view.GetAddressOf(), //
                                              nullptr);                                 //
  }

  void SetPrimitiveTopologyPipeline(enum D3D_PRIMITIVE_TOPOLOGY topology) {
    m_dx11_device_context->IASetPrimitiveTopology(topology);
  }

  void ConfigureViewport(int width, int height) {
    D3D11_VIEWPORT viewport;
    viewport.Width    = width;
    viewport.Height   = height;
    viewport.MinDepth = 0;
    viewport.MaxDepth = 1;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    m_dx11_device_context->RSSetViewports(1, &viewport);
  }

  void RenderVertices(const Vertex (&vertices)[3]) {
    m_dx11_device_context->Draw(static_cast<UINT>(std::size(vertices)), //
                                0);                                     //
  }

  void onRender(const Vertex (&vertices)[3],            //
                const wchar_t* const PixelShaderFile,   //
                const wchar_t* const VertexShaderFile,  //
                enum D3D_PRIMITIVE_TOPOLOGY topology) { //
    VertexBufferPipeline(vertices);
    ShaderPipeline(PixelShaderFile, VertexShaderFile);
    BindTargetPipeline();
    SetPrimitiveTopologyPipeline(topology);
    ConfigureViewport(get_viewport_width(), get_viewport_height());
    RenderVertices(vertices);
  }

  int get_viewport_width() const {
    return m_viewport_width;
  }

  int get_viewport_height() const {
    return m_viewport_height;
  }

  void set_viewport_width(const HWND& hwnd) {
    RECT rect;
    if (GetWindowRect(hwnd, &rect)) {
      m_viewport_width = rect.right - rect.left;
    }
  }

  void set_viewport_height(const HWND& hwnd) {
    RECT rect;
    if (GetWindowRect(hwnd, &rect)) {
      m_viewport_height = rect.bottom - rect.top;
    }
  }
#endif

#if WIN32_OPENGL
  void configShader(void) {
    std::string vertexCode;
    load_shader(vertexCode, "libng\\shader\\glsl\\vertex.glsl");

    const char* vertexSrcData = vertexCode.c_str();
    GLint vertexSrcLen        = vertexCode.size();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSrcData, &vertexSrcLen);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
      throw error_handler("vertex shader error");
    }

    std::string fragmentCode;
    load_shader(fragmentCode, "libng\\shader\\glsl\\fragment.glsl");

    const char* fragmentSrcData = fragmentCode.c_str();
    GLint fragmentSrcLen        = fragmentCode.size();

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSrcData, &fragmentSrcLen);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
      throw error_handler("fragment shader error");
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
      throw error_handler("shader linking error");
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // clang-format off
    float vertices[] = {
      -0.5f, -0.5f, 0.0f, // left
      +0.5f, -0.5f, 0.0f, // right
      +0.0f, +0.5f, 0.0f  // top
    };
    // clang-format on

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
#endif

  void SetBackgroundColor(void) {
#if WIN32_OPENGL
    glClearColor(0.0f, 0.2f, 0.2f, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif

#if WIN32_DX11
    const float color[] = {1.0f, 0.0f, 0.0f, 1.0f};
    m_dx11_device_context->ClearRenderTargetView(m_dx11_render_target_view.Get(), // render target
                                                 color);                          // 4-dim array
#endif
  }

  void SetTriangle(void) {
#if WIN32_OPENGL
    configShader();
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
#endif

#if WIN32_DX11
    // create vertex buffer (1 2d triangle at center of screen)
    const Vertex vertices[] = {
      {+0.0f, +0.5f, 0.0f, 0.0f, 0.0f},
      {+0.5f, -0.5f, 1.0f, 1.0f, 0.0f},
      {-0.5f, -0.5f, 0.0f, 0.0f, 1.0f},
    };
    onRender(vertices,                               //
             L"build\\sample\\shader\\pixel.cso",    //
             L"build\\sample\\shader\\vertex.cso",   //
             D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); //
#endif
  }

  void makeCurrent() {
#if WIN32_OPENGL
    if (m_rc) {
      wglMakeContextCurrentARB(m_dc, m_dc, m_rc);
    }
#endif
#if WIN32_DX11
#endif
  }

  void swapBuffers() {
#if WIN32_OPENGL
    if (m_dc) {
      ::SwapBuffers(m_dc);
    }
#endif

#if WIN32_DX11
    m_hresult = m_dxgi_swapchain->Present(1,  // synchronize option pre frame
                                          0); // swap chain option
#endif
  }

private:
#if _WIN32
  HWND m_hwnd = nullptr;
  HDC m_dc    = nullptr;
  HGLRC m_rc  = nullptr;
#endif

#if WIN32_DX11
  HRESULT m_hresult;

  int m_viewport_width  = 0;
  int m_viewport_height = 0;

  Microsoft::WRL::ComPtr<ID3D11Device> m_dx11_device;
  Microsoft::WRL::ComPtr<IDXGISwapChain> m_dxgi_swapchain;
  Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_dx11_device_context;
  Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_dx11_render_target_view;
#endif

#if WIN32_OPENGL
  unsigned int shaderProgram;
  unsigned int VBO, VAO;
#endif
};

class MSWindow : public noncopyable {
public:
  MSWindow() = default;

  ~MSWindow() {
    destroy();
  }

  void set_width(int width) {
    if (width > 0) {
      m_width = width;
    }
  }

  void set_height(int height) {
    if (height > 0) {
      m_height = height;
    }
  }

  void set_title(const wchar_t* const title) {
    if (title != nullptr) {
      m_title.clear();
      m_title = title;
    }
  }

  void create(int width, int height, const wchar_t* const title) {
    set_width(width);
    set_height(height);
    set_title(title);

#if _WIN32
    auto hInstance = GetModuleHandle(nullptr);
#endif
    destroy();

#if WIN32_OPENGL
    MSWindowFalseContext falseContext;
    falseContext.create();
    glewInit();
#endif

#if _WIN32
    WNDCLASSEX wc;
    if (!GetClassInfoEx(hInstance, wndClassName(), &wc)) {
      memset(&wc, 0, sizeof(wc));
      wc.cbSize        = sizeof(wc);
      wc.style         = CS_OWNDC;
      wc.lpfnWndProc   = WndProc;
      wc.hInstance     = hInstance;
      wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
      wc.hbrBackground = nullptr;
      wc.lpszClassName = wndClassName();

      if (!RegisterClassEx(&wc)) {
        throw error_handler("RegisterClassEx");
      }
    }

    m_hwnd = CreateWindowEx(0,                   //
                            wndClassName(),      //
                            m_title.c_str(),     //
                            WS_OVERLAPPEDWINDOW, //
                            CW_USEDEFAULT,       //
                            CW_USEDEFAULT,       //
                            m_width,             //
                            m_height,            //
                            nullptr,             //
                            nullptr,             //
                            hInstance,           //
                            this);               //

    if (!m_hwnd) {
      throw error_handler("CreateWindow");
    }

    m_renderer = Renderer(m_hwnd);

    makeCurrent();
    onInit();

    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);
#endif
  }

  void destroy() {
    m_renderer.destory();

#if _WIN32
    if (m_hwnd) {
      DestroyWindow(m_hwnd);
      m_hwnd = nullptr;
    }
#endif
  }

  virtual bool onShouldClose() {
    return true;
  }

  virtual void onDestroy() {
  }

  virtual void onPaint() {
  }

  virtual void onInit() {
  }

  static const wchar_t* wndClassName() {
    return L"MSWindowClass";
  }

  void makeCurrent() {
    m_renderer.makeCurrent();
  }

  void swapBuffers() {
    m_renderer.swapBuffers();
  }

  int canvasWidth() const {
    return m_canvasWidth;
  }

  int canvasHeight() const {
    return m_canvasHeight;
  }

protected:
  Renderer m_renderer;

private:
#if _WIN32
  static LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
      case WM_CREATE: {
        auto* cs      = reinterpret_cast<CREATESTRUCT*>(lParam);
        auto* thisObj = reinterpret_cast<MSWindow*>(cs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG)thisObj);
      } break;
      case WM_PAINT: {
#if 0
				PAINTSTRUCT ps;
				BeginPaint(hwnd, &ps);
				getThis(hwnd)->onPaint();
				EndPaint(hwnd, &ps);
#else
        getThis(hwnd)->onPaint();
        return 0;
#endif
      } break;
      case WM_DESTROY: {
        getThis(hwnd)->onDestroy();
      } break;
      case WM_SIZE: {
        auto* thisObj           = getThis(hwnd);
        auto w                  = GET_X_LPARAM(lParam);
        auto h                  = GET_Y_LPARAM(lParam);
        thisObj->m_canvasWidth  = w;
        thisObj->m_canvasHeight = h;
      } break;
      case WM_CLOSE: {
        if (!getThis(hwnd)->onShouldClose()) {
          return 1;
        }
      } break;
      default: break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
  }
#endif

#if _WIN32
  static MSWindow* getThis(HWND hwnd) {
    auto data     = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    auto* thisObj = reinterpret_cast<MSWindow*>(data);
    if (hwnd != thisObj->m_hwnd)
      throw error_handler("getThis()");
    return thisObj;
  }
#endif

#if _WIN32
  HWND m_hwnd = nullptr;
#endif

  int m_canvasWidth  = 0;
  int m_canvasHeight = 0;
  int m_width        = 0;
  int m_height       = 0;

  std::wstring m_title;
};

class UIWindow : public MSWindow {
public:
  virtual void onInit() override {
    m_renderer.init();
  }

  virtual void onDestroy() override {
#if _WIN32
    PostQuitMessage(0);
#endif
  }

  virtual void onPaint() override {
    m_renderer.SetBackgroundColor();
    m_renderer.SetTriangle();
    swapBuffers();
  }
};

class App : public noncopyable {
public:
  explicit App(const int width, const int height, const wchar_t* const title) {
    m_window.create(width, height, title);
  }

  ~App() = default;

  int execute(void) {
#if _WIN32
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    return msg.wParam;
#endif

#if __linux__
    return 0;
#endif
  }

private:
  UIWindow m_window;
};