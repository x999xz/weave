// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_LEGITSETTINGSTABLE_H_
#define FLATBUFFERS_GENERATED_LEGITSETTINGSTABLE_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 5 &&
              FLATBUFFERS_VERSION_REVISION == 26,
             "Non-compatible flatbuffers version included");

struct legit_settings;
struct legit_settingsBuilder;
struct legit_settingsT;

bool operator==(const legit_settingsT &lhs, const legit_settingsT &rhs);
bool operator!=(const legit_settingsT &lhs, const legit_settingsT &rhs);

inline const ::flatbuffers::TypeTable *legit_settingsTypeTable();

struct legit_settingsT : public ::flatbuffers::NativeTable {
  typedef legit_settings TableType;
  int32_t m_index = 0;
  int32_t m_group = 0;
  float test = 0.0f;
  std::string name{};
};

struct legit_settings FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef legit_settingsT NativeTableType;
  typedef legit_settingsBuilder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return legit_settingsTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_M_INDEX = 4,
    VT_M_GROUP = 6,
    VT_TEST = 8,
    VT_NAME = 10
  };
  int32_t m_index() const {
    return GetField<int32_t>(VT_M_INDEX, 0);
  }
  bool mutate_m_index(int32_t _m_index = 0) {
    return SetField<int32_t>(VT_M_INDEX, _m_index, 0);
  }
  int32_t m_group() const {
    return GetField<int32_t>(VT_M_GROUP, 0);
  }
  bool mutate_m_group(int32_t _m_group = 0) {
    return SetField<int32_t>(VT_M_GROUP, _m_group, 0);
  }
  float test() const {
    return GetField<float>(VT_TEST, 0.0f);
  }
  bool mutate_test(float _test = 0.0f) {
    return SetField<float>(VT_TEST, _test, 0.0f);
  }
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  ::flatbuffers::String *mutable_name() {
    return GetPointer<::flatbuffers::String *>(VT_NAME);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_M_INDEX, 4) &&
           VerifyField<int32_t>(verifier, VT_M_GROUP, 4) &&
           VerifyField<float>(verifier, VT_TEST, 4) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           verifier.EndTable();
  }
  legit_settingsT *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(legit_settingsT *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<legit_settings> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const legit_settingsT* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct legit_settingsBuilder {
  typedef legit_settings Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_m_index(int32_t m_index) {
    fbb_.AddElement<int32_t>(legit_settings::VT_M_INDEX, m_index, 0);
  }
  void add_m_group(int32_t m_group) {
    fbb_.AddElement<int32_t>(legit_settings::VT_M_GROUP, m_group, 0);
  }
  void add_test(float test) {
    fbb_.AddElement<float>(legit_settings::VT_TEST, test, 0.0f);
  }
  void add_name(::flatbuffers::Offset<::flatbuffers::String> name) {
    fbb_.AddOffset(legit_settings::VT_NAME, name);
  }
  explicit legit_settingsBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<legit_settings> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<legit_settings>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<legit_settings> Createlegit_settings(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    int32_t m_index = 0,
    int32_t m_group = 0,
    float test = 0.0f,
    ::flatbuffers::Offset<::flatbuffers::String> name = 0) {
  legit_settingsBuilder builder_(_fbb);
  builder_.add_name(name);
  builder_.add_test(test);
  builder_.add_m_group(m_group);
  builder_.add_m_index(m_index);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<legit_settings> Createlegit_settingsDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    int32_t m_index = 0,
    int32_t m_group = 0,
    float test = 0.0f,
    const char *name = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return Createlegit_settings(
      _fbb,
      m_index,
      m_group,
      test,
      name__);
}

::flatbuffers::Offset<legit_settings> Createlegit_settings(::flatbuffers::FlatBufferBuilder &_fbb, const legit_settingsT *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);


inline bool operator==(const legit_settingsT &lhs, const legit_settingsT &rhs) {
  return
      (lhs.m_index == rhs.m_index) &&
      (lhs.m_group == rhs.m_group) &&
      (lhs.test == rhs.test) &&
      (lhs.name == rhs.name);
}

inline bool operator!=(const legit_settingsT &lhs, const legit_settingsT &rhs) {
    return !(lhs == rhs);
}


inline legit_settingsT *legit_settings::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<legit_settingsT>(new legit_settingsT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void legit_settings::UnPackTo(legit_settingsT *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = m_index(); _o->m_index = _e; }
  { auto _e = m_group(); _o->m_group = _e; }
  { auto _e = test(); _o->test = _e; }
  { auto _e = name(); if (_e) _o->name = _e->str(); }
}

inline ::flatbuffers::Offset<legit_settings> legit_settings::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const legit_settingsT* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return Createlegit_settings(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<legit_settings> Createlegit_settings(::flatbuffers::FlatBufferBuilder &_fbb, const legit_settingsT *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const legit_settingsT* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _m_index = _o->m_index;
  auto _m_group = _o->m_group;
  auto _test = _o->test;
  auto _name = _o->name.empty() ? 0 : _fbb.CreateString(_o->name);
  return Createlegit_settings(
      _fbb,
      _m_index,
      _m_group,
      _test,
      _name);
}

inline const ::flatbuffers::TypeTable *legit_settingsTypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_INT, 0, -1 },
    { ::flatbuffers::ET_INT, 0, -1 },
    { ::flatbuffers::ET_FLOAT, 0, -1 },
    { ::flatbuffers::ET_STRING, 0, -1 }
  };
  static const char * const names[] = {
    "m_index",
    "m_group",
    "test",
    "name"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 4, type_codes, nullptr, nullptr, nullptr, names
  };
  return &tt;
}

#endif  // FLATBUFFERS_GENERATED_LEGITSETTINGSTABLE_H_