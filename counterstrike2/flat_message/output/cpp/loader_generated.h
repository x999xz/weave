// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_LOADER_H_
#define FLATBUFFERS_GENERATED_LOADER_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 5 &&
              FLATBUFFERS_VERSION_REVISION == 26,
             "Non-compatible flatbuffers version included");

struct LoaderUser;
struct LoaderUserBuilder;
struct LoaderUserT;

struct Build;
struct BuildBuilder;
struct BuildT;

struct Subscription;
struct SubscriptionBuilder;
struct SubscriptionT;

struct Loader;
struct LoaderBuilder;
struct LoaderT;

bool operator==(const LoaderUserT &lhs, const LoaderUserT &rhs);
bool operator!=(const LoaderUserT &lhs, const LoaderUserT &rhs);
bool operator==(const BuildT &lhs, const BuildT &rhs);
bool operator!=(const BuildT &lhs, const BuildT &rhs);
bool operator==(const SubscriptionT &lhs, const SubscriptionT &rhs);
bool operator!=(const SubscriptionT &lhs, const SubscriptionT &rhs);
bool operator==(const LoaderT &lhs, const LoaderT &rhs);
bool operator!=(const LoaderT &lhs, const LoaderT &rhs);

inline const ::flatbuffers::TypeTable *LoaderUserTypeTable();

inline const ::flatbuffers::TypeTable *BuildTypeTable();

inline const ::flatbuffers::TypeTable *SubscriptionTypeTable();

inline const ::flatbuffers::TypeTable *LoaderTypeTable();

struct LoaderUserT : public ::flatbuffers::NativeTable {
  typedef LoaderUser TableType;
  std::string username{};
  std::string prefix{};
  std::string id{};
};

