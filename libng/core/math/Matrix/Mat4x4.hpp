#pragma once

#include <cassert>

#include <math/Vector/Vec3.hpp>
#include <math/Vector/Vec4.hpp>

namespace libng {

template<typename T>
class Mat4x4 {
  static constexpr int kCol = 4;
  static constexpr int kRow = 4;
  static constexpr int kElm = kCol * kRow;

public:
  union {
    struct {
      Vec4<T> cx, cy, cz, cw;
    };
    Vec4<T> col[kCol];
    T data[kElm];
  };

  ~Mat4x4() = default;

  Mat4x4() = default;

  Mat4x4(const Vec4<T>& cx_, const Vec4<T>& cy_, const Vec4<T>& cz_, const Vec4<T>& cw_) {
    cx = cx_;
    cy = cy_;
    cz = cz_;
    cw = cw_;
  }

  // clang-format off
  Mat4x4(T xx, T xy, T xz, T xw,
         T yx, T yy, T yz, T yw,
         T zx, T zy, T zz, T zw,
         T wx, T wy, T wz, T ww) {
    cx.set(xx, xy, xz, xw);
    cy.set(yx, yy, yz, yw);
    cz.set(zx, zy, zz, zw);
    cw.set(wx, wy, wz, ww);
  }
  // clang-format on

  // clang-format off
  void set(T xx, T xy, T xz, T xw,
           T yx, T yy, T yz, T yw,
           T zx, T zy, T zz, T zw,
           T wx, T wy, T wz, T ww) {
    cx.set(xx, xy, xz, xw);
    cy.set(yx, yy, yz, yw);
    cz.set(zx, zy, zz, zw);
    cw.set(wx, wy, wz, ww);
  }
  // clang-format on

  static Mat4x4 kIdentity() {
    // clang-format off
  	return Mat4x4(1, 0, 0, 0, 
  	              0, 1, 0, 0, 
  	              0, 0, 1, 0, 
  	              0, 0, 0, 1);
    // clang-format on
  }

  void setIdentity() {
    *this = kIdentity();
  }

  void translate(T x, T y, T z) {
    Mat4x4 m;
    m.setTranslate(x, y, z);
    operator*=(m);
  }

  void setTranslate(T x, T y, T z) {
    // clang-format off
    set(1, 0, 0, 0, 
        0, 1, 0, 0, 
        0, 0, 1, 0, 
        x, y, z, 1);
    // clang-format on
  }

  void setTranslate(const Vec3<T>& v) {
    setTranslate(v.x, v.y, v.z);
  }

  void setRotateX(T rad) {
    T s, c;
    getSinAndCos(rad, s, c);
    // clang-format off
  	cx.set(1,  0, 0, 0);
  	cy.set(0,  c, s, 0);
  	cz.set(0, -s, c, 0);
  	cw.set(0,  0, 0, 1);
    // clang-format on
  }

  void setRotateY(T rad) {
    T s, c;
    getSinAndCos(rad, s, c);
    // clang-format off
  	cx.set(c, 0, -s, 0);
  	cy.set(0, 1,  0, 0);
  	cz.set(s, 0,  c, 0);
  	cw.set(0, 0,  0, 1);
    // clang-format on
  }

  void setRotateZ(T rad) {
    T s, c;
    getSinAndCos(rad, s, c);
    // clang-format off
  	cx.set( c, s, 0, 0);
  	cy.set(-s, c, 0, 0);
  	cz.set(0,  0, 1, 0);
  	cw.set(0,  0, 0, 1);
    // clang-format on
  }

  void setScale(const Vec3<T>& v) {
    // clang-format off
  	cx.set(v.x, 0,   0,   0);
  	cy.set(0,   v.y, 0,   0);
  	cz.set(0,   0,   v.z, 0);
  	cw.set(0,   0,   0,   1);
    // clang-format on
  }

  void rotateX(T rad) {
    Mat4x4 m;
    m.setRotateX(rad);
    operator*=(m);
  }

  void rotateY(T rad) {
    Mat4x4 m;
    m.setRotateY(rad);
    operator*=(m);
  }

  void rotateZ(T rad) {
    Mat4x4 m;
    m.setRotateZ(rad);
    operator*=(m);
  }

