#ifndef __GNET_NONCOPYABLE_H__
#define __GNET_NONCOPYABLE_H__

namespace gnet {

class noncopyable {
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

public:
  noncopyable()  = default;
  ~noncopyable() = default;
};

} // namespace gnet

#endif
