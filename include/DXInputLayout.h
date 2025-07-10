/*****************************************************************************/
/**
 * @file    DXInputLayout.h
 * @author  Samuel Prince (samuel.prince.quezada@gmail.com)
 * @date    2025/07/07
 * @brief   Object that describes the memory layout of a Vertex Buffer in DX.
 *
 * Object that describes the memory layout of a Vertex Buffer in DX.
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
#include <geInputLayout.h>

namespace geEngineSDK {

  class DXInputLayout : public InputLayout
  {
   public:
    DXInputLayout() = default;
    virtual ~DXInputLayout() = default;

   protected:
    friend class DX11RenderAPI;
    friend class DXInputLayoutManager;

    ID3D11InputLayout* m_inputLayout = nullptr;
  };
  /*
  class DXInputLayoutManager
  {
   public:
    DXInputLayoutManager() = default;
    virtual ~DXInputLayoutManager() = default;

   protected:
    friend class RenderAPI;
    
    void
    addInputLayout(const SPtr<InputLayout>& pLayout);

    void
    removeInputLayout(const SPtr<InputLayout>& pLayout);

    struct InputLayoutElement
    {
      SPtr<InputLayout> layout;
      uint32 id;
    };

   protected:
    UnorderedMap<uint32, SPtr<InputLayout>> m_inputLayouts;
    uint32 m_nextId = 0;
  };
  */
} // namespace geEngineSDK
