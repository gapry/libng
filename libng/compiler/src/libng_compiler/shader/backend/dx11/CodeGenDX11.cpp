#include <libng_compiler/shader/backend/dx11/CodeGenDX11.hpp>

namespace libng {

#if defined(LIBNG_OS_WINDOWS) && defined(LIBNG_RENDER_DX11)

void CodeGenDX11::Execute(StrView outPath,             //
                          ShaderStageMask shaderStage, //
                          StrView srcFilename,         //
                          StrView entryFunc) {         //
  LIBNG_LOG("CodeGen Stage = {}\n", __LIBNG_FUNCTION__);

  TempStringA entryPoint = entryFunc;
  LIBNG_LOG("entry point = {}\n", entryPoint);

  MemMapFile mmapFile;
  mmapFile.open(srcFilename);
  LIBNG_LOG("memMapFileName = {}\n", mmapFile.filename().c_str());

  auto profile = Util::getDxStageProfile(shaderStage);
  LIBNG_LOG("profile = {}\n", profile);

  // https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/d3dcompile-constants
  UINT flags1 = 0; // D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
  UINT flags2 = 0;
#if _DEBUG
  // flags1 |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

  ComPtr<ID3DBlob> byteCode;
  ComPtr<ID3DBlob> errorMsg;

  auto hlsl = mmapFile.span();

  // https://docs.microsoft.com/en-us/windows/win32/api/d3dcompiler/nf-d3dcompiler-d3dcompile
  auto hr = D3DCompile2(hlsl.data(),                 //
                        hlsl.size(),                 //
                        mmapFile.filename().c_str(), //
                        nullptr,                     //
                        nullptr,                     //
                        entryPoint.c_str(),          //
                        profile,                     //
                        flags1,                      //
                        flags2,                      //
                        0,                           //
                        nullptr,                     //
                        0,                           //
                        byteCode.ptrForInit(),       //
                        errorMsg.ptrForInit());      //

  if (FAILED(hr)) {
    throw LIBNG_ERROR("HRESULT = {}\n Error Message: {}", hr, Util::toStrView(errorMsg));
  }

  Directory::create(outPath);
  auto byteCodeSpan = Util::toSpan(byteCode);
  auto outFileName  = Fmt("{}/{}.bin", outPath, profile);
  File::writeFileIfChanged(outFileName, byteCodeSpan, true, true);
  LIBNG_LOG("outputFileName = {}\n", outFileName);

  _Reflect(outFileName, byteCodeSpan, shaderStage, profile);
}

// https://docs.microsoft.com/en-us/windows/win32/api/d3d11shader/nn-d3d11shader-id3d11shaderreflection
// https://docs.microsoft.com/en-us/windows/win32/api/unknwn/nn-unknwn-iunknown
// https://docs.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-iid_ppv_args
// https://docs.microsoft.com/en-us/windows/win32/api/d3dcompiler/nf-d3dcompiler-d3dreflect
// https://docs.microsoft.com/en-us/windows/win32/api/d3d11shader/ns-d3d11shader-d3d11_shader_desc
void CodeGenDX11::_Reflect(StrView outFilename,   //
                           ByteSpan bytecode,     //
                           ShaderStageMask stage, //
                           StrView profile) {     //
  LIBNG_LOG("CodeGen Stage = {}\n", __LIBNG_FUNCTION__);

  ComPtr<ID3D11ShaderReflection> reflect;

  auto hr = D3DReflect(bytecode.data(),                     //
                       bytecode.size(),                     //
                       IID_PPV_ARGS(reflect.ptrForInit())); //
  Util::throwIfError(hr);

  D3D11_SHADER_DESC desc;
  hr = reflect->GetDesc(&desc);
  Util::throwIfError(hr);

  ShaderStageInfo outInfo;
  outInfo.profile = profile;
  outInfo.stage   = stage;

  // clang-format off
  {
    _ReflectInputs       (outInfo, reflect, desc);
    _ReflectConstBuffers (outInfo, reflect, desc);
    _ReflectTextures     (outInfo, reflect, desc);
    _ReflectSamplers     (outInfo, reflect, desc);
  }
  // clang-format on

  {
    auto jsonFilename = Fmt("{}.json", outFilename);
    JsonFile::writeIfChanged(jsonFilename, outInfo, true, true);
  }
}

// https://docs.microsoft.com/en-us/windows/win32/api/d3d11shader/ns-d3d11shader-d3d11_signature_parameter_desc
// https://docs.microsoft.com/en-us/windows/win32/api/d3dcommon/ne-d3dcommon-d3d_register_component_type
void CodeGenDX11::_ReflectInputs(ShaderStageInfo& outInfo,        //
                                 ID3D11ShaderReflection* reflect, //
                                 D3D11_SHADER_DESC& desc) {       //
  LIBNG_LOG("CodeGen Stage = {}\n", __LIBNG_FUNCTION__);

  // HRESULT hr;
  outInfo.inputs.reserve(desc.InputParameters);

  for (UINT i = 0; i < desc.InputParameters; i++) {
    LIBNG_LOG("[Reflect Input] index = {}\n", i);

    D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
    HRESULT hr = reflect->GetInputParameterDesc(i, &paramDesc);
    Util::throwIfError(hr);

    VertexSemanticType semanticType;
    semanticType = Util::parseDxSemanticName(StrView_c_str(paramDesc.SemanticName));

    auto& dst    = outInfo.inputs.emplace_back();
    dst.semantic = VertexSemanticUtil::make(semanticType, //
                                            static_cast<VertexSemanticIndex>(paramDesc.SemanticIndex));

    TempString semantic = enumStr(dst.semantic);
    if (!semantic.size()) {
      throw LIBNG_ERROR("unsupported sematic name {}", paramDesc.SemanticName);
    }

    // clang-format off
    TempString dataType;
    switch (paramDesc.ComponentType) {
      case D3D_REGISTER_COMPONENT_UINT32:  dataType.append("UInt8");   break;
      case D3D_REGISTER_COMPONENT_SINT32:  dataType.append("Int32");   break;
      case D3D_REGISTER_COMPONENT_FLOAT32: dataType.append("Float32"); break;
      default: throw LIBNG_ERROR("unsupported component type {}", paramDesc.ComponentType);
    }
    // clang-format on

    auto componentCount = BitUtil::count1(paramDesc.Mask);
    if (componentCount < 1 || componentCount > 4) {
      throw LIBNG_ERROR("invalid componentCount {}", componentCount);
    }
    if (componentCount > 1) {
      FmtTo(dataType, "x{}", componentCount);
    }

    if (!enumTryParse(dst.dataType, dataType)) {
      throw LIBNG_ERROR("cannot parse dataType enum {}", dataType);
    }
  }
}

void CodeGenDX11::_ReflectConstBuffers(ShaderStageInfo& outInfo,        //
                                       ID3D11ShaderReflection* reflect, //
                                       D3D11_SHADER_DESC& desc) {       //
  LIBNG_LOG("CodeGen Stage = {}\n", __LIBNG_FUNCTION__);
}

void CodeGenDX11::_ReflectTextures(ShaderStageInfo& outInfo,        //
                                   ID3D11ShaderReflection* reflect, //
                                   D3D11_SHADER_DESC& desc) {       //
  LIBNG_LOG("CodeGen Stage = {}\n", __LIBNG_FUNCTION__);
}

void CodeGenDX11::_ReflectSamplers(ShaderStageInfo& outInfo,        //
                                   ID3D11ShaderReflection* reflect, //
                                   D3D11_SHADER_DESC& desc) {       //
  LIBNG_LOG("CodeGen Stage = {}\n", __LIBNG_FUNCTION__);
}
#endif

} // namespace libng