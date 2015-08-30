// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Reviews.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Reviews.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* Reviews_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Reviews_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Reviews_2eproto() {
  protobuf_AddDesc_Reviews_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Reviews.proto");
  GOOGLE_CHECK(file != NULL);
  Reviews_descriptor_ = file->message_type(0);
  static const int Reviews_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Reviews, grade_rank_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Reviews, proposal_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Reviews, review_comments_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Reviews, reviewer_id_),
  };
  Reviews_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Reviews_descriptor_,
      Reviews::default_instance_,
      Reviews_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Reviews, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Reviews, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Reviews));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Reviews_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Reviews_descriptor_, &Reviews::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Reviews_2eproto() {
  delete Reviews::default_instance_;
  delete Reviews_reflection_;
}

void protobuf_AddDesc_Reviews_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rReviews.proto\"`\n\007Reviews\022\022\n\ngrade_rank"
    "\030\001 \001(\t\022\023\n\013proposal_id\030\002 \001(\003\022\027\n\017review_co"
    "mments\030\003 \001(\t\022\023\n\013reviewer_id\030\004 \001(\003", 113);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Reviews.proto", &protobuf_RegisterTypes);
  Reviews::default_instance_ = new Reviews();
  Reviews::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Reviews_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Reviews_2eproto {
  StaticDescriptorInitializer_Reviews_2eproto() {
    protobuf_AddDesc_Reviews_2eproto();
  }
} static_descriptor_initializer_Reviews_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Reviews::kGradeRankFieldNumber;
const int Reviews::kProposalIdFieldNumber;
const int Reviews::kReviewCommentsFieldNumber;
const int Reviews::kReviewerIdFieldNumber;
#endif  // !_MSC_VER

Reviews::Reviews()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Reviews)
}

void Reviews::InitAsDefaultInstance() {
}

Reviews::Reviews(const Reviews& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Reviews)
}

void Reviews::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  grade_rank_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  proposal_id_ = GOOGLE_LONGLONG(0);
  review_comments_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  reviewer_id_ = GOOGLE_LONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Reviews::~Reviews() {
  // @@protoc_insertion_point(destructor:Reviews)
  SharedDtor();
}

void Reviews::SharedDtor() {
  if (grade_rank_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete grade_rank_;
  }
  if (review_comments_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete review_comments_;
  }
  if (this != default_instance_) {
  }
}

void Reviews::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Reviews::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Reviews_descriptor_;
}

const Reviews& Reviews::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Reviews_2eproto();
  return *default_instance_;
}

Reviews* Reviews::default_instance_ = NULL;

Reviews* Reviews::New() const {
  return new Reviews;
}

void Reviews::Clear() {
  if (_has_bits_[0 / 32] & 15) {
    if (has_grade_rank()) {
      if (grade_rank_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        grade_rank_->clear();
      }
    }
    proposal_id_ = GOOGLE_LONGLONG(0);
    if (has_review_comments()) {
      if (review_comments_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        review_comments_->clear();
      }
    }
    reviewer_id_ = GOOGLE_LONGLONG(0);
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Reviews::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Reviews)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string grade_rank = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_grade_rank()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->grade_rank().data(), this->grade_rank().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "grade_rank");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_proposal_id;
        break;
      }

      // optional int64 proposal_id = 2;
      case 2: {
        if (tag == 16) {
         parse_proposal_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &proposal_id_)));
          set_has_proposal_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_review_comments;
        break;
      }

      // optional string review_comments = 3;
      case 3: {
        if (tag == 26) {
         parse_review_comments:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_review_comments()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->review_comments().data(), this->review_comments().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "review_comments");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_reviewer_id;
        break;
      }

      // optional int64 reviewer_id = 4;
      case 4: {
        if (tag == 32) {
         parse_reviewer_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &reviewer_id_)));
          set_has_reviewer_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Reviews)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Reviews)
  return false;
#undef DO_
}

void Reviews::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Reviews)
  // optional string grade_rank = 1;
  if (has_grade_rank()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->grade_rank().data(), this->grade_rank().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "grade_rank");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->grade_rank(), output);
  }

  // optional int64 proposal_id = 2;
  if (has_proposal_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(2, this->proposal_id(), output);
  }

  // optional string review_comments = 3;
  if (has_review_comments()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->review_comments().data(), this->review_comments().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "review_comments");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->review_comments(), output);
  }

  // optional int64 reviewer_id = 4;
  if (has_reviewer_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(4, this->reviewer_id(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Reviews)
}

::google::protobuf::uint8* Reviews::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Reviews)
  // optional string grade_rank = 1;
  if (has_grade_rank()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->grade_rank().data(), this->grade_rank().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "grade_rank");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->grade_rank(), target);
  }

  // optional int64 proposal_id = 2;
  if (has_proposal_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(2, this->proposal_id(), target);
  }

  // optional string review_comments = 3;
  if (has_review_comments()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->review_comments().data(), this->review_comments().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "review_comments");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->review_comments(), target);
  }

  // optional int64 reviewer_id = 4;
  if (has_reviewer_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(4, this->reviewer_id(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Reviews)
  return target;
}

int Reviews::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string grade_rank = 1;
    if (has_grade_rank()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->grade_rank());
    }

    // optional int64 proposal_id = 2;
    if (has_proposal_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->proposal_id());
    }

    // optional string review_comments = 3;
    if (has_review_comments()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->review_comments());
    }

    // optional int64 reviewer_id = 4;
    if (has_reviewer_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->reviewer_id());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Reviews::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Reviews* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Reviews*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Reviews::MergeFrom(const Reviews& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_grade_rank()) {
      set_grade_rank(from.grade_rank());
    }
    if (from.has_proposal_id()) {
      set_proposal_id(from.proposal_id());
    }
    if (from.has_review_comments()) {
      set_review_comments(from.review_comments());
    }
    if (from.has_reviewer_id()) {
      set_reviewer_id(from.reviewer_id());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Reviews::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Reviews::CopyFrom(const Reviews& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Reviews::IsInitialized() const {

  return true;
}

void Reviews::Swap(Reviews* other) {
  if (other != this) {
    std::swap(grade_rank_, other->grade_rank_);
    std::swap(proposal_id_, other->proposal_id_);
    std::swap(review_comments_, other->review_comments_);
    std::swap(reviewer_id_, other->reviewer_id_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Reviews::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Reviews_descriptor_;
  metadata.reflection = Reviews_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