  void setTRS(const Vec3<T>& translate, const Vec3<T>& rotate, const Vec3<T>& scale) {
    Vec3<T> s, c;
    getSinAndCos(rotate.x, s.x, c.x);
    getSinAndCos(rotate.y, s.y, c.y);
    getSinAndCos(rotate.z, s.z, c.z);

    // clang-format off
    set(scale.x * (c.y * c.z),				           scale.x * (c.y * s.z),                   scale.x * (-s.y),      0,
    	  scale.y * (s.x * s.y * c.z - c.x * s.z), scale.y * (c.x * c.z + s.x * s.y * s.z), scale.y * (s.x * c.y), 0,
    	  scale.z * (s.x * s.z + c.x * s.y * c.z), scale.z * (c.x * s.y * s.z - s.x * c.z), scale.z * (c.x * c.y), 0,
    	  translate.x,                             translate.y,                             translate.z,           1);
    // clang-format on
  }

  void setPerspective(T fovy_rad, T aspect, T zNear, T zFar) {
    T s, c, deltaZ;
    T fov = fovy_rad / 2;

    deltaZ = zFar - zNear;
    s      = sin(fov);

    if ((deltaZ == 0) || (s == 0) || (aspect == 0)) {
      setIdentity();
      return;
    }
    c = cos(fov) / s;

    // clang-format off
		cx.set(c / aspect, 0, 0,                          0);
		cy.set(0,          c, 0,                          0);
		cz.set(0,          0, -(zFar + zNear) / deltaZ,  -1);
		cw.set(0,          0, -2 * zNear * zFar / deltaZ, 0);
    // clang-format on
  }

  void setOrtho(T left, T right, T bottom, T top, T zNear, T zFar) {
    T w = right - left;
    T h = top - bottom;
    T d = zFar - zNear;

    if (w == 0 || h == 0 || d == 0) {
      setIdentity();
    } else {
      // clang-format off
  	  set(2 / w,               0,                 0,                   0,
		      0,                   2 / h,             0,                   0,
		      0,                   0,                 -2 / d,              0,
		      -(right + left) / w, -(top+bottom) / h, -(zFar + zNear) / d, 1);
      // clang-format on
    }
  }

  void setLookAt(const Vec3<T>& eye, const Vec3<T>& aim, const Vec3<T>& up) {
    Vec3<T> f = (aim - eye).normalize();
    Vec3<T> s = f.cross(up).normalize();
    Vec3<T> u = s.cross(f);

    Mat4x4 m;
    // clang-format off
  	m.set(s.x, u.x, -f.x, 0.0, 
  	      s.y, u.y, -f.y, 0.0, 
  	      s.z, u.z, -f.z, 0.0, 
  	      0,   0,   0,    1);
    // clang-format on

    Mat4x4 t;
    t.setTranslate(-eye);

    *this = m * t;
  }

  void operator*=(const Mat4x4& r) {
    *this = *this * r;
  }

  Mat4x4 operator*(const Mat4x4& r) const {
    Mat4x4 o;

    T e0, e1, e2, e3;
    e0 = cx.x, e1 = cy.x, e2 = cz.x, e3 = cw.x;
    o.cx.x = e0 * r.cx.x + e1 * r.cx.y + e2 * r.cx.z + e3 * r.cx.w;
    o.cy.x = e0 * r.cy.x + e1 * r.cy.y + e2 * r.cy.z + e3 * r.cy.w;
    o.cz.x = e0 * r.cz.x + e1 * r.cz.y + e2 * r.cz.z + e3 * r.cz.w;
    o.cw.x = e0 * r.cw.x + e1 * r.cw.y + e2 * r.cw.z + e3 * r.cw.w;

    e0 = cx.y, e1 = cy.y, e2 = cz.y, e3 = cw.y;
    o.cx.y = e0 * r.cx.x + e1 * r.cx.y + e2 * r.cx.z + e3 * r.cx.w;
    o.cy.y = e0 * r.cy.x + e1 * r.cy.y + e2 * r.cy.z + e3 * r.cy.w;
    o.cz.y = e0 * r.cz.x + e1 * r.cz.y + e2 * r.cz.z + e3 * r.cz.w;
    o.cw.y = e0 * r.cw.x + e1 * r.cw.y + e2 * r.cw.z + e3 * r.cw.w;

    e0 = cx.z, e1 = cy.z, e2 = cz.z, e3 = cw.z;
    o.cx.z = e0 * r.cx.x + e1 * r.cx.y + e2 * r.cx.z + e3 * r.cx.w;
    o.cy.z = e0 * r.cy.x + e1 * r.cy.y + e2 * r.cy.z + e3 * r.cy.w;
    o.cz.z = e0 * r.cz.x + e1 * r.cz.y + e2 * r.cz.z + e3 * r.cz.w;
    o.cw.z = e0 * r.cw.x + e1 * r.cw.y + e2 * r.cw.z + e3 * r.cw.w;

    e0 = cx.w, e1 = cy.w, e2 = cz.w, e3 = cw.w;
    o.cx.w = e0 * r.cx.x + e1 * r.cx.y + e2 * r.cx.z + e3 * r.cx.w;
    o.cy.w = e0 * r.cy.x + e1 * r.cy.y + e2 * r.cy.z + e3 * r.cy.w;
    o.cz.w = e0 * r.cz.x + e1 * r.cz.y + e2 * r.cz.z + e3 * r.cz.w;
    o.cw.w = e0 * r.cw.x + e1 * r.cw.y + e2 * r.cw.z + e3 * r.cw.w;

    return o;
  }

