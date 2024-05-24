// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_RESPONSE_H_
#define FLATBUFFERS_GENERATED_RESPONSE_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 5 &&
              FLATBUFFERS_VERSION_REVISION == 26,
             "Non-compatible flatbuffers version included");

struct Response;
struct ResponseBuilder;
struct ResponseT;

bool operator==(const ResponseT &lhs, const ResponseT &rhs);
bool operator!=(const ResponseT &lhs, const ResponseT &rhs);

inline const ::flatbuffers::TypeTable *ResponseTypeTable();

struct ResponseT : public ::flatbuffers::NativeTable {
  typedef Response TableType;
  int32_t type = 0;
  std::vector<int8_t> data{};
  std::string error{};
};

struct Response FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef ResponseT NativeTableType;
  typedef ResponseBuilder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return ResponseTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TYPE = 4,
    VT_DATA = 6,
    VT_ERROR = 8
  };
  int32_t type() const {
    return GetField<int32_t>(VT_TYPE, 0);
  }
  bool mutate_type(int32_t _type = 0) {
    return SetField<int32_t>(VT_TYPE, _type, 0);
  }
  const ::flatbuffers::Vector<int8_t> *data() const {
    return GetPointer<const ::flatbuffers::Vector<int8_t> *>(VT_DATA);
  }
  ::flatbuffers::Vector<int8_t> *mutable_data() {
    return GetPointer<::flatbuffers::Vector<int8_t> *>(VT_DATA);
  }
  const ::flatbuffers::String *error() const {
    return GetPointer<const ::flatbuffers::String *>(VT_ERROR);
  }
  ::flatbuffers::String *mutable_error() {
    return GetPointer<::flatbuffers::String *>(VT_ERROR);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_TYPE, 4) &&
           VerifyOffset(verifier, VT_DATA) &&
           verifier.VerifyVector(data()) &&
           VerifyOffset(verifier, VT_ERROR) &&
           verifier.VerifyString(error()) &&
           verifier.EndTable();
  }
  ResponseT *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ResponseT *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<Response> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const ResponseT* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ResponseBuilder {
  typedef Response Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_type(int32_t type) {
    fbb_.AddElement<int32_t>(Response::VT_TYPE, type, 0);
  }
  void add_data(::flatbuffers::Offset<::flatbuffers::Vector<int8_t>> data) {
    fbb_.AddOffset(Response::VT_DATA, data);
  }
  void add_error(::flatbuffers::Offset<::flatbuffers::String> error) {
    fbb_.AddOffset(Response::VT_ERROR, error);
  }
  explicit ResponseBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Response> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Response>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Response> CreateResponse(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    int32_t type = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<int8_t>> data = 0,
    ::flatbuffers::Offset<::flatbuffers::String> error = 0) {
  ResponseBuilder builder_(_fbb);
  builder_.add_error(error);
  builder_.add_data(data);
  builder_.add_type(type);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Response> CreateResponseDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    int32_t type = 0,
    const std::vector<int8_t> *data = nullptr,
    const char *error = nullptr) {
  auto data__ = data ? _fbb.CreateVector<int8_t>(*data) : 0;
  auto error__ = error ? _fbb.CreateString(error) : 0;
  return CreateResponse(
      _fbb,
      type,
      data__,
      error__);
}

::flatbuffers::Offset<Response> CreateResponse(::flatbuffers::FlatBufferBuilder &_fbb, const ResponseT *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);


inline bool operator==(const ResponseT &lhs, const ResponseT &rhs) {
  return
      (lhs.type == rhs.type) &&
      (lhs.data == rhs.data) &&
      (lhs.error == rhs.error);
}

inline bool operator!=(const ResponseT &lhs, const ResponseT &rhs) {
    return !(lhs == rhs);
}


inline ResponseT *Response::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<ResponseT>(new ResponseT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Response::UnPackTo(ResponseT *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = type(); _o->type = _e; }
  { auto _e = data(); if (_e) { _o->data.resize(_e->size()); std::copy(_e->begin(), _e->end(), _o->data.begin()); } }
  { auto _e = error(); if (_e) _o->error = _e->str(); }
}

inline ::flatbuffers::Offset<Response> Response::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const ResponseT* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return CreateResponse(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<Response> CreateResponse(::flatbuffers::FlatBufferBuilder &_fbb, const ResponseT *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const ResponseT* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _type = _o->type;
  auto _data = _o->data.size() ? _fbb.CreateVector(_o->data) : 0;
  auto _error = _o->error.empty() ? 0 : _fbb.CreateString(_o->error);
  return CreateResponse(
      _fbb,
      _type,
      _data,
      _error);
}

inline const ::flatbuffers::TypeTable *ResponseTypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_INT, 0, -1 },
    { ::flatbuffers::ET_CHAR, 1, -1 },
    { ::flatbuffers::ET_STRING, 0, -1 }
  };
  static const char * const names[] = {
    "type",
    "data",
    "error"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 3, type_codes, nullptr, nullptr, nullptr, names
  };
  return &tt;
}

#endif  // FLATBUFFERS_GENERATED_RESPONSE_H_
