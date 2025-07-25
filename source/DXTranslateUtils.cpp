#include "DXTranslateUtils.h"

namespace geEngineSDK {
  namespace TranslateUtils {

    DXGI_FORMAT
    get(GRAPHICS_FORMAT::E inFormat) {
      switch (inFormat) {
      case GRAPHICS_FORMAT::kR32G32B32A32_TYPELESS:
        return DXGI_FORMAT_R32G32B32A32_TYPELESS;
      case GRAPHICS_FORMAT::kR32G32B32A32_FLOAT:
        return DXGI_FORMAT_R32G32B32A32_FLOAT;
      case GRAPHICS_FORMAT::kR32G32B32A32_UINT:
        return DXGI_FORMAT_R32G32B32A32_UINT;
      case GRAPHICS_FORMAT::kR32G32B32A32_SINT:
        return DXGI_FORMAT_R32G32B32A32_SINT;
      case GRAPHICS_FORMAT::kR32G32B32_TYPELESS:
        return DXGI_FORMAT_R32G32B32_TYPELESS;
      case GRAPHICS_FORMAT::kR32G32B32_FLOAT:
        return DXGI_FORMAT_R32G32B32_FLOAT;
      case GRAPHICS_FORMAT::kR32G32B32_UINT:
        return DXGI_FORMAT_R32G32B32_UINT;
      case GRAPHICS_FORMAT::kR32G32B32_SINT:
        return DXGI_FORMAT_R32G32B32_SINT;
      case GRAPHICS_FORMAT::kR16G16B16A16_TYPELESS:
        return DXGI_FORMAT_R16G16B16A16_TYPELESS;
      case GRAPHICS_FORMAT::kR16G16B16A16_FLOAT:
        return DXGI_FORMAT_R16G16B16A16_FLOAT;
      case GRAPHICS_FORMAT::kR16G16B16A16_UNORM:
        return DXGI_FORMAT_R16G16B16A16_UNORM;
      case GRAPHICS_FORMAT::kR16G16B16A16_UINT:
        return DXGI_FORMAT_R16G16B16A16_UINT;
      case GRAPHICS_FORMAT::kR16G16B16A16_SNORM:
        return DXGI_FORMAT_R16G16B16A16_SNORM;
      case GRAPHICS_FORMAT::kR16G16B16A16_SINT:
        return DXGI_FORMAT_R16G16B16A16_SINT;
      case GRAPHICS_FORMAT::kR32G32_TYPELESS:
        return DXGI_FORMAT_R32G32_TYPELESS;
      case GRAPHICS_FORMAT::kR32G32_FLOAT:
        return DXGI_FORMAT_R32G32_FLOAT;
      case GRAPHICS_FORMAT::kR32G32_UINT:
        return DXGI_FORMAT_R32G32_UINT;
      case GRAPHICS_FORMAT::kR32G32_SINT:
        return DXGI_FORMAT_R32G32_SINT;
      case GRAPHICS_FORMAT::kR32G8X24_TYPELESS:
        return DXGI_FORMAT_R32G8X24_TYPELESS;
      case GRAPHICS_FORMAT::kD32_FLOAT_S8X24_UINT:
        return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
      case GRAPHICS_FORMAT::kR32_FLOAT_X8X24_TYPELESS:
        return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
      case GRAPHICS_FORMAT::kX32_TYPELESS_G8X24_UINT:
        return DXGI_FORMAT_X32_TYPELESS_G8X24_UINT;
      case GRAPHICS_FORMAT::kR10G10B10A2_TYPELESS:
        return DXGI_FORMAT_R10G10B10A2_TYPELESS;
      case GRAPHICS_FORMAT::kR10G10B10A2_UNORM:
        return DXGI_FORMAT_R10G10B10A2_UNORM;
      case GRAPHICS_FORMAT::kR10G10B10A2_UINT:
        return DXGI_FORMAT_R10G10B10A2_UINT;
      case GRAPHICS_FORMAT::kR11G11B10_FLOAT:
        return DXGI_FORMAT_R11G11B10_FLOAT;
      case GRAPHICS_FORMAT::kR8G8B8A8_TYPELESS:
        return DXGI_FORMAT_R8G8B8A8_TYPELESS;
      case GRAPHICS_FORMAT::kR8G8B8A8_UNORM:
        return DXGI_FORMAT_R8G8B8A8_UNORM;
      case GRAPHICS_FORMAT::kR8G8B8A8_UNORM_SRGB:
        return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
      case GRAPHICS_FORMAT::kR8G8B8A8_UINT:
        return DXGI_FORMAT_R8G8B8A8_UINT;
      case GRAPHICS_FORMAT::kR8G8B8A8_SNORM:
        return DXGI_FORMAT_R8G8B8A8_SNORM;
      case GRAPHICS_FORMAT::kR8G8B8A8_SINT:
        return DXGI_FORMAT_R8G8B8A8_SINT;
      case GRAPHICS_FORMAT::kR16G16_TYPELESS:
        return DXGI_FORMAT_R16G16_TYPELESS;
      case GRAPHICS_FORMAT::kR16G16_FLOAT:
        return DXGI_FORMAT_R16G16_FLOAT;
      case GRAPHICS_FORMAT::kR16G16_UNORM:
        return DXGI_FORMAT_R16G16_UNORM;
      case GRAPHICS_FORMAT::kR16G16_UINT:
        return DXGI_FORMAT_R16G16_UINT;
      case GRAPHICS_FORMAT::kR16G16_SNORM:
        return DXGI_FORMAT_R16G16_SNORM;
      case GRAPHICS_FORMAT::kR16G16_SINT:
        return DXGI_FORMAT_R16G16_SINT;
      case GRAPHICS_FORMAT::kR32_TYPELESS:
        return DXGI_FORMAT_R32_TYPELESS;
      case GRAPHICS_FORMAT::kD32_FLOAT:
        return DXGI_FORMAT_D32_FLOAT;
      case GRAPHICS_FORMAT::kR32_FLOAT:
        return DXGI_FORMAT_R32_FLOAT;
      case GRAPHICS_FORMAT::kR32_UINT:
        return DXGI_FORMAT_R32_UINT;
      case GRAPHICS_FORMAT::kR32_SINT:
        return DXGI_FORMAT_R32_SINT;
      case GRAPHICS_FORMAT::kR24G8_TYPELESS:
        return DXGI_FORMAT_R24G8_TYPELESS;
      case GRAPHICS_FORMAT::kD24_UNORM_S8_UINT:
        return DXGI_FORMAT_D24_UNORM_S8_UINT;
      case GRAPHICS_FORMAT::kR24_UNORM_X8_TYPELESS:
        return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
      case GRAPHICS_FORMAT::kX24_TYPELESS_G8_UINT:
        return DXGI_FORMAT_X24_TYPELESS_G8_UINT;
      case GRAPHICS_FORMAT::kR8G8_TYPELESS:
        return DXGI_FORMAT_R8G8_TYPELESS;
      case GRAPHICS_FORMAT::kR8G8_UNORM:
        return DXGI_FORMAT_R8G8_UNORM;
      case GRAPHICS_FORMAT::kR8G8_UINT:
        return DXGI_FORMAT_R8G8_UINT;
      case GRAPHICS_FORMAT::kR8G8_SNORM:
        return DXGI_FORMAT_R8G8_SNORM;
      case GRAPHICS_FORMAT::kR8G8_SINT:
        return DXGI_FORMAT_R8G8_SINT;
      case GRAPHICS_FORMAT::kR16_TYPELESS:
        return DXGI_FORMAT_R16_TYPELESS;
      case GRAPHICS_FORMAT::kR16_FLOAT:
        return DXGI_FORMAT_R16_FLOAT;
      case GRAPHICS_FORMAT::kD16_UNORM:
        return DXGI_FORMAT_D16_UNORM;
      case GRAPHICS_FORMAT::kR16_UNORM:
        return DXGI_FORMAT_R16_UNORM;
      case GRAPHICS_FORMAT::kR16_UINT:
        return DXGI_FORMAT_R16_UINT;
      case GRAPHICS_FORMAT::kR16_SNORM:
        return DXGI_FORMAT_R16_SNORM;
      case GRAPHICS_FORMAT::kR16_SINT:
        return DXGI_FORMAT_R16_SINT;
      case GRAPHICS_FORMAT::kR8_TYPELESS:
        return DXGI_FORMAT_R8_TYPELESS;
      case GRAPHICS_FORMAT::kR8_UNORM:
        return DXGI_FORMAT_R8_UNORM;
      case GRAPHICS_FORMAT::kR8_UINT:
        return DXGI_FORMAT_R8_UINT;
      case GRAPHICS_FORMAT::kR8_SNORM:
        return DXGI_FORMAT_R8_SNORM;
      case GRAPHICS_FORMAT::kR8_SINT:
        return DXGI_FORMAT_R8_SINT;
      case GRAPHICS_FORMAT::kA8_UNORM:
        return DXGI_FORMAT_A8_UNORM;
      case GRAPHICS_FORMAT::kR1_UNORM:
        return DXGI_FORMAT_R1_UNORM;
      case GRAPHICS_FORMAT::kR9G9B9E5_SHAREDEXP:
        return DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
      case GRAPHICS_FORMAT::kR8G8_B8G8_UNORM:
        return DXGI_FORMAT_R8G8_B8G8_UNORM;
      case GRAPHICS_FORMAT::kG8R8_G8B8_UNORM:
        return DXGI_FORMAT_G8R8_G8B8_UNORM;
      case GRAPHICS_FORMAT::kBC1_TYPELESS:
        return DXGI_FORMAT_BC1_TYPELESS;
      case GRAPHICS_FORMAT::kBC1_UNORM:
        return DXGI_FORMAT_BC1_UNORM;
      case GRAPHICS_FORMAT::kBC1_UNORM_SRGB:
        return DXGI_FORMAT_BC1_UNORM_SRGB;
      case GRAPHICS_FORMAT::kBC2_TYPELESS:
        return DXGI_FORMAT_BC2_TYPELESS;
      case GRAPHICS_FORMAT::kBC2_UNORM:
        return DXGI_FORMAT_BC2_UNORM;
      case GRAPHICS_FORMAT::kBC2_UNORM_SRGB:
        return DXGI_FORMAT_BC2_UNORM_SRGB;
      case GRAPHICS_FORMAT::kBC3_TYPELESS:
        return DXGI_FORMAT_BC3_TYPELESS;
      case GRAPHICS_FORMAT::kBC3_UNORM:
        return DXGI_FORMAT_BC3_UNORM;
      case GRAPHICS_FORMAT::kBC3_UNORM_SRGB:
        return DXGI_FORMAT_BC3_UNORM_SRGB;
      case GRAPHICS_FORMAT::kBC4_TYPELESS:
        return DXGI_FORMAT_BC4_TYPELESS;
      case GRAPHICS_FORMAT::kBC4_UNORM:
        return DXGI_FORMAT_BC4_UNORM;
      case GRAPHICS_FORMAT::kBC4_SNORM:
        return DXGI_FORMAT_BC4_SNORM;
      case GRAPHICS_FORMAT::kBC5_TYPELESS:
        return DXGI_FORMAT_BC5_TYPELESS;
      case GRAPHICS_FORMAT::kBC5_UNORM:
        return DXGI_FORMAT_BC5_UNORM;
      case GRAPHICS_FORMAT::kBC5_SNORM:
        return DXGI_FORMAT_BC5_SNORM;
      case GRAPHICS_FORMAT::kB5G6R5_UNORM:
        return DXGI_FORMAT_B5G6R5_UNORM;
      case GRAPHICS_FORMAT::kB5G5R5A1_UNORM:
        return DXGI_FORMAT_B5G5R5A1_UNORM;
      case GRAPHICS_FORMAT::kB8G8R8A8_UNORM:
        return DXGI_FORMAT_B8G8R8A8_UNORM;
      case GRAPHICS_FORMAT::kB8G8R8X8_UNORM:
        return DXGI_FORMAT_B8G8R8X8_UNORM;
      case GRAPHICS_FORMAT::kR10G10B10_XR_BIAS_A2_UNORM:
        return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;
      case GRAPHICS_FORMAT::kB8G8R8A8_TYPELESS:
        return DXGI_FORMAT_B8G8R8A8_TYPELESS;
      case GRAPHICS_FORMAT::kB8G8R8A8_UNORM_SRGB:
        return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
      case GRAPHICS_FORMAT::kB8G8R8X8_TYPELESS:
        return DXGI_FORMAT_B8G8R8X8_TYPELESS;
      case GRAPHICS_FORMAT::kB8G8R8X8_UNORM_SRGB:
        return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
      case GRAPHICS_FORMAT::kBC6H_TYPELESS:
        return DXGI_FORMAT_BC6H_TYPELESS;
      case GRAPHICS_FORMAT::kBC6H_UF16:
        return DXGI_FORMAT_BC6H_UF16;
      case GRAPHICS_FORMAT::kBC6H_SF16:
        return DXGI_FORMAT_BC6H_SF16;
      case GRAPHICS_FORMAT::kBC7_TYPELESS:
        return DXGI_FORMAT_BC7_TYPELESS;
      case GRAPHICS_FORMAT::kBC7_UNORM:
        return DXGI_FORMAT_BC7_UNORM;
      case GRAPHICS_FORMAT::kBC7_UNORM_SRGB:
        return DXGI_FORMAT_BC7_UNORM_SRGB;
      case GRAPHICS_FORMAT::kAYUV:
        return DXGI_FORMAT_AYUV;
      case GRAPHICS_FORMAT::kY410:
        return DXGI_FORMAT_Y410;
      case GRAPHICS_FORMAT::kY416:
        return DXGI_FORMAT_Y416;
      case GRAPHICS_FORMAT::kNV12:
        return DXGI_FORMAT_NV12;
      case GRAPHICS_FORMAT::kP010:
        return DXGI_FORMAT_P010;
      case GRAPHICS_FORMAT::kP016:
        return DXGI_FORMAT_P016;
      case GRAPHICS_FORMAT::k420_OPAQUE:
        return DXGI_FORMAT_420_OPAQUE;
      case GRAPHICS_FORMAT::kYUY2:
        return DXGI_FORMAT_YUY2;
      case GRAPHICS_FORMAT::kY210:
        return DXGI_FORMAT_Y210;
      case GRAPHICS_FORMAT::kY216:
        return DXGI_FORMAT_Y216;
      case GRAPHICS_FORMAT::kNV11:
        return DXGI_FORMAT_NV11;
      case GRAPHICS_FORMAT::kAI44:
        return DXGI_FORMAT_AI44;
      case GRAPHICS_FORMAT::kIA44:
        return DXGI_FORMAT_IA44;
      case GRAPHICS_FORMAT::kP8:
        return DXGI_FORMAT_P8;
      case GRAPHICS_FORMAT::kA8P8:
        return DXGI_FORMAT_A8P8;
      case GRAPHICS_FORMAT::kB4G4R4A4_UNORM:
        return DXGI_FORMAT_B4G4R4A4_UNORM;

      case GRAPHICS_FORMAT::kP208:
        return DXGI_FORMAT_P208;
      case GRAPHICS_FORMAT::kV208:
        return DXGI_FORMAT_V208;
      case GRAPHICS_FORMAT::kV408:
        return DXGI_FORMAT_V408;

      case GRAPHICS_FORMAT::kSAMPLER_FEEDBACK_MIN_MIP_OPAQUE:
        return DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE;
      case GRAPHICS_FORMAT::kSAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE:
        return DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE;
      default:
        return DXGI_FORMAT_UNKNOWN;
      }
    }

