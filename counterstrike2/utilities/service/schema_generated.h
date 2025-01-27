// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_SCHEMA_H_
#define FLATBUFFERS_GENERATED_SCHEMA_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 5 &&
              FLATBUFFERS_VERSION_REVISION == 26,
             "Non-compatible flatbuffers version included");

struct Field;
struct FieldBuilder;

struct Schema;
struct SchemaBuilder;

struct SchemaClass;
struct SchemaClassBuilder;

struct Field FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef FieldBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_OFFSET = 6,
    VT_KEY = 8,
    VT_HASH_KEY = 10
  };
  uint64_t name() const {
    return GetField<uint64_t>(VT_NAME, 0);
  }
  uint64_t offset() const {
    return GetField<uint64_t>(VT_OFFSET, 0);
  }
  uint64_t key() const {
    return GetField<uint64_t>(VT_KEY, 0);
  }
  uint64_t hash_key() const {
    return GetField<uint64_t>(VT_HASH_KEY, 0);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_NAME, 8) &&
           VerifyField<uint64_t>(verifier, VT_OFFSET, 8) &&
           VerifyField<uint64_t>(verifier, VT_KEY, 8) &&
           VerifyField<uint64_t>(verifier, VT_HASH_KEY, 8) &&
           verifier.EndTable();
  }
};

struct FieldBuilder {
  typedef Field Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_name(uint64_t name) {
    fbb_.AddElement<uint64_t>(Field::VT_NAME, name, 0);
  }
  void add_offset(uint64_t offset) {
    fbb_.AddElement<uint64_t>(Field::VT_OFFSET, offset, 0);
  }
  void add_key(uint64_t key) {
    fbb_.AddElement<uint64_t>(Field::VT_KEY, key, 0);
  }
  void add_hash_key(uint64_t hash_key) {
    fbb_.AddElement<uint64_t>(Field::VT_HASH_KEY, hash_key, 0);
  }
  explicit FieldBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Field> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Field>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Field> CreateField(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t name = 0,
    uint64_t offset = 0,
    uint64_t key = 0,
    uint64_t hash_key = 0) {
  FieldBuilder builder_(_fbb);
  builder_.add_hash_key(hash_key);
  builder_.add_key(key);
  builder_.add_offset(offset);
  builder_.add_name(name);
  return builder_.Finish();
}

struct Schema FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef SchemaBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_BINARY_NAME = 4,
    VT_FIELDS = 6
  };
  uint64_t binary_name() const {
    return GetField<uint64_t>(VT_BINARY_NAME, 0);
  }
  const ::flatbuffers::Vector<::flatbuffers::Offset<Field>> *fields() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<Field>> *>(VT_FIELDS);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_BINARY_NAME, 8) &&
           VerifyOffset(verifier, VT_FIELDS) &&
           verifier.VerifyVector(fields()) &&
           verifier.VerifyVectorOfTables(fields()) &&
           verifier.EndTable();
  }
};

struct SchemaBuilder {
  typedef Schema Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_binary_name(uint64_t binary_name) {
    fbb_.AddElement<uint64_t>(Schema::VT_BINARY_NAME, binary_name, 0);
  }
  void add_fields(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Field>>> fields) {
    fbb_.AddOffset(Schema::VT_FIELDS, fields);
  }
  explicit SchemaBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Schema> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Schema>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Schema> CreateSchema(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t binary_name = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Field>>> fields = 0) {
  SchemaBuilder builder_(_fbb);
  builder_.add_binary_name(binary_name);
  builder_.add_fields(fields);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Schema> CreateSchemaDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t binary_name = 0,
    const std::vector<::flatbuffers::Offset<Field>> *fields = nullptr) {
  auto fields__ = fields ? _fbb.CreateVector<::flatbuffers::Offset<Field>>(*fields) : 0;
  return CreateSchema(
      _fbb,
      binary_name,
      fields__);
}

struct SchemaClass FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef SchemaClassBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_SCHEMA = 4
  };
  const ::flatbuffers::Vector<::flatbuffers::Offset<Schema>> *schema() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<Schema>> *>(VT_SCHEMA);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_SCHEMA) &&
           verifier.VerifyVector(schema()) &&
           verifier.VerifyVector(schema()) &&
           verifier.VerifyVectorOfTables(schema()) &&
           verifier.EndTable();
  }
};

struct SchemaClassBuilder {
  typedef SchemaClass Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_schema(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Schema>>> schema) {
    fbb_.AddOffset(SchemaClass::VT_SCHEMA, schema);
  }
  explicit SchemaClassBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<SchemaClass> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<SchemaClass>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<SchemaClass> CreateSchemaClass(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Schema>>> schema = 0) {
  SchemaClassBuilder builder_(_fbb);
  builder_.add_schema(schema);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<SchemaClass> CreateSchemaClassDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<::flatbuffers::Offset<Schema>> *schema = nullptr) {
  auto schema__ = schema ? _fbb.CreateVector<::flatbuffers::Offset<Schema>>(*schema) : 0;
  return CreateSchemaClass(
      _fbb,
      schema__);
}

#endif  // FLATBUFFERS_GENERATED_SCHEMA_H_
