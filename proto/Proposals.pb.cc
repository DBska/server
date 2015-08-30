// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Proposals.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Proposals.pb.h"

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

const ::google::protobuf::Descriptor* Proposals_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Proposals_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Proposals_2eproto() {
  protobuf_AddDesc_Proposals_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Proposals.proto");
  GOOGLE_CHECK(file != NULL);
  Proposals_descriptor_ = file->message_type(0);
  static const int Proposals_offsets_[11] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Proposals, abstract_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Proposals, more_info_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Proposals, proposal_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Proposals, proposal_status_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Proposals, proposal_type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Proposals, m_coauthors_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Proposals, m_proposaleditors_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Proposals, m_tacreviews_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Proposals, m_reviews_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Proposals, m_supportingdocuments_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Proposals, m_sciencegoals_),
  };
  Proposals_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Proposals_descriptor_,
      Proposals::default_instance_,
      Proposals_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Proposals, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Proposals, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Proposals));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Proposals_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Proposals_descriptor_, &Proposals::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Proposals_2eproto() {
  delete Proposals::default_instance_;
  delete Proposals_reflection_;
}

void protobuf_AddDesc_Proposals_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::protobuf_AddDesc_ProposalStatus_2eproto();
  ::protobuf_AddDesc_ProposalType_2eproto();
  ::protobuf_AddDesc_CoAuthors_2eproto();
  ::protobuf_AddDesc_ProposalEditors_2eproto();
  ::protobuf_AddDesc_Reviews_2eproto();
  ::protobuf_AddDesc_ScienceGoals_2eproto();
  ::protobuf_AddDesc_SupportingDocuments_2eproto();
  ::protobuf_AddDesc_TACReviews_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017Proposals.proto\032\024ProposalStatus.proto\032"
    "\022ProposalType.proto\032\017CoAuthors.proto\032\025Pr"
    "oposalEditors.proto\032\rReviews.proto\032\022Scie"
    "nceGoals.proto\032\031SupportingDocuments.prot"
    "o\032\020TACReviews.proto\"\377\002\n\tProposals\022\020\n\010abs"
    "tract\030\001 \001(\t\022\021\n\tmore_info\030\002 \001(\t\022\023\n\013propos"
    "al_id\030\003 \001(\t\022(\n\017proposal_status\030\004 \001(\0162\017.P"
    "roposalStatus\022$\n\rproposal_type\030\005 \001(\0162\r.P"
    "roposalType\022\037\n\013m_CoAuthors\030\006 \001(\0132\n.CoAut"
    "hors\022+\n\021m_ProposalEditors\030\007 \001(\0132\020.Propos"
    "alEditors\022!\n\014m_TACReviews\030\010 \001(\0132\013.TACRev"
    "iews\022\033\n\tm_Reviews\030\t \001(\0132\010.Reviews\0223\n\025m_S"
    "upportingDocuments\030\n \001(\0132\024.SupportingDoc"
    "uments\022%\n\016m_ScienceGoals\030\013 \001(\0132\r.Science"
    "Goals", 565);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Proposals.proto", &protobuf_RegisterTypes);
  Proposals::default_instance_ = new Proposals();
  Proposals::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Proposals_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Proposals_2eproto {
  StaticDescriptorInitializer_Proposals_2eproto() {
    protobuf_AddDesc_Proposals_2eproto();
  }
} static_descriptor_initializer_Proposals_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Proposals::kAbstractFieldNumber;
const int Proposals::kMoreInfoFieldNumber;
const int Proposals::kProposalIdFieldNumber;
const int Proposals::kProposalStatusFieldNumber;
const int Proposals::kProposalTypeFieldNumber;
const int Proposals::kMCoAuthorsFieldNumber;
const int Proposals::kMProposalEditorsFieldNumber;
const int Proposals::kMTACReviewsFieldNumber;
const int Proposals::kMReviewsFieldNumber;
const int Proposals::kMSupportingDocumentsFieldNumber;
const int Proposals::kMScienceGoalsFieldNumber;
#endif  // !_MSC_VER

Proposals::Proposals()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Proposals)
}

