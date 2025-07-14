/*****************************************************************************/
/**
 * @file    geGraphicsInterfaces.h
 * @author  Samuel Prince (samuel.prince.quezada@gmail.com)
 * @date    2025/06/26
 * @brief   Graphics Interfaces Implementation with DirectX11.
 *
 * Graphics Interfaces.
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
#include "gePrerequisitesRenderAPIDX11.h"
#include <geGraphicsInterfaces.h>
#include <geVector4.h>

namespace geEngineSDK
{

  class DXRasterizerState : public RasterizerState
  {
   public:
    virtual ~DXRasterizerState() {
      release();
    }

    void
    release() override {
      safeRelease(m_pRasterizerState);
    }

    void
    setDebugName(const String& name) override {
#if USING(GE_DEBUG_MODE)
      if (m_pRasterizerState) {
        m_pRasterizerState->SetPrivateData(WKPDID_D3DDebugObjectName,
                                           static_cast<UINT>(name.size()),
                                           name.c_str());
      }
#endif
    }

   protected:
    friend class DX11RenderAPI;

    D3DRasterizerState* m_pRasterizerState = nullptr;
  };

  class DXDepthStencilState : public DepthStencilState
  {
   public:
    virtual ~DXDepthStencilState() {
      release();
    }

    void
    release() override {
      safeRelease(m_pDepthStencilState);
    }

    void
    setDebugName(const String& name) override {
#if USING(GE_DEBUG_MODE)
      if (m_pDepthStencilState) {
        m_pDepthStencilState->SetPrivateData(WKPDID_D3DDebugObjectName,
                                             static_cast<UINT>(name.size()),
                                             name.c_str());
      }
#endif
    }

   protected:
    friend class DX11RenderAPI;
    ID3D11DepthStencilState* m_pDepthStencilState = nullptr;
  };

  class DXBlendState : public BlendState
  {
   public:
    virtual ~DXBlendState() {
      release();
    }

    void
    release() override {
      safeRelease(m_pBlendState);
    }

    void
    setDebugName(const String& name) override {
#if USING(GE_DEBUG_MODE)
      if (m_pBlendState) {
        m_pBlendState->SetPrivateData(WKPDID_D3DDebugObjectName,
                                      static_cast<UINT>(name.size()),
                                      name.c_str());
      }
#endif
    }

   protected:
    friend class DX11RenderAPI;
    D3DBlendState* m_pBlendState = nullptr;
    Vector4 m_blendFactors = Vector4::ZERO;
    uint32 m_sampleMask = NumLimit::MAX_UINT32;
  };

  class DXSamplerState : public SamplerState
  {
   public:
    virtual ~DXSamplerState() {
      release();
    }

    void
    release() override {
      safeRelease(m_pSampler);
    }
    
    void
    setDebugName(const String& name) override {
#if USING(GE_DEBUG_MODE)
      if (m_pSampler) {
        m_pSampler->SetPrivateData(WKPDID_D3DDebugObjectName,
                                   static_cast<UINT>(name.size()),
                                   name.c_str());
      }
#endif
    }
   protected:
    friend class DX11RenderAPI;
    ID3D11SamplerState* m_pSampler = nullptr;
  };

} // namespace geEngineSDK
