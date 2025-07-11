/*****************************************************************************/
/**
 * @file    DX11RenderAPI.cpp
 * @author  Samuel Prince (samuel.prince.quezada@gmail.com)
 * @date    2025/06/29
 * @brief   Graphics API Implementation with DirectX11.
 *
 * Graphics API Implementation with DirectX11.
 *
 * @bug	    No known bugs.
 */
/*****************************************************************************/

/*****************************************************************************/
/**
 * Includes
 */
/*****************************************************************************/
#include "geRenderAPI.h"
#include "DX11RenderAPI.h"
#include "DXTranslateUtils.h"

#include <geGameConfig.h>
#include <geMath.h>
#include <geDebug.h>
#include <geFileSystem.h>
#include <geDataStream.h>
#include <d3dcompiler.h>

namespace geEngineSDK {

  using std::pair;
  using std::make_pair;

  class D3DIncludeHandler : public ID3DInclude
  {
   public:
    D3DIncludeHandler(const Vector<Path>& includeDirs)
      : m_includePaths(includeDirs)
    {}

    //Called when an #include is encountered
    HRESULT __stdcall
    Open(D3D_INCLUDE_TYPE IncludeType,
         LPCSTR pFileName,
         LPCVOID pParentData,
         LPCVOID* ppData,
         UINT* pBytes) noexcept override {
      GE_UNREFERENCED_PARAMETER(pParentData);

      Path filePath;
      if (IncludeType == D3D_INCLUDE_LOCAL || IncludeType == D3D_INCLUDE_SYSTEM) {
        //Search for the file in the include paths
        filePath = _findFile(pFileName);
        if (filePath == Path::BLANK) {
          GE_LOG(kError,
                 Uncategorized,
                 "Failed to find {0} in include folders",
                 pFileName);
          return E_FAIL;
        }
      }
      else {
        return E_FAIL;
      }

      //Open the file and read its content into memory
      auto fileStream = FileSystem::openFile(filePath);
      if (!fileStream) {
        GE_LOG(kError,
               Uncategorized,
               "Failed to open shader include file: {0}",
               filePath.toString());
        return E_FAIL; //Failed to open the include file
      }

#if USING(GE_DEBUG_MODE)
      auto msg = StringUtil::format("Included file from include folder: {0} \n",
                                    filePath.toString().c_str());
      g_debug().log(msg, LogVerbosity::kInfo);
#endif

      auto size = fileStream->size();
      char* data = reinterpret_cast<char*>(ge_alloc<char>(size * sizeof(char)));
      fileStream->read(data, size);

      *ppData = data;
      *pBytes = static_cast<UINT>(size);

      return S_OK;
    }

    //Called when the file is no longer needed
    HRESULT __stdcall
    Close(LPCVOID pData) noexcept override {
      ge_free(const_cast<void*>(pData));
      return S_OK;
    }

   private:
    Path
    _findFile(const String& fileName) {
      //Get working directory
      static Path workingDir = FileSystem::getWorkingDirectoryPath();

      //Search all paths for the file
      for (const Path& path : m_includePaths) {
        Path fullSearchPath = path.getAbsolute(workingDir);
        fullSearchPath.append(fileName);
        if (FileSystem::isFile(fullSearchPath)) {
          return fullSearchPath;
        }
      }

      return Path::BLANK;  //File not found
    }

    Vector<Path> m_includePaths;
  };

  bool
  DX11RenderAPI::initRenderAPI(void* scrHandle, bool bFullScreen) {
    auto hWnd = reinterpret_cast<HWND>(scrHandle);
    m_bFullScreen = bFullScreen;

    Vector<IDXGIAdapter1*> vecAdapters;
    IDXGIAdapter1* pAdapter = nullptr;
    IDXGIFactory1* pFactory = nullptr;

    //Get from the configuration file the index of the adapter to use
    auto& config = GameConfig::instance();
    int32 adapterIndex = config.get<int32>("RenderAPI", "AdapterIndex", 0);

    //Enumerate all the graphic adapters
    CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&pFactory);
    while (DXGI_ERROR_NOT_FOUND !=
           pFactory->EnumAdapters1(UINT(vecAdapters.size()), &pAdapter)) {
      vecAdapters.push_back(pAdapter);
    }

    safeRelease(pFactory);

    if(vecAdapters.empty()) {
      //No adapters found, cannot initialize the render API
      GE_EXCEPT(RenderingAPIException,
                "No graphic adapters found. Cannot initialize the render API.");
      return false;
    }

    //Check that the adapter index is valid
    adapterIndex = Math::max(0, adapterIndex);
    if (adapterIndex >= static_cast<int32>(vecAdapters.size())) {
      GE_LOG(kWarning, RenderAPI, "Invalid adapter index, use the first one");
      adapterIndex = 0;
    }

    //Get the adapter description
    DXGI_ADAPTER_DESC1 aDesc1;
    vecAdapters[adapterIndex]->GetDesc1(&aDesc1);
    memcpy(&m_selectedAdapterDesc, &aDesc1, sizeof(m_selectedAdapterDesc));

    Vector<D3D_FEATURE_LEVEL> featureLevels =
    {
#if !USING(DX_VERSION_11_0)
      D3D_FEATURE_LEVEL_11_1
#else
      D3D_FEATURE_LEVEL_11_0
#endif
    };
    D3D_FEATURE_LEVEL selectedFeatureLevel;

    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* deviceContext = nullptr;

    uint32 deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if USING(GE_DEBUG_MODE)
    deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    //Create a device and immediate device context
    throwIfFailed(D3D11CreateDevice(vecAdapters[adapterIndex],
                                    D3D_DRIVER_TYPE_UNKNOWN,
                                    nullptr,
                                    deviceFlags,
                                    &featureLevels[0],
                                    static_cast<UINT>(featureLevels.size()),
                                    D3D11_SDK_VERSION,
                                    &device,
                                    &selectedFeatureLevel,
                                    &deviceContext));

