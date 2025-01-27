// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_CHAT_H_
#define FLATBUFFERS_GENERATED_CHAT_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 5 &&
              FLATBUFFERS_VERSION_REVISION == 26,
             "Non-compatible flatbuffers version included");

struct Message;
struct MessageBuilder;
struct MessageT;

struct AvatarData;
struct AvatarDataBuilder;
struct AvatarDataT;

struct Messages;
struct MessagesBuilder;
struct MessagesT;

struct RequestStickyMessage;
struct RequestStickyMessageBuilder;
struct RequestStickyMessageT;

bool operator==(const MessageT &lhs, const MessageT &rhs);
bool operator!=(const MessageT &lhs, const MessageT &rhs);
bool operator==(const AvatarDataT &lhs, const AvatarDataT &rhs);
bool operator!=(const AvatarDataT &lhs, const AvatarDataT &rhs);
bool operator==(const MessagesT &lhs, const MessagesT &rhs);
bool operator!=(const MessagesT &lhs, const MessagesT &rhs);
bool operator==(const RequestStickyMessageT &lhs, const RequestStickyMessageT &rhs);
bool operator!=(const RequestStickyMessageT &lhs, const RequestStickyMessageT &rhs);

inline const ::flatbuffers::TypeTable *MessageTypeTable();

inline const ::flatbuffers::TypeTable *AvatarDataTypeTable();

inline const ::flatbuffers::TypeTable *MessagesTypeTable();

inline const ::flatbuffers::TypeTable *RequestStickyMessageTypeTable();

struct MessageT : public ::flatbuffers::NativeTable {
  typedef Message TableType;
  std::string username{};
  std::string message{};
  bool sticky = false;
  uint64_t time = 0;
};

