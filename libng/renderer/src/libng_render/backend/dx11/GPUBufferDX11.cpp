#include <libng_render/backend/dx11/GPUBufferDX11.hpp>
#include <libng_render/backend/dx11/RendererDX11.hpp>

namespace libng {

GPUBufferDX11::GPUBufferDX11(CreateDesc& desc)
  : Base(desc) {
  if (desc.bufferSize <= 0)
    throw LIBNG_ERROR("buffer size = 0");

  if (desc.stride <= 0)
    throw LIBNG_ERROR("stride == 0");

  D3D11_BUFFER_DESC bd = {};

  bd.ByteWidth           = Util::castUINT(allocator::alignTo(desc.bufferSize, 16));
  bd.StructureByteStride = Util::castUINT(desc.stride);

  // clang-format off
	switch (desc.type) {
		case Type::Vertex: {
			bd.Usage			    = D3D11_USAGE_DYNAMIC;
			bd.BindFlags		  = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;
		} break;
		case Type::Index: {
			bd.Usage			    = D3D11_USAGE_DYNAMIC;
			bd.BindFlags		  = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;
		} break;
		case Type::Const: {
			bd.Usage			    = D3D11_USAGE_DYNAMIC;
			bd.BindFlags		  = D3D11_BIND_CONSTANT_BUFFER;
			bd.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;
		} break;
		default: throw LIBNG_ERROR("unsupport gpu buffer type");
	}
  // clang-format on

  auto* renderer = RendererDX11::current();
  auto* dev      = renderer->d3dDevice();

  auto hr = dev->CreateBuffer(&bd, nullptr, _d3dBuf.ptrForInit());
  Util::throwIfError(hr);
}

void GPUBufferDX11::onUploadToGPU(Span<const u8> data, size_t offset) {
  auto* renderer = RendererDX11::current();
  auto* ctx      = renderer->d3dDeviceContext();

  D3D11_MAPPED_SUBRESOURCE mapped = {};

  auto hr = ctx->Map(_d3dBuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
  Util::throwIfError(hr);

  u8* dst = reinterpret_cast<u8*>(mapped.pData);
  memcpy(dst + offset, data.data(), data.size());

  ctx->Unmap(_d3dBuf, 0);
}

} // namespace libng