    String
    toString(const DXGI_FORMAT& format) {
      switch (format) {
      case DXGI_FORMAT_UNKNOWN:
        return "UNKNOWN";
      case DXGI_FORMAT_R32G32B32A32_TYPELESS:
        return "R32G32B32A32_TYPELESS";
      case DXGI_FORMAT_R32G32B32A32_FLOAT:
        return "R32G32B32A32_FLOAT";
      case DXGI_FORMAT_R32G32B32A32_UINT:
        return "R32G32B32A32_UINT";
      case DXGI_FORMAT_R32G32B32A32_SINT:
        return "R32G32B32A32_SINT";
      case DXGI_FORMAT_R32G32B32_TYPELESS:
        return "R32G32B32_TYPELESS";
      case DXGI_FORMAT_R32G32B32_FLOAT:
        return "R32G32B32_FLOAT";
      case DXGI_FORMAT_R32G32B32_UINT:
        return "R32G32B32_UINT";
      case DXGI_FORMAT_R32G32B32_SINT:
        return "R32G32B32_SINT";
      case DXGI_FORMAT_R16G16B16A16_TYPELESS:
        return "R16G16B16A16_TYPELESS";
      case DXGI_FORMAT_R16G16B16A16_FLOAT:
        return "R16G16B16A16_FLOAT";
      case DXGI_FORMAT_R16G16B16A16_UNORM:
        return "R16G16B16A16_UNORM";
      case DXGI_FORMAT_R16G16B16A16_UINT:
        return "R16G16B16A16_UINT";
      case DXGI_FORMAT_R16G16B16A16_SNORM:
        return "R16G16B16A16_SNORM";
      case DXGI_FORMAT_R16G16B16A16_SINT:
        return "R16G16B16A16_SINT";
      case DXGI_FORMAT_R32G32_TYPELESS:
        return "R32G32_TYPELESS";
      case DXGI_FORMAT_R32G32_FLOAT:
        return "R32G32_FLOAT";
      case DXGI_FORMAT_R32G32_UINT:
        return "R32G32_UINT";
      case DXGI_FORMAT_R32G32_SINT:
        return "R32G32_SINT";
      case DXGI_FORMAT_R32G8X24_TYPELESS:
        return "R32G8X24_TYPELESS";
      case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
        return "D32_FLOAT_S8X24_UINT";
      case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
        return "R32_FLOAT_X8X24_TYPELESS";
      case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
        return "X32_TYPELESS_G8X24_UINT";
      case DXGI_FORMAT_Y416:
        return "Y416";
      case DXGI_FORMAT_Y210:
        return "Y210";
      case DXGI_FORMAT_Y216:
        return "Y216";
      case DXGI_FORMAT_R10G10B10A2_TYPELESS:
        return "R10G10B10A2_TYPELESS";
      case DXGI_FORMAT_R10G10B10A2_UNORM:
        return "R10G10B10A2_UNORM";
      case DXGI_FORMAT_R10G10B10A2_UINT:
        return "R10G10B10A2_UINT";
      case DXGI_FORMAT_R11G11B10_FLOAT:
        return "R11G11B10_FLOAT";
      case DXGI_FORMAT_R8G8B8A8_TYPELESS:
        return "R8G8B8A8_TYPELESS";
      case DXGI_FORMAT_R8G8B8A8_UNORM:
        return "R8G8B8A8_UNORM";
      case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
        return "R8G8B8A8_UNORM_SRGB";
      case DXGI_FORMAT_R8G8B8A8_UINT:
        return "R8G8B8A8_UINT";
      case DXGI_FORMAT_R8G8B8A8_SNORM:
        return "R8G8B8A8_SNORM";
      case DXGI_FORMAT_R8G8B8A8_SINT:
        return "R8G8B8A8_SINT";
      case DXGI_FORMAT_R16G16_TYPELESS:
        return "R16G16_TYPELESS";
      case DXGI_FORMAT_R16G16_FLOAT:
        return "R16G16_FLOAT";
      case DXGI_FORMAT_R16G16_UNORM:
        return "R16G16_UNORM";
      case DXGI_FORMAT_R16G16_UINT:
        return "R16G16_UINT";
      case DXGI_FORMAT_R16G16_SNORM:
        return "R16G16_SNORM";
      case DXGI_FORMAT_R16G16_SINT:
        return "R16G16_SINT";
      case DXGI_FORMAT_R32_TYPELESS:
        return "R32_TYPELESS";
      case DXGI_FORMAT_D32_FLOAT:
        return "D32_FLOAT";
      case DXGI_FORMAT_R32_FLOAT:
        return "R32_FLOAT";
      case DXGI_FORMAT_R24G8_TYPELESS:
        return "R24G8_TYPELESS";
      case DXGI_FORMAT_D24_UNORM_S8_UINT:
        return "D24_UNORM_S8_UINT";
      case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
        return "R24_UNORM_X8_TYPELESS";
      case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
        return "X24_TYPELESS_G8_UINT";
      case DXGI_FORMAT_R8G8_TYPELESS:
        return "R8G8_TYPELESS";
      case DXGI_FORMAT_R8G8_UNORM:
        return "R8G8_UNORM";
      case DXGI_FORMAT_R8G8_UINT:
        return "R8G8_UINT";
      case DXGI_FORMAT_R8G8_SNORM:
        return "R8G8_SNORM";
      case DXGI_FORMAT_R8G8_SINT:
        return "R8G8_SINT";
      case DXGI_FORMAT_R16_TYPELESS:
        return "R16_TYPELESS";
      case DXGI_FORMAT_R16_FLOAT:
        return "R16_FLOAT";
      case DXGI_FORMAT_D16_UNORM:
        return "D16_UNORM";
      case DXGI_FORMAT_R16_UNORM:
        return "R16_UNORM";
      case DXGI_FORMAT_R16_UINT:
        return "R16_UINT";
      case DXGI_FORMAT_R16_SNORM:
        return "R16_SNORM";
      case DXGI_FORMAT_R16_SINT:
        return "R16_SINT";
      case DXGI_FORMAT_R8_TYPELESS:
        return "R8_TYPELESS";
      case DXGI_FORMAT_R8_UNORM:
        return "R8_UNORM";
      case DXGI_FORMAT_R8_UINT:
        return "R8_UINT";
      case DXGI_FORMAT_R8_SNORM:
        return "R8_SNORM";
      case DXGI_FORMAT_R8_SINT:
        return "R8_SINT";
      case DXGI_FORMAT_A8_UNORM:
        return "A8_UNORM";
      case DXGI_FORMAT_R1_UNORM:
        return "R1_UNORM";
      case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
        return "R9G9B9E5_SHAREDEXP";
      case DXGI_FORMAT_R8G8_B8G8_UNORM:
        return "R8G8_B8G8_UNORM";
      case DXGI_FORMAT_G8R8_G8B8_UNORM:
        return "G8R8_G8B8_UNORM";
      case DXGI_FORMAT_BC1_TYPELESS:
        return "BC1_TYPELESS";
      case DXGI_FORMAT_BC1_UNORM:
        return "BC1_UNORM";
      case DXGI_FORMAT_BC1_UNORM_SRGB:
        return "BC1_UNORM_SRGB";
      case DXGI_FORMAT_BC2_TYPELESS:
        return "BC2_TYPELESS";
      case DXGI_FORMAT_BC2_UNORM:
        return "BC2_UNORM";
      case DXGI_FORMAT_BC2_UNORM_SRGB:
        return "BC2_UNORM_SRGB";
      case DXGI_FORMAT_BC3_TYPELESS:
        return "BC3_TYPELESS";
      case DXGI_FORMAT_BC3_UNORM:
        return "BC3_UNORM";
      case DXGI_FORMAT_BC3_UNORM_SRGB:
        return "BC3_UNORM_SRGB";
      case DXGI_FORMAT_BC4_TYPELESS:
        return "BC4_TYPELESS";
      case DXGI_FORMAT_BC4_UNORM:
        return "BC4_UNORM";
      case DXGI_FORMAT_BC4_SNORM:
        return "BC4_SNORM";
      case DXGI_FORMAT_BC5_TYPELESS:
        return "BC5_TYPELESS";
      case DXGI_FORMAT_BC5_UNORM:
        return "BC5_UNORM";
      case DXGI_FORMAT_BC5_SNORM:
        return "BC5_SNORM";
      case DXGI_FORMAT_B5G6R5_UNORM:
        return "B5G6R5_UNORM";
      case DXGI_FORMAT_B5G5R5A1_UNORM:
        return "B5G5R5A1_UNORM";
      case DXGI_FORMAT_B8G8R8A8_UNORM:
        return "B8G8R8A8_UNORM";
      case DXGI_FORMAT_B8G8R8X8_UNORM:
        return "B8G8R8X8_UNORM";
      case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
        return "R10G10B10_XR_BIAS_A2_UNORM";
      case DXGI_FORMAT_B8G8R8A8_TYPELESS:
        return "B8G8R8A8_TYPELESS";
      case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
        return "B8G8R8A8_UNORM_SRGB";
      case DXGI_FORMAT_B8G8R8X8_TYPELESS:
        return "B8G8R8X8_TYPELESS";
      case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
        return "B8G8R8X8_UNORM_SRGB";
      case DXGI_FORMAT_BC6H_TYPELESS:
        return "BC6H_TYPELESS";
      case DXGI_FORMAT_BC6H_UF16:
        return "BC6H_UF16";
      case DXGI_FORMAT_BC6H_SF16:
        return "BC6H_SF16";
      case DXGI_FORMAT_BC7_TYPELESS:
        return "BC7_TYPELESS";
      case DXGI_FORMAT_BC7_UNORM:
        return "BC7_UNORM";
      case DXGI_FORMAT_BC7_UNORM_SRGB:
        return "BC7_UNORM_SRGB";
      case DXGI_FORMAT_AYUV:
        return "AYUV";
      case DXGI_FORMAT_Y410:
        return "Y410";
      case DXGI_FORMAT_NV12:
        return "NV12";
      case DXGI_FORMAT_P010:
        return "P010";
      case DXGI_FORMAT_P016:
        return "P016";
      case DXGI_FORMAT_420_OPAQUE:
        return "420_OPAQUE";
      case DXGI_FORMAT_YUY2:
        return "YUY2";
      case DXGI_FORMAT_NV11:
        return "NV11";
      case DXGI_FORMAT_AI44:
        return "AI44";
      case DXGI_FORMAT_IA44:
        return "IA44";
      case DXGI_FORMAT_P8:
        return "P8";
      case DXGI_FORMAT_A8P8:
        return "A8P8";
      case DXGI_FORMAT_B4G4R4A4_UNORM:
        return "B4G4R4A4_UNORM";
      case DXGI_FORMAT_P208:
        return "P208";
      case DXGI_FORMAT_V208:
        return "V208";
      case DXGI_FORMAT_V408:
        return "V408";
      case DXGI_FORMAT_FORCE_UINT:
        return "FORCE_UINT";
      default:break;
      }

      return "Unknown DXGI_FORMAT";
    }

