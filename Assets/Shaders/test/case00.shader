Shader "case00" {
	Properties {
    Mat4 MVP
    Color4f color = {1.0f, 1.0f, 1.0f, 1.0f}
	}
	
	Pass {
    // Queue "Transparent"
    Cull None

    BlendRGB   Add One OneMinusSrcAlpha
    BlendAlpha Add One OneMinusSrcAlpha

    DepthTest  Always
    DepthWrite false

    VsFunc     vs_main
    PsFunc     ps_main
	}

  Pass {
    VsFunc vs2_main
    PsFunc ps_main
    GsFunc gs_main
    CsFunc cs_main
  }
}

struct VIn {
  float4 position : POSITION;
  float4 color : COLOR;
};

struct VOut {
  float4 position : SV_POSITION;
  float4 color : COLOR;
};

float a1;
float a2;
float a3;

VOut vs_main(VIn in) {
  VOut output;

  output.position = position;
  output.color    = color;

  return output;
}

float4 ps_main(Vout) : SV_TARGET {
  return color;
}
