/*****************************************************************************/
/**
 * @file    DXGraphicsBuffer.h
 * @author  Samuel Prince (samuel.prince.quezada@gmail.com)
 * @date    2025/06/26
 * @brief   Graphics Buffer Interface .
 *
 * Graphics Buffer Interface. This interface defines the methods and properties
 * To unify the management of graphics buffers across different graphics APIs.
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
#include "DXGraphicsInterfaces.h"

namespace geEngineSDK
{

  class DXGraphicsBuffer : public GraphicsBuffer
  {
   public:
    DXGraphicsBuffer() = default;
    virtual ~DXGraphicsBuffer() = default;
    
    virtual void*
    _getGraphicsBuffer() const = 0;

   protected:
    friend class RenderAPI;
    ID3D11Buffer* m_pBuffer = nullptr;
    D3D11_BUFFER_DESC m_Desc{};
  };
} // namespace geEngineSDK