    DXGI_FORMAT
    fromString(const String& strFormat) {
      if (strFormat == "UNKNOWN") return DXGI_FORMAT_UNKNOWN;

      if (strFormat == "R32G32B32A32_TYPELESS") return DXGI_FORMAT_R32G32B32A32_TYPELESS;
      if (strFormat == "R32G32B32A32_FLOAT") return DXGI_FORMAT_R32G32B32A32_FLOAT;
      if (strFormat == "R32G32B32A32_UINT") return DXGI_FORMAT_R32G32B32A32_UINT;
      if (strFormat == "R32G32B32A32_SINT") return DXGI_FORMAT_R32G32B32A32_SINT;

      if (strFormat == "R32G32B32_TYPELESS") return DXGI_FORMAT_R32G32B32_TYPELESS;
      if (strFormat == "R32G32B32_FLOAT") return DXGI_FORMAT_R32G32B32_FLOAT;
      if (strFormat == "R32G32B32_UINT") return DXGI_FORMAT_R32G32B32_UINT;
      if (strFormat == "R32G32B32_SINT") return DXGI_FORMAT_R32G32B32_SINT;

      if (strFormat == "R16G16B16A16_TYPELESS") return DXGI_FORMAT_R16G16B16A16_TYPELESS;
      if (strFormat == "R16G16B16A16_FLOAT") return DXGI_FORMAT_R16G16B16A16_FLOAT;
      if (strFormat == "R16G16B16A16_UNORM") return DXGI_FORMAT_R16G16B16A16_UNORM;
      if (strFormat == "R16G16B16A16_UINT") return DXGI_FORMAT_R16G16B16A16_UINT;
      if (strFormat == "R16G16B16A16_SNORM") return DXGI_FORMAT_R16G16B16A16_SNORM;
      if (strFormat == "R16G16B16A16_SINT") return DXGI_FORMAT_R16G16B16A16_SINT;

      if (strFormat == "R32G32_TYPELESS") return DXGI_FORMAT_R32G32_TYPELESS;
      if (strFormat == "R32G32_FLOAT") return DXGI_FORMAT_R32G32_FLOAT;
      if (strFormat == "R32G32_UINT") return DXGI_FORMAT_R32G32_UINT;
      if (strFormat == "R32G32_SINT") return DXGI_FORMAT_R32G32_SINT;
      
      if (strFormat == "R32G8X24_TYPELESS") return DXGI_FORMAT_R32G8X24_TYPELESS;
      if (strFormat == "D32_FLOAT_S8X24_UINT") return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
      if (strFormat == "R32_FLOAT_X8X24_TYPELESS") return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
      if (strFormat == "X32_TYPELESS_G8X24_UINT") return DXGI_FORMAT_X32_TYPELESS_G8X24_UINT;

      if (strFormat == "Y416") return DXGI_FORMAT_Y416;
      if (strFormat == "Y210") return DXGI_FORMAT_Y210;
      if (strFormat == "Y216") return DXGI_FORMAT_Y216;

      if (strFormat == "R10G10B10A2_TYPELESS") return DXGI_FORMAT_R10G10B10A2_TYPELESS;
      if (strFormat == "R10G10B10A2_UNORM") return DXGI_FORMAT_R10G10B10A2_UNORM;
      if (strFormat == "R10G10B10A2_UINT") return DXGI_FORMAT_R10G10B10A2_UINT;
      if (strFormat == "R11G11B10_FLOAT") return DXGI_FORMAT_R11G11B10_FLOAT;

      if (strFormat == "R8G8B8A8_TYPELESS") return DXGI_FORMAT_R8G8B8A8_TYPELESS;
      if (strFormat == "R8G8B8A8_UNORM") return DXGI_FORMAT_R8G8B8A8_UNORM;
      if (strFormat == "R8G8B8A8_UNORM_SRGB") return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
      if (strFormat == "R8G8B8A8_UINT") return DXGI_FORMAT_R8G8B8A8_UINT;
      if (strFormat == "R8G8B8A8_SNORM") return DXGI_FORMAT_R8G8B8A8_SNORM;
      if (strFormat == "R8G8B8A8_SINT") return DXGI_FORMAT_R8G8B8A8_SINT;

      if (strFormat == "R16G16_TYPELESS") return DXGI_FORMAT_R16G16_TYPELESS;
      if (strFormat == "R16G16_FLOAT") return DXGI_FORMAT_R16G16_FLOAT;
      if (strFormat == "R16G16_UNORM") return DXGI_FORMAT_R16G16_UNORM;
      if (strFormat == "R16G16_UINT") return DXGI_FORMAT_R16G16_UINT;
      if (strFormat == "R16G16_SNORM") return DXGI_FORMAT_R16G16_SNORM;
      if (strFormat == "R16G16_SINT") return DXGI_FORMAT_R16G16_SINT;

      if (strFormat == "R32_TYPELESS") return DXGI_FORMAT_R32_TYPELESS;
      if (strFormat == "D32_FLOAT") return DXGI_FORMAT_D32_FLOAT;
      if (strFormat == "R32_FLOAT") return DXGI_FORMAT_R32_FLOAT;

      if (strFormat == "R24G8_TYPELESS") return DXGI_FORMAT_R24G8_TYPELESS;
      if (strFormat == "D24_UNORM_S8_UINT") return DXGI_FORMAT_D24_UNORM_S8_UINT;
      if (strFormat == "R24_UNORM_X8_TYPELESS") return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
      if (strFormat == "X24_TYPELESS_G8_UINT") return DXGI_FORMAT_X24_TYPELESS_G8_UINT;

      if (strFormat == "R8G8_TYPELESS") return DXGI_FORMAT_R8G8_TYPELESS;
      if (strFormat == "R8G8_UNORM") return DXGI_FORMAT_R8G8_UNORM;
      if (strFormat == "R8G8_UINT") return DXGI_FORMAT_R8G8_UINT;
      if (strFormat == "R8G8_SNORM") return DXGI_FORMAT_R8G8_SNORM;
      if (strFormat == "R8G8_SINT") return DXGI_FORMAT_R8G8_SINT;

      if (strFormat == "R16_TYPELESS") return DXGI_FORMAT_R16_TYPELESS;
      if (strFormat == "R16_FLOAT") return DXGI_FORMAT_R16_FLOAT;
      if (strFormat == "D16_UNORM") return DXGI_FORMAT_D16_UNORM;
      if (strFormat == "R16_UNORM") return DXGI_FORMAT_R16_UNORM;
      if (strFormat == "R16_UINT") return DXGI_FORMAT_R16_UINT;
      if (strFormat == "R16_SNORM") return DXGI_FORMAT_R16_SNORM;
      if (strFormat == "R16_SINT") return DXGI_FORMAT_R16_SINT;

      if (strFormat == "R8_TYPELESS") return DXGI_FORMAT_R8_TYPELESS;
      if (strFormat == "R8_UNORM") return DXGI_FORMAT_R8_UNORM;
      if (strFormat == "R8_UINT") return DXGI_FORMAT_R8_UINT;
      if (strFormat == "R8_SNORM") return DXGI_FORMAT_R8_SNORM;
      if (strFormat == "R8_SINT") return DXGI_FORMAT_R8_SINT;
      if (strFormat == "A8_UNORM") return DXGI_FORMAT_A8_UNORM;
      if (strFormat == "R1_UNORM") return DXGI_FORMAT_R1_UNORM;

      if (strFormat == "R9G9B9E5_SHAREDEXP") return DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
      if (strFormat == "R8G8_B8G8_UNORM") return DXGI_FORMAT_R8G8_B8G8_UNORM;
      if (strFormat == "G8R8_G8B8_UNORM") return DXGI_FORMAT_G8R8_G8B8_UNORM;

      if (strFormat == "BC1_TYPELESS") return DXGI_FORMAT_BC1_TYPELESS;
      if (strFormat == "BC1_UNORM") return DXGI_FORMAT_BC1_UNORM;
      if (strFormat == "BC1_UNORM_SRGB") return DXGI_FORMAT_BC1_UNORM_SRGB;
      if (strFormat == "BC2_TYPELESS") return DXGI_FORMAT_BC2_TYPELESS;
      if (strFormat == "BC2_UNORM") return DXGI_FORMAT_BC2_UNORM;
      if (strFormat == "BC2_UNORM_SRGB") return DXGI_FORMAT_BC2_UNORM_SRGB;
      if (strFormat == "BC3_TYPELESS") return DXGI_FORMAT_BC3_TYPELESS;
      if (strFormat == "BC3_UNORM") return DXGI_FORMAT_BC3_UNORM;
      if (strFormat == "BC3_UNORM_SRGB") return DXGI_FORMAT_BC3_UNORM_SRGB;
      if (strFormat == "BC4_TYPELESS") return DXGI_FORMAT_BC4_TYPELESS;
      if (strFormat == "BC4_UNORM") return DXGI_FORMAT_BC4_UNORM;
      if (strFormat == "BC4_SNORM") return DXGI_FORMAT_BC4_SNORM;
      if (strFormat == "BC5_TYPELESS") return DXGI_FORMAT_BC5_TYPELESS;
      if (strFormat == "BC5_UNORM") return DXGI_FORMAT_BC5_UNORM;
      if (strFormat == "BC5_SNORM") return DXGI_FORMAT_BC5_SNORM;

      if (strFormat == "B5G6R5_UNORM") return DXGI_FORMAT_B5G6R5_UNORM;
      if (strFormat == "B5G5R5A1_UNORM") return DXGI_FORMAT_B5G5R5A1_UNORM;
      if (strFormat == "B8G8R8A8_UNORM") return DXGI_FORMAT_B8G8R8A8_UNORM;
      if (strFormat == "B8G8R8X8_UNORM") return DXGI_FORMAT_B8G8R8X8_UNORM;
      if (strFormat == "R10G10B10_XR_BIAS_A2_UNORM")
        return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;

      if (strFormat == "B8G8R8A8_TYPELESS") return DXGI_FORMAT_B8G8R8A8_TYPELESS;
      if (strFormat == "B8G8R8A8_UNORM_SRGB") return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
      if (strFormat == "B8G8R8X8_TYPELESS") return DXGI_FORMAT_B8G8R8X8_TYPELESS;
      if (strFormat == "B8G8R8X8_UNORM_SRGB") return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;

      if (strFormat == "BC6H_TYPELESS") return DXGI_FORMAT_BC6H_TYPELESS;
      if (strFormat == "BC6H_UF16") return DXGI_FORMAT_BC6H_UF16;
      if (strFormat == "BC6H_SF16") return DXGI_FORMAT_BC6H_SF16;

      if (strFormat == "BC7_TYPELESS") return DXGI_FORMAT_BC7_TYPELESS;
      if (strFormat == "BC7_UNORM") return DXGI_FORMAT_BC7_UNORM;
      if (strFormat == "BC7_UNORM_SRGB") return DXGI_FORMAT_BC7_UNORM_SRGB;

      if (strFormat == "AYUV") return DXGI_FORMAT_AYUV;
      if (strFormat == "Y410") return DXGI_FORMAT_Y410;
      if (strFormat == "NV12") return DXGI_FORMAT_NV12;
      if (strFormat == "P010") return DXGI_FORMAT_P010;
      if (strFormat == "P016") return DXGI_FORMAT_P016;
      if (strFormat == "420_OPAQUE") return DXGI_FORMAT_420_OPAQUE;
      if (strFormat == "YUY2") return DXGI_FORMAT_YUY2;
      if (strFormat == "NV11") return DXGI_FORMAT_NV11;
      if (strFormat == "AI44") return DXGI_FORMAT_AI44;
      if (strFormat == "IA44") return DXGI_FORMAT_IA44;
      if (strFormat == "P8") return DXGI_FORMAT_P8;
      if (strFormat == "A8P8") return DXGI_FORMAT_A8P8;
      if (strFormat == "B4G4R4A4_UNORM") return DXGI_FORMAT_B4G4R4A4_UNORM;
      if (strFormat == "P208") return DXGI_FORMAT_P208;
      if (strFormat == "V208") return DXGI_FORMAT_V208;
      if (strFormat == "V408") return DXGI_FORMAT_V408;
      if (strFormat == "FORCE_UINT") return DXGI_FORMAT_FORCE_UINT;

      return DXGI_FORMAT_UNKNOWN;
    }

