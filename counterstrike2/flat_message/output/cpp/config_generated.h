// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_CONFIG_H_
#define FLATBUFFERS_GENERATED_CONFIG_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 5 &&
              FLATBUFFERS_VERSION_REVISION == 26,
             "Non-compatible flatbuffers version included");

struct config_request;
struct config_requestBuilder;
struct config_requestT;

bool operator==(const config_requestT &lhs, const config_requestT &rhs);
bool operator!=(const config_requestT &lhs, const config_requestT &rhs);

inline const ::flatbuffers::TypeTable *config_requestTypeTable();

struct config_requestT : public ::flatbuffers::NativeTable {
  typedef config_request TableType;
  std::string token{};
  std::string share{};
  std::string value{};
  std::string name{};
};

struct config_request FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef config_requestT NativeTableType;
  typedef config_requestBuilder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return config_requestTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TOKEN = 4,
    VT_SHARE = 6,
    VT_VALUE = 8,
    VT_NAME = 10
  };
  const ::flatbuffers::String *token() const {
    return GetPointer<const ::flatbuffers::String *>(VT_TOKEN);
  }
  ::flatbuffers::String *mutable_token() {
    return GetPointer<::flatbuffers::String *>(VT_TOKEN);
  }
  const ::flatbuffers::String *share() const {
    return GetPointer<const ::flatbuffers::String *>(VT_SHARE);
  }
  ::flatbuffers::String *mutable_share() {
    return GetPointer<::flatbuffers::String *>(VT_SHARE);
  }
  const ::flatbuffers::String *value() const {
    return GetPointer<const ::flatbuffers::String *>(VT_VALUE);
  }
  ::flatbuffers::String *mutable_value() {
    return GetPointer<::flatbuffers::String *>(VT_VALUE);
  }
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  ::flatbuffers::String *mutable_name() {
    return GetPointer<::flatbuffers::String *>(VT_NAME);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_TOKEN) &&
           verifier.VerifyString(token()) &&
           VerifyOffset(verifier, VT_SHARE) &&
           verifier.VerifyString(share()) &&
           VerifyOffset(verifier, VT_VALUE) &&
           verifier.VerifyString(value()) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           verifier.EndTable();
  }
  config_requestT *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(config_requestT *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<config_request> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const config_requestT* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct config_requestBuilder {
  typedef config_request Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_token(::flatbuffers::Offset<::flatbuffers::String> token) {
    fbb_.AddOffset(config_request::VT_TOKEN, token);
  }
  void add_share(::flatbuffers::Offset<::flatbuffers::String> share) {
    fbb_.AddOffset(config_request::VT_SHARE, share);
  }
  void add_value(::flatbuffers::Offset<::flatbuffers::String> value) {
    fbb_.AddOffset(config_request::VT_VALUE, value);
  }
  void add_name(::flatbuffers::Offset<::flatbuffers::String> name) {
    fbb_.AddOffset(config_request::VT_NAME, name);
  }
  explicit config_requestBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<config_request> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<config_request>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<config_request> Createconfig_request(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> token = 0,
    ::flatbuffers::Offset<::flatbuffers::String> share = 0,
    ::flatbuffers::Offset<::flatbuffers::String> value = 0,
    ::flatbuffers::Offset<::flatbuffers::String> name = 0) {
  config_requestBuilder builder_(_fbb);
  builder_.add_name(name);
  builder_.add_value(value);
  builder_.add_share(share);
  builder_.add_token(token);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<config_request> Createconfig_requestDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *token = nullptr,
    const char *share = nullptr,
    const char *value = nullptr,
    const char *name = nullptr) {
  auto token__ = token ? _fbb.CreateString(token) : 0;
  auto share__ = share ? _fbb.CreateString(share) : 0;
  auto value__ = value ? _fbb.CreateString(value) : 0;
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return Createconfig_request(
      _fbb,
      token__,
      share__,
      value__,
      name__);
}

::flatbuffers::Offset<config_request> Createconfig_request(::flatbuffers::FlatBufferBuilder &_fbb, const config_requestT *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);


inline bool operator==(const config_requestT &lhs, const config_requestT &rhs) {
  return
      (lhs.token == rhs.token) &&
      (lhs.share == rhs.share) &&
      (lhs.value == rhs.value) &&
      (lhs.name == rhs.name);
}

inline bool operator!=(const config_requestT &lhs, const config_requestT &rhs) {
    return !(lhs == rhs);
}


inline config_requestT *config_request::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<config_requestT>(new config_requestT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void config_request::UnPackTo(config_requestT *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = token(); if (_e) _o->token = _e->str(); }
  { auto _e = share(); if (_e) _o->share = _e->str(); }
  { auto _e = value(); if (_e) _o->value = _e->str(); }
  { auto _e = name(); if (_e) _o->name = _e->str(); }
}

inline ::flatbuffers::Offset<config_request> config_request::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const config_requestT* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return Createconfig_request(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<config_request> Createconfig_request(::flatbuffers::FlatBufferBuilder &_fbb, const config_requestT *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const config_requestT* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _token = _o->token.empty() ? 0 : _fbb.CreateString(_o->token);
  auto _share = _o->share.empty() ? 0 : _fbb.CreateString(_o->share);
  auto _value = _o->value.empty() ? 0 : _fbb.CreateString(_o->value);
  auto _name = _o->name.empty() ? 0 : _fbb.CreateString(_o->name);
  return Createconfig_request(
      _fbb,
      _token,
      _share,
      _value,
      _name);
}

inline const ::flatbuffers::TypeTable *config_requestTypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_STRING, 0, -1 },
    { ::flatbuffers::ET_STRING, 0, -1 },
    { ::flatbuffers::ET_STRING, 0, -1 },
    { ::flatbuffers::ET_STRING, 0, -1 }
  };
  static const char * const names[] = {
    "token",
    "share",
    "value",
    "name"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 4, type_codes, nullptr, nullptr, nullptr, names
  };
  return &tt;
}

#endif  // FLATBUFFERS_GENERATED_CONFIG_H_