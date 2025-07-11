/*****************************************************************************/
/**
 * @file    DXTexture.cpp
 * @author  Samuel Prince (samuel.prince.quezada@gmail.com)
 * @date    2025/06/26
 * @brief   DirectX Implementation of the Texture Object.
 *
 * DirectX Implementation of the Texture Object.
 *
 * @bug	    No known bugs.
 */
/*****************************************************************************/

/*****************************************************************************/
/**
 * Includes
 */
/*****************************************************************************/
#include "DXTexture.h"
#include "DXTranslateUtils.h"

#include <geVector3.h>

namespace geEngineSDK {

  DXTexture::~DXTexture() {
    release();
  }

  void
  DXTexture::release() {
    safeRelease(m_pTexture);
    safeRelease(m_pDSV);
    safeRelease(m_pRO_DSV);

    if (m_desc.bindFlags & D3D11_BIND_SHADER_RESOURCE) {
      for (auto& pSRV : m_ppSRV) {
        safeRelease(pSRV);
      }
      m_ppSRV.clear();
    }
    if (m_desc.bindFlags & D3D11_BIND_RENDER_TARGET) {
      for (auto& pRTV : m_ppRTV) {
        safeRelease(pRTV);
      }
      m_ppRTV.clear();
    }
    if (m_desc.bindFlags & D3D11_BIND_UNORDERED_ACCESS) {
      for (auto& pUAV : m_ppUAV) {
        safeRelease(pUAV);
      }
      m_ppUAV.clear();
    }

    m_desc.bindFlags = 0;
  }

  Vector3
  DXTexture::getDimensions() const {
    return Vector3();
  }

  void
  DXTexture::setDebugName(const String& name) {
#if USING(GE_DEBUG_MODE)
    m_debugName = name;
#endif
    return;
  }

  SIZE_T
  DXTexture::getMemoryUsage() const {
    SIZE_T sizeInMemory = 0;
    if (m_pTexture) {
      const SIZE_T& width = m_desc.width;
      const SIZE_T& height = m_desc.height;
      const SIZE_T& mipLevels = m_desc.mipLevels;
      const SIZE_T bpp =
        TranslateUtils::getBitsPerPixel(static_cast<const DXGI_FORMAT>(m_desc.format));

      for (SIZE_T i = 0; i < mipLevels; ++i) {
        sizeInMemory += (width >> i) * (height >> i) * (bpp >> 3);
      }
    }

    return sizeInMemory;
  }

  void
  DXTexture::_setDesc(D3D11_TEXTURE2D_DESC& desc) {
    m_desc = TranslateUtils::get(desc);
  }

  void*
  DXTexture::_getGraphicsResource() const {
    return m_pTexture;
  }

}