  // clang-format off
  Mat4x4 inverse() const {
	  T wtmp[4][8];
	  T m0, m1, m2, m3, s;
	  T *r0, *r1, *r2, *r3;

	  r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];

	  r0[0] = cx.x;
	  r0[1] = cx.y;
	  r0[2] = cx.z;
	  r0[3] = cx.w;
	  r0[4] = 1.0;
	  r0[5] = r0[6] = r0[7] = 0.0;

	  r1[0] = cy.x;
	  r1[1] = cy.y;
	  r1[2] = cy.z;
	  r1[3] = cy.w;
	  r1[5] = 1.0;
	  r1[4] = r1[6] = r1[7] = 0.0;

	  r2[0] = cz.x;
	  r2[1] = cz.y;
	  r2[2] = cz.z;
	  r2[3] = cz.w;
	  r2[6] = 1.0;
	  r2[4] = r2[5] = r2[7] = 0.0;

	  r3[0] = cw.x;
	  r3[1] = cw.y;
	  r3[2] = cw.z;
	  r3[3] = cw.w;
	  r3[7] = 1.0;
	  r3[4] = r3[5] = r3[6] = 0.0;

	  // Pivot
	  if (std::abs(r3[0]) > std::abs(r2[0])) std::swap(r3, r2);
	  if (std::abs(r2[0]) > std::abs(r1[0])) std::swap(r2, r1);
	  if (std::abs(r1[0]) > std::abs(r0[0])) std::swap(r1, r0);
	  if (0.0 == r0[0]) return kIdentity();

	  // Elimination
	  m1 = r1[0] / r0[0];
	  m2 = r2[0] / r0[0];
	  m3 = r3[0] / r0[0];

	  s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
	  s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
	  s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
	  s = r0[4]; if (s != 0.0) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
	  s = r0[5]; if (s != 0.0) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
	  s = r0[6]; if (s != 0.0) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
	  s = r0[7]; if (s != 0.0) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }

	  // Pivot
	  if (std::abs(r3[1]) > std::abs(r2[1])) std::swap(r3, r2);
	  if (std::abs(r2[1]) > std::abs(r1[1])) std::swap(r2, r1);
	  if (0.0 == r1[1]) {
	  	assert(false); // [Issue]
	  	return kIdentity();
	  }

	  // Elimination 
	  m2 = r2[1] / r1[1];
	  m3 = r3[1] / r1[1];

	  r2[2] -= m2 * r1[2];
	  r3[2] -= m3 * r1[2];
	  r2[3] -= m2 * r1[3];
	  r3[3] -= m3 * r1[3];

	  s = r1[4]; if (0.0 != s) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
	  s = r1[5]; if (0.0 != s) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
	  s = r1[6]; if (0.0 != s) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
	  s = r1[7]; if (0.0 != s) { r2[7] -= m2 * s; r3[7] -= m3 * s; }

	  // Pivot
	  if (std::abs(r3[2]) > std::abs(r2[2])) std::swap(r3, r2);
	  if (0.0 == r2[2]) return kIdentity();

	  // Elimination
	  m3 = r3[2] / r2[2];

