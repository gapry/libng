Shader {
  Properties {
    Float s   = 0.5
    Vec4f v   = {1.2, 2.3, 3.4, 4.5}
    Color4f c = {1.0, 1.0, 1.0, 1.0}
  }
  
  Pass {
    VsFunc vs_main
    PsFunc ps_main
  }
}

struct VertexIn {
  float4 position : POSITION;
  float4 color : COLOR;
};

struct PixelIn {
  float4 position : SV_POSITION;
  float4 color : COLOR;
};

PixelIn vs_main(VertexIn vertexIn) {
}

float4 ps_main(PixelIn pixelIn) : SV_TARGET {
}