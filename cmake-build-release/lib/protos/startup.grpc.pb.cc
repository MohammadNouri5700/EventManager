// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: startup.proto

#include "startup.pb.h"
#include "startup.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>

static const char* SystemStartupConfig_method_names[] = {
  "/SystemStartupConfig/SendSystemStartupConfig",
};

std::unique_ptr< SystemStartupConfig::Stub> SystemStartupConfig::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< SystemStartupConfig::Stub> stub(new SystemStartupConfig::Stub(channel, options));
  return stub;
}

SystemStartupConfig::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_SendSystemStartupConfig_(SystemStartupConfig_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status SystemStartupConfig::Stub::SendSystemStartupConfig(::grpc::ClientContext* context, const ::StartupConfig& request, ::StartupResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::StartupConfig, ::StartupResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_SendSystemStartupConfig_, context, request, response);
}

void SystemStartupConfig::Stub::async::SendSystemStartupConfig(::grpc::ClientContext* context, const ::StartupConfig* request, ::StartupResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::StartupConfig, ::StartupResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendSystemStartupConfig_, context, request, response, std::move(f));
}

void SystemStartupConfig::Stub::async::SendSystemStartupConfig(::grpc::ClientContext* context, const ::StartupConfig* request, ::StartupResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendSystemStartupConfig_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::StartupResponse>* SystemStartupConfig::Stub::PrepareAsyncSendSystemStartupConfigRaw(::grpc::ClientContext* context, const ::StartupConfig& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::StartupResponse, ::StartupConfig, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_SendSystemStartupConfig_, context, request);
}

::grpc::ClientAsyncResponseReader< ::StartupResponse>* SystemStartupConfig::Stub::AsyncSendSystemStartupConfigRaw(::grpc::ClientContext* context, const ::StartupConfig& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSendSystemStartupConfigRaw(context, request, cq);
  result->StartCall();
  return result;
}

SystemStartupConfig::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      SystemStartupConfig_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< SystemStartupConfig::Service, ::StartupConfig, ::StartupResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](SystemStartupConfig::Service* service,
             ::grpc::ServerContext* ctx,
             const ::StartupConfig* req,
             ::StartupResponse* resp) {
               return service->SendSystemStartupConfig(ctx, req, resp);
             }, this)));
}

SystemStartupConfig::Service::~Service() {
}

::grpc::Status SystemStartupConfig::Service::SendSystemStartupConfig(::grpc::ServerContext* context, const ::StartupConfig* request, ::StartupResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

