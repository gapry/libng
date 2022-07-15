#pragma once

#include <libng_core/debug/SourceLocation.hpp>
#include <libng_core/encoding/UtfUtil.hpp>
#include <libng_core/exception/error.hpp>
#include <libng_core/libcxx/fixed_vector.hpp>
#include <libng_core/libcxx/optional.hpp>
#include <libng_core/libcxx/span.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/libcxx/type_make.hpp>
#include <libng_core/libcxx/unique_ptr.hpp>
#include <libng_core/libcxx/vector.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/log/variable.hpp>
#include <libng_core/math/Color/Color.hpp>
#include <libng_core/math/Color/ColorType.hpp>
#include <libng_core/math/Maths.hpp>
#include <libng_core/math/Matrix/Mat4.hpp>
#include <libng_core/math/Tuple/Tuple2.hpp>
#include <libng_core/math/Tuple/Tuple3.hpp>
#include <libng_core/math/Tuple/Tuple4.hpp>
#include <libng_core/math/Vector/Vec2.hpp>
#include <libng_core/memory/ComPtr.hpp>
#include <libng_core/memory/SPtr.hpp>
#include <libng_core/memory/util.hpp>
#include <libng_core/platform/os.hpp>
#include <libng_core/serializer/json/json_serializer.hpp>
#include <libng_core/types/Object.hpp>
#include <libng_core/types/RefCountBase.hpp>
#include <libng_core/types/enum.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/types/noncopyable.hpp>
#include <libng_core/types/number.hpp>
#include <libng_core/ui/platform/win32/MSWindow.hpp>