    TEXTURE2D_DESC
    get(const D3D11_TEXTURE2D_DESC& desc) {
      TEXTURE2D_DESC tDesc;
      memcpy(&tDesc, &desc, sizeof(TEXTURE2D_DESC));
      return tDesc;
    }

    SIZE_T
    getBitsPerPixel(const DXGI_FORMAT& format) {
      switch (format) {
      case DXGI_FORMAT_R32G32B32A32_TYPELESS:
      case DXGI_FORMAT_R32G32B32A32_FLOAT:
      case DXGI_FORMAT_R32G32B32A32_UINT:
      case DXGI_FORMAT_R32G32B32A32_SINT:
        return 128;

      case DXGI_FORMAT_R32G32B32_TYPELESS:
      case DXGI_FORMAT_R32G32B32_FLOAT:
      case DXGI_FORMAT_R32G32B32_UINT:
      case DXGI_FORMAT_R32G32B32_SINT:
        return 96;

      case DXGI_FORMAT_R16G16B16A16_TYPELESS:
      case DXGI_FORMAT_R16G16B16A16_FLOAT:
      case DXGI_FORMAT_R16G16B16A16_UNORM:
      case DXGI_FORMAT_R16G16B16A16_UINT:
      case DXGI_FORMAT_R16G16B16A16_SNORM:
      case DXGI_FORMAT_R16G16B16A16_SINT:
      case DXGI_FORMAT_R32G32_TYPELESS:
      case DXGI_FORMAT_R32G32_FLOAT:
      case DXGI_FORMAT_R32G32_UINT:
      case DXGI_FORMAT_R32G32_SINT:
      case DXGI_FORMAT_R32G8X24_TYPELESS:
      case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
      case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
      case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
      case DXGI_FORMAT_Y416:
      case DXGI_FORMAT_Y210:
      case DXGI_FORMAT_Y216:
        return 64;

      case DXGI_FORMAT_R10G10B10A2_TYPELESS:
      case DXGI_FORMAT_R10G10B10A2_UNORM:
      case DXGI_FORMAT_R10G10B10A2_UINT:
      case DXGI_FORMAT_R11G11B10_FLOAT:
      case DXGI_FORMAT_R8G8B8A8_TYPELESS:
      case DXGI_FORMAT_R8G8B8A8_UNORM:
      case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
      case DXGI_FORMAT_R8G8B8A8_UINT:
      case DXGI_FORMAT_R8G8B8A8_SNORM:
      case DXGI_FORMAT_R8G8B8A8_SINT:
      case DXGI_FORMAT_R16G16_TYPELESS:
      case DXGI_FORMAT_R16G16_FLOAT:
      case DXGI_FORMAT_R16G16_UNORM:
      case DXGI_FORMAT_R16G16_UINT:
      case DXGI_FORMAT_R16G16_SNORM:
      case DXGI_FORMAT_R16G16_SINT:
      case DXGI_FORMAT_R32_TYPELESS:
      case DXGI_FORMAT_D32_FLOAT:
      case DXGI_FORMAT_R32_FLOAT:
      case DXGI_FORMAT_R32_UINT:
      case DXGI_FORMAT_R32_SINT:
      case DXGI_FORMAT_R24G8_TYPELESS:
      case DXGI_FORMAT_D24_UNORM_S8_UINT:
      case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
      case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
      case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
      case DXGI_FORMAT_R8G8_B8G8_UNORM:
      case DXGI_FORMAT_G8R8_G8B8_UNORM:
      case DXGI_FORMAT_B8G8R8A8_UNORM:
      case DXGI_FORMAT_B8G8R8X8_UNORM:
      case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
      case DXGI_FORMAT_B8G8R8A8_TYPELESS:
      case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
      case DXGI_FORMAT_B8G8R8X8_TYPELESS:
      case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
      case DXGI_FORMAT_AYUV:
      case DXGI_FORMAT_Y410:
      case DXGI_FORMAT_YUY2:
      case DXGI_FORMAT_NV12:
      case DXGI_FORMAT_P010:
      case DXGI_FORMAT_P016:
      case DXGI_FORMAT_420_OPAQUE:
      case DXGI_FORMAT_NV11:
      case DXGI_FORMAT_FORCE_UINT:
      case DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE:
      case DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE:
        return 32;

      case DXGI_FORMAT_R8G8_TYPELESS:
      case DXGI_FORMAT_R8G8_UNORM:
      case DXGI_FORMAT_R8G8_UINT:
      case DXGI_FORMAT_R8G8_SNORM:
      case DXGI_FORMAT_R8G8_SINT:
      case DXGI_FORMAT_R16_TYPELESS:
      case DXGI_FORMAT_R16_FLOAT:
      case DXGI_FORMAT_D16_UNORM:
      case DXGI_FORMAT_R16_UNORM:
      case DXGI_FORMAT_R16_UINT:
      case DXGI_FORMAT_R16_SNORM:
      case DXGI_FORMAT_R16_SINT:
      case DXGI_FORMAT_B5G6R5_UNORM:
      case DXGI_FORMAT_B5G5R5A1_UNORM:
      case DXGI_FORMAT_A8P8:
      case DXGI_FORMAT_B4G4R4A4_UNORM:
      case DXGI_FORMAT_A4B4G4R4_UNORM:
      case DXGI_FORMAT_P208:
      case DXGI_FORMAT_V208:
      case DXGI_FORMAT_V408:
        return 16;

      case DXGI_FORMAT_R8_TYPELESS:
      case DXGI_FORMAT_R8_UNORM:
      case DXGI_FORMAT_R8_UINT:
      case DXGI_FORMAT_R8_SNORM:
      case DXGI_FORMAT_R8_SINT:
      case DXGI_FORMAT_A8_UNORM:
      case DXGI_FORMAT_AI44:
      case DXGI_FORMAT_IA44:
      case DXGI_FORMAT_P8:
        return 8;

      case DXGI_FORMAT_R1_UNORM:
        return 1;

      case DXGI_FORMAT_BC1_TYPELESS:
      case DXGI_FORMAT_BC1_UNORM:
      case DXGI_FORMAT_BC1_UNORM_SRGB:
      case DXGI_FORMAT_BC4_TYPELESS:
      case DXGI_FORMAT_BC4_UNORM:
      case DXGI_FORMAT_BC4_SNORM:
        return 4;

      case DXGI_FORMAT_BC2_TYPELESS:
      case DXGI_FORMAT_BC2_UNORM:
      case DXGI_FORMAT_BC2_UNORM_SRGB:
      case DXGI_FORMAT_BC3_TYPELESS:
      case DXGI_FORMAT_BC3_UNORM:
      case DXGI_FORMAT_BC3_UNORM_SRGB:
      case DXGI_FORMAT_BC5_TYPELESS:
      case DXGI_FORMAT_BC5_UNORM:
      case DXGI_FORMAT_BC5_SNORM:
      case DXGI_FORMAT_BC6H_TYPELESS:
      case DXGI_FORMAT_BC6H_UF16:
      case DXGI_FORMAT_BC6H_SF16:
      case DXGI_FORMAT_BC7_TYPELESS:
      case DXGI_FORMAT_BC7_UNORM:
      case DXGI_FORMAT_BC7_UNORM_SRGB:
        return 8;

      case DXGI_FORMAT_UNKNOWN:
        return 0;
      }

      return 0;
    }