    m_pDevice = getAs<D3DDevice>(device);

#if USING(GE_DEBUG_MODE)
    m_pDebug = getAs<ID3D11Debug>(device);
#endif
    m_pImmediateDC = getAs<D3DDeviceContext>(deviceContext);
    GE_ASSERT(m_pDevice);
    GE_ASSERT(m_pImmediateDC);

    //Create a swap chain
#if USING(DX_VERSION_11_0)
    DXGI_SWAP_CHAIN_DESC scDesc;
#else
    DXGI_SWAP_CHAIN_DESC1 scDesc;
#endif
    ge_zero_out(scDesc);

#if USING(DX_VERSION_11_0)
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.OutputWindow = hWnd;
    scDesc.BufferDesc.RefreshRate.Numerator = 60;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;
    scDesc.Windowed = !m_bFullScreen;
    auto& scDesc_Width = scDesc.BufferDesc.Width;
    auto& scDesc_Height = scDesc.BufferDesc.Height;
#else
    scDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
    scDesc.Stereo = false;
    scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    auto& scDesc_Width = scDesc.Width;
    auto& scDesc_Height = scDesc.Height;
#endif

#if USING(DX_VERSION_11_3)
    //scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
#endif

    scDesc.BufferCount = config.get<uint32>("RenderAPI", "BufferCount", 2);
    scDesc.SampleDesc.Count = 1;
    scDesc.SampleDesc.Quality = 0;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    if (!m_bFullScreen) {
      RECT rc;
      GetClientRect(hWnd, &rc);
      scDesc_Width = rc.right - rc.left;
      scDesc_Height = rc.bottom - rc.top;
    }
    else {
      //Get the screen resolution from the adapter description
      IDXGIOutput* pOutput = nullptr;
      if (vecAdapters[adapterIndex]->EnumOutputs(0, &pOutput) == DXGI_ERROR_NOT_FOUND) {
        //No outputs found, use the default screen resolution
        scDesc_Width = GetSystemMetrics(SM_CXSCREEN);
        scDesc_Height = GetSystemMetrics(SM_CYSCREEN);
      }
      else {
        DXGI_OUTPUT_DESC outDesc;
        pOutput->GetDesc(&outDesc);
        scDesc_Width = outDesc.DesktopCoordinates.right - outDesc.DesktopCoordinates.left;
        scDesc_Height = outDesc.DesktopCoordinates.bottom - outDesc.DesktopCoordinates.top;
        safeRelease(pOutput);
      }
    }

#if !USING(DX_VERSION_11_0)
    String scalingMode = config.get<String>("RenderAPI", "Scaling", "None");
    StringUtil::toUpperCase(scalingMode);
    if (scalingMode == "STRETCH") {
      scDesc.Scaling = DXGI_SCALING_STRETCH;
    }
    else if (scalingMode == "ASPECT") {
      scDesc.Scaling = DXGI_SCALING_ASPECT_RATIO_STRETCH;
    }
    else {
      scDesc.Scaling = DXGI_SCALING_NONE;
    }

    String flipMode = config.get<String>("RenderAPI", "FlipMode", "None");
    StringUtil::toUpperCase(flipMode);
    if (flipMode == "SEQUENTIAL") {
      scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    }
    else {
      scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    }
#endif

    DXGIDevice* dxgiDevice = getAs<DXGIDevice>(m_pDevice);

    IDXGIAdapter* dxgiAdapter = nullptr;
    dxgiDevice->GetAdapter(&dxgiAdapter);

    DXFactory* dxgiFactory = nullptr;
    dxgiAdapter->GetParent(__uuidof(DXFactory), reinterpret_cast<void**>(&dxgiFactory));
#if USING(DX_VERSION_11_0)
    throwIfFailed(dxgiFactory->CreateSwapChain(m_pDevice, &scDesc, &m_pSwapChain));
#else
    IDXGISwapChain1* pSwapChain = nullptr;
    throwIfFailed(dxgiFactory->CreateSwapChainForHwnd(m_pDevice,
                                                      hWnd,
                                                      &scDesc,
                                                      nullptr,
                                                      nullptr,
                                                      &pSwapChain));
    m_pSwapChain = getAs<D3DSwapChain>(pSwapChain);
    safeRelease(pSwapChain);
#endif

    uint32 MaximumFrameLatency = config.get<uint32>("RenderAPI", "MaximumFrameLatency", 1);
    throwIfFailed(dxgiDevice->SetMaximumFrameLatency(MaximumFrameLatency));

    setImmediateContext();

    //Get the required interfaces for the screen and targets
    _updateBackBufferTexture();

    GRAPHICS_VIEWPORT scDesc_Viewport;
    scDesc_Viewport.x = 0.0f;
    scDesc_Viewport.y = 0.0f;
    scDesc_Viewport.width = float(m_pBackBufferTexture->getDesc().width);
    scDesc_Viewport.height = float(m_pBackBufferTexture->getDesc().height);
    scDesc_Viewport.zNear = 0.0f;
    scDesc_Viewport.zFar = 1.0f;

    setViewports({ scDesc_Viewport });

    setRenderTargets({ {m_pBackBufferTexture, 0} }, WeakSPtr<Texture>());

#if USING(GE_DEBUG_MODE)
    String objectName = "DX Main Device";
    m_pDevice->SetPrivateData(WKPDID_D3DDebugObjectName,
                              static_cast<uint32>(objectName.size()),
                              objectName.c_str());
    
    objectName = "DX Immediate Context";
    m_pImmediateDC->SetPrivateData(WKPDID_D3DDebugObjectName,
                                   static_cast<uint32>(objectName.size()),
                                   objectName.c_str());

    objectName = "DX Swap Chain";
    m_pSwapChain->SetPrivateData(WKPDID_D3DDebugObjectName,
                                 static_cast<uint32>(objectName.size()),
                                 objectName.c_str());
#endif

    //Release all the adapters
    for (auto& adapter : vecAdapters) {
      safeRelease(adapter);
    }

