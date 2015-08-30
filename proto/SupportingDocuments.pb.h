// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SupportingDocuments.proto

#ifndef PROTOBUF_SupportingDocuments_2eproto__INCLUDED
#define PROTOBUF_SupportingDocuments_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_SupportingDocuments_2eproto();
void protobuf_AssignDesc_SupportingDocuments_2eproto();
void protobuf_ShutdownFile_SupportingDocuments_2eproto();

class SupportingDocuments;

// ===================================================================

class SupportingDocuments : public ::google::protobuf::Message {
 public:
  SupportingDocuments();
  virtual ~SupportingDocuments();

  SupportingDocuments(const SupportingDocuments& from);

  inline SupportingDocuments& operator=(const SupportingDocuments& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const SupportingDocuments& default_instance();

  void Swap(SupportingDocuments* other);

  // implements Message ----------------------------------------------

  SupportingDocuments* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SupportingDocuments& from);
  void MergeFrom(const SupportingDocuments& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string preprints = 1;
  inline bool has_preprints() const;
  inline void clear_preprints();
  static const int kPreprintsFieldNumber = 1;
  inline const ::std::string& preprints() const;
  inline void set_preprints(const ::std::string& value);
  inline void set_preprints(const char* value);
  inline void set_preprints(const char* value, size_t size);
  inline ::std::string* mutable_preprints();
  inline ::std::string* release_preprints();
  inline void set_allocated_preprints(::std::string* preprints);

  // optional string scientific_justification = 2;
  inline bool has_scientific_justification() const;
  inline void clear_scientific_justification();
  static const int kScientificJustificationFieldNumber = 2;
  inline const ::std::string& scientific_justification() const;
  inline void set_scientific_justification(const ::std::string& value);
  inline void set_scientific_justification(const char* value);
  inline void set_scientific_justification(const char* value, size_t size);
  inline ::std::string* mutable_scientific_justification();
  inline ::std::string* release_scientific_justification();
  inline void set_allocated_scientific_justification(::std::string* scientific_justification);

  // optional string technical_justification = 3;
  inline bool has_technical_justification() const;
  inline void clear_technical_justification();
  static const int kTechnicalJustificationFieldNumber = 3;
  inline const ::std::string& technical_justification() const;
  inline void set_technical_justification(const ::std::string& value);
  inline void set_technical_justification(const char* value);
  inline void set_technical_justification(const char* value, size_t size);
  inline ::std::string* mutable_technical_justification();
  inline ::std::string* release_technical_justification();
  inline void set_allocated_technical_justification(::std::string* technical_justification);

  // @@protoc_insertion_point(class_scope:SupportingDocuments)
 private:
  inline void set_has_preprints();
  inline void clear_has_preprints();
  inline void set_has_scientific_justification();
  inline void clear_has_scientific_justification();
  inline void set_has_technical_justification();
  inline void clear_has_technical_justification();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* preprints_;
  ::std::string* scientific_justification_;
  ::std::string* technical_justification_;
  friend void  protobuf_AddDesc_SupportingDocuments_2eproto();
  friend void protobuf_AssignDesc_SupportingDocuments_2eproto();
  friend void protobuf_ShutdownFile_SupportingDocuments_2eproto();

  void InitAsDefaultInstance();
  static SupportingDocuments* default_instance_;
};
// ===================================================================


// ===================================================================

// SupportingDocuments

// optional string preprints = 1;
inline bool SupportingDocuments::has_preprints() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SupportingDocuments::set_has_preprints() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SupportingDocuments::clear_has_preprints() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SupportingDocuments::clear_preprints() {
  if (preprints_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    preprints_->clear();
  }
  clear_has_preprints();
}
inline const ::std::string& SupportingDocuments::preprints() const {
  // @@protoc_insertion_point(field_get:SupportingDocuments.preprints)
  return *preprints_;
}
inline void SupportingDocuments::set_preprints(const ::std::string& value) {
  set_has_preprints();
  if (preprints_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    preprints_ = new ::std::string;
  }
  preprints_->assign(value);
  // @@protoc_insertion_point(field_set:SupportingDocuments.preprints)
}
inline void SupportingDocuments::set_preprints(const char* value) {
  set_has_preprints();
  if (preprints_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    preprints_ = new ::std::string;
  }
  preprints_->assign(value);
  // @@protoc_insertion_point(field_set_char:SupportingDocuments.preprints)
}
inline void SupportingDocuments::set_preprints(const char* value, size_t size) {
  set_has_preprints();
  if (preprints_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    preprints_ = new ::std::string;
  }
  preprints_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:SupportingDocuments.preprints)
}
inline ::std::string* SupportingDocuments::mutable_preprints() {
  set_has_preprints();
  if (preprints_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    preprints_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:SupportingDocuments.preprints)
  return preprints_;
}
inline ::std::string* SupportingDocuments::release_preprints() {
  clear_has_preprints();
  if (preprints_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = preprints_;
    preprints_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void SupportingDocuments::set_allocated_preprints(::std::string* preprints) {
  if (preprints_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete preprints_;
  }
  if (preprints) {
    set_has_preprints();
    preprints_ = preprints;
  } else {
    clear_has_preprints();
    preprints_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:SupportingDocuments.preprints)
}

// optional string scientific_justification = 2;
inline bool SupportingDocuments::has_scientific_justification() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SupportingDocuments::set_has_scientific_justification() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SupportingDocuments::clear_has_scientific_justification() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SupportingDocuments::clear_scientific_justification() {
  if (scientific_justification_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    scientific_justification_->clear();
  }
  clear_has_scientific_justification();
}
inline const ::std::string& SupportingDocuments::scientific_justification() const {
  // @@protoc_insertion_point(field_get:SupportingDocuments.scientific_justification)
  return *scientific_justification_;
}
inline void SupportingDocuments::set_scientific_justification(const ::std::string& value) {
  set_has_scientific_justification();
  if (scientific_justification_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    scientific_justification_ = new ::std::string;
  }
  scientific_justification_->assign(value);
  // @@protoc_insertion_point(field_set:SupportingDocuments.scientific_justification)
}
inline void SupportingDocuments::set_scientific_justification(const char* value) {
  set_has_scientific_justification();
  if (scientific_justification_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    scientific_justification_ = new ::std::string;
  }
  scientific_justification_->assign(value);
  // @@protoc_insertion_point(field_set_char:SupportingDocuments.scientific_justification)
}
inline void SupportingDocuments::set_scientific_justification(const char* value, size_t size) {
  set_has_scientific_justification();
  if (scientific_justification_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    scientific_justification_ = new ::std::string;
  }
  scientific_justification_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:SupportingDocuments.scientific_justification)
}
inline ::std::string* SupportingDocuments::mutable_scientific_justification() {
  set_has_scientific_justification();
  if (scientific_justification_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    scientific_justification_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:SupportingDocuments.scientific_justification)
  return scientific_justification_;
}
inline ::std::string* SupportingDocuments::release_scientific_justification() {
  clear_has_scientific_justification();
  if (scientific_justification_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = scientific_justification_;
    scientific_justification_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void SupportingDocuments::set_allocated_scientific_justification(::std::string* scientific_justification) {
  if (scientific_justification_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete scientific_justification_;
  }
  if (scientific_justification) {
    set_has_scientific_justification();
    scientific_justification_ = scientific_justification;
  } else {
    clear_has_scientific_justification();
    scientific_justification_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:SupportingDocuments.scientific_justification)
}

// optional string technical_justification = 3;
inline bool SupportingDocuments::has_technical_justification() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void SupportingDocuments::set_has_technical_justification() {
  _has_bits_[0] |= 0x00000004u;
}
inline void SupportingDocuments::clear_has_technical_justification() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void SupportingDocuments::clear_technical_justification() {
  if (technical_justification_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    technical_justification_->clear();
  }
  clear_has_technical_justification();
}
inline const ::std::string& SupportingDocuments::technical_justification() const {
  // @@protoc_insertion_point(field_get:SupportingDocuments.technical_justification)
  return *technical_justification_;
}
inline void SupportingDocuments::set_technical_justification(const ::std::string& value) {
  set_has_technical_justification();
  if (technical_justification_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    technical_justification_ = new ::std::string;
  }
  technical_justification_->assign(value);
  // @@protoc_insertion_point(field_set:SupportingDocuments.technical_justification)
}
inline void SupportingDocuments::set_technical_justification(const char* value) {
  set_has_technical_justification();
  if (technical_justification_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    technical_justification_ = new ::std::string;
  }
  technical_justification_->assign(value);
  // @@protoc_insertion_point(field_set_char:SupportingDocuments.technical_justification)
}
inline void SupportingDocuments::set_technical_justification(const char* value, size_t size) {
  set_has_technical_justification();
  if (technical_justification_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    technical_justification_ = new ::std::string;
  }
  technical_justification_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:SupportingDocuments.technical_justification)
}
inline ::std::string* SupportingDocuments::mutable_technical_justification() {
  set_has_technical_justification();
  if (technical_justification_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    technical_justification_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:SupportingDocuments.technical_justification)
  return technical_justification_;
}
inline ::std::string* SupportingDocuments::release_technical_justification() {
  clear_has_technical_justification();
  if (technical_justification_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = technical_justification_;
    technical_justification_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void SupportingDocuments::set_allocated_technical_justification(::std::string* technical_justification) {
  if (technical_justification_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete technical_justification_;
  }
  if (technical_justification) {
    set_has_technical_justification();
    technical_justification_ = technical_justification;
  } else {
    clear_has_technical_justification();
    technical_justification_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:SupportingDocuments.technical_justification)
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_SupportingDocuments_2eproto__INCLUDED