    DXGI_FORMAT
    get(VERTEX_ELEMENT_TYPE::E type) {
      switch (type)
      {
      case VERTEX_ELEMENT_TYPE::COLOR:
      case VERTEX_ELEMENT_TYPE::COLOR_ABGR:
      case VERTEX_ELEMENT_TYPE::COLOR_ARGB:
      case VERTEX_ELEMENT_TYPE::UBYTE4_NORM:
        return DXGI_FORMAT_R8G8B8A8_UNORM;
      case VERTEX_ELEMENT_TYPE::FLOAT1:
        return DXGI_FORMAT_R32_FLOAT;
      case VERTEX_ELEMENT_TYPE::FLOAT2:
        return DXGI_FORMAT_R32G32_FLOAT;
      case VERTEX_ELEMENT_TYPE::FLOAT3:
        return DXGI_FORMAT_R32G32B32_FLOAT;
      case VERTEX_ELEMENT_TYPE::FLOAT4:
        return DXGI_FORMAT_R32G32B32A32_FLOAT;
      case VERTEX_ELEMENT_TYPE::USHORT1:
        return DXGI_FORMAT_R16_UINT;
      case VERTEX_ELEMENT_TYPE::USHORT2:
        return DXGI_FORMAT_R16G16_UINT;
      case VERTEX_ELEMENT_TYPE::USHORT4:
        return DXGI_FORMAT_R16G16B16A16_UINT;
      case VERTEX_ELEMENT_TYPE::SHORT1:
        return DXGI_FORMAT_R16_SINT;
      case VERTEX_ELEMENT_TYPE::SHORT2:
        return DXGI_FORMAT_R16G16_SINT;
      case VERTEX_ELEMENT_TYPE::SHORT4:
        return DXGI_FORMAT_R16G16B16A16_SINT;
      case VERTEX_ELEMENT_TYPE::UINT1:
        return DXGI_FORMAT_R32_UINT;
      case VERTEX_ELEMENT_TYPE::UINT2:
        return DXGI_FORMAT_R32G32_UINT;
      case VERTEX_ELEMENT_TYPE::UINT3:
        return DXGI_FORMAT_R32G32B32_UINT;
      case VERTEX_ELEMENT_TYPE::UINT4:
        return DXGI_FORMAT_R32G32B32A32_UINT;
      case VERTEX_ELEMENT_TYPE::INT1:
        return DXGI_FORMAT_R32_SINT;
      case VERTEX_ELEMENT_TYPE::INT2:
        return DXGI_FORMAT_R32G32_SINT;
      case VERTEX_ELEMENT_TYPE::INT3:
        return DXGI_FORMAT_R32G32B32_SINT;
      case VERTEX_ELEMENT_TYPE::INT4:
        return DXGI_FORMAT_R32G32B32A32_SINT;
      case VERTEX_ELEMENT_TYPE::UBYTE4:
        return DXGI_FORMAT_R8G8B8A8_UINT;
      default:
        break;
      }

      // Unsupported type
      return DXGI_FORMAT_R32G32B32A32_FLOAT;
    }

