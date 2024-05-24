// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_REQUEST_H_
#define FLATBUFFERS_GENERATED_REQUEST_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 5 &&
              FLATBUFFERS_VERSION_REVISION == 26,
             "Non-compatible flatbuffers version included");

struct Request;
struct RequestBuilder;

struct Request FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef RequestBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TYPE = 4,
    VT_GAME = 6,
    VT_DATA = 8
  };
  uint64_t type() const {
    return GetField<uint64_t>(VT_TYPE, 0);
  }
  int32_t game() const {
    return GetField<int32_t>(VT_GAME, 0);
  }
  const ::flatbuffers::Vector<int8_t> *data() const {
    return GetPointer<const ::flatbuffers::Vector<int8_t> *>(VT_DATA);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_TYPE, 8) &&
           VerifyField<int32_t>(verifier, VT_GAME, 4) &&
           VerifyOffset(verifier, VT_DATA) &&
           verifier.VerifyVector(data()) &&
           verifier.EndTable();
  }
};

struct RequestBuilder {
  typedef Request Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_type(uint64_t type) {
    fbb_.AddElement<uint64_t>(Request::VT_TYPE, type, 0);
  }
  void add_game(int32_t game) {
    fbb_.AddElement<int32_t>(Request::VT_GAME, game, 0);
  }
  void add_data(::flatbuffers::Offset<::flatbuffers::Vector<int8_t>> data) {
    fbb_.AddOffset(Request::VT_DATA, data);
  }
  explicit RequestBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Request> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Request>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Request> CreateRequest(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t type = 0,
    int32_t game = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<int8_t>> data = 0) {
  RequestBuilder builder_(_fbb);
  builder_.add_type(type);
  builder_.add_data(data);
  builder_.add_game(game);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Request> CreateRequestDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t type = 0,
    int32_t game = 0,
    const std::vector<int8_t> *data = nullptr) {
  auto data__ = data ? _fbb.CreateVector<int8_t>(*data) : 0;
  return CreateRequest(
      _fbb,
      type,
      game,
      data__);
}

#endif  // FLATBUFFERS_GENERATED_REQUEST_H_