struct Message FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef MessageT NativeTableType;
  typedef MessageBuilder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return MessageTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_USERNAME = 4,
    VT_MESSAGE = 6,
    VT_STICKY = 8,
    VT_TIME = 10
  };
  const ::flatbuffers::String *username() const {
    return GetPointer<const ::flatbuffers::String *>(VT_USERNAME);
  }
  ::flatbuffers::String *mutable_username() {
    return GetPointer<::flatbuffers::String *>(VT_USERNAME);
  }
  const ::flatbuffers::String *message() const {
    return GetPointer<const ::flatbuffers::String *>(VT_MESSAGE);
  }
  ::flatbuffers::String *mutable_message() {
    return GetPointer<::flatbuffers::String *>(VT_MESSAGE);
  }
  bool sticky() const {
    return GetField<uint8_t>(VT_STICKY, 0) != 0;
  }
  bool mutate_sticky(bool _sticky = 0) {
    return SetField<uint8_t>(VT_STICKY, static_cast<uint8_t>(_sticky), 0);
  }
  uint64_t time() const {
    return GetField<uint64_t>(VT_TIME, 0);
  }
  bool mutate_time(uint64_t _time = 0) {
    return SetField<uint64_t>(VT_TIME, _time, 0);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_USERNAME) &&
           verifier.VerifyString(username()) &&
           VerifyOffset(verifier, VT_MESSAGE) &&
           verifier.VerifyString(message()) &&
           VerifyField<uint8_t>(verifier, VT_STICKY, 1) &&
           VerifyField<uint64_t>(verifier, VT_TIME, 8) &&
           verifier.EndTable();
  }
  MessageT *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(MessageT *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<Message> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const MessageT* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct MessageBuilder {
  typedef Message Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_username(::flatbuffers::Offset<::flatbuffers::String> username) {
    fbb_.AddOffset(Message::VT_USERNAME, username);
  }
  void add_message(::flatbuffers::Offset<::flatbuffers::String> message) {
    fbb_.AddOffset(Message::VT_MESSAGE, message);
  }
  void add_sticky(bool sticky) {
    fbb_.AddElement<uint8_t>(Message::VT_STICKY, static_cast<uint8_t>(sticky), 0);
  }
  void add_time(uint64_t time) {
    fbb_.AddElement<uint64_t>(Message::VT_TIME, time, 0);
  }
  explicit MessageBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Message> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Message>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Message> CreateMessage(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> username = 0,
    ::flatbuffers::Offset<::flatbuffers::String> message = 0,
    bool sticky = false,
    uint64_t time = 0) {
  MessageBuilder builder_(_fbb);
  builder_.add_time(time);
  builder_.add_message(message);
  builder_.add_username(username);
  builder_.add_sticky(sticky);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Message> CreateMessageDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *username = nullptr,
    const char *message = nullptr,
    bool sticky = false,
    uint64_t time = 0) {
  auto username__ = username ? _fbb.CreateString(username) : 0;
  auto message__ = message ? _fbb.CreateString(message) : 0;
  return CreateMessage(
      _fbb,
      username__,
      message__,
      sticky,
      time);
}

::flatbuffers::Offset<Message> CreateMessage(::flatbuffers::FlatBufferBuilder &_fbb, const MessageT *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct AvatarDataT : public ::flatbuffers::NativeTable {
  typedef AvatarData TableType;
  std::string username{};
  std::vector<int8_t> data{};
};

struct AvatarData FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef AvatarDataT NativeTableType;
  typedef AvatarDataBuilder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return AvatarDataTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_USERNAME = 4,
    VT_DATA = 6
  };
  const ::flatbuffers::String *username() const {
    return GetPointer<const ::flatbuffers::String *>(VT_USERNAME);
  }
  ::flatbuffers::String *mutable_username() {
    return GetPointer<::flatbuffers::String *>(VT_USERNAME);
  }
  const ::flatbuffers::Vector<int8_t> *data() const {
    return GetPointer<const ::flatbuffers::Vector<int8_t> *>(VT_DATA);
  }
  ::flatbuffers::Vector<int8_t> *mutable_data() {
    return GetPointer<::flatbuffers::Vector<int8_t> *>(VT_DATA);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_USERNAME) &&
           verifier.VerifyString(username()) &&
           VerifyOffset(verifier, VT_DATA) &&
           verifier.VerifyVector(data()) &&
           verifier.EndTable();
  }
  AvatarDataT *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(AvatarDataT *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<AvatarData> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const AvatarDataT* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct AvatarDataBuilder {
  typedef AvatarData Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_username(::flatbuffers::Offset<::flatbuffers::String> username) {
    fbb_.AddOffset(AvatarData::VT_USERNAME, username);
  }
  void add_data(::flatbuffers::Offset<::flatbuffers::Vector<int8_t>> data) {
    fbb_.AddOffset(AvatarData::VT_DATA, data);
  }
  explicit AvatarDataBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<AvatarData> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<AvatarData>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<AvatarData> CreateAvatarData(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> username = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<int8_t>> data = 0) {
  AvatarDataBuilder builder_(_fbb);
  builder_.add_data(data);
  builder_.add_username(username);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<AvatarData> CreateAvatarDataDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *username = nullptr,
    const std::vector<int8_t> *data = nullptr) {
  auto username__ = username ? _fbb.CreateString(username) : 0;
  auto data__ = data ? _fbb.CreateVector<int8_t>(*data) : 0;
  return CreateAvatarData(
      _fbb,
      username__,
      data__);
}

::flatbuffers::Offset<AvatarData> CreateAvatarData(::flatbuffers::FlatBufferBuilder &_fbb, const AvatarDataT *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct MessagesT : public ::flatbuffers::NativeTable {
  typedef Messages TableType;
  std::vector<std::unique_ptr<AvatarDataT>> avatar{};
  std::vector<std::unique_ptr<MessageT>> messages{};
  MessagesT() = default;
  MessagesT(const MessagesT &o);
  MessagesT(MessagesT&&) FLATBUFFERS_NOEXCEPT = default;
  MessagesT &operator=(MessagesT o) FLATBUFFERS_NOEXCEPT;
};

struct Messages FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef MessagesT NativeTableType;
  typedef MessagesBuilder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return MessagesTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_AVATAR = 4,
    VT_MESSAGES = 6
  };
  const ::flatbuffers::Vector<::flatbuffers::Offset<AvatarData>> *avatar() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<AvatarData>> *>(VT_AVATAR);
  }
  ::flatbuffers::Vector<::flatbuffers::Offset<AvatarData>> *mutable_avatar() {
    return GetPointer<::flatbuffers::Vector<::flatbuffers::Offset<AvatarData>> *>(VT_AVATAR);
  }
  const ::flatbuffers::Vector<::flatbuffers::Offset<Message>> *messages() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<Message>> *>(VT_MESSAGES);
  }
  ::flatbuffers::Vector<::flatbuffers::Offset<Message>> *mutable_messages() {
    return GetPointer<::flatbuffers::Vector<::flatbuffers::Offset<Message>> *>(VT_MESSAGES);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_AVATAR) &&
           verifier.VerifyVector(avatar()) &&
           verifier.VerifyVectorOfTables(avatar()) &&
           VerifyOffset(verifier, VT_MESSAGES) &&
           verifier.VerifyVector(messages()) &&
           verifier.VerifyVectorOfTables(messages()) &&
           verifier.EndTable();
  }
  MessagesT *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(MessagesT *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<Messages> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const MessagesT* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct MessagesBuilder {
  typedef Messages Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_avatar(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<AvatarData>>> avatar) {
    fbb_.AddOffset(Messages::VT_AVATAR, avatar);
  }
  void add_messages(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Message>>> messages) {
    fbb_.AddOffset(Messages::VT_MESSAGES, messages);
  }
  explicit MessagesBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Messages> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Messages>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Messages> CreateMessages(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<AvatarData>>> avatar = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Message>>> messages = 0) {
  MessagesBuilder builder_(_fbb);
  builder_.add_messages(messages);
  builder_.add_avatar(avatar);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Messages> CreateMessagesDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<::flatbuffers::Offset<AvatarData>> *avatar = nullptr,
    const std::vector<::flatbuffers::Offset<Message>> *messages = nullptr) {
  auto avatar__ = avatar ? _fbb.CreateVector<::flatbuffers::Offset<AvatarData>>(*avatar) : 0;
  auto messages__ = messages ? _fbb.CreateVector<::flatbuffers::Offset<Message>>(*messages) : 0;
  return CreateMessages(
      _fbb,
      avatar__,
      messages__);
}

::flatbuffers::Offset<Messages> CreateMessages(::flatbuffers::FlatBufferBuilder &_fbb, const MessagesT *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct RequestStickyMessageT : public ::flatbuffers::NativeTable {
  typedef RequestStickyMessage TableType;
  int32_t index = 0;
  bool sticky = false;
};

struct RequestStickyMessage FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef RequestStickyMessageT NativeTableType;
  typedef RequestStickyMessageBuilder Builder;
  static const ::flatbuffers::TypeTable *MiniReflectTypeTable() {
    return RequestStickyMessageTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_INDEX = 4,
    VT_STICKY = 6
  };
  int32_t index() const {
    return GetField<int32_t>(VT_INDEX, 0);
  }
  bool mutate_index(int32_t _index = 0) {
    return SetField<int32_t>(VT_INDEX, _index, 0);
  }
  bool sticky() const {
    return GetField<uint8_t>(VT_STICKY, 0) != 0;
  }
  bool mutate_sticky(bool _sticky = 0) {
    return SetField<uint8_t>(VT_STICKY, static_cast<uint8_t>(_sticky), 0);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_INDEX, 4) &&
           VerifyField<uint8_t>(verifier, VT_STICKY, 1) &&
           verifier.EndTable();
  }
  RequestStickyMessageT *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(RequestStickyMessageT *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<RequestStickyMessage> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const RequestStickyMessageT* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct RequestStickyMessageBuilder {
  typedef RequestStickyMessage Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_index(int32_t index) {
    fbb_.AddElement<int32_t>(RequestStickyMessage::VT_INDEX, index, 0);
  }
  void add_sticky(bool sticky) {
    fbb_.AddElement<uint8_t>(RequestStickyMessage::VT_STICKY, static_cast<uint8_t>(sticky), 0);
  }
  explicit RequestStickyMessageBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<RequestStickyMessage> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<RequestStickyMessage>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<RequestStickyMessage> CreateRequestStickyMessage(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    int32_t index = 0,
    bool sticky = false) {
  RequestStickyMessageBuilder builder_(_fbb);
  builder_.add_index(index);
  builder_.add_sticky(sticky);
  return builder_.Finish();
}

::flatbuffers::Offset<RequestStickyMessage> CreateRequestStickyMessage(::flatbuffers::FlatBufferBuilder &_fbb, const RequestStickyMessageT *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);


inline bool operator==(const MessageT &lhs, const MessageT &rhs) {
  return
      (lhs.username == rhs.username) &&
      (lhs.message == rhs.message) &&
      (lhs.sticky == rhs.sticky) &&
      (lhs.time == rhs.time);
}

inline bool operator!=(const MessageT &lhs, const MessageT &rhs) {
    return !(lhs == rhs);
}


inline MessageT *Message::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<MessageT>(new MessageT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Message::UnPackTo(MessageT *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = username(); if (_e) _o->username = _e->str(); }
  { auto _e = message(); if (_e) _o->message = _e->str(); }
  { auto _e = sticky(); _o->sticky = _e; }
  { auto _e = time(); _o->time = _e; }
}

inline ::flatbuffers::Offset<Message> Message::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const MessageT* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return CreateMessage(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<Message> CreateMessage(::flatbuffers::FlatBufferBuilder &_fbb, const MessageT *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const MessageT* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _username = _o->username.empty() ? 0 : _fbb.CreateString(_o->username);
  auto _message = _o->message.empty() ? 0 : _fbb.CreateString(_o->message);
  auto _sticky = _o->sticky;
  auto _time = _o->time;
  return CreateMessage(
      _fbb,
      _username,
      _message,
      _sticky,
      _time);
}


inline bool operator==(const AvatarDataT &lhs, const AvatarDataT &rhs) {
  return
      (lhs.username == rhs.username) &&
      (lhs.data == rhs.data);
}

inline bool operator!=(const AvatarDataT &lhs, const AvatarDataT &rhs) {
    return !(lhs == rhs);
}


inline AvatarDataT *AvatarData::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<AvatarDataT>(new AvatarDataT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void AvatarData::UnPackTo(AvatarDataT *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = username(); if (_e) _o->username = _e->str(); }
  { auto _e = data(); if (_e) { _o->data.resize(_e->size()); std::copy(_e->begin(), _e->end(), _o->data.begin()); } }
}

inline ::flatbuffers::Offset<AvatarData> AvatarData::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const AvatarDataT* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return CreateAvatarData(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<AvatarData> CreateAvatarData(::flatbuffers::FlatBufferBuilder &_fbb, const AvatarDataT *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const AvatarDataT* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _username = _o->username.empty() ? 0 : _fbb.CreateString(_o->username);
  auto _data = _o->data.size() ? _fbb.CreateVector(_o->data) : 0;
  return CreateAvatarData(
      _fbb,
      _username,
      _data);
}


inline bool operator==(const MessagesT &lhs, const MessagesT &rhs) {
  return
      (lhs.avatar.size() == rhs.avatar.size() && std::equal(lhs.avatar.cbegin(), lhs.avatar.cend(), rhs.avatar.cbegin(), [](std::unique_ptr<AvatarDataT> const &a, std::unique_ptr<AvatarDataT> const &b) { return (a == b) || (a && b && *a == *b); })) &&
      (lhs.messages.size() == rhs.messages.size() && std::equal(lhs.messages.cbegin(), lhs.messages.cend(), rhs.messages.cbegin(), [](std::unique_ptr<MessageT> const &a, std::unique_ptr<MessageT> const &b) { return (a == b) || (a && b && *a == *b); }));
}

inline bool operator!=(const MessagesT &lhs, const MessagesT &rhs) {
    return !(lhs == rhs);
}


inline MessagesT::MessagesT(const MessagesT &o) {
  avatar.reserve(o.avatar.size());
  for (const auto &avatar_ : o.avatar) { avatar.emplace_back((avatar_) ? new AvatarDataT(*avatar_) : nullptr); }
  messages.reserve(o.messages.size());
  for (const auto &messages_ : o.messages) { messages.emplace_back((messages_) ? new MessageT(*messages_) : nullptr); }
}

inline MessagesT &MessagesT::operator=(MessagesT o) FLATBUFFERS_NOEXCEPT {
  std::swap(avatar, o.avatar);
  std::swap(messages, o.messages);
  return *this;
}

inline MessagesT *Messages::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<MessagesT>(new MessagesT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Messages::UnPackTo(MessagesT *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = avatar(); if (_e) { _o->avatar.resize(_e->size()); for (::flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { if(_o->avatar[_i]) { _e->Get(_i)->UnPackTo(_o->avatar[_i].get(), _resolver); } else { _o->avatar[_i] = std::unique_ptr<AvatarDataT>(_e->Get(_i)->UnPack(_resolver)); }; } } else { _o->avatar.resize(0); } }
  { auto _e = messages(); if (_e) { _o->messages.resize(_e->size()); for (::flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { if(_o->messages[_i]) { _e->Get(_i)->UnPackTo(_o->messages[_i].get(), _resolver); } else { _o->messages[_i] = std::unique_ptr<MessageT>(_e->Get(_i)->UnPack(_resolver)); }; } } else { _o->messages.resize(0); } }
}

inline ::flatbuffers::Offset<Messages> Messages::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const MessagesT* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return CreateMessages(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<Messages> CreateMessages(::flatbuffers::FlatBufferBuilder &_fbb, const MessagesT *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const MessagesT* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _avatar = _o->avatar.size() ? _fbb.CreateVector<::flatbuffers::Offset<AvatarData>> (_o->avatar.size(), [](size_t i, _VectorArgs *__va) { return CreateAvatarData(*__va->__fbb, __va->__o->avatar[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _messages = _o->messages.size() ? _fbb.CreateVector<::flatbuffers::Offset<Message>> (_o->messages.size(), [](size_t i, _VectorArgs *__va) { return CreateMessage(*__va->__fbb, __va->__o->messages[i].get(), __va->__rehasher); }, &_va ) : 0;
  return CreateMessages(
      _fbb,
      _avatar,
      _messages);
}


inline bool operator==(const RequestStickyMessageT &lhs, const RequestStickyMessageT &rhs) {
  return
      (lhs.index == rhs.index) &&
      (lhs.sticky == rhs.sticky);
}

inline bool operator!=(const RequestStickyMessageT &lhs, const RequestStickyMessageT &rhs) {
    return !(lhs == rhs);
}


inline RequestStickyMessageT *RequestStickyMessage::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<RequestStickyMessageT>(new RequestStickyMessageT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void RequestStickyMessage::UnPackTo(RequestStickyMessageT *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = index(); _o->index = _e; }
  { auto _e = sticky(); _o->sticky = _e; }
}

inline ::flatbuffers::Offset<RequestStickyMessage> RequestStickyMessage::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const RequestStickyMessageT* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return CreateRequestStickyMessage(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<RequestStickyMessage> CreateRequestStickyMessage(::flatbuffers::FlatBufferBuilder &_fbb, const RequestStickyMessageT *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const RequestStickyMessageT* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _index = _o->index;
  auto _sticky = _o->sticky;
  return CreateRequestStickyMessage(
      _fbb,
      _index,
      _sticky);
}

inline const ::flatbuffers::TypeTable *MessageTypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_STRING, 0, -1 },
    { ::flatbuffers::ET_STRING, 0, -1 },
    { ::flatbuffers::ET_BOOL, 0, -1 },
    { ::flatbuffers::ET_ULONG, 0, -1 }
  };
  static const char * const names[] = {
    "username",
    "message",
    "sticky",
    "time"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 4, type_codes, nullptr, nullptr, nullptr, names
  };
  return &tt;
}

inline const ::flatbuffers::TypeTable *AvatarDataTypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_STRING, 0, -1 },
    { ::flatbuffers::ET_CHAR, 1, -1 }
  };
  static const char * const names[] = {
    "username",
    "data"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 2, type_codes, nullptr, nullptr, nullptr, names
  };
  return &tt;
}

inline const ::flatbuffers::TypeTable *MessagesTypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_SEQUENCE, 1, 0 },
    { ::flatbuffers::ET_SEQUENCE, 1, 1 }
  };
  static const ::flatbuffers::TypeFunction type_refs[] = {
    AvatarDataTypeTable,
    MessageTypeTable
  };
  static const char * const names[] = {
    "avatar",
    "messages"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 2, type_codes, type_refs, nullptr, nullptr, names
  };
  return &tt;
}

inline const ::flatbuffers::TypeTable *RequestStickyMessageTypeTable() {
  static const ::flatbuffers::TypeCode type_codes[] = {
    { ::flatbuffers::ET_INT, 0, -1 },
    { ::flatbuffers::ET_BOOL, 0, -1 }
  };
  static const char * const names[] = {
    "index",
    "sticky"
  };
  static const ::flatbuffers::TypeTable tt = {
    ::flatbuffers::ST_TABLE, 2, type_codes, nullptr, nullptr, nullptr, names
  };
  return &tt;
}

#endif  // FLATBUFFERS_GENERATED_CHAT_H_