    VERTEX_ELEMENT_SEMANTIC::E
    get(const char* sem) {
      if (strcmp(sem, "BLENDINDICES") == 0)
        return VERTEX_ELEMENT_SEMANTIC::BLENDINDICES;
      if (strcmp(sem, "BLENDWEIGHT") == 0)
        return VERTEX_ELEMENT_SEMANTIC::BLENDWEIGHT;
      if (strcmp(sem, "COLOR") == 0)
        return VERTEX_ELEMENT_SEMANTIC::COLOR;
      if (strcmp(sem, "NORMAL") == 0)
        return VERTEX_ELEMENT_SEMANTIC::NORMAL;
      if (strcmp(sem, "POSITION") == 0)
        return VERTEX_ELEMENT_SEMANTIC::POSITION;
      if (strcmp(sem, "TEXCOORD") == 0)
        return VERTEX_ELEMENT_SEMANTIC::TEXCOORD;
      if (strcmp(sem, "BINORMAL") == 0)
        return VERTEX_ELEMENT_SEMANTIC::BITANGENT;
      if (strcmp(sem, "TANGENT") == 0)
        return VERTEX_ELEMENT_SEMANTIC::TANGENT;
      if (strcmp(sem, "POSITIONT") == 0)
        return VERTEX_ELEMENT_SEMANTIC::POSITIONT;
      if (strcmp(sem, "PSIZE") == 0)
        return VERTEX_ELEMENT_SEMANTIC::PSIZE;

      // Unsupported type
      return VERTEX_ELEMENT_SEMANTIC::POSITION;
    }

