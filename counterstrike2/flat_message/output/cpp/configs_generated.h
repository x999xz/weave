// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_CONFIGS_H_
#define FLATBUFFERS_GENERATED_CONFIGS_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 5 &&
              FLATBUFFERS_VERSION_REVISION == 26,
             "Non-compatible flatbuffers version included");

struct Config;
struct ConfigBuilder;
struct ConfigT;

struct Configs;
struct ConfigsBuilder;
struct ConfigsT;

bool operator==(const ConfigT &lhs, const ConfigT &rhs);
bool operator!=(const ConfigT &lhs, const ConfigT &rhs);
bool operator==(const ConfigsT &lhs, const ConfigsT &rhs);
bool operator!=(const ConfigsT &lhs, const ConfigsT &rhs);

inline const ::flatbuffers::TypeTable *ConfigTypeTable();

inline const ::flatbuffers::TypeTable *ConfigsTypeTable();

struct ConfigT : public ::flatbuffers::NativeTable {
  typedef Config TableType;
  std::string name{};
  std::string value{};
  std::string share{};
  uint64_t updated = 0;
  uint64_t created = 0;
  std::string user{};
  std::string owner{};
};

struct Config FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef ConfigT NativeTableType;
  typedef ConfigBuilder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return ConfigTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_VALUE = 6,
    VT_SHARE = 8,
    VT_UPDATED = 10,
    VT_CREATED = 12,
    VT_USER = 14,
    VT_OWNER = 16
  };
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  ::flatbuffers::String *mutable_name() {
    return GetPointer<::flatbuffers::String *>(VT_NAME);
  }
  const ::flatbuffers::String *value() const {
    return GetPointer<const ::flatbuffers::String *>(VT_VALUE);
  }
  ::flatbuffers::String *mutable_value() {
    return GetPointer<::flatbuffers::String *>(VT_VALUE);
  }
  const ::flatbuffers::String *share() const {
    return GetPointer<const ::flatbuffers::String *>(VT_SHARE);
  }
  ::flatbuffers::String *mutable_share() {
    return GetPointer<::flatbuffers::String *>(VT_SHARE);
  }
  uint64_t updated() const {
    return GetField<uint64_t>(VT_UPDATED, 0);
  }
  bool mutate_updated(uint64_t _updated = 0) {
    return SetField<uint64_t>(VT_UPDATED, _updated, 0);
  }
  uint64_t created() const {
    return GetField<uint64_t>(VT_CREATED, 0);
  }
  bool mutate_created(uint64_t _created = 0) {
    return SetField<uint64_t>(VT_CREATED, _created, 0);
  }
  const ::flatbuffers::String *user() const {
    return GetPointer<const ::flatbuffers::String *>(VT_USER);
  }
  ::flatbuffers::String *mutable_user() {
    return GetPointer<::flatbuffers::String *>(VT_USER);
  }
  const ::flatbuffers::String *owner() const {
    return GetPointer<const ::flatbuffers::String *>(VT_OWNER);
  }
  ::flatbuffers::String *mutable_owner() {
    return GetPointer<::flatbuffers::String *>(VT_OWNER);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_VALUE) &&
           verifier.VerifyString(value()) &&
           VerifyOffset(verifier, VT_SHARE) &&
           verifier.VerifyString(share()) &&
           VerifyField<uint64_t>(verifier, VT_UPDATED, 8) &&
           VerifyField<uint64_t>(verifier, VT_CREATED, 8) &&
           VerifyOffset(verifier, VT_USER) &&
           verifier.VerifyString(user()) &&
           VerifyOffset(verifier, VT_OWNER) &&
           verifier.VerifyString(owner()) &&
           verifier.EndTable();
  }
  ConfigT *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ConfigT *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<Config> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const ConfigT* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ConfigBuilder {
  typedef Config Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_name(::flatbuffers::Offset<::flatbuffers::String> name) {
    fbb_.AddOffset(Config::VT_NAME, name);
  }
  void add_value(::flatbuffers::Offset<::flatbuffers::String> value) {
    fbb_.AddOffset(Config::VT_VALUE, value);
  }
  void add_share(::flatbuffers::Offset<::flatbuffers::String> share) {
    fbb_.AddOffset(Config::VT_SHARE, share);
  }
  void add_updated(uint64_t updated) {
    fbb_.AddElement<uint64_t>(Config::VT_UPDATED, updated, 0);
  }
  void add_created(uint64_t created) {
    fbb_.AddElement<uint64_t>(Config::VT_CREATED, created, 0);
  }
  void add_user(::flatbuffers::Offset<::flatbuffers::String> user) {
    fbb_.AddOffset(Config::VT_USER, user);
  }
  void add_owner(::flatbuffers::Offset<::flatbuffers::String> owner) {
    fbb_.AddOffset(Config::VT_OWNER, owner);
  }
  explicit ConfigBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Config> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Config>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Config> CreateConfig(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> name = 0,
    ::flatbuffers::Offset<::flatbuffers::String> value = 0,
    ::flatbuffers::Offset<::flatbuffers::String> share = 0,
    uint64_t updated = 0,
    uint64_t created = 0,
    ::flatbuffers::Offset<::flatbuffers::String> user = 0,
    ::flatbuffers::Offset<::flatbuffers::String> owner = 0) {
  ConfigBuilder builder_(_fbb);
  builder_.add_created(created);
  builder_.add_updated(updated);
  builder_.add_owner(owner);
  builder_.add_user(user);
  builder_.add_share(share);
  builder_.add_value(value);
  builder_.add_name(name);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Config> CreateConfigDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    const char *value = nullptr,
    const char *share = nullptr,
    uint64_t updated = 0,
    uint64_t created = 0,
    const char *user = nullptr,
    const char *owner = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto value__ = value ? _fbb.CreateString(value) : 0;
  auto share__ = share ? _fbb.CreateString(share) : 0;
  auto user__ = user ? _fbb.CreateString(user) : 0;
  auto owner__ = owner ? _fbb.CreateString(owner) : 0;
  return CreateConfig(
      _fbb,
      name__,
      value__,
      share__,
      updated,
      created,
      user__,
      owner__);
}

::flatbuffers::Offset<Config> CreateConfig(::flatbuffers::FlatBufferBuilder &_fbb, const ConfigT *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct ConfigsT : public ::flatbuffers::NativeTable {
  typedef Configs TableType;
  std::vector<std::unique_ptr<ConfigT>> config{};
  ConfigsT() = default;
  ConfigsT(const ConfigsT &o);
  ConfigsT(ConfigsT&&) FLATBUFFERS_NOEXCEPT = default;
  ConfigsT &operator=(ConfigsT o) FLATBUFFERS_NOEXCEPT;
};

struct Configs FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef ConfigsT NativeTableType;
  typedef ConfigsBuilder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return ConfigsTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_CONFIG = 4
  };
  const ::flatbuffers::Vector<::flatbuffers::Offset<Config>> *config() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<Config>> *>(VT_CONFIG);
  }
  ::flatbuffers::Vector<::flatbuffers::Offset<Config>> *mutable_config() {
    return GetPointer<::flatbuffers::Vector<::flatbuffers::Offset<Config>> *>(VT_CONFIG);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_CONFIG) &&
           verifier.VerifyVector(config()) &&
           verifier.VerifyVectorOfTables(config()) &&
           verifier.EndTable();
  }
  ConfigsT *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ConfigsT *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<Configs> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const ConfigsT* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ConfigsBuilder {
  typedef Configs Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_config(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Config>>> config) {
    fbb_.AddOffset(Configs::VT_CONFIG, config);
  }
  explicit ConfigsBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Configs> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Configs>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Configs> CreateConfigs(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Config>>> config = 0) {
  ConfigsBuilder builder_(_fbb);
  builder_.add_config(config);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Configs> CreateConfigsDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<::flatbuffers::Offset<Config>> *config = nullptr) {
  auto config__ = config ? _fbb.CreateVector<::flatbuffers::Offset<Config>>(*config) : 0;
  return CreateConfigs(
      _fbb,
      config__);
}

::flatbuffers::Offset<Configs> CreateConfigs(::flatbuffers::FlatBufferBuilder &_fbb, const ConfigsT *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);


inline bool operator==(const ConfigT &lhs, const ConfigT &rhs) {
  return
      (lhs.name == rhs.name) &&
      (lhs.value == rhs.value) &&
      (lhs.share == rhs.share) &&
      (lhs.updated == rhs.updated) &&
      (lhs.created == rhs.created) &&
      (lhs.user == rhs.user) &&
      (lhs.owner == rhs.owner);
}

inline bool operator!=(const ConfigT &lhs, const ConfigT &rhs) {
    return !(lhs == rhs);
}


inline ConfigT *Config::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<ConfigT>(new ConfigT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Config::UnPackTo(ConfigT *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = name(); if (_e) _o->name = _e->str(); }
  { auto _e = value(); if (_e) _o->value = _e->str(); }
  { auto _e = share(); if (_e) _o->share = _e->str(); }
  { auto _e = updated(); _o->updated = _e; }
  { auto _e = created(); _o->created = _e; }
  { auto _e = user(); if (_e) _o->user = _e->str(); }
  { auto _e = owner(); if (_e) _o->owner = _e->str(); }
}

inline ::flatbuffers::Offset<Config> Config::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const ConfigT* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return CreateConfig(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<Config> CreateConfig(::flatbuffers::FlatBufferBuilder &_fbb, const ConfigT *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const ConfigT* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _name = _o->name.empty() ? 0 : _fbb.CreateString(_o->name);
  auto _value = _o->value.empty() ? 0 : _fbb.CreateString(_o->value);
  auto _share = _o->share.empty() ? 0 : _fbb.CreateString(_o->share);
  auto _updated = _o->updated;
  auto _created = _o->created;
  auto _user = _o->user.empty() ? 0 : _fbb.CreateString(_o->user);
  auto _owner = _o->owner.empty() ? 0 : _fbb.CreateString(_o->owner);
  return CreateConfig(
      _fbb,
      _name,
      _value,
      _share,
      _updated,
      _created,
      _user,
      _owner);
}


inline bool operator==(const ConfigsT &lhs, const ConfigsT &rhs) {
  return
      (lhs.config.size() == rhs.config.size() && std::equal(lhs.config.cbegin(), lhs.config.cend(), rhs.config.cbegin(), [](std::unique_ptr<ConfigT> const &a, std::unique_ptr<ConfigT> const &b) { return (a == b) || (a && b && *a == *b); }));
}

inline bool operator!=(const ConfigsT &lhs, const ConfigsT &rhs) {
    return !(lhs == rhs);
}


inline ConfigsT::ConfigsT(const ConfigsT &o) {
  config.reserve(o.config.size());
  for (const auto &config_ : o.config) { config.emplace_back((config_) ? new ConfigT(*config_) : nullptr); }
}

inline ConfigsT &ConfigsT::operator=(ConfigsT o) FLATBUFFERS_NOEXCEPT {
  std::swap(config, o.config);
  return *this;
}

inline ConfigsT *Configs::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<ConfigsT>(new ConfigsT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Configs::UnPackTo(ConfigsT *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = config(); if (_e) { _o->config.resize(_e->size()); for (::flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { if(_o->config[_i]) { _e->Get(_i)->UnPackTo(_o->config[_i].get(), _resolver); } else { _o->config[_i] = std::unique_ptr<ConfigT>(_e->Get(_i)->UnPack(_resolver)); }; } } else { _o->config.resize(0); } }
}

inline ::flatbuffers::Offset<Configs> Configs::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const ConfigsT* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return CreateConfigs(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<Configs> CreateConfigs(::flatbuffers::FlatBufferBuilder &_fbb, const ConfigsT *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const ConfigsT* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _config = _o->config.size() ? _fbb.CreateVector<::flatbuffers::Offset<Config>> (_o->config.size(), [](size_t i, _VectorArgs *__va) { return CreateConfig(*__va->__fbb, __va->__o->config[i].get(), __va->__rehasher); }, &_va ) : 0;
  return CreateConfigs(
      _fbb,
      _config);
}

inline const ::flatbuffers::TypeTable *ConfigTypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_STRING, 0, -1 },
    { ::flatbuffers::ET_STRING, 0, -1 },
    { ::flatbuffers::ET_STRING, 0, -1 },
    { ::flatbuffers::ET_ULONG, 0, -1 },
    { ::flatbuffers::ET_ULONG, 0, -1 },
    { ::flatbuffers::ET_STRING, 0, -1 },
    { ::flatbuffers::ET_STRING, 0, -1 }
  };
  static const char * const names[] = {
    "name",
    "value",
    "share",
    "updated",
    "created",
    "user",
    "owner"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 7, type_codes, nullptr, nullptr, nullptr, names
  };
  return &tt;
}

inline const ::flatbuffers::TypeTable *ConfigsTypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_SEQUENCE, 1, 0 }
  };
  static const ::flatbuffers::TypeFunction type_refs[] = {
    ConfigTypeTable
  };
  static const char * const names[] = {
    "config"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 1, type_codes, type_refs, nullptr, nullptr, names
  };
  return &tt;
}

#endif  // FLATBUFFERS_GENERATED_CONFIGS_H_