// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProposalStatus.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ProposalStatus.pb.h"

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

const ::google::protobuf::EnumDescriptor* ProposalStatus_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_ProposalStatus_2eproto() {
  protobuf_AddDesc_ProposalStatus_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ProposalStatus.proto");
  GOOGLE_CHECK(file != NULL);
  ProposalStatus_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ProposalStatus_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_ProposalStatus_2eproto() {
}

void protobuf_AddDesc_ProposalStatus_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024ProposalStatus.proto*R\n\016ProposalStatus"
    "\022\t\n\005Draft\020\000\022\014\n\010Accepted\020\001\022\014\n\010Rejected\020\002\022"
    "\r\n\tSubmitted\020\003\022\n\n\006Merged\020\004", 106);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ProposalStatus.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ProposalStatus_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ProposalStatus_2eproto {
  StaticDescriptorInitializer_ProposalStatus_2eproto() {
    protobuf_AddDesc_ProposalStatus_2eproto();
  }
} static_descriptor_initializer_ProposalStatus_2eproto_;
const ::google::protobuf::EnumDescriptor* ProposalStatus_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ProposalStatus_descriptor_;
}
bool ProposalStatus_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