    const char*
    toString(VERTEX_ELEMENT_SEMANTIC::E sem) {
      switch (sem)
      {
      case VERTEX_ELEMENT_SEMANTIC::BLENDINDICES:
        return "BLENDINDICES";
      case VERTEX_ELEMENT_SEMANTIC::BLENDWEIGHT:
        return "BLENDWEIGHT";
      case VERTEX_ELEMENT_SEMANTIC::COLOR:
        return "COLOR";
      case VERTEX_ELEMENT_SEMANTIC::NORMAL:
        return "NORMAL";
      case VERTEX_ELEMENT_SEMANTIC::POSITION:
        return "POSITION";
      case VERTEX_ELEMENT_SEMANTIC::TEXCOORD:
        return "TEXCOORD";
      case VERTEX_ELEMENT_SEMANTIC::BITANGENT:
        return "BINORMAL";
      case VERTEX_ELEMENT_SEMANTIC::TANGENT:
        return "TANGENT";
      case VERTEX_ELEMENT_SEMANTIC::POSITIONT:
        return "POSITIONT";
      case VERTEX_ELEMENT_SEMANTIC::PSIZE:
        return "PSIZE";
      case VERTEX_ELEMENT_SEMANTIC::CUSTOM:
        return "CUSTOM";
      }

      //Unsupported type
      return "";
    }

