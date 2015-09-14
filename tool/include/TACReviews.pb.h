// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: TACReviews.proto

#ifndef PROTOBUF_TACReviews_2eproto__INCLUDED
#define PROTOBUF_TACReviews_2eproto__INCLUDED

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

namespace PHT {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_TACReviews_2eproto();
void protobuf_AssignDesc_TACReviews_2eproto();
void protobuf_ShutdownFile_TACReviews_2eproto();

class TACReviews;

// ===================================================================

class TACReviews : public ::google::protobuf::Message {
 public:
  TACReviews();
  virtual ~TACReviews();

  TACReviews(const TACReviews& from);

  inline TACReviews& operator=(const TACReviews& from) {
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
  static const TACReviews& default_instance();

  void Swap(TACReviews* other);

  // implements Message ----------------------------------------------

  TACReviews* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TACReviews& from);
  void MergeFrom(const TACReviews& from);
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

  // optional string comments = 1;
  inline bool has_comments() const;
  inline void clear_comments();
  static const int kCommentsFieldNumber = 1;
  inline const ::std::string& comments() const;
  inline void set_comments(const ::std::string& value);
  inline void set_comments(const char* value);
  inline void set_comments(const char* value, size_t size);
  inline ::std::string* mutable_comments();
  inline ::std::string* release_comments();
  inline void set_allocated_comments(::std::string* comments);

  // optional string final_grade = 2;
  inline bool has_final_grade() const;
  inline void clear_final_grade();
  static const int kFinalGradeFieldNumber = 2;
  inline const ::std::string& final_grade() const;
  inline void set_final_grade(const ::std::string& value);
  inline void set_final_grade(const char* value);
  inline void set_final_grade(const char* value, size_t size);
  inline ::std::string* mutable_final_grade();
  inline ::std::string* release_final_grade();
  inline void set_allocated_final_grade(::std::string* final_grade);

  // optional int64 tac_id = 3;
  inline bool has_tac_id() const;
  inline void clear_tac_id();
  static const int kTacIdFieldNumber = 3;
  inline ::google::protobuf::int64 tac_id() const;
  inline void set_tac_id(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:PHT.TACReviews)
 private:
  inline void set_has_comments();
  inline void clear_has_comments();
  inline void set_has_final_grade();
  inline void clear_has_final_grade();
  inline void set_has_tac_id();
  inline void clear_has_tac_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* comments_;
  ::std::string* final_grade_;
  ::google::protobuf::int64 tac_id_;
  friend void  protobuf_AddDesc_TACReviews_2eproto();
  friend void protobuf_AssignDesc_TACReviews_2eproto();
  friend void protobuf_ShutdownFile_TACReviews_2eproto();

  void InitAsDefaultInstance();
  static TACReviews* default_instance_;
};
// ===================================================================


// ===================================================================

// TACReviews

// optional string comments = 1;
inline bool TACReviews::has_comments() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TACReviews::set_has_comments() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TACReviews::clear_has_comments() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TACReviews::clear_comments() {
  if (comments_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    comments_->clear();
  }
  clear_has_comments();
}
inline const ::std::string& TACReviews::comments() const {
  // @@protoc_insertion_point(field_get:PHT.TACReviews.comments)
  return *comments_;
}
inline void TACReviews::set_comments(const ::std::string& value) {
  set_has_comments();
  if (comments_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    comments_ = new ::std::string;
  }
  comments_->assign(value);
  // @@protoc_insertion_point(field_set:PHT.TACReviews.comments)
}
inline void TACReviews::set_comments(const char* value) {
  set_has_comments();
  if (comments_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    comments_ = new ::std::string;
  }
  comments_->assign(value);
  // @@protoc_insertion_point(field_set_char:PHT.TACReviews.comments)
}
inline void TACReviews::set_comments(const char* value, size_t size) {
  set_has_comments();
  if (comments_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    comments_ = new ::std::string;
  }
  comments_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:PHT.TACReviews.comments)
}
inline ::std::string* TACReviews::mutable_comments() {
  set_has_comments();
  if (comments_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    comments_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:PHT.TACReviews.comments)
  return comments_;
}
inline ::std::string* TACReviews::release_comments() {
  clear_has_comments();
  if (comments_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = comments_;
    comments_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void TACReviews::set_allocated_comments(::std::string* comments) {
  if (comments_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete comments_;
  }
  if (comments) {
    set_has_comments();
    comments_ = comments;
  } else {
    clear_has_comments();
    comments_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:PHT.TACReviews.comments)
}

// optional string final_grade = 2;
inline bool TACReviews::has_final_grade() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TACReviews::set_has_final_grade() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TACReviews::clear_has_final_grade() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TACReviews::clear_final_grade() {
  if (final_grade_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    final_grade_->clear();
  }
  clear_has_final_grade();
}
inline const ::std::string& TACReviews::final_grade() const {
  // @@protoc_insertion_point(field_get:PHT.TACReviews.final_grade)
  return *final_grade_;
}
inline void TACReviews::set_final_grade(const ::std::string& value) {
  set_has_final_grade();
  if (final_grade_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    final_grade_ = new ::std::string;
  }
  final_grade_->assign(value);
  // @@protoc_insertion_point(field_set:PHT.TACReviews.final_grade)
}
inline void TACReviews::set_final_grade(const char* value) {
  set_has_final_grade();
  if (final_grade_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    final_grade_ = new ::std::string;
  }
  final_grade_->assign(value);
  // @@protoc_insertion_point(field_set_char:PHT.TACReviews.final_grade)
}
inline void TACReviews::set_final_grade(const char* value, size_t size) {
  set_has_final_grade();
  if (final_grade_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    final_grade_ = new ::std::string;
  }
  final_grade_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:PHT.TACReviews.final_grade)
}
inline ::std::string* TACReviews::mutable_final_grade() {
  set_has_final_grade();
  if (final_grade_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    final_grade_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:PHT.TACReviews.final_grade)
  return final_grade_;
}
inline ::std::string* TACReviews::release_final_grade() {
  clear_has_final_grade();
  if (final_grade_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = final_grade_;
    final_grade_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void TACReviews::set_allocated_final_grade(::std::string* final_grade) {
  if (final_grade_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete final_grade_;
  }
  if (final_grade) {
    set_has_final_grade();
    final_grade_ = final_grade;
  } else {
    clear_has_final_grade();
    final_grade_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:PHT.TACReviews.final_grade)
}

// optional int64 tac_id = 3;
inline bool TACReviews::has_tac_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TACReviews::set_has_tac_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TACReviews::clear_has_tac_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TACReviews::clear_tac_id() {
  tac_id_ = GOOGLE_LONGLONG(0);
  clear_has_tac_id();
}
inline ::google::protobuf::int64 TACReviews::tac_id() const {
  // @@protoc_insertion_point(field_get:PHT.TACReviews.tac_id)
  return tac_id_;
}
inline void TACReviews::set_tac_id(::google::protobuf::int64 value) {
  set_has_tac_id();
  tac_id_ = value;
  // @@protoc_insertion_point(field_set:PHT.TACReviews.tac_id)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace PHT

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_TACReviews_2eproto__INCLUDED