void Proposals::InitAsDefaultInstance() {
  m_coauthors_ = const_cast< ::CoAuthors*>(&::CoAuthors::default_instance());
  m_proposaleditors_ = const_cast< ::ProposalEditors*>(&::ProposalEditors::default_instance());
  m_tacreviews_ = const_cast< ::TACReviews*>(&::TACReviews::default_instance());
  m_reviews_ = const_cast< ::Reviews*>(&::Reviews::default_instance());
  m_supportingdocuments_ = const_cast< ::SupportingDocuments*>(&::SupportingDocuments::default_instance());
  m_sciencegoals_ = const_cast< ::ScienceGoals*>(&::ScienceGoals::default_instance());
}

Proposals::Proposals(const Proposals& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Proposals)
}

void Proposals::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  abstract_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  more_info_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  proposal_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  proposal_status_ = 0;
  proposal_type_ = 0;
  m_coauthors_ = NULL;
  m_proposaleditors_ = NULL;
  m_tacreviews_ = NULL;
  m_reviews_ = NULL;
  m_supportingdocuments_ = NULL;
  m_sciencegoals_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Proposals::~Proposals() {
  // @@protoc_insertion_point(destructor:Proposals)
  SharedDtor();
}

void Proposals::SharedDtor() {
  if (abstract_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete abstract_;
  }
  if (more_info_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete more_info_;
  }
  if (proposal_id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete proposal_id_;
  }
  if (this != default_instance_) {
    delete m_coauthors_;
    delete m_proposaleditors_;
    delete m_tacreviews_;
    delete m_reviews_;
    delete m_supportingdocuments_;
    delete m_sciencegoals_;
  }
}

void Proposals::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Proposals::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Proposals_descriptor_;
}

const Proposals& Proposals::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Proposals_2eproto();
  return *default_instance_;
}

Proposals* Proposals::default_instance_ = NULL;

Proposals* Proposals::New() const {
  return new Proposals;
}

void Proposals::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Proposals*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 255) {
    ZR_(proposal_status_, proposal_type_);
    if (has_abstract()) {
      if (abstract_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        abstract_->clear();
      }
    }
    if (has_more_info()) {
      if (more_info_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        more_info_->clear();
      }
    }
    if (has_proposal_id()) {
      if (proposal_id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        proposal_id_->clear();
      }
    }
    if (has_m_coauthors()) {
      if (m_coauthors_ != NULL) m_coauthors_->::CoAuthors::Clear();
    }
    if (has_m_proposaleditors()) {
      if (m_proposaleditors_ != NULL) m_proposaleditors_->::ProposalEditors::Clear();
    }
    if (has_m_tacreviews()) {
      if (m_tacreviews_ != NULL) m_tacreviews_->::TACReviews::Clear();
    }
  }
  if (_has_bits_[8 / 32] & 1792) {
    if (has_m_reviews()) {
      if (m_reviews_ != NULL) m_reviews_->::Reviews::Clear();
    }
    if (has_m_supportingdocuments()) {
      if (m_supportingdocuments_ != NULL) m_supportingdocuments_->::SupportingDocuments::Clear();
    }
    if (has_m_sciencegoals()) {
      if (m_sciencegoals_ != NULL) m_sciencegoals_->::ScienceGoals::Clear();
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Proposals::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Proposals)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string abstract = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_abstract()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->abstract().data(), this->abstract().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "abstract");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_more_info;
        break;
      }

      // optional string more_info = 2;
      case 2: {
        if (tag == 18) {
         parse_more_info:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_more_info()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->more_info().data(), this->more_info().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "more_info");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_proposal_id;
        break;
      }

      // optional string proposal_id = 3;
      case 3: {
        if (tag == 26) {
         parse_proposal_id:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_proposal_id()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->proposal_id().data(), this->proposal_id().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "proposal_id");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_proposal_status;
        break;
      }

      // optional .ProposalStatus proposal_status = 4;
      case 4: {
        if (tag == 32) {
         parse_proposal_status:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::ProposalStatus_IsValid(value)) {
            set_proposal_status(static_cast< ::ProposalStatus >(value));
          } else {
            mutable_unknown_fields()->AddVarint(4, value);
          }
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_proposal_type;
        break;
      }

      // optional .ProposalType proposal_type = 5;
      case 5: {
        if (tag == 40) {
         parse_proposal_type:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::ProposalType_IsValid(value)) {
            set_proposal_type(static_cast< ::ProposalType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(5, value);
          }
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(50)) goto parse_m_CoAuthors;
        break;
      }

      // optional .CoAuthors m_CoAuthors = 6;
      case 6: {
        if (tag == 50) {
         parse_m_CoAuthors:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_m_coauthors()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(58)) goto parse_m_ProposalEditors;
        break;
      }

      // optional .ProposalEditors m_ProposalEditors = 7;
      case 7: {
        if (tag == 58) {
         parse_m_ProposalEditors:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_m_proposaleditors()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(66)) goto parse_m_TACReviews;
        break;
      }

      // optional .TACReviews m_TACReviews = 8;
      case 8: {
        if (tag == 66) {
         parse_m_TACReviews:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_m_tacreviews()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(74)) goto parse_m_Reviews;
        break;
      }

      // optional .Reviews m_Reviews = 9;
      case 9: {
        if (tag == 74) {
         parse_m_Reviews:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_m_reviews()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(82)) goto parse_m_SupportingDocuments;
        break;
      }

      // optional .SupportingDocuments m_SupportingDocuments = 10;
      case 10: {
        if (tag == 82) {
         parse_m_SupportingDocuments:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_m_supportingdocuments()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(90)) goto parse_m_ScienceGoals;
        break;
      }

      // optional .ScienceGoals m_ScienceGoals = 11;
      case 11: {
        if (tag == 90) {
         parse_m_ScienceGoals:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_m_sciencegoals()));
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
  // @@protoc_insertion_point(parse_success:Proposals)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Proposals)
  return false;