    r3[3] -= m3 * r2[3];
    r3[4] -= m3 * r2[4];
    r3[5] -= m3 * r2[5];
    r3[6] -= m3 * r2[6];
    r3[7] -= m3 * r2[7];

    //
	  if (0.0 == r3[3]) {
	  	return kIdentity();
	  }

    // Substitute(Row[3])
	  s = 1.0f / r3[3]; 
	  r3[4] *= s; 
    r3[5] *= s; 
    r3[6] *= s; 
    r3[7] *= s;

    // Substitute(Row[2])
	  m2 = r2[3]; 
	  s = 1.0f / r2[2];
	  r2[4] = s * (r2[4] - r3[4] * m2);
    r2[5] = s * (r2[5] - r3[5] * m2);
    r2[6] = s * (r2[6] - r3[6] * m2);
    r2[7] = s * (r2[7] - r3[7] * m2);

	  m1 = r1[3];
	  r1[4] -= r3[4] * m1;
	  r1[5] -= r3[5] * m1;
	  r1[6] -= r3[6] * m1;
	  r1[7] -= r3[7] * m1;

	  m0 = r0[3];
	  r0[4] -= r3[4] * m0;
	  r0[5] -= r3[5] * m0;
	  r0[6] -= r3[6] * m0;
	  r0[7] -= r3[7] * m0;

    // Substitute(Row[1])
	  m1 = r1[2]; 
	  s = 1.0f / r1[1];
	  r1[4] = s * (r1[4] - r2[4] * m1);
	  r1[5] = s * (r1[5] - r2[5] * m1);
	  r1[6] = s * (r1[6] - r2[6] * m1);
	  r1[7] = s * (r1[7] - r2[7] * m1);

	  m0 = r0[2];
	  r0[4] -= r2[4] * m0;
	  r0[5] -= r2[5] * m0;
	  r0[6] -= r2[6] * m0;
	  r0[7] -= r2[7] * m0;

    // Substitute(Row[0])
	  m0 = r0[1]; 
	  s = 1.0f / r0[0];
	  r0[4] = s * (r0[4] - r1[4] * m0);
	  r0[5] = s * (r0[5] - r1[5] * m0);
	  r0[6] = s * (r0[6] - r1[6] * m0);
	  r0[7] = s * (r0[7] - r1[7] * m0);

	  return Mat4x4(r0[4], r0[5], r0[6], r0[7],
	  				      r1[4], r1[5], r1[6], r1[7],
	  				      r2[4], r2[5], r2[6], r2[7],
	  				      r3[4], r3[5], r3[6], r3[7]);
  }

  Vec4<T> mulPoint(const Vec4<T>& v) const {
    return Vec4<T>(v.x * cx.x + v.y * cy.x + v.z * cz.x + v.w * cw.x,  //
                   v.x * cx.y + v.y * cy.y + v.z * cz.y + v.w * cw.y,  //
                   v.x * cx.z + v.y * cy.z + v.z * cz.z + v.w * cw.z,  //
                   v.x * cx.w + v.y * cy.w + v.z * cz.w + v.w * cw.w); //
  }

  Vec3<T> mulPoint(const Vec3<T>& v) const {
    return Vec3<T>(v.x * cx.x + v.y * cy.x + v.z * cz.x + cw.x,  //
                   v.x * cx.y + v.y * cy.y + v.z * cz.y + cw.y,  //
                   v.x * cx.z + v.y * cy.z + v.z * cz.z + cw.z); //
  }

  Vec3<T> mulVector(const Vec3<T>& v) const {
    return Vec3<T>(v.x * cx.x + v.y * cy.x + v.z * cz.x,  //
                   v.x * cx.y + v.y * cy.y + v.z * cz.y,  //
                   v.x * cx.z + v.y * cy.z + v.z * cz.z); //
  }

  Vec3<T> mulNormal(const Vec3<T>& v) const {
    auto invM = inverse(); // [Issue] mul the inverse transpose ???
    return Vec3<T>(v.x * cx.x + v.y * cx.y + v.z * cx.z,  //
                   v.x * cy.x + v.y * cy.y + v.z * cy.z,  //
                   v.x * cz.x + v.y * cz.y + v.z * cz.z); //
  }
  // clang-format on  
};

using Mat4f = Mat4x4<float>;

static_assert(sizeof(Mat4f) == sizeof(float) * 16, "");

}