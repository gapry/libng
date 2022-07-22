#pragma once

#include <libng_core/file/File.hpp>
#include <libng_core/file/MemMapFile.hpp>
#include <libng_core/libcxx/json.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/libcxx/type_make.hpp>
#include <libng_core/serializer/json/json_deserializer.hpp>
#include <libng_core/serializer/json/json_io.hpp>
#include <libng_core/serializer/json/json_serializer.hpp>
#include <libng_core/serializer/json/json_util.hpp>
#include <libng_core/types/function.hpp>

namespace libng {

struct JsonFile {
  JsonFile() = delete;

  template<class T>
  static void writeIfChanged(StrView filename, T& obj, bool createDir, bool logResult = true);

  template<class T>
  static void write(StrView filename, T& obj, bool createDir, bool logResult = true);

  template<class T, size_t N>
  static void serialize(String_<N>& json, T& obj);

  template<class T>
  static void read(StrView filename, T& obj);

  template<class T>
  static void deserialize(StrView json, T& obj);
};

template<class T>
inline void JsonFile::writeIfChanged(StrView filename, T& obj, bool createDir, bool logResult) {
  TempString json;
  serialize(json, obj);
  File::writeFileIfChanged(filename, json, createDir, logResult);
}

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

  // the data which will be output to the json file
  auto tmp = data.dump(1, '\t');
  outJson  = tmp.c_str();
}

template<class T>
LIBNG_INLINE void JsonFile::read(StrView filename, T& obj) {
  MemMapFile mm;
  mm.open(filename);
  auto str = StrView_make(mm);

  auto json = Json::parse(str.begin(), str.end());
  json_deserializer de(json);
  de.io(obj);
}

template<class T>
LIBNG_INLINE void JsonFile::deserialize(StrView json, T& obj) {
  json_deserializer se(json);
  se.io(obj);
}

} // namespace libng