#undef DO_
}

void Proposals::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Proposals)
  // optional string abstract = 1;
  if (has_abstract()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->abstract().data(), this->abstract().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "abstract");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->abstract(), output);
  }

  // optional string more_info = 2;
  if (has_more_info()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->more_info().data(), this->more_info().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "more_info");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->more_info(), output);
  }

  // optional string proposal_id = 3;
  if (has_proposal_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->proposal_id().data(), this->proposal_id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "proposal_id");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->proposal_id(), output);
  }

  // optional .ProposalStatus proposal_status = 4;
  if (has_proposal_status()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      4, this->proposal_status(), output);
  }

  // optional .ProposalType proposal_type = 5;
  if (has_proposal_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      5, this->proposal_type(), output);
  }

  // optional .CoAuthors m_CoAuthors = 6;
  if (has_m_coauthors()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      6, this->m_coauthors(), output);
  }

  // optional .ProposalEditors m_ProposalEditors = 7;
  if (has_m_proposaleditors()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      7, this->m_proposaleditors(), output);
  }

  // optional .TACReviews m_TACReviews = 8;
  if (has_m_tacreviews()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      8, this->m_tacreviews(), output);
  }

  // optional .Reviews m_Reviews = 9;
  if (has_m_reviews()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      9, this->m_reviews(), output);
  }

  // optional .SupportingDocuments m_SupportingDocuments = 10;
  if (has_m_supportingdocuments()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      10, this->m_supportingdocuments(), output);
  }

  // optional .ScienceGoals m_ScienceGoals = 11;
  if (has_m_sciencegoals()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      11, this->m_sciencegoals(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Proposals)
}

::google::protobuf::uint8* Proposals::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Proposals)
  // optional string abstract = 1;
  if (has_abstract()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->abstract().data(), this->abstract().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "abstract");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->abstract(), target);
  }

  // optional string more_info = 2;
  if (has_more_info()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->more_info().data(), this->more_info().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "more_info");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->more_info(), target);
  }

  // optional string proposal_id = 3;
  if (has_proposal_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->proposal_id().data(), this->proposal_id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "proposal_id");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->proposal_id(), target);
  }

  // optional .ProposalStatus proposal_status = 4;
  if (has_proposal_status()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      4, this->proposal_status(), target);
  }

  // optional .ProposalType proposal_type = 5;
  if (has_proposal_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      5, this->proposal_type(), target);
  }

  // optional .CoAuthors m_CoAuthors = 6;
  if (has_m_coauthors()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        6, this->m_coauthors(), target);
  }

  // optional .ProposalEditors m_ProposalEditors = 7;
  if (has_m_proposaleditors()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        7, this->m_proposaleditors(), target);
  }

  // optional .TACReviews m_TACReviews = 8;
  if (has_m_tacreviews()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        8, this->m_tacreviews(), target);
  }

  // optional .Reviews m_Reviews = 9;
  if (has_m_reviews()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        9, this->m_reviews(), target);
  }

  // optional .SupportingDocuments m_SupportingDocuments = 10;
  if (has_m_supportingdocuments()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        10, this->m_supportingdocuments(), target);
  }

  // optional .ScienceGoals m_ScienceGoals = 11;
  if (has_m_sciencegoals()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        11, this->m_sciencegoals(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Proposals)
  return target;
}