    //Cleanup all the temporal objects in order
    safeRelease(dxgiAdapter);
    safeRelease(dxgiFactory);
    safeRelease(deviceContext);
    safeRelease(device);
    safeRelease(dxgiDevice);

    return false;
  }

  DX11RenderAPI::~DX11RenderAPI() {
    //Cleanup all the member objects in order
    m_pBackBufferTexture = nullptr;
    safeRelease(m_pSwapChain);

    m_pActiveContext = nullptr;
    safeRelease(m_pImmediateDC);

#if USING(GE_DEBUG_MODE)
    reportLiveObjects();
    safeRelease(m_pDebug);
#endif

    safeRelease(m_pDevice);
  }

  bool
  DX11RenderAPI::resizeSwapChain(uint32 newWidth, uint32 newHeight) {
    if (!m_pSwapChain) {
      return false;
    }

    m_pBackBufferTexture->release();
    m_pImmediateDC->ClearState();

    DXGI_SWAP_CHAIN_DESC scDesc;
    m_pSwapChain->GetDesc(&scDesc);

    throwIfFailed(m_pSwapChain->ResizeBuffers(scDesc.BufferCount,
                                              newWidth,
                                              newHeight,
                                              scDesc.BufferDesc.Format,
                                              DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));
    _updateBackBufferTexture();

    return true;
  }

  bool
  DX11RenderAPI::isMSAAFormatSupported(const TEXTURE_FORMAT::E format,
                                       int32& samplesPerPixel,
                                       int32& sampleQuality) const {
    GE_ASSERT(m_pDevice);

    SPtr<DXTexture> pBackBuffer = ge_shared_ptr_new<DXTexture>();

#if USING(GE_CPP17_OR_LATER)
    static UnorderedMap<TEXTURE_FORMAT::E, Optional<pair<int32, int32>>> s_msaaCache;
    auto it = s_msaaCache.find(format);
    if (it != s_msaaCache.end()) {
      if(it->second.has_value()) {
        samplesPerPixel = it->second->first;
        sampleQuality = it->second->second;
        return true;
      }
      return true;
    }
#endif

    samplesPerPixel = 1;
    sampleQuality = 0;
    const DXGI_FORMAT dxFormat = TranslateUtils::get(format);

    if (dxFormat == DXGI_FORMAT_UNKNOWN) {
      return false;
    }

    //Iterate to determine the maximum sample count supported for the format
    for (int32 i = D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; i > 0; --i) {
      uint32 quality;
      HRESULT hr = E_FAIL;
#if USING(DX_VERSION_11_0)
      hr = m_pDevice->CheckMultisampleQualityLevels(dxFormat, i, &quality);
#else
      hr = m_pDevice->CheckMultisampleQualityLevels1(dxFormat, i, 0, &quality);
#endif
      if (SUCCEEDED(hr)) {
        if (quality > 0) {
          samplesPerPixel = i;
          sampleQuality = quality - 1;
#if USING(GE_CPP17_OR_LATER)
          s_msaaCache[format] = make_pair(samplesPerPixel, sampleQuality);
#endif
          return true;
        }
      }
    }
#if USING(GE_CPP17_OR_LATER)
    s_msaaCache[format] = NullOpt;
#endif
    return false;
  }

  void
  DX11RenderAPI::msaaResolveRenderTarget(const WeakSPtr<Texture>& pSrc,
                                         const WeakSPtr<Texture>& pDst) {
    GE_ASSERT(m_pActiveContext);

    if (pDst.expired() || pSrc.expired()) {
      return;
    }

    auto pDstObj = reinterpret_cast<DXTexture*>(pDst.lock().get());
    auto pSrcObj = reinterpret_cast<DXTexture*>(pSrc.lock().get());

    auto dstFormat = TranslateUtils::get(pDstObj->getDesc().format);

    m_pActiveContext->ResolveSubresource(pDstObj->m_pTexture, 0,
                                         pSrcObj->m_pTexture, 0,
                                         dstFormat);
  }

  void
  DX11RenderAPI::reportLiveObjects(){
#if !USING(GE_DEBUG_MODE)
    return;
#endif
    if (!m_pDebug) {
      return;
    }
    //Report live objects
    m_pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
  }
  
  SPtr<Texture>
  DX11RenderAPI::createTexture(uint32 width,
                               uint32 height,
                               TEXTURE_FORMAT::E format,
                               uint32 bindFlags,
                               uint32 mipLevels,
                               RESOURCE_USAGE::E usage,
                               uint32 cpuAccessFlags,
                               uint32 sampleCount,
                               bool isMSAA,
                               bool isCubeMap,
                               uint32 arraySize) {
    GE_ASSERT(m_pDevice);

    auto pTexture = ge_shared_ptr_new<DXTexture>();

    DXGI_FORMAT inFormat = TranslateUtils::get(format);
    DXGI_FORMAT tex_format = inFormat;
    DXGI_FORMAT srv_format = tex_format;
    DXGI_FORMAT dsv_format = tex_format;

    if (bindFlags & D3D11_BIND_DEPTH_STENCIL) {
      bindFlags |= D3D11_BIND_SHADER_RESOURCE;

      switch (inFormat)
      {
      case DXGI_FORMAT_D32_FLOAT:
        tex_format = DXGI_FORMAT_R32_TYPELESS;
        srv_format = DXGI_FORMAT_R32_FLOAT;
        dsv_format = DXGI_FORMAT_D32_FLOAT;
        break;

      case DXGI_FORMAT_D24_UNORM_S8_UINT:
        tex_format = DXGI_FORMAT_R24G8_TYPELESS;
        srv_format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
        dsv_format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        break;

      case DXGI_FORMAT_D16_UNORM:
        tex_format = DXGI_FORMAT_R16_TYPELESS;
        srv_format = DXGI_FORMAT_R16_UNORM;
        dsv_format = DXGI_FORMAT_D16_UNORM;
        break;

      default:
        return nullptr;
      }
    }

    uint32 realArraySize = arraySize * (isCubeMap ? 6 : 1);

    if (usage == RESOURCE_USAGE::DYNAMIC) {
      cpuAccessFlags = D3D11_CPU_ACCESS_WRITE;
    }

    D3D11_TEXTURE2D_DESC tDesc;
    tDesc.Height = height;
    tDesc.Width = width;
    tDesc.MipLevels = mipLevels;
    tDesc.ArraySize = realArraySize;
    tDesc.Format = tex_format;
    tDesc.SampleDesc.Count = sampleCount;
    tDesc.SampleDesc.Quality = 0;
    tDesc.Usage = static_cast<D3D11_USAGE>(usage);
    tDesc.BindFlags = bindFlags;
    tDesc.CPUAccessFlags = cpuAccessFlags;
    tDesc.MiscFlags = isCubeMap ? D3D11_RESOURCE_MISC_TEXTURECUBE : 0;

    bool autogenMipmaps = false;
    if (mipLevels != 1 && usage != RESOURCE_USAGE::STAGING) {
      //Check if the format supports mipmaps
      uint32 fmtSupport = 0;
      HRESULT hr = m_pDevice->CheckFormatSupport(tex_format, &fmtSupport);
      if (SUCCEEDED(hr) && (fmtSupport & D3D11_FORMAT_SUPPORT_MIP_AUTOGEN)) {
        //If we want mipmaps, we REQUIRE that it is binded as a render target too
        tDesc.BindFlags |= D3D11_BIND_RENDER_TARGET;
        tDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
        if (mipLevels == 0) {
          mipLevels = static_cast<uint32>(Math::log2(float(Math::max(width, height)))) + 1;
          autogenMipmaps = true;
        }
      }
    }

    throwIfFailed(m_pDevice->CreateTexture2D(&tDesc,
                                             nullptr,
                                             &pTexture->m_pTexture));

    if (bindFlags & D3D11_BIND_RENDER_TARGET && !isCubeMap) {
#if !USING(DX_VERSION_11_3) && !USING(DX_VERSION_11_4)
      D3D11_RENDER_TARGET_VIEW_DESC rDesc;
#else
      D3D11_RENDER_TARGET_VIEW_DESC1 rDesc;
#endif
      rDesc.Format = tex_format;
      rDesc.ViewDimension = (sampleCount > 1 || isMSAA) ?
        D3D11_RTV_DIMENSION_TEXTURE2DMS : D3D11_RTV_DIMENSION_TEXTURE2D;

      pTexture->m_ppRTV.resize(mipLevels);
      for (uint32 i = 0; i < mipLevels; ++i) {
        rDesc.Texture2D.MipSlice = i;
#if USING(DX_VERSION_11_3) || USING(DX_VERSION_11_4)
        rDesc.Texture2D.PlaneSlice = 0;
        throwIfFailed(m_pDevice->CreateRenderTargetView1(pTexture->m_pTexture,
                                                         &rDesc,
                                                         &pTexture->m_ppRTV[i]));
#else
        throwIfFailed(m_pDevice->CreateRenderTargetView1(pTexture->m_pTexture,
                                                         &rDesc,
                                                         &pTexture->m_ppRTV[i]));
#endif          
      }
    }

    if (bindFlags & D3D11_BIND_DEPTH_STENCIL && !isCubeMap) {
      D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
      ge_zero_out(descDSV);

      descDSV.Flags = 0;
      descDSV.Format = dsv_format;
      descDSV.ViewDimension = (sampleCount > 1 || isMSAA) ?
        D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
      descDSV.Texture2D.MipSlice = 0;

      throwIfFailed(m_pDevice->CreateDepthStencilView(pTexture->m_pTexture,
        &descDSV,
        &pTexture->m_pDSV));

      descDSV.Flags |= D3D11_DSV_READ_ONLY_DEPTH;
      if (DXGI_FORMAT_D24_UNORM_S8_UINT == dsv_format) {
        descDSV.Flags |= D3D11_DSV_READ_ONLY_STENCIL;
      }

      throwIfFailed(m_pDevice->CreateDepthStencilView(pTexture->m_pTexture,
        &descDSV,
        &pTexture->m_pRO_DSV));
    }

    if (bindFlags & D3D11_BIND_UNORDERED_ACCESS && !isCubeMap) {
      D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
      uavDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
      uavDesc.Format = tex_format;

      pTexture->m_ppUAV.resize(mipLevels);
      for (uint32 i = 0; i < mipLevels; ++i) {
        uavDesc.Texture2D.MipSlice = i;
        throwIfFailed(m_pDevice->CreateUnorderedAccessView(pTexture->m_pTexture,
          &uavDesc,
          &pTexture->m_ppUAV[i]));
      }
    }

    if (bindFlags & D3D11_BIND_SHADER_RESOURCE) {
      pTexture->m_ppSRV.resize(mipLevels);

      D3D11_SHADER_RESOURCE_VIEW_DESC sDesc = CD3D11_SHADER_RESOURCE_VIEW_DESC();
      sDesc.Format = srv_format;
      uint32* pMostDetailedMip = nullptr;

      if (isCubeMap) {
        if (arraySize > 1) {
          sDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
          sDesc.TextureCubeArray.First2DArrayFace = 0;
          sDesc.TextureCubeArray.NumCubes = arraySize;
          sDesc.TextureCubeArray.MipLevels = mipLevels;
          pMostDetailedMip = &sDesc.TextureCubeArray.MostDetailedMip;
        }
        else {
          sDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
          sDesc.TextureCube.MipLevels = mipLevels;
          pMostDetailedMip = &sDesc.TextureCube.MostDetailedMip;
        }
      }
      else {
        sDesc.ViewDimension = (sampleCount > 1 || isMSAA) ?
          D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
        sDesc.Texture2D.MipLevels = mipLevels;
        pMostDetailedMip = &sDesc.Texture2D.MostDetailedMip;
      }

      for (uint32 i = 0; i < mipLevels; ++i) {
        *pMostDetailedMip = i;
        throwIfFailed(m_pDevice->CreateShaderResourceView(pTexture->m_pTexture,
                                                          &sDesc,
                                                          &pTexture->m_ppSRV[i]));
      }
    }

    if (autogenMipmaps) {
      generateMips(pTexture);
    }

    pTexture->m_desc = TranslateUtils::get(tDesc);
    pTexture->m_bIsCubeMap = isCubeMap;

    return pTexture;
  }

  SPtr<VertexDeclaration>
  DX11RenderAPI::createVertexDeclaration(const Vector<VertexElement>& elements) {
    GE_ASSERT(m_pDevice);
    if (elements.empty()) {
      GE_LOG(kError,
             Uncategorized,
             "DX11RenderAPI::createVertexDeclaration called with no elements.");
      return nullptr;
    }
    return ge_shared_ptr_new<VertexDeclaration>(elements);
  }

  SPtr<InputLayout>
  DX11RenderAPI::createInputLayout(const WeakSPtr<VertexDeclaration>& descArray,
                                   const WeakSPtr<VertexShader>& pVS) {
    GE_ASSERT(m_pDevice);

    if(descArray.expired() || pVS.expired()) {
      GE_LOG(kError,
             Uncategorized,
             "DX11RenderAPI::createInputLayout called with Invalid Parameters");
      return nullptr;
    }
    
    auto inputLayout = ge_unique_ptr_new<DXInputLayout>();

    auto pDesc = descArray.lock();
    auto vs = reinterpret_cast<DXShader*>(pVS.lock().get());

    //Translate the vertex elements to D3D11_INPUT_ELEMENT_DESC
    auto& declElements = pDesc->getProperties().getElements();
    Vector<D3D11_INPUT_ELEMENT_DESC> dxDescArray;

    int32 maxStreamIndex = -1;
    for(auto& elem : declElements) {
      dxDescArray.emplace_back();
      D3D11_INPUT_ELEMENT_DESC& desc = dxDescArray.back();

      desc.SemanticName = TranslateUtils::toString(elem.getSemantic());
      desc.SemanticIndex = elem.getSemanticIndex();
      desc.Format = TranslateUtils::get(elem.getType());
      desc.InputSlot = elem.getStreamIndex();
      desc.AlignedByteOffset = static_cast<WORD>(elem.getOffset());

      if (elem.getInstanceStepRate() == 0) {
        desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        desc.InstanceDataStepRate = 0;
      }
      else {
        desc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
        desc.InstanceDataStepRate = elem.getInstanceStepRate();
      }

      maxStreamIndex = Math::max(maxStreamIndex, int32(elem.getStreamIndex()));
    }

    HRESULT hr = m_pDevice->CreateInputLayout(&dxDescArray[0],
                                              static_cast<uint32>(dxDescArray.size()),
                                              vs->m_pBlob->GetBufferPointer(),
                                              vs->m_pBlob->GetBufferSize(),
                                              &inputLayout->m_inputLayout);
    if (FAILED(hr)) {
      GE_LOG(kError,
        Uncategorized,
        "Failed to create Input Layout.");
      return nullptr;
    }
    
    //Should we set the vertex declaration here?
    inputLayout->m_vertexDeclaration = pDesc;

    return inputLayout;
  }

  SPtr<InputLayout>
  DX11RenderAPI::createInputLayoutFromShader(const WeakSPtr<VertexShader>& pVS) {
    GE_ASSERT(m_pDevice);

    if (pVS.expired()) {
      GE_LOG(kError,
             Uncategorized,
             "Vertex Shader is expired.");
      return nullptr;
    }

    //Use the reflection API to get the input layout
    ID3D11ShaderReflection* pReflector = nullptr;
    {//This scope is to unlock the Vertex Shader after reflection
      auto pDXVS = reinterpret_cast<DXShader*>(pVS.lock().get());
      throwIfFailed(D3DReflect(pDXVS->m_pBlob->GetBufferPointer(),
                               pDXVS->m_pBlob->GetBufferSize(),
                               __uuidof(ID3D11ShaderReflection),
                               reinterpret_cast<void**>(&pReflector)));

    }

    D3D11_SHADER_DESC shaderDesc;
    pReflector->GetDesc(&shaderDesc);

    Vector<D3D11_INPUT_ELEMENT_DESC> descArray;
    descArray.reserve(shaderDesc.InputParameters);
    
    Vector<VertexElement> vertexElements;
    vertexElements.reserve(shaderDesc.InputParameters);

    //Loop through all the input parameters and create the input element descriptors
    uint32 offset = 0;
    for (uint32 i = 0; i < shaderDesc.InputParameters; ++i) {
      D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
      throwIfFailed(pReflector->GetInputParameterDesc(i, &paramDesc));

      //We ignore the system value semantics, as they are not used in the vertex shader
      if (StringUtil::startsWith(String(paramDesc.SemanticName), "sv_")) {
        continue;
      }

      vertexElements.emplace_back(paramDesc.Stream,
                                  offset,
                                  TranslateUtils::getInputType(paramDesc.ComponentType,
                                    paramDesc.Mask),
                                  TranslateUtils::get(paramDesc.SemanticName),
                                  paramDesc.SemanticIndex);

      offset += vertexElements.back().getSize();
    }

    safeRelease(pReflector);

    //Create the vertex declaration from the elements
    auto pVertexDecl = createVertexDeclaration(vertexElements);
    
    return createInputLayout(pVertexDecl, pVS);
  }

  /*************************************************************************/
  // Create Shaders
  /*************************************************************************/
  bool
  _compileFromFile(const Path& fileName,
                   const Vector<ShaderMacro>& pMacros,
                   const String szEntryPoint,
                   const String szShaderModel,
                   ID3DBlob** pBlob) {
    HRESULT hr = S_OK;
    int32 dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS ;
#if USING(GE_DEBUG_MODE)
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    static D3DIncludeHandler includeHandler({
      "Data/Engine/Shaders/",
      "Data/Shaders/"
    });

    //Add shader preprocessor definitions
    Vector<D3D_SHADER_MACRO> defines;
    defines.reserve(pMacros.size() + 1);
    for (const auto& macro : pMacros)
    {
      D3D_SHADER_MACRO def;
      def.Name = macro.name.c_str();
      def.Definition = macro.definition.c_str();
      defines.push_back(def);
    }

    defines.push_back({ nullptr, nullptr });

    ID3DBlob* pErrorBlob = nullptr;
    WString file = fileName.toPlatformString();
    hr = D3DCompileFromFile(file.c_str(),
                            defines.data(),
                            &includeHandler,
                            szEntryPoint.c_str(),
                            szShaderModel.c_str(),
                            dwShaderFlags,
                            0,
                            pBlob,
                            &pErrorBlob);

    if (FAILED(hr)) {
      if (nullptr != pErrorBlob) {
        GE_LOG(kError,
               Uncategorized,
               reinterpret_cast<char*>(pErrorBlob->GetBufferPointer()));
        safeRelease(pErrorBlob);
      }

      return false;
    }

    safeRelease(pErrorBlob);

    return true;
  }

  SPtr<VertexShader>
  DX11RenderAPI::createVertexShader(CREATE_SHADER_PARAMS) {
    GE_ASSERT(m_pDevice);
    auto vShader = ge_shared_ptr_new<DXShader>();

    if (!_compileFromFile(fileName, pMacro, szEntryPoint, szShaderModel, &vShader->m_pBlob)) {
      GE_LOG(kError,
             Uncategorized,
             "Could not compile VertexShader Shader from {1}", fileName);
      return nullptr;
    }

    HRESULT hr = m_pDevice->CreateVertexShader(vShader->m_pBlob->GetBufferPointer(),
                              vShader->m_pBlob->GetBufferSize(),
                              nullptr,
                              reinterpret_cast<ID3D11VertexShader**>(&vShader->m_pShader));
    if (FAILED(hr)) {
      GE_LOG(kError,
             Uncategorized,
             "Failed to create VertexShader Shader '{1}' from '{2}'",
             szEntryPoint,
             fileName);
      return nullptr;
    }

    return vShader;
  }

  SPtr<PixelShader>
  DX11RenderAPI::createPixelShader(CREATE_SHADER_PARAMS) {
    GE_ASSERT(m_pDevice);
    auto vShader = ge_shared_ptr_new<DXShader>();

    if (!_compileFromFile(fileName, pMacro, szEntryPoint, szShaderModel, &vShader->m_pBlob)) {
      GE_LOG(kError,
             Uncategorized,
             "Could not compile PixelShader Shader from {1}", fileName);
      return nullptr;
    }

    HRESULT hr = m_pDevice->CreatePixelShader(vShader->m_pBlob->GetBufferPointer(),
                              vShader->m_pBlob->GetBufferSize(),
                              nullptr,
                              reinterpret_cast<ID3D11PixelShader**>(&vShader->m_pShader));
    if (FAILED(hr)) {
      GE_LOG(kError,
             Uncategorized,
             "Failed to create PixelShader Shader '{1}' from '{2}'",
             szEntryPoint,
             fileName);
      return nullptr;
    }

    return vShader;
  }

  SPtr<GeometryShader>
  DX11RenderAPI::createGeometryShader(CREATE_SHADER_PARAMS) {
    GE_ASSERT(m_pDevice);
    auto vShader = ge_shared_ptr_new<DXShader>();

    if (!_compileFromFile(fileName, pMacro, szEntryPoint, szShaderModel, &vShader->m_pBlob)) {
      GE_LOG(kError,
             Uncategorized,
             "Could not compile GeometryShader Shader from {1}", fileName);
      return nullptr;
    }

    HRESULT hr = m_pDevice->CreateGeometryShader(vShader->m_pBlob->GetBufferPointer(),
                              vShader->m_pBlob->GetBufferSize(),
                              nullptr,
                              reinterpret_cast<ID3D11GeometryShader**>(&vShader->m_pShader));
    if (FAILED(hr)) {
      GE_LOG(kError,
             Uncategorized,
             "Failed to create GeometryShader Shader '{1}' from '{2}'",
             szEntryPoint,
             fileName);
      return nullptr;
    }

    return vShader;
  }

  SPtr<HullShader>
  DX11RenderAPI::createHullShader(CREATE_SHADER_PARAMS) {
    GE_ASSERT(m_pDevice);
    auto vShader = ge_shared_ptr_new<DXShader>();

    if (!_compileFromFile(fileName, pMacro, szEntryPoint, szShaderModel, &vShader->m_pBlob)) {
      GE_LOG(kError,
             Uncategorized,
             "Could not compile HullShader Shader from {1}", fileName);
      return nullptr;
    }

    HRESULT hr = m_pDevice->CreateHullShader(vShader->m_pBlob->GetBufferPointer(),
                              vShader->m_pBlob->GetBufferSize(),
                              nullptr,
                              reinterpret_cast<ID3D11HullShader**>(&vShader->m_pShader));
    if (FAILED(hr)) {
      GE_LOG(kError,
             Uncategorized,
             "Failed to create GeometryShader Shader '{1}' from '{2}'",
             szEntryPoint,
             fileName);
      return nullptr;
    }

    return vShader;
  }

  SPtr<DomainShader>
  DX11RenderAPI::createDomainShader(CREATE_SHADER_PARAMS) {
    GE_ASSERT(m_pDevice);
    auto vShader = ge_shared_ptr_new<DXShader>();

    if (!_compileFromFile(fileName, pMacro, szEntryPoint, szShaderModel, &vShader->m_pBlob)) {
      GE_LOG(kError,
             Uncategorized,
             "Could not compile DomainShader Shader from {1}", fileName);
      return nullptr;
    }

    HRESULT hr = m_pDevice->CreateDomainShader(vShader->m_pBlob->GetBufferPointer(),
                              vShader->m_pBlob->GetBufferSize(),
                              nullptr,
                              reinterpret_cast<ID3D11DomainShader**>(&vShader->m_pShader));
    if (FAILED(hr)) {
      GE_LOG(kError,
             Uncategorized,
             "Failed to create DomainShader Shader '{1}' from '{2}'",
             szEntryPoint,
             fileName);
      return nullptr;
    }

    return vShader;
  }

  SPtr<ComputeShader>
  DX11RenderAPI::createComputeShader(CREATE_SHADER_PARAMS) {
    GE_ASSERT(m_pDevice);
    auto vShader = ge_shared_ptr_new<DXShader>();

    if (!_compileFromFile(fileName, pMacro, szEntryPoint, szShaderModel, &vShader->m_pBlob)) {
      GE_LOG(kError,
             Uncategorized,
             "Could not compile ComputeShader Shader from {1}", fileName);
      return nullptr;
    }

    HRESULT hr = m_pDevice->CreateComputeShader(vShader->m_pBlob->GetBufferPointer(),
                              vShader->m_pBlob->GetBufferSize(),
                              nullptr,
                              reinterpret_cast<ID3D11ComputeShader**>(&vShader->m_pShader));
    if (FAILED(hr)) {
      GE_LOG(kError,
             Uncategorized,
             "Failed to create ComputeShader Shader '{1}' from '{2}'",
             szEntryPoint,
             fileName);
      return nullptr;
    }

    return vShader;
  }

  /*************************************************************************/
  // Write Functions
  /*************************************************************************/

  void
  DX11RenderAPI::writeToResource(const WeakSPtr<GraphicsResource>& pResource,
                                 uint32 dstSubRes,
                                 const GRAPHICS_BOX* pDstBox,
                                 const void* pSrcData,
                                 uint32 srcRowPitch,
                                 uint32 srcDepthPitch,
                                 uint32 copyFlags) {
    GE_ASSERT(m_pActiveContext);

    if (pResource.expired()) {
      return;
    }

    auto pTex = pResource.lock();
    auto pGraphRes =
      reinterpret_cast<ID3D11Resource*>(pTex->_getGraphicsResource());
    GE_ASSERT(pGraphRes);

    m_pActiveContext->UpdateSubresource1(pGraphRes,
                                         dstSubRes,
                                         pDstBox ? nullptr :
                                         reinterpret_cast<const D3D11_BOX*>(pDstBox),
                                         pSrcData,
                                         srcRowPitch,
                                         srcDepthPitch,
                                         copyFlags);
  }

  MappedSubresource
  DX11RenderAPI::mapToRead(const WeakSPtr<GraphicsResource>& pResource,
                           uint32 subResource,
                           uint32 mapFlags) {
    GE_ASSERT(m_pActiveContext);

    MappedSubresource mappedSubresource;
    mappedSubresource.pData = nullptr;

    if (pResource.expired()) {
      return mappedSubresource;
    }

    auto pTex = pResource.lock();
    auto pGraphRes =
      reinterpret_cast<ID3D11Resource*>(pTex->_getGraphicsResource());
    GE_ASSERT(pGraphRes);

    ge_zero_out(mappedSubresource);
    m_pActiveContext->Map(pGraphRes,
                          subResource,
                          D3D11_MAP_READ,
                          mapFlags,
                          reinterpret_cast<D3D11_MAPPED_SUBRESOURCE*>(&mappedSubresource));

    if (mappedSubresource.pData == nullptr) {
      GE_LOG(kError, Uncategorized, "Failed to map texture.");
    }

    return mappedSubresource;
  }

  void
  DX11RenderAPI::unmap(const WeakSPtr<GraphicsResource>& pResource,
                       uint32 subResource) {
    GE_ASSERT(m_pActiveContext);
    if (pResource.expired()) {
      return;
    }

    auto pTex = pResource.lock();
    auto pGraphRes =
      reinterpret_cast<ID3D11Resource*>(pTex->_getGraphicsResource());
    GE_ASSERT(pGraphRes);

    m_pActiveContext->Unmap(pGraphRes, subResource);
  }

  void
  DX11RenderAPI::copyResource(const WeakSPtr<GraphicsResource>& pSrcObj,
                              const WeakSPtr<GraphicsResource>& pDstObj) {
    GE_ASSERT(m_pActiveContext);

    if (pSrcObj.expired() || pDstObj.expired()) {
      return;
    }

    auto pSrc = pSrcObj.lock();
    auto pDst = pDstObj.lock();

    auto pSrcDst = reinterpret_cast<ID3D11Resource*>(pSrc->_getGraphicsResource());
    auto pResDst = reinterpret_cast<ID3D11Resource*>(pDst->_getGraphicsResource());

    GE_ASSERT(pSrcDst && pResDst);

    //Copy the resource to the destination
    m_pActiveContext->CopyResource(pResDst, pSrcDst);
  }

  void
  DX11RenderAPI::generateMips(const WeakSPtr<Texture>& pTexture) {
    GE_ASSERT(m_pActiveContext);

    if (pTexture.expired()) {
      return;
    }

    auto pObj = pTexture.lock();
    auto pDXObj = reinterpret_cast<DXTexture*>(pObj.get());

    m_pActiveContext->GenerateMips(pDXObj->m_ppSRV[0]);
  }

  void
  DX11RenderAPI::clearRenderTarget(const WeakSPtr<Texture>& pRenderTarget,
                                   const LinearColor& color) {
    GE_ASSERT(m_pActiveContext);

    if (pRenderTarget.expired()) {
      return;
    }

    auto pObj = pRenderTarget.lock();
    auto pDXObj = reinterpret_cast<DXTexture*>(pObj.get());
    GE_ASSERT(!pDXObj->m_ppRTV.empty());

    ID3D11RenderTargetView* pTarget = pDXObj->m_ppRTV[0];
    m_pActiveContext->ClearRenderTargetView(pTarget, reinterpret_cast<const FLOAT*>(&color));
  }

  void
  DX11RenderAPI::clearDepthStencil(const WeakSPtr<Texture>& pDepthStencilView,
                                   uint32 flags,
                                   float depthVal,
                                   uint8 stencilVal) {
    GE_ASSERT(m_pActiveContext);

    if (pDepthStencilView.expired()) {
      return;
    }

    auto pObj = pDepthStencilView.lock();
    auto pDXObj = reinterpret_cast<DXTexture*>(pObj.get());
    GE_ASSERT(pDXObj->m_pDSV);

    m_pActiveContext->ClearDepthStencilView(pDXObj->m_pDSV, flags, depthVal, stencilVal);
  }

  void
  DX11RenderAPI::discardView(WeakSPtr<Texture> pTexture) {
    GE_ASSERT(m_pActiveContext);

    if (pTexture.expired()) {
      return;
    }

    auto pObj = pTexture.lock();
    auto pDXObj = reinterpret_cast<DXTexture*>(pObj.get());

    ID3D11View* pView = nullptr;
    if (!pDXObj->m_ppRTV.empty()) {
      pView = pDXObj->m_ppRTV[0];
    }
    else if (pDXObj->m_pDSV) {
      pView = pDXObj->m_pDSV;
    }
    else {
      GE_ASSERT(false && "Texture has no RTV or DSV to discard.");
      return;
    }

    m_pActiveContext->DiscardView(pView);
  }

  void
  DX11RenderAPI::present() {
    GE_ASSERT(m_pSwapChain && m_pActiveContext && m_pBackBufferTexture);

#if USING(DX_VERSION_11_0)
    m_pSwapChain->Present(1, 0);
#else
    static DXGI_PRESENT_PARAMETERS presentParams = {};
    m_pSwapChain->Present1(1, 0, &presentParams);
    //m_pActiveContext->DiscardView(m_pBackBufferTexture->m_ppRTV[0]);
    //m_pActiveContext->DiscardView(m_pDepthStencil->m_pDSV);
#endif
  }

  void
  DX11RenderAPI::setImmediateContext() {
    m_pActiveContext = m_pImmediateDC;
  }

  void
  DX11RenderAPI::setViewports(const Vector<GRAPHICS_VIEWPORT>& viewports) {
    GE_ASSERT(m_pActiveContext);
    
    uint32 numViewports = static_cast<uint32>(viewports.size());
    GE_ASSERT(numViewports >= 0 &&
              numViewports <= D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE);

    //This conteiner is used to store the converted viewports
    static Vector<D3D11_VIEWPORT>
      dxViewports(D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE);

    memcpy(&dxViewports[0], viewports.data(), sizeof(D3D11_VIEWPORT) * numViewports);
    m_pActiveContext->RSSetViewports(numViewports, &dxViewports[0]);
  }

  void
  DX11RenderAPI::setRenderTargets(const Vector<RenderTarget>& pTargets,
                                  const WeakSPtr<Texture>& pDepthStencilView) {
    GE_ASSERT(m_pActiveContext);

    static Vector<ID3D11RenderTargetView*>
      pRTVs(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT);

    uint32 numTargets = static_cast<uint32>(pTargets.size());

    for(uint32 i = 0; i < numTargets; ++i) {
      const RenderTarget& target = pTargets[i];
      if (target.pRenderTarget.expired()) {
        pRTVs[i] = nullptr;
        continue;
      }

      auto pObj = target.pRenderTarget.lock();
      auto pDXObj = reinterpret_cast<DXTexture*>(pObj.get());

      GE_ASSERT(pDXObj->m_ppRTV.size() > target.mipLevel);
      ID3D11RenderTargetView* pRTV = pDXObj->m_ppRTV[target.mipLevel];
      pRTVs[i] = pRTV;
    }

    ID3D11DepthStencilView* pDS = nullptr;
    if (!pDepthStencilView.expired()) {
      auto pObj = pDepthStencilView.lock();
      auto pDXObj = reinterpret_cast<DXTexture*>(pObj.get());
      pDS = pDXObj->m_pDSV;
    }

    m_pActiveContext->OMSetRenderTargets(numTargets, pRTVs.data(), pDS);
  }

  void
  DX11RenderAPI::_updateBackBufferTexture() {
    GE_ASSERT(m_pDevice && m_pSwapChain);

    //Release the old back buffer and creates a new one
    m_pBackBufferTexture = ge_shared_ptr_new<DXTexture>();
    if(!m_pBackBufferTexture) {
      GE_EXCEPT(RenderingAPIException,
                "Failed to allocate back buffer texture.");
    }
    
    m_pBackBufferTexture->m_ppRTV.push_back(nullptr);

    //Create a render target view
    throwIfFailed(m_pSwapChain->GetBuffer(0,
      __uuidof(ID3D11Texture2D),
      reinterpret_cast<LPVOID*>(&m_pBackBufferTexture->m_pTexture)));

#if !USING(DX_VERSION_11_3) && !USING(DX_VERSION_11_4)
    throwIfFailed(m_pDevice->CreateRenderTargetView(m_pBackBufferTexture->m_pTexture,
                                                    nullptr,
                                                    &m_pBackBufferTexture->m_ppRTV[0]));
#else
    throwIfFailed(m_pDevice->CreateRenderTargetView1(m_pBackBufferTexture->m_pTexture,
                                                    nullptr,
                                                    &m_pBackBufferTexture->m_ppRTV[0]));
#endif

    D3D11_TEXTURE2D_DESC desc;
    m_pBackBufferTexture->m_pTexture->GetDesc(&desc);
    m_pBackBufferTexture->_setDesc(desc);
  }

  WeakSPtr<Texture>
  DX11RenderAPI::getBackBuffer() const {
    return m_pBackBufferTexture;
  }



}