    VERTEX_ELEMENT_TYPE::E
    getInputType(D3D_REGISTER_COMPONENT_TYPE type, uint8 mask) {
      VERTEX_ELEMENT_TYPE::E ret = VERTEX_ELEMENT_TYPE::UNKNOWN;

      if (mask == 1) {
        if (type == D3D_REGISTER_COMPONENT_UINT32) {
          ret = VERTEX_ELEMENT_TYPE::UINT1;
        }
        else if (type == D3D_REGISTER_COMPONENT_SINT32) {
          ret = VERTEX_ELEMENT_TYPE::INT1;
        }
        else if (type == D3D_REGISTER_COMPONENT_FLOAT32) {
          ret = VERTEX_ELEMENT_TYPE::FLOAT1;
        }
      }
      else if (mask <= 3) {
        if (type == D3D_REGISTER_COMPONENT_UINT32) {
          ret = VERTEX_ELEMENT_TYPE::UINT2;
        }
        else if (type == D3D_REGISTER_COMPONENT_SINT32) {
          ret = VERTEX_ELEMENT_TYPE::INT2;
        }
        else if (type == D3D_REGISTER_COMPONENT_FLOAT32) {
          ret = VERTEX_ELEMENT_TYPE::FLOAT2;
        }
      }
      else if (mask <= 7) {
        if (type == D3D_REGISTER_COMPONENT_UINT32) {
          ret = VERTEX_ELEMENT_TYPE::UINT3;
        }
        else if (type == D3D_REGISTER_COMPONENT_SINT32) {
          ret = VERTEX_ELEMENT_TYPE::INT3;
        }
        else if (type == D3D_REGISTER_COMPONENT_FLOAT32) {
          ret = VERTEX_ELEMENT_TYPE::FLOAT3;
        }
      }
      else if (mask <= 15) {
        if (type == D3D_REGISTER_COMPONENT_UINT32) {
          ret = VERTEX_ELEMENT_TYPE::UINT4;
        }
        else if (type == D3D_REGISTER_COMPONENT_SINT32) {
          ret = VERTEX_ELEMENT_TYPE::INT4;
        }
        else if (type == D3D_REGISTER_COMPONENT_FLOAT32) {
          ret = VERTEX_ELEMENT_TYPE::FLOAT4;
        }
      }

      return ret;
    }

  } // namespace TranslateUtils

}
