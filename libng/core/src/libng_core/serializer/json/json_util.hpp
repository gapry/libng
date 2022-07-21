#pragma once

#include <libng_core/exception/error.hpp>
#include <libng_core/file/File.hpp>
#include <libng_core/file/MemMapFile.hpp>
#include <libng_core/libcxx/json.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/libcxx/type_make.hpp>
#include <libng_core/serializer/json/json_deserializer.hpp>
#include <libng_core/serializer/json/json_serializer.hpp>
#include <libng_core/types/function.hpp>

namespace libng {

// clang-format off
struct JsonUtil {
  JsonUtil() = delete;

  template<class T>           static void readFile(StrView filename, T& obj);

  template<class T>           static void writeFile         (StrView filename, T& obj, bool createDir, bool logResult = true);
  template<class T>           static void writeFileIfChanged(StrView filename, T& obj, bool createDir, bool logResult = true);

  template<class T, size_t N> static void serialize  (String_<N>& json, T& obj);
  template<class T>           static void deserialize(StrView     json, T& obj);
};
// clang-format on

template<class T>
LIBNG_INLINE void JsonUtil::readFile(StrView filename, T& obj) {
  MemMapFile mm;
  mm.open(filename);

  auto str  = StrView_make(mm);
  auto json = Json::parse(str.begin(), str.end());
  json_deserializer de(json);
  de.io(obj);
}

template<class T>
LIBNG_INLINE void JsonUtil::writeFile(StrView filename, T& obj, bool createDir, bool logResult) {
  TempString json;
  serialize(json, obj);
  File::writeFile(filename, json, createDir, logResult);
}

template<class T>
LIBNG_INLINE void JsonUtil::writeFileIfChanged(StrView filename, T& obj, bool createDir, bool logResult) {
  TempString json;
  serialize(json, obj);
  File::writeFileIfChanged(filename, json, createDir, logResult);
}

template<class T, size_t N>
LIBNG_INLINE void JsonUtil::serialize(String_<N>& outJson, T& obj) {
  Json json;
  json_serializer se(json);
  se.io(obj);
  auto tmp = json.dump(1, '\t');
  outJson  = tmp.c_str();
}

template<class T>
LIBNG_INLINE void JsonUtil::deserialize(StrView json, T& obj) {
  json_deserializer se(json);
  se.io(obj);
}

} // namespace libng