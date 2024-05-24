// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_VISUALSTABLE_H_
#define FLATBUFFERS_GENERATED_VISUALSTABLE_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 5 &&
              FLATBUFFERS_VERSION_REVISION == 26,
             "Non-compatible flatbuffers version included");

struct flags_;
struct flags_Builder;
struct flags_T;

struct weapons_;
struct weapons_Builder;
struct weapons_T;

struct visuals;
struct visualsBuilder;
struct visualsT;

bool operator==(const flags_T &lhs, const flags_T &rhs);
bool operator!=(const flags_T &lhs, const flags_T &rhs);
bool operator==(const weapons_T &lhs, const weapons_T &rhs);
bool operator!=(const weapons_T &lhs, const weapons_T &rhs);
bool operator==(const visualsT &lhs, const visualsT &rhs);
bool operator!=(const visualsT &lhs, const visualsT &rhs);

inline const ::flatbuffers::TypeTable *flags_TypeTable();

inline const ::flatbuffers::TypeTable *weapons_TypeTable();

inline const ::flatbuffers::TypeTable *visualsTypeTable();

struct flags_T : public ::flatbuffers::NativeTable {
  typedef flags_ TableType;
  bool bomb = false;
  bool kits = false;
  bool armor = false;
  bool flashed = false;
  bool zeus = false;
  bool defuser = false;
};

struct flags_ FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef flags_T NativeTableType;
  typedef flags_Builder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return flags_TypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_BOMB = 4,
    VT_KITS = 6,
    VT_ARMOR = 8,
    VT_FLASHED = 10,
    VT_ZEUS = 12,
    VT_DEFUSER = 14
  };
  bool bomb() const {
    return GetField<uint8_t>(VT_BOMB, 0) != 0;
  }
  bool mutate_bomb(bool _bomb = 0) {
    return SetField<uint8_t>(VT_BOMB, static_cast<uint8_t>(_bomb), 0);
  }
  bool kits() const {
    return GetField<uint8_t>(VT_KITS, 0) != 0;
  }
  bool mutate_kits(bool _kits = 0) {
    return SetField<uint8_t>(VT_KITS, static_cast<uint8_t>(_kits), 0);
  }
  bool armor() const {
    return GetField<uint8_t>(VT_ARMOR, 0) != 0;
  }
  bool mutate_armor(bool _armor = 0) {
    return SetField<uint8_t>(VT_ARMOR, static_cast<uint8_t>(_armor), 0);
  }
  bool flashed() const {
    return GetField<uint8_t>(VT_FLASHED, 0) != 0;
  }
  bool mutate_flashed(bool _flashed = 0) {
    return SetField<uint8_t>(VT_FLASHED, static_cast<uint8_t>(_flashed), 0);
  }
  bool zeus() const {
    return GetField<uint8_t>(VT_ZEUS, 0) != 0;
  }
  bool mutate_zeus(bool _zeus = 0) {
    return SetField<uint8_t>(VT_ZEUS, static_cast<uint8_t>(_zeus), 0);
  }
  bool defuser() const {
    return GetField<uint8_t>(VT_DEFUSER, 0) != 0;
  }
  bool mutate_defuser(bool _defuser = 0) {
    return SetField<uint8_t>(VT_DEFUSER, static_cast<uint8_t>(_defuser), 0);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_BOMB, 1) &&
           VerifyField<uint8_t>(verifier, VT_KITS, 1) &&
           VerifyField<uint8_t>(verifier, VT_ARMOR, 1) &&
           VerifyField<uint8_t>(verifier, VT_FLASHED, 1) &&
           VerifyField<uint8_t>(verifier, VT_ZEUS, 1) &&
           VerifyField<uint8_t>(verifier, VT_DEFUSER, 1) &&
           verifier.EndTable();
  }
  flags_T *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(flags_T *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<flags_> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const flags_T* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct flags_Builder {
  typedef flags_ Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_bomb(bool bomb) {
    fbb_.AddElement<uint8_t>(flags_::VT_BOMB, static_cast<uint8_t>(bomb), 0);
  }
  void add_kits(bool kits) {
    fbb_.AddElement<uint8_t>(flags_::VT_KITS, static_cast<uint8_t>(kits), 0);
  }
  void add_armor(bool armor) {
    fbb_.AddElement<uint8_t>(flags_::VT_ARMOR, static_cast<uint8_t>(armor), 0);
  }
  void add_flashed(bool flashed) {
    fbb_.AddElement<uint8_t>(flags_::VT_FLASHED, static_cast<uint8_t>(flashed), 0);
  }
  void add_zeus(bool zeus) {
    fbb_.AddElement<uint8_t>(flags_::VT_ZEUS, static_cast<uint8_t>(zeus), 0);
  }
  void add_defuser(bool defuser) {
    fbb_.AddElement<uint8_t>(flags_::VT_DEFUSER, static_cast<uint8_t>(defuser), 0);
  }
  explicit flags_Builder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<flags_> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<flags_>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<flags_> Createflags_(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    bool bomb = false,
    bool kits = false,
    bool armor = false,
    bool flashed = false,
    bool zeus = false,
    bool defuser = false) {
  flags_Builder builder_(_fbb);
  builder_.add_defuser(defuser);
  builder_.add_zeus(zeus);
  builder_.add_flashed(flashed);
  builder_.add_armor(armor);
  builder_.add_kits(kits);
  builder_.add_bomb(bomb);
  return builder_.Finish();
}

::flatbuffers::Offset<flags_> Createflags_(::flatbuffers::FlatBufferBuilder &_fbb, const flags_T *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct weapons_T : public ::flatbuffers::NativeTable {
  typedef weapons_ TableType;
  bool name = false;
  bool icon = false;
};

struct weapons_ FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef weapons_T NativeTableType;
  typedef weapons_Builder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return weapons_TypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_ICON = 6
  };
  bool name() const {
    return GetField<uint8_t>(VT_NAME, 0) != 0;
  }
  bool mutate_name(bool _name = 0) {
    return SetField<uint8_t>(VT_NAME, static_cast<uint8_t>(_name), 0);
  }
  bool icon() const {
    return GetField<uint8_t>(VT_ICON, 0) != 0;
  }
  bool mutate_icon(bool _icon = 0) {
    return SetField<uint8_t>(VT_ICON, static_cast<uint8_t>(_icon), 0);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_NAME, 1) &&
           VerifyField<uint8_t>(verifier, VT_ICON, 1) &&
           verifier.EndTable();
  }
  weapons_T *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(weapons_T *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<weapons_> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const weapons_T* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct weapons_Builder {
  typedef weapons_ Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_name(bool name) {
    fbb_.AddElement<uint8_t>(weapons_::VT_NAME, static_cast<uint8_t>(name), 0);
  }
  void add_icon(bool icon) {
    fbb_.AddElement<uint8_t>(weapons_::VT_ICON, static_cast<uint8_t>(icon), 0);
  }
  explicit weapons_Builder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<weapons_> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<weapons_>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<weapons_> Createweapons_(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    bool name = false,
    bool icon = false) {
  weapons_Builder builder_(_fbb);
  builder_.add_icon(icon);
  builder_.add_name(name);
  return builder_.Finish();
}

::flatbuffers::Offset<weapons_> Createweapons_(::flatbuffers::FlatBufferBuilder &_fbb, const weapons_T *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct visualsT : public ::flatbuffers::NativeTable {
  typedef visuals TableType;
  bool name = false;
  uint32_t name_color = 0;
  bool box = false;
  uint32_t box_color = 0;
  bool avatar = false;
  bool health = false;
  std::unique_ptr<flags_T> flags{};
  bool skeleton = false;
  uint32_t skeleton_color = 0;
  std::unique_ptr<weapons_T> m_weapons{};
  bool chams_visible = false;
  uint32_t chams_visible_color = 0;
  int32_t chams_type = 0;
  bool chams_invisible = false;
  uint32_t chams_invisible_color = 0;
  bool attachment_chams = false;
  uint32_t attachment_chams_color = 0;
  visualsT() = default;
  visualsT(const visualsT &o);
  visualsT(visualsT&&) FLATBUFFERS_NOEXCEPT = default;
  visualsT &operator=(visualsT o) FLATBUFFERS_NOEXCEPT;
};

struct visuals FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef visualsT NativeTableType;
  typedef visualsBuilder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return visualsTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_NAME_COLOR = 6,
    VT_BOX = 8,
    VT_BOX_COLOR = 10,
    VT_AVATAR = 12,
    VT_HEALTH = 14,
    VT_FLAGS = 16,
    VT_SKELETON = 18,
    VT_SKELETON_COLOR = 20,
    VT_M_WEAPONS = 22,
    VT_CHAMS_VISIBLE = 24,
    VT_CHAMS_VISIBLE_COLOR = 26,
    VT_CHAMS_TYPE = 28,
    VT_CHAMS_INVISIBLE = 30,
    VT_CHAMS_INVISIBLE_COLOR = 32,
    VT_ATTACHMENT_CHAMS = 34,
    VT_ATTACHMENT_CHAMS_COLOR = 36
  };
  bool name() const {
    return GetField<uint8_t>(VT_NAME, 0) != 0;
  }
  bool mutate_name(bool _name = 0) {
    return SetField<uint8_t>(VT_NAME, static_cast<uint8_t>(_name), 0);
  }
  uint32_t name_color() const {
    return GetField<uint32_t>(VT_NAME_COLOR, 0);
  }
  bool mutate_name_color(uint32_t _name_color = 0) {
    return SetField<uint32_t>(VT_NAME_COLOR, _name_color, 0);
  }
  bool box() const {
    return GetField<uint8_t>(VT_BOX, 0) != 0;
  }
  bool mutate_box(bool _box = 0) {
    return SetField<uint8_t>(VT_BOX, static_cast<uint8_t>(_box), 0);
  }
  uint32_t box_color() const {
    return GetField<uint32_t>(VT_BOX_COLOR, 0);
  }
  bool mutate_box_color(uint32_t _box_color = 0) {
    return SetField<uint32_t>(VT_BOX_COLOR, _box_color, 0);
  }
  bool avatar() const {
    return GetField<uint8_t>(VT_AVATAR, 0) != 0;
  }
  bool mutate_avatar(bool _avatar = 0) {
    return SetField<uint8_t>(VT_AVATAR, static_cast<uint8_t>(_avatar), 0);
  }
  bool health() const {
    return GetField<uint8_t>(VT_HEALTH, 0) != 0;
  }
  bool mutate_health(bool _health = 0) {
    return SetField<uint8_t>(VT_HEALTH, static_cast<uint8_t>(_health), 0);
  }
  const flags_ *flags() const {
    return GetPointer<const flags_ *>(VT_FLAGS);
  }
  flags_ *mutable_flags() {
    return GetPointer<flags_ *>(VT_FLAGS);
  }
  bool skeleton() const {
    return GetField<uint8_t>(VT_SKELETON, 0) != 0;
  }
  bool mutate_skeleton(bool _skeleton = 0) {
    return SetField<uint8_t>(VT_SKELETON, static_cast<uint8_t>(_skeleton), 0);
  }
  uint32_t skeleton_color() const {
    return GetField<uint32_t>(VT_SKELETON_COLOR, 0);
  }
  bool mutate_skeleton_color(uint32_t _skeleton_color = 0) {
    return SetField<uint32_t>(VT_SKELETON_COLOR, _skeleton_color, 0);
  }
  const weapons_ *m_weapons() const {
    return GetPointer<const weapons_ *>(VT_M_WEAPONS);
  }
  weapons_ *mutable_m_weapons() {
    return GetPointer<weapons_ *>(VT_M_WEAPONS);
  }
  bool chams_visible() const {
    return GetField<uint8_t>(VT_CHAMS_VISIBLE, 0) != 0;
  }
  bool mutate_chams_visible(bool _chams_visible = 0) {
    return SetField<uint8_t>(VT_CHAMS_VISIBLE, static_cast<uint8_t>(_chams_visible), 0);
  }
  uint32_t chams_visible_color() const {
    return GetField<uint32_t>(VT_CHAMS_VISIBLE_COLOR, 0);
  }
  bool mutate_chams_visible_color(uint32_t _chams_visible_color = 0) {
    return SetField<uint32_t>(VT_CHAMS_VISIBLE_COLOR, _chams_visible_color, 0);
  }
  int32_t chams_type() const {
    return GetField<int32_t>(VT_CHAMS_TYPE, 0);
  }
  bool mutate_chams_type(int32_t _chams_type = 0) {
    return SetField<int32_t>(VT_CHAMS_TYPE, _chams_type, 0);
  }
  bool chams_invisible() const {
    return GetField<uint8_t>(VT_CHAMS_INVISIBLE, 0) != 0;
  }
  bool mutate_chams_invisible(bool _chams_invisible = 0) {
    return SetField<uint8_t>(VT_CHAMS_INVISIBLE, static_cast<uint8_t>(_chams_invisible), 0);
  }
  uint32_t chams_invisible_color() const {
    return GetField<uint32_t>(VT_CHAMS_INVISIBLE_COLOR, 0);
  }
  bool mutate_chams_invisible_color(uint32_t _chams_invisible_color = 0) {
    return SetField<uint32_t>(VT_CHAMS_INVISIBLE_COLOR, _chams_invisible_color, 0);
  }
  bool attachment_chams() const {
    return GetField<uint8_t>(VT_ATTACHMENT_CHAMS, 0) != 0;
  }
  bool mutate_attachment_chams(bool _attachment_chams = 0) {
    return SetField<uint8_t>(VT_ATTACHMENT_CHAMS, static_cast<uint8_t>(_attachment_chams), 0);
  }
  uint32_t attachment_chams_color() const {
    return GetField<uint32_t>(VT_ATTACHMENT_CHAMS_COLOR, 0);
  }
  bool mutate_attachment_chams_color(uint32_t _attachment_chams_color = 0) {
    return SetField<uint32_t>(VT_ATTACHMENT_CHAMS_COLOR, _attachment_chams_color, 0);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_NAME, 1) &&
           VerifyField<uint32_t>(verifier, VT_NAME_COLOR, 4) &&
           VerifyField<uint8_t>(verifier, VT_BOX, 1) &&
           VerifyField<uint32_t>(verifier, VT_BOX_COLOR, 4) &&
           VerifyField<uint8_t>(verifier, VT_AVATAR, 1) &&
           VerifyField<uint8_t>(verifier, VT_HEALTH, 1) &&
           VerifyOffset(verifier, VT_FLAGS) &&
           verifier.VerifyTable(flags()) &&
           VerifyField<uint8_t>(verifier, VT_SKELETON, 1) &&
           VerifyField<uint32_t>(verifier, VT_SKELETON_COLOR, 4) &&
           VerifyOffset(verifier, VT_M_WEAPONS) &&
           verifier.VerifyTable(m_weapons()) &&
           VerifyField<uint8_t>(verifier, VT_CHAMS_VISIBLE, 1) &&
           VerifyField<uint32_t>(verifier, VT_CHAMS_VISIBLE_COLOR, 4) &&
           VerifyField<int32_t>(verifier, VT_CHAMS_TYPE, 4) &&
           VerifyField<uint8_t>(verifier, VT_CHAMS_INVISIBLE, 1) &&
           VerifyField<uint32_t>(verifier, VT_CHAMS_INVISIBLE_COLOR, 4) &&
           VerifyField<uint8_t>(verifier, VT_ATTACHMENT_CHAMS, 1) &&
           VerifyField<uint32_t>(verifier, VT_ATTACHMENT_CHAMS_COLOR, 4) &&
           verifier.EndTable();
  }
  visualsT *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(visualsT *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<visuals> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const visualsT* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct visualsBuilder {
  typedef visuals Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_name(bool name) {
    fbb_.AddElement<uint8_t>(visuals::VT_NAME, static_cast<uint8_t>(name), 0);
  }
  void add_name_color(uint32_t name_color) {
    fbb_.AddElement<uint32_t>(visuals::VT_NAME_COLOR, name_color, 0);
  }
  void add_box(bool box) {
    fbb_.AddElement<uint8_t>(visuals::VT_BOX, static_cast<uint8_t>(box), 0);
  }
  void add_box_color(uint32_t box_color) {
    fbb_.AddElement<uint32_t>(visuals::VT_BOX_COLOR, box_color, 0);
  }
  void add_avatar(bool avatar) {
    fbb_.AddElement<uint8_t>(visuals::VT_AVATAR, static_cast<uint8_t>(avatar), 0);
  }
  void add_health(bool health) {
    fbb_.AddElement<uint8_t>(visuals::VT_HEALTH, static_cast<uint8_t>(health), 0);
  }
  void add_flags(::flatbuffers::Offset<flags_> flags) {
    fbb_.AddOffset(visuals::VT_FLAGS, flags);
  }
  void add_skeleton(bool skeleton) {
    fbb_.AddElement<uint8_t>(visuals::VT_SKELETON, static_cast<uint8_t>(skeleton), 0);
  }
  void add_skeleton_color(uint32_t skeleton_color) {
    fbb_.AddElement<uint32_t>(visuals::VT_SKELETON_COLOR, skeleton_color, 0);
  }
  void add_m_weapons(::flatbuffers::Offset<weapons_> m_weapons) {
    fbb_.AddOffset(visuals::VT_M_WEAPONS, m_weapons);
  }
  void add_chams_visible(bool chams_visible) {
    fbb_.AddElement<uint8_t>(visuals::VT_CHAMS_VISIBLE, static_cast<uint8_t>(chams_visible), 0);
  }
  void add_chams_visible_color(uint32_t chams_visible_color) {
    fbb_.AddElement<uint32_t>(visuals::VT_CHAMS_VISIBLE_COLOR, chams_visible_color, 0);
  }
  void add_chams_type(int32_t chams_type) {
    fbb_.AddElement<int32_t>(visuals::VT_CHAMS_TYPE, chams_type, 0);
  }
  void add_chams_invisible(bool chams_invisible) {
    fbb_.AddElement<uint8_t>(visuals::VT_CHAMS_INVISIBLE, static_cast<uint8_t>(chams_invisible), 0);
  }
  void add_chams_invisible_color(uint32_t chams_invisible_color) {
    fbb_.AddElement<uint32_t>(visuals::VT_CHAMS_INVISIBLE_COLOR, chams_invisible_color, 0);
  }
  void add_attachment_chams(bool attachment_chams) {
    fbb_.AddElement<uint8_t>(visuals::VT_ATTACHMENT_CHAMS, static_cast<uint8_t>(attachment_chams), 0);
  }
  void add_attachment_chams_color(uint32_t attachment_chams_color) {
    fbb_.AddElement<uint32_t>(visuals::VT_ATTACHMENT_CHAMS_COLOR, attachment_chams_color, 0);
  }
  explicit visualsBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<visuals> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<visuals>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<visuals> Createvisuals(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    bool name = false,
    uint32_t name_color = 0,
    bool box = false,
    uint32_t box_color = 0,
    bool avatar = false,
    bool health = false,
    ::flatbuffers::Offset<flags_> flags = 0,
    bool skeleton = false,
    uint32_t skeleton_color = 0,
    ::flatbuffers::Offset<weapons_> m_weapons = 0,
    bool chams_visible = false,
    uint32_t chams_visible_color = 0,
    int32_t chams_type = 0,
    bool chams_invisible = false,
    uint32_t chams_invisible_color = 0,
    bool attachment_chams = false,
    uint32_t attachment_chams_color = 0) {
  visualsBuilder builder_(_fbb);
  builder_.add_attachment_chams_color(attachment_chams_color);
  builder_.add_chams_invisible_color(chams_invisible_color);
  builder_.add_chams_type(chams_type);
  builder_.add_chams_visible_color(chams_visible_color);
  builder_.add_m_weapons(m_weapons);
  builder_.add_skeleton_color(skeleton_color);
  builder_.add_flags(flags);
  builder_.add_box_color(box_color);
  builder_.add_name_color(name_color);
  builder_.add_attachment_chams(attachment_chams);
  builder_.add_chams_invisible(chams_invisible);
  builder_.add_chams_visible(chams_visible);
  builder_.add_skeleton(skeleton);
  builder_.add_health(health);
  builder_.add_avatar(avatar);
  builder_.add_box(box);
  builder_.add_name(name);
  return builder_.Finish();
}

::flatbuffers::Offset<visuals> Createvisuals(::flatbuffers::FlatBufferBuilder &_fbb, const visualsT *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);


inline bool operator==(const flags_T &lhs, const flags_T &rhs) {
  return
      (lhs.bomb == rhs.bomb) &&
      (lhs.kits == rhs.kits) &&
      (lhs.armor == rhs.armor) &&
      (lhs.flashed == rhs.flashed) &&
      (lhs.zeus == rhs.zeus) &&
      (lhs.defuser == rhs.defuser);
}

inline bool operator!=(const flags_T &lhs, const flags_T &rhs) {
    return !(lhs == rhs);
}


inline flags_T *flags_::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<flags_T>(new flags_T());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void flags_::UnPackTo(flags_T *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = bomb(); _o->bomb = _e; }
  { auto _e = kits(); _o->kits = _e; }
  { auto _e = armor(); _o->armor = _e; }
  { auto _e = flashed(); _o->flashed = _e; }
  { auto _e = zeus(); _o->zeus = _e; }
  { auto _e = defuser(); _o->defuser = _e; }
}

inline ::flatbuffers::Offset<flags_> flags_::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const flags_T* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return Createflags_(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<flags_> Createflags_(::flatbuffers::FlatBufferBuilder &_fbb, const flags_T *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const flags_T* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _bomb = _o->bomb;
  auto _kits = _o->kits;
  auto _armor = _o->armor;
  auto _flashed = _o->flashed;
  auto _zeus = _o->zeus;
  auto _defuser = _o->defuser;
  return Createflags_(
      _fbb,
      _bomb,
      _kits,
      _armor,
      _flashed,
      _zeus,
      _defuser);
}


inline bool operator==(const weapons_T &lhs, const weapons_T &rhs) {
  return
      (lhs.name == rhs.name) &&
      (lhs.icon == rhs.icon);
}

inline bool operator!=(const weapons_T &lhs, const weapons_T &rhs) {
    return !(lhs == rhs);
}


inline weapons_T *weapons_::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<weapons_T>(new weapons_T());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void weapons_::UnPackTo(weapons_T *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = name(); _o->name = _e; }
  { auto _e = icon(); _o->icon = _e; }
}

inline ::flatbuffers::Offset<weapons_> weapons_::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const weapons_T* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return Createweapons_(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<weapons_> Createweapons_(::flatbuffers::FlatBufferBuilder &_fbb, const weapons_T *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const weapons_T* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _name = _o->name;
  auto _icon = _o->icon;
  return Createweapons_(
      _fbb,
      _name,
      _icon);
}


inline bool operator==(const visualsT &lhs, const visualsT &rhs) {
  return
      (lhs.name == rhs.name) &&
      (lhs.name_color == rhs.name_color) &&
      (lhs.box == rhs.box) &&
      (lhs.box_color == rhs.box_color) &&
      (lhs.avatar == rhs.avatar) &&
      (lhs.health == rhs.health) &&
      ((lhs.flags == rhs.flags) || (lhs.flags && rhs.flags && *lhs.flags == *rhs.flags)) &&
      (lhs.skeleton == rhs.skeleton) &&
      (lhs.skeleton_color == rhs.skeleton_color) &&
      ((lhs.m_weapons == rhs.m_weapons) || (lhs.m_weapons && rhs.m_weapons && *lhs.m_weapons == *rhs.m_weapons)) &&
      (lhs.chams_visible == rhs.chams_visible) &&
      (lhs.chams_visible_color == rhs.chams_visible_color) &&
      (lhs.chams_type == rhs.chams_type) &&
      (lhs.chams_invisible == rhs.chams_invisible) &&
      (lhs.chams_invisible_color == rhs.chams_invisible_color) &&
      (lhs.attachment_chams == rhs.attachment_chams) &&
      (lhs.attachment_chams_color == rhs.attachment_chams_color);
}

inline bool operator!=(const visualsT &lhs, const visualsT &rhs) {
    return !(lhs == rhs);
}


inline visualsT::visualsT(const visualsT &o)
      : name(o.name),
        name_color(o.name_color),
        box(o.box),
        box_color(o.box_color),
        avatar(o.avatar),
        health(o.health),
        flags((o.flags) ? new flags_T(*o.flags) : nullptr),
        skeleton(o.skeleton),
        skeleton_color(o.skeleton_color),
        m_weapons((o.m_weapons) ? new weapons_T(*o.m_weapons) : nullptr),
        chams_visible(o.chams_visible),
        chams_visible_color(o.chams_visible_color),
        chams_type(o.chams_type),
        chams_invisible(o.chams_invisible),
        chams_invisible_color(o.chams_invisible_color),
        attachment_chams(o.attachment_chams),
        attachment_chams_color(o.attachment_chams_color) {
}

inline visualsT &visualsT::operator=(visualsT o) FLATBUFFERS_NOEXCEPT {
  std::swap(name, o.name);
  std::swap(name_color, o.name_color);
  std::swap(box, o.box);
  std::swap(box_color, o.box_color);
  std::swap(avatar, o.avatar);
  std::swap(health, o.health);
  std::swap(flags, o.flags);
  std::swap(skeleton, o.skeleton);
  std::swap(skeleton_color, o.skeleton_color);
  std::swap(m_weapons, o.m_weapons);
  std::swap(chams_visible, o.chams_visible);
  std::swap(chams_visible_color, o.chams_visible_color);
  std::swap(chams_type, o.chams_type);
  std::swap(chams_invisible, o.chams_invisible);
  std::swap(chams_invisible_color, o.chams_invisible_color);
  std::swap(attachment_chams, o.attachment_chams);
  std::swap(attachment_chams_color, o.attachment_chams_color);
  return *this;
}

inline visualsT *visuals::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<visualsT>(new visualsT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void visuals::UnPackTo(visualsT *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = name(); _o->name = _e; }
  { auto _e = name_color(); _o->name_color = _e; }
  { auto _e = box(); _o->box = _e; }
  { auto _e = box_color(); _o->box_color = _e; }
  { auto _e = avatar(); _o->avatar = _e; }
  { auto _e = health(); _o->health = _e; }
  { auto _e = flags(); if (_e) { if(_o->flags) { _e->UnPackTo(_o->flags.get(), _resolver); } else { _o->flags = std::unique_ptr<flags_T>(_e->UnPack(_resolver)); } } else if (_o->flags) { _o->flags.reset(); } }
  { auto _e = skeleton(); _o->skeleton = _e; }
  { auto _e = skeleton_color(); _o->skeleton_color = _e; }
  { auto _e = m_weapons(); if (_e) { if(_o->m_weapons) { _e->UnPackTo(_o->m_weapons.get(), _resolver); } else { _o->m_weapons = std::unique_ptr<weapons_T>(_e->UnPack(_resolver)); } } else if (_o->m_weapons) { _o->m_weapons.reset(); } }
  { auto _e = chams_visible(); _o->chams_visible = _e; }
  { auto _e = chams_visible_color(); _o->chams_visible_color = _e; }
  { auto _e = chams_type(); _o->chams_type = _e; }
  { auto _e = chams_invisible(); _o->chams_invisible = _e; }
  { auto _e = chams_invisible_color(); _o->chams_invisible_color = _e; }
  { auto _e = attachment_chams(); _o->attachment_chams = _e; }
  { auto _e = attachment_chams_color(); _o->attachment_chams_color = _e; }
}

inline ::flatbuffers::Offset<visuals> visuals::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const visualsT* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return Createvisuals(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<visuals> Createvisuals(::flatbuffers::FlatBufferBuilder &_fbb, const visualsT *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const visualsT* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _name = _o->name;
  auto _name_color = _o->name_color;
  auto _box = _o->box;
  auto _box_color = _o->box_color;
  auto _avatar = _o->avatar;
  auto _health = _o->health;
  auto _flags = _o->flags ? Createflags_(_fbb, _o->flags.get(), _rehasher) : 0;
  auto _skeleton = _o->skeleton;
  auto _skeleton_color = _o->skeleton_color;
  auto _m_weapons = _o->m_weapons ? Createweapons_(_fbb, _o->m_weapons.get(), _rehasher) : 0;
  auto _chams_visible = _o->chams_visible;
  auto _chams_visible_color = _o->chams_visible_color;
  auto _chams_type = _o->chams_type;
  auto _chams_invisible = _o->chams_invisible;
  auto _chams_invisible_color = _o->chams_invisible_color;
  auto _attachment_chams = _o->attachment_chams;
  auto _attachment_chams_color = _o->attachment_chams_color;
  return Createvisuals(
      _fbb,
      _name,
      _name_color,
      _box,
      _box_color,
      _avatar,
      _health,
      _flags,
      _skeleton,
      _skeleton_color,
      _m_weapons,
      _chams_visible,
      _chams_visible_color,
      _chams_type,
      _chams_invisible,
      _chams_invisible_color,
      _attachment_chams,
      _attachment_chams_color);
}

inline const ::flatbuffers::TypeTable *flags_TypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_BOOL, 0, -1 },
    { ::flatbuffers::ET_BOOL, 0, -1 },
    { ::flatbuffers::ET_BOOL, 0, -1 },
    { ::flatbuffers::ET_BOOL, 0, -1 },
    { ::flatbuffers::ET_BOOL, 0, -1 },
    { ::flatbuffers::ET_BOOL, 0, -1 }
  };
  static const char * const names[] = {
    "bomb",
    "kits",
    "armor",
    "flashed",
    "zeus",
    "defuser"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 6, type_codes, nullptr, nullptr, nullptr, names
  };
  return &tt;
}

inline const ::flatbuffers::TypeTable *weapons_TypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_BOOL, 0, -1 },
    { ::flatbuffers::ET_BOOL, 0, -1 }
  };
  static const char * const names[] = {
    "name",
    "icon"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 2, type_codes, nullptr, nullptr, nullptr, names
  };
  return &tt;
}

