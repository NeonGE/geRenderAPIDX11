/*****************************************************************************/
/**
 * @file    DX11GraphicsManager.h
 * @author  Samuel Prince (samuel.prince.quezada@gmail.com)
 * @date    2025/06/29
 * @brief   Graphics API implementation on DirectX11.
 *
 * Graphics API implementation on DirectX11.
 *
 * @bug	    No known bugs.
 */
/*****************************************************************************/
#pragma once

/*****************************************************************************/
/**
 * Includes
 */
/*****************************************************************************/

#include <gePrerequisitesRenderAPIDX11.h>
#include <geRenderAPI.h>

#include "DXInputLayout.h"
#include "DXTexture.h"
#include "DXShader.h"


namespace geEngineSDK {

  class DX11RenderAPI : public RenderAPI
  {
   public:
    DX11RenderAPI() = default;
    virtual ~DX11RenderAPI();
    
    bool
    initRenderAPI(void* scrHandle, bool bFullScreen) override;

    bool
    resizeSwapChain(uint32 newWidth, uint32 newHeight) override;

    bool
    isMSAAFormatSupported(const GRAPHICS_FORMAT::E format,
                          int32& samplesPerPixel,
                          int32& sampleQuality) const override;

    void
    msaaResolveRenderTarget(const WeakSPtr<Texture>& pSrc,
                            const WeakSPtr<Texture>& pDst) override;

    void
    reportLiveObjects() override;

    //************************************************************************/
    // Get methods
    //************************************************************************/
    WeakSPtr<Texture>
    getBackBuffer() const override;

    /*************************************************************************/
    // Create methods
    /*************************************************************************/
    SPtr<Texture>
    createTexture(uint32 width,
                  uint32 height,
                  GRAPHICS_FORMAT::E format,
                  uint32 bindFlags = BIND_FLAG::SHADER_RESOURCE,
                  uint32 mipLevels = 1,
                  RESOURCE_USAGE::E usage = RESOURCE_USAGE::DEFAULT,
                  uint32 cpuAccessFlags = 0,
                  uint32 sampleCount = 1,
                  bool isMSAA = false,
                  bool isCubeMap = false,
                  uint32 arraySize = 1) override;

    SPtr<VertexDeclaration>
    createVertexDeclaration(const Vector<VertexElement>& elements) override;

    SPtr<InputLayout>
    createInputLayout(const WeakSPtr<VertexDeclaration>& descArray,
                      const WeakSPtr<VertexShader>& pVS);

    SPtr<InputLayout>
    createInputLayoutFromShader(const WeakSPtr<VertexShader>& pVS);

    /*************************************************************************/
    // Create Buffers
    /*************************************************************************/
   private:
    void
    _createBuffer(uint32 bindFlags,
                  SIZE_T sizeInBytes,
                  const void* pInitialData,
                  const uint32 usage,
                  const uint32 byteStride,
                  ID3D11Buffer** outBuffer,
                  D3D11_BUFFER_DESC& outDesc) const;

   public:
    SPtr<VertexBuffer>
    createVertexBuffer(const SPtr<VertexDeclaration>& pDecl, 
                       const SIZE_T sizeInBytes,
                       const void* pInitialData = nullptr,
                       const uint32 usage = RESOURCE_USAGE::DEFAULT) override;

    SPtr<IndexBuffer>
    createIndexBuffer(const SIZE_T sizeInBytes,
                      const void* pInitialData = nullptr,
                      const INDEX_BUFFER_FORMAT::E format = INDEX_BUFFER_FORMAT::R32_UINT,
                      const uint32 usage = RESOURCE_USAGE::DEFAULT) override;

    SPtr<ConstantBuffer>
    createConstantBuffer(const SIZE_T sizeInBytes,
                         const void* pInitialData = nullptr,
                         const uint32 usage = RESOURCE_USAGE::DEFAULT) override;

