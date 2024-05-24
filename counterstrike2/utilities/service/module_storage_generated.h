// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_MODULESTORAGE_H_
#define FLATBUFFERS_GENERATED_MODULESTORAGE_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 5 &&
              FLATBUFFERS_VERSION_REVISION == 26,
             "Non-compatible flatbuffers version included");

struct ModuleStorage;
struct ModuleStorageBuilder;

struct ModuleStorage FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef ModuleStorageBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_MODULES = 4
  };
  const ::flatbuffers::Vector<uint64_t> *modules() const {
    return GetPointer<const ::flatbuffers::Vector<uint64_t> *>(VT_MODULES);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_MODULES) &&
           verifier.VerifyVector(modules()) &&
           verifier.EndTable();
  }
};

struct ModuleStorageBuilder {
  typedef ModuleStorage Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_modules(::flatbuffers::Offset<::flatbuffers::Vector<uint64_t>> modules) {
    fbb_.AddOffset(ModuleStorage::VT_MODULES, modules);
  }
  explicit ModuleStorageBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<ModuleStorage> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<ModuleStorage>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<ModuleStorage> CreateModuleStorage(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::Vector<uint64_t>> modules = 0) {
  ModuleStorageBuilder builder_(_fbb);
  builder_.add_modules(modules);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<ModuleStorage> CreateModuleStorageDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<uint64_t> *modules = nullptr) {
  auto modules__ = modules ? _fbb.CreateVector<uint64_t>(*modules) : 0;
  return CreateModuleStorage(
      _fbb,
      modules__);
}

#endif  // FLATBUFFERS_GENERATED_MODULESTORAGE_H_