inline const ::flatbuffers::TypeTable *visualsTypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_BOOL, 0, -1 },
    { ::flatbuffers::ET_UINT, 0, -1 },
    { ::flatbuffers::ET_BOOL, 0, -1 },
    { ::flatbuffers::ET_UINT, 0, -1 },
    { ::flatbuffers::ET_BOOL, 0, -1 },
    { ::flatbuffers::ET_BOOL, 0, -1 },
    { ::flatbuffers::ET_SEQUENCE, 0, 0 },
    { ::flatbuffers::ET_BOOL, 0, -1 },
    { ::flatbuffers::ET_UINT, 0, -1 },
    { ::flatbuffers::ET_SEQUENCE, 0, 1 },
    { ::flatbuffers::ET_BOOL, 0, -1 },
    { ::flatbuffers::ET_UINT, 0, -1 },
    { ::flatbuffers::ET_INT, 0, -1 },
    { ::flatbuffers::ET_BOOL, 0, -1 },
    { ::flatbuffers::ET_UINT, 0, -1 },
    { ::flatbuffers::ET_BOOL, 0, -1 },
    { ::flatbuffers::ET_UINT, 0, -1 }
  };
  static const ::flatbuffers::TypeFunction type_refs[] = {
    flags_TypeTable,
    weapons_TypeTable
  };
  static const char * const names[] = {
    "name",
    "name_color",
    "box",
    "box_color",
    "avatar",
    "health",
    "flags",
    "skeleton",
    "skeleton_color",
    "m_weapons",
    "chams_visible",
    "chams_visible_color",
    "chams_type",
    "chams_invisible",
    "chams_invisible_color",
    "attachment_chams",
    "attachment_chams_color"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 17, type_codes, type_refs, nullptr, nullptr, names
  };
  return &tt;
}

#endif  // FLATBUFFERS_GENERATED_VISUALSTABLE_H_