#pragma once

namespace libng {

#define DDS_FOURCC      0x00000004 // DDPF_FOURCC
#define DDS_RGB         0x00000040 // DDPF_RGB
#define DDS_RGBA        0x00000041 // DDPF_RGB | DDPF_ALPHAPIXELS
#define DDS_LUMINANCE   0x00020000 // DDPF_LUMINANCE
#define DDS_LUMINANCEA  0x00020001 // DDPF_LUMINANCE | DDPF_ALPHAPIXELS
#define DDS_ALPHAPIXELS 0x00000001 // DDPF_ALPHAPIXELS
#define DDS_ALPHA       0x00000002 // DDPF_ALPHA
#define DDS_PAL8        0x00000020 // DDPF_PALETTEINDEXED8
#define DDS_PAL8A       0x00000021 // DDPF_PALETTEINDEXED8 | DDPF_ALPHAPIXELS
#define DDS_BUMPDUDV    0x00080000 // DDPF_BUMPDUDV

} // namespace libng