int Proposals::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string abstract = 1;
    if (has_abstract()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->abstract());
    }

    // optional string more_info = 2;
    if (has_more_info()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->more_info());
    }

    // optional string proposal_id = 3;
    if (has_proposal_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->proposal_id());
    }

    // optional .ProposalStatus proposal_status = 4;
    if (has_proposal_status()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->proposal_status());
    }

    // optional .ProposalType proposal_type = 5;
    if (has_proposal_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->proposal_type());
    }

    // optional .CoAuthors m_CoAuthors = 6;
    if (has_m_coauthors()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->m_coauthors());
    }

    // optional .ProposalEditors m_ProposalEditors = 7;
    if (has_m_proposaleditors()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->m_proposaleditors());
    }

    // optional .TACReviews m_TACReviews = 8;
    if (has_m_tacreviews()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->m_tacreviews());
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional .Reviews m_Reviews = 9;
    if (has_m_reviews()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->m_reviews());
    }

    // optional .SupportingDocuments m_SupportingDocuments = 10;
    if (has_m_supportingdocuments()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->m_supportingdocuments());
    }

    // optional .ScienceGoals m_ScienceGoals = 11;
    if (has_m_sciencegoals()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->m_sciencegoals());
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

void Proposals::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Proposals* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Proposals*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Proposals::MergeFrom(const Proposals& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_abstract()) {
      set_abstract(from.abstract());
    }
    if (from.has_more_info()) {
      set_more_info(from.more_info());
    }
    if (from.has_proposal_id()) {
      set_proposal_id(from.proposal_id());
    }
    if (from.has_proposal_status()) {
      set_proposal_status(from.proposal_status());
    }
    if (from.has_proposal_type()) {
      set_proposal_type(from.proposal_type());
    }
    if (from.has_m_coauthors()) {
      mutable_m_coauthors()->::CoAuthors::MergeFrom(from.m_coauthors());
    }
    if (from.has_m_proposaleditors()) {
      mutable_m_proposaleditors()->::ProposalEditors::MergeFrom(from.m_proposaleditors());
    }
    if (from.has_m_tacreviews()) {
      mutable_m_tacreviews()->::TACReviews::MergeFrom(from.m_tacreviews());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_m_reviews()) {
      mutable_m_reviews()->::Reviews::MergeFrom(from.m_reviews());
    }
    if (from.has_m_supportingdocuments()) {
      mutable_m_supportingdocuments()->::SupportingDocuments::MergeFrom(from.m_supportingdocuments());
    }
    if (from.has_m_sciencegoals()) {
      mutable_m_sciencegoals()->::ScienceGoals::MergeFrom(from.m_sciencegoals());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Proposals::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Proposals::CopyFrom(const Proposals& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Proposals::IsInitialized() const {

  return true;
}

void Proposals::Swap(Proposals* other) {
  if (other != this) {
    std::swap(abstract_, other->abstract_);
    std::swap(more_info_, other->more_info_);
    std::swap(proposal_id_, other->proposal_id_);
    std::swap(proposal_status_, other->proposal_status_);
    std::swap(proposal_type_, other->proposal_type_);
    std::swap(m_coauthors_, other->m_coauthors_);
    std::swap(m_proposaleditors_, other->m_proposaleditors_);
    std::swap(m_tacreviews_, other->m_tacreviews_);
    std::swap(m_reviews_, other->m_reviews_);
    std::swap(m_supportingdocuments_, other->m_supportingdocuments_);
    std::swap(m_sciencegoals_, other->m_sciencegoals_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Proposals::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Proposals_descriptor_;
  metadata.reflection = Proposals_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