struct LoaderUser FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef LoaderUserT NativeTableType;
  typedef LoaderUserBuilder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return LoaderUserTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_USERNAME = 4,
    VT_PREFIX = 6,
    VT_ID = 8
  };
  const ::flatbuffers::String *username() const {
    return GetPointer<const ::flatbuffers::String *>(VT_USERNAME);
  }
  ::flatbuffers::String *mutable_username() {
    return GetPointer<::flatbuffers::String *>(VT_USERNAME);
  }
  const ::flatbuffers::String *prefix() const {
    return GetPointer<const ::flatbuffers::String *>(VT_PREFIX);
  }
  ::flatbuffers::String *mutable_prefix() {
    return GetPointer<::flatbuffers::String *>(VT_PREFIX);
  }
  const ::flatbuffers::String *id() const {
    return GetPointer<const ::flatbuffers::String *>(VT_ID);
  }
  ::flatbuffers::String *mutable_id() {
    return GetPointer<::flatbuffers::String *>(VT_ID);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_USERNAME) &&
           verifier.VerifyString(username()) &&
           VerifyOffset(verifier, VT_PREFIX) &&
           verifier.VerifyString(prefix()) &&
           VerifyOffset(verifier, VT_ID) &&
           verifier.VerifyString(id()) &&
           verifier.EndTable();
  }
  LoaderUserT *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(LoaderUserT *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<LoaderUser> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const LoaderUserT* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct LoaderUserBuilder {
  typedef LoaderUser Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_username(::flatbuffers::Offset<::flatbuffers::String> username) {
    fbb_.AddOffset(LoaderUser::VT_USERNAME, username);
  }
  void add_prefix(::flatbuffers::Offset<::flatbuffers::String> prefix) {
    fbb_.AddOffset(LoaderUser::VT_PREFIX, prefix);
  }
  void add_id(::flatbuffers::Offset<::flatbuffers::String> id) {
    fbb_.AddOffset(LoaderUser::VT_ID, id);
  }
  explicit LoaderUserBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<LoaderUser> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<LoaderUser>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<LoaderUser> CreateLoaderUser(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> username = 0,
    ::flatbuffers::Offset<::flatbuffers::String> prefix = 0,
    ::flatbuffers::Offset<::flatbuffers::String> id = 0) {
  LoaderUserBuilder builder_(_fbb);
  builder_.add_id(id);
  builder_.add_prefix(prefix);
  builder_.add_username(username);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<LoaderUser> CreateLoaderUserDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *username = nullptr,
    const char *prefix = nullptr,
    const char *id = nullptr) {
  auto username__ = username ? _fbb.CreateString(username) : 0;
  auto prefix__ = prefix ? _fbb.CreateString(prefix) : 0;
  auto id__ = id ? _fbb.CreateString(id) : 0;
  return CreateLoaderUser(
      _fbb,
      username__,
      prefix__,
      id__);
}

::flatbuffers::Offset<LoaderUser> CreateLoaderUser(::flatbuffers::FlatBufferBuilder &_fbb, const LoaderUserT *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct BuildT : public ::flatbuffers::NativeTable {
  typedef Build TableType;
  std::string build{};
  uint64_t sub_time = 0;
  std::string process{};
  std::string command{};
  int32_t id = 0;
};

struct Build FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef BuildT NativeTableType;
  typedef BuildBuilder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return BuildTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_BUILD = 4,
    VT_SUB_TIME = 6,
    VT_PROCESS = 8,
    VT_COMMAND = 10,
    VT_ID = 12
  };
  const ::flatbuffers::String *build() const {
    return GetPointer<const ::flatbuffers::String *>(VT_BUILD);
  }
  ::flatbuffers::String *mutable_build() {
    return GetPointer<::flatbuffers::String *>(VT_BUILD);
  }
  uint64_t sub_time() const {
    return GetField<uint64_t>(VT_SUB_TIME, 0);
  }
  bool mutate_sub_time(uint64_t _sub_time = 0) {
    return SetField<uint64_t>(VT_SUB_TIME, _sub_time, 0);
  }
  const ::flatbuffers::String *process() const {
    return GetPointer<const ::flatbuffers::String *>(VT_PROCESS);
  }
  ::flatbuffers::String *mutable_process() {
    return GetPointer<::flatbuffers::String *>(VT_PROCESS);
  }
  const ::flatbuffers::String *command() const {
    return GetPointer<const ::flatbuffers::String *>(VT_COMMAND);
  }
  ::flatbuffers::String *mutable_command() {
    return GetPointer<::flatbuffers::String *>(VT_COMMAND);
  }
  int32_t id() const {
    return GetField<int32_t>(VT_ID, 0);
  }
  bool mutate_id(int32_t _id = 0) {
    return SetField<int32_t>(VT_ID, _id, 0);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_BUILD) &&
           verifier.VerifyString(build()) &&
           VerifyField<uint64_t>(verifier, VT_SUB_TIME, 8) &&
           VerifyOffset(verifier, VT_PROCESS) &&
           verifier.VerifyString(process()) &&
           VerifyOffset(verifier, VT_COMMAND) &&
           verifier.VerifyString(command()) &&
           VerifyField<int32_t>(verifier, VT_ID, 4) &&
           verifier.EndTable();
  }
  BuildT *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(BuildT *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<Build> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const BuildT* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct BuildBuilder {
  typedef Build Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_build(::flatbuffers::Offset<::flatbuffers::String> build) {
    fbb_.AddOffset(Build::VT_BUILD, build);
  }
  void add_sub_time(uint64_t sub_time) {
    fbb_.AddElement<uint64_t>(Build::VT_SUB_TIME, sub_time, 0);
  }
  void add_process(::flatbuffers::Offset<::flatbuffers::String> process) {
    fbb_.AddOffset(Build::VT_PROCESS, process);
  }
  void add_command(::flatbuffers::Offset<::flatbuffers::String> command) {
    fbb_.AddOffset(Build::VT_COMMAND, command);
  }
  void add_id(int32_t id) {
    fbb_.AddElement<int32_t>(Build::VT_ID, id, 0);
  }
  explicit BuildBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Build> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Build>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Build> CreateBuild(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> build = 0,
    uint64_t sub_time = 0,
    ::flatbuffers::Offset<::flatbuffers::String> process = 0,
    ::flatbuffers::Offset<::flatbuffers::String> command = 0,
    int32_t id = 0) {
  BuildBuilder builder_(_fbb);
  builder_.add_sub_time(sub_time);
  builder_.add_id(id);
  builder_.add_command(command);
  builder_.add_process(process);
  builder_.add_build(build);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Build> CreateBuildDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *build = nullptr,
    uint64_t sub_time = 0,
    const char *process = nullptr,
    const char *command = nullptr,
    int32_t id = 0) {
  auto build__ = build ? _fbb.CreateString(build) : 0;
  auto process__ = process ? _fbb.CreateString(process) : 0;
  auto command__ = command ? _fbb.CreateString(command) : 0;
  return CreateBuild(
      _fbb,
      build__,
      sub_time,
      process__,
      command__,
      id);
}

::flatbuffers::Offset<Build> CreateBuild(::flatbuffers::FlatBufferBuilder &_fbb, const BuildT *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct SubscriptionT : public ::flatbuffers::NativeTable {
  typedef Subscription TableType;
  std::vector<std::unique_ptr<BuildT>> cs2{};
  std::vector<std::unique_ptr<BuildT>> dota2{};
  SubscriptionT() = default;
  SubscriptionT(const SubscriptionT &o);
  SubscriptionT(SubscriptionT&&) FLATBUFFERS_NOEXCEPT = default;
  SubscriptionT &operator=(SubscriptionT o) FLATBUFFERS_NOEXCEPT;
};

struct Subscription FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef SubscriptionT NativeTableType;
  typedef SubscriptionBuilder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return SubscriptionTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_CS2 = 4,
    VT_DOTA2 = 6
  };
  const ::flatbuffers::Vector<::flatbuffers::Offset<Build>> *cs2() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<Build>> *>(VT_CS2);
  }
  ::flatbuffers::Vector<::flatbuffers::Offset<Build>> *mutable_cs2() {
    return GetPointer<::flatbuffers::Vector<::flatbuffers::Offset<Build>> *>(VT_CS2);
  }
  const ::flatbuffers::Vector<::flatbuffers::Offset<Build>> *dota2() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<Build>> *>(VT_DOTA2);
  }
  ::flatbuffers::Vector<::flatbuffers::Offset<Build>> *mutable_dota2() {
    return GetPointer<::flatbuffers::Vector<::flatbuffers::Offset<Build>> *>(VT_DOTA2);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_CS2) &&
           verifier.VerifyVector(cs2()) &&
           verifier.VerifyVectorOfTables(cs2()) &&
           VerifyOffset(verifier, VT_DOTA2) &&
           verifier.VerifyVector(dota2()) &&
           verifier.VerifyVectorOfTables(dota2()) &&
           verifier.EndTable();
  }
  SubscriptionT *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(SubscriptionT *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<Subscription> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const SubscriptionT* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct SubscriptionBuilder {
  typedef Subscription Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_cs2(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Build>>> cs2) {
    fbb_.AddOffset(Subscription::VT_CS2, cs2);
  }
  void add_dota2(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Build>>> dota2) {
    fbb_.AddOffset(Subscription::VT_DOTA2, dota2);
  }
  explicit SubscriptionBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Subscription> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Subscription>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Subscription> CreateSubscription(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Build>>> cs2 = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Build>>> dota2 = 0) {
  SubscriptionBuilder builder_(_fbb);
  builder_.add_dota2(dota2);
  builder_.add_cs2(cs2);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Subscription> CreateSubscriptionDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<::flatbuffers::Offset<Build>> *cs2 = nullptr,
    const std::vector<::flatbuffers::Offset<Build>> *dota2 = nullptr) {
  auto cs2__ = cs2 ? _fbb.CreateVector<::flatbuffers::Offset<Build>>(*cs2) : 0;
  auto dota2__ = dota2 ? _fbb.CreateVector<::flatbuffers::Offset<Build>>(*dota2) : 0;
  return CreateSubscription(
      _fbb,
      cs2__,
      dota2__);
}

::flatbuffers::Offset<Subscription> CreateSubscription(::flatbuffers::FlatBufferBuilder &_fbb, const SubscriptionT *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct LoaderT : public ::flatbuffers::NativeTable {
  typedef Loader TableType;
  std::unique_ptr<LoaderUserT> user{};
  std::unique_ptr<SubscriptionT> sub{};
  LoaderT() = default;
  LoaderT(const LoaderT &o);
  LoaderT(LoaderT&&) FLATBUFFERS_NOEXCEPT = default;
  LoaderT &operator=(LoaderT o) FLATBUFFERS_NOEXCEPT;
};

struct Loader FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef LoaderT NativeTableType;
  typedef LoaderBuilder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return LoaderTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_USER = 4,
    VT_SUB = 6
  };
  const LoaderUser *user() const {
    return GetPointer<const LoaderUser *>(VT_USER);
  }
  LoaderUser *mutable_user() {
    return GetPointer<LoaderUser *>(VT_USER);
  }
  const Subscription *sub() const {
    return GetPointer<const Subscription *>(VT_SUB);
  }
  Subscription *mutable_sub() {
    return GetPointer<Subscription *>(VT_SUB);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_USER) &&
           verifier.VerifyTable(user()) &&
           VerifyOffset(verifier, VT_SUB) &&
           verifier.VerifyTable(sub()) &&
           verifier.EndTable();
  }
  LoaderT *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(LoaderT *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<Loader> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const LoaderT* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct LoaderBuilder {
  typedef Loader Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_user(::flatbuffers::Offset<LoaderUser> user) {
    fbb_.AddOffset(Loader::VT_USER, user);
  }
  void add_sub(::flatbuffers::Offset<Subscription> sub) {
    fbb_.AddOffset(Loader::VT_SUB, sub);
  }
  explicit LoaderBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Loader> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Loader>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Loader> CreateLoader(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<LoaderUser> user = 0,
    ::flatbuffers::Offset<Subscription> sub = 0) {
  LoaderBuilder builder_(_fbb);
  builder_.add_sub(sub);
  builder_.add_user(user);
  return builder_.Finish();
}

::flatbuffers::Offset<Loader> CreateLoader(::flatbuffers::FlatBufferBuilder &_fbb, const LoaderT *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);


inline bool operator==(const LoaderUserT &lhs, const LoaderUserT &rhs) {
  return
      (lhs.username == rhs.username) &&
      (lhs.prefix == rhs.prefix) &&
      (lhs.id == rhs.id);
}

inline bool operator!=(const LoaderUserT &lhs, const LoaderUserT &rhs) {
    return !(lhs == rhs);
}


inline LoaderUserT *LoaderUser::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<LoaderUserT>(new LoaderUserT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void LoaderUser::UnPackTo(LoaderUserT *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = username(); if (_e) _o->username = _e->str(); }
  { auto _e = prefix(); if (_e) _o->prefix = _e->str(); }
  { auto _e = id(); if (_e) _o->id = _e->str(); }
}

inline ::flatbuffers::Offset<LoaderUser> LoaderUser::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const LoaderUserT* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return CreateLoaderUser(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<LoaderUser> CreateLoaderUser(::flatbuffers::FlatBufferBuilder &_fbb, const LoaderUserT *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const LoaderUserT* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _username = _o->username.empty() ? 0 : _fbb.CreateString(_o->username);
  auto _prefix = _o->prefix.empty() ? 0 : _fbb.CreateString(_o->prefix);
  auto _id = _o->id.empty() ? 0 : _fbb.CreateString(_o->id);
  return CreateLoaderUser(
      _fbb,
      _username,
      _prefix,
      _id);
}


inline bool operator==(const BuildT &lhs, const BuildT &rhs) {
  return
      (lhs.build == rhs.build) &&
      (lhs.sub_time == rhs.sub_time) &&
      (lhs.process == rhs.process) &&
      (lhs.command == rhs.command) &&
      (lhs.id == rhs.id);
}

inline bool operator!=(const BuildT &lhs, const BuildT &rhs) {
    return !(lhs == rhs);
}


inline BuildT *Build::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<BuildT>(new BuildT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Build::UnPackTo(BuildT *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = build(); if (_e) _o->build = _e->str(); }
  { auto _e = sub_time(); _o->sub_time = _e; }
  { auto _e = process(); if (_e) _o->process = _e->str(); }
  { auto _e = command(); if (_e) _o->command = _e->str(); }
  { auto _e = id(); _o->id = _e; }
}

inline ::flatbuffers::Offset<Build> Build::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const BuildT* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return CreateBuild(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<Build> CreateBuild(::flatbuffers::FlatBufferBuilder &_fbb, const BuildT *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const BuildT* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _build = _o->build.empty() ? 0 : _fbb.CreateString(_o->build);
  auto _sub_time = _o->sub_time;
  auto _process = _o->process.empty() ? 0 : _fbb.CreateString(_o->process);
  auto _command = _o->command.empty() ? 0 : _fbb.CreateString(_o->command);
  auto _id = _o->id;
  return CreateBuild(
      _fbb,
      _build,
      _sub_time,
      _process,
      _command,
      _id);
}


inline bool operator==(const SubscriptionT &lhs, const SubscriptionT &rhs) {
  return
      (lhs.cs2.size() == rhs.cs2.size() && std::equal(lhs.cs2.cbegin(), lhs.cs2.cend(), rhs.cs2.cbegin(), [](std::unique_ptr<BuildT> const &a, std::unique_ptr<BuildT> const &b) { return (a == b) || (a && b && *a == *b); })) &&
      (lhs.dota2.size() == rhs.dota2.size() && std::equal(lhs.dota2.cbegin(), lhs.dota2.cend(), rhs.dota2.cbegin(), [](std::unique_ptr<BuildT> const &a, std::unique_ptr<BuildT> const &b) { return (a == b) || (a && b && *a == *b); }));
}

inline bool operator!=(const SubscriptionT &lhs, const SubscriptionT &rhs) {
    return !(lhs == rhs);
}


inline SubscriptionT::SubscriptionT(const SubscriptionT &o) {
  cs2.reserve(o.cs2.size());
  for (const auto &cs2_ : o.cs2) { cs2.emplace_back((cs2_) ? new BuildT(*cs2_) : nullptr); }
  dota2.reserve(o.dota2.size());
  for (const auto &dota2_ : o.dota2) { dota2.emplace_back((dota2_) ? new BuildT(*dota2_) : nullptr); }
}

inline SubscriptionT &SubscriptionT::operator=(SubscriptionT o) FLATBUFFERS_NOEXCEPT {
  std::swap(cs2, o.cs2);
  std::swap(dota2, o.dota2);
  return *this;
}

inline SubscriptionT *Subscription::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<SubscriptionT>(new SubscriptionT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Subscription::UnPackTo(SubscriptionT *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = cs2(); if (_e) { _o->cs2.resize(_e->size()); for (::flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { if(_o->cs2[_i]) { _e->Get(_i)->UnPackTo(_o->cs2[_i].get(), _resolver); } else { _o->cs2[_i] = std::unique_ptr<BuildT>(_e->Get(_i)->UnPack(_resolver)); }; } } else { _o->cs2.resize(0); } }
  { auto _e = dota2(); if (_e) { _o->dota2.resize(_e->size()); for (::flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { if(_o->dota2[_i]) { _e->Get(_i)->UnPackTo(_o->dota2[_i].get(), _resolver); } else { _o->dota2[_i] = std::unique_ptr<BuildT>(_e->Get(_i)->UnPack(_resolver)); }; } } else { _o->dota2.resize(0); } }
}

inline ::flatbuffers::Offset<Subscription> Subscription::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const SubscriptionT* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return CreateSubscription(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<Subscription> CreateSubscription(::flatbuffers::FlatBufferBuilder &_fbb, const SubscriptionT *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const SubscriptionT* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _cs2 = _o->cs2.size() ? _fbb.CreateVector<::flatbuffers::Offset<Build>> (_o->cs2.size(), [](size_t i, _VectorArgs *__va) { return CreateBuild(*__va->__fbb, __va->__o->cs2[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _dota2 = _o->dota2.size() ? _fbb.CreateVector<::flatbuffers::Offset<Build>> (_o->dota2.size(), [](size_t i, _VectorArgs *__va) { return CreateBuild(*__va->__fbb, __va->__o->dota2[i].get(), __va->__rehasher); }, &_va ) : 0;
  return CreateSubscription(
      _fbb,
      _cs2,
      _dota2);
}


inline bool operator==(const LoaderT &lhs, const LoaderT &rhs) {
  return
      ((lhs.user == rhs.user) || (lhs.user && rhs.user && *lhs.user == *rhs.user)) &&
      ((lhs.sub == rhs.sub) || (lhs.sub && rhs.sub && *lhs.sub == *rhs.sub));
}

inline bool operator!=(const LoaderT &lhs, const LoaderT &rhs) {
    return !(lhs == rhs);
}


inline LoaderT::LoaderT(const LoaderT &o)
      : user((o.user) ? new LoaderUserT(*o.user) : nullptr),
        sub((o.sub) ? new SubscriptionT(*o.sub) : nullptr) {
}

inline LoaderT &LoaderT::operator=(LoaderT o) FLATBUFFERS_NOEXCEPT {
  std::swap(user, o.user);
  std::swap(sub, o.sub);
  return *this;
}

inline LoaderT *Loader::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<LoaderT>(new LoaderT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Loader::UnPackTo(LoaderT *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = user(); if (_e) { if(_o->user) { _e->UnPackTo(_o->user.get(), _resolver); } else { _o->user = std::unique_ptr<LoaderUserT>(_e->UnPack(_resolver)); } } else if (_o->user) { _o->user.reset(); } }
  { auto _e = sub(); if (_e) { if(_o->sub) { _e->UnPackTo(_o->sub.get(), _resolver); } else { _o->sub = std::unique_ptr<SubscriptionT>(_e->UnPack(_resolver)); } } else if (_o->sub) { _o->sub.reset(); } }
}

inline ::flatbuffers::Offset<Loader> Loader::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const LoaderT* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return CreateLoader(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<Loader> CreateLoader(::flatbuffers::FlatBufferBuilder &_fbb, const LoaderT *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const LoaderT* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _user = _o->user ? CreateLoaderUser(_fbb, _o->user.get(), _rehasher) : 0;
  auto _sub = _o->sub ? CreateSubscription(_fbb, _o->sub.get(), _rehasher) : 0;
  return CreateLoader(
      _fbb,
      _user,
      _sub);
}

inline const ::flatbuffers::TypeTable *LoaderUserTypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_STRING, 0, -1 },
    { ::flatbuffers::ET_STRING, 0, -1 },
    { ::flatbuffers::ET_STRING, 0, -1 }
  };
  static const char * const names[] = {
    "username",
    "prefix",
    "id"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 3, type_codes, nullptr, nullptr, nullptr, names
  };
  return &tt;
}

inline const ::flatbuffers::TypeTable *BuildTypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_STRING, 0, -1 },
    { ::flatbuffers::ET_ULONG, 0, -1 },
    { ::flatbuffers::ET_STRING, 0, -1 },
    { ::flatbuffers::ET_STRING, 0, -1 },
    { ::flatbuffers::ET_INT, 0, -1 }
  };
  static const char * const names[] = {
    "build",
    "sub_time",
    "process",
    "command",
    "id"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 5, type_codes, nullptr, nullptr, nullptr, names
  };
  return &tt;
}

inline const ::flatbuffers::TypeTable *SubscriptionTypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_SEQUENCE, 1, 0 },
    { ::flatbuffers::ET_SEQUENCE, 1, 0 }
  };
  static const ::flatbuffers::TypeFunction type_refs[] = {
    BuildTypeTable
  };
  static const char * const names[] = {
    "cs2",
    "dota2"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 2, type_codes, type_refs, nullptr, nullptr, names
  };
  return &tt;
}

inline const ::flatbuffers::TypeTable *LoaderTypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_SEQUENCE, 0, 0 },
    { ::flatbuffers::ET_SEQUENCE, 0, 1 }
  };
  static const ::flatbuffers::TypeFunction type_refs[] = {
    LoaderUserTypeTable,
    SubscriptionTypeTable
  };
  static const char * const names[] = {
    "user",
    "sub"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 2, type_codes, type_refs, nullptr, nullptr, names
  };
  return &tt;
}

#endif  // FLATBUFFERS_GENERATED_LOADER_H_