    /*************************************************************************/
    // Create Pipeline State Objects
    /*************************************************************************/
    SPtr<RasterizerState>
    createRasterizerState(const RASTERIZER_DESC& rasterDesc) override;

    SPtr<DepthStencilState>
    createDepthStencilState(const DEPTH_STENCIL_DESC& depthStencilDesc) override;

    SPtr<BlendState>
    createBlendState(const BLEND_DESC& blendDesc,
                     const Vector4 blendFactors = Vector4::ZERO,
                     const uint32 sampleMask = NumLimit::MAX_UINT32) override;

    SPtr<SamplerState>
    createSamplerState(const SAMPLER_DESC& samplerDesc) override;

    /*************************************************************************/
    // Create Shaders
    /*************************************************************************/

    SPtr<VertexShader>
    createVertexShader(CREATE_SHADER_PARAMS) override;

    SPtr<PixelShader>
    createPixelShader(CREATE_SHADER_PARAMS) override;

    SPtr<GeometryShader>
    createGeometryShader(CREATE_SHADER_PARAMS) override;

    SPtr<HullShader>
    createHullShader(CREATE_SHADER_PARAMS) override;

    SPtr<DomainShader>
    createDomainShader(CREATE_SHADER_PARAMS) override;

    SPtr<ComputeShader>
    createComputeShader(CREATE_SHADER_PARAMS) override;

    /*************************************************************************/
    // Write Functions
    /*************************************************************************/
    void
    writeToResource(const WeakSPtr<GraphicsResource>& pResource,
                    uint32 dstSubRes,
                    const GRAPHICS_BOX* pDstBox,
                    const void* pSrcData,
                    uint32 srcRowPitch,
                    uint32 srcDepthPitch,
                    uint32 copyFlags = 0) override;

    MappedSubresource
    mapToRead(const WeakSPtr<GraphicsResource>& pTexture,
              uint32 subResource = 0,
              uint32 mapFlags = 0) override;

    void
    unmap(const WeakSPtr<GraphicsResource>& pTexture,
          uint32 subResource = 0) override;

    void
    copyResource(const WeakSPtr<GraphicsResource>& pSrcObj,
                 const WeakSPtr<GraphicsResource>& pDstObj) override;

    void
    generateMips(const WeakSPtr<Texture>& pTexture) override;

    void
    clearRenderTarget(const WeakSPtr<Texture>& pRenderTarget,
                      const LinearColor& color = LinearColor::Black) override;

    void
    clearDepthStencil(const WeakSPtr<Texture>& pDepthStencilView,
                      uint32 flags = CLEAR_FLAG::DEPTH | CLEAR_FLAG::STENCIL,
                      float depthVal = 1.0f,
                      uint8 stencilVal = 0U) override;

    void
    discardView(WeakSPtr<Texture> pTexture) override;

    void
    present() override;

    /*************************************************************************/
    // Set Objects
    /*************************************************************************/

    void
    setImmediateContext() override;

    void
    setTopology(PRIMITIVE_TOPOLOGY::E topologyType) override;

    void
    setViewports(const Vector<GRAPHICS_VIEWPORT>& viewports) override;

    void
    setRenderTargets(const Vector<RenderTarget>& pTargets,
                     const WeakSPtr<Texture>& pDepthStencilView) override;

   private:
    void
    _updateBackBufferTexture();

   private:
    D3DDevice* m_pDevice = nullptr;

    D3DDeviceContext* m_pActiveContext = nullptr;
    D3DDeviceContext* m_pImmediateDC = nullptr;

    D3DSwapChain* m_pSwapChain = nullptr;

#if USING(GE_DEBUG_MODE)
    ID3D11Debug* m_pDebug = nullptr;
#endif
    //Helper variables
    bool m_bFullScreen = false;
    ADAPTER_DESC m_selectedAdapterDesc;

    //Back buffer control
    SPtr<DXTexture> m_pBackBufferTexture;
  };
} // namespace geEngineSDK
