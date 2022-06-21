#pragma once

#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/libcxx/type_make.hpp>
#include <libng_core/libcxx/json.hpp>
#include <libng_core/serializer/json/json_serializer.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/file/File.hpp>
#include <libng_core/file/MemMapFile.hpp>

namespace libng {

struct JsonFile {
  JsonFile() = delete;

  template<class T>
  static void write(StrView filename, T& obj, bool createDir, bool logResult = true);

  template<class T, size_t N>
  static void serialize(String_<N>& json, T& obj);
};

template<class T>
LIBNG_INLINE void JsonFile::write(StrView filename, T& obj, bool createDir, bool logResult) {
  TempString json;
  serialize(json, obj);
  File::writeFile(filename, json, createDir, logResult);
}

template<class T, size_t N>
LIBNG_INLINE void JsonFile::serialize(String_<N>& outJson, T& obj) {
  Json data;
  json_serializer se(data);
  se.io(obj);
}

} // namespace libng