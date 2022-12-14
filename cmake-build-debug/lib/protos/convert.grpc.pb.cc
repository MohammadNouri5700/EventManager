// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: convert.proto

#include "convert.pb.h"
#include "convert.grpc.pb.h"

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

static const char* SystemConvertProtocolConfig_method_names[] = {
  "/SystemConvertProtocolConfig/SendSystemConvertProtocolConfig",
};

std::unique_ptr< SystemConvertProtocolConfig::Stub> SystemConvertProtocolConfig::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< SystemConvertProtocolConfig::Stub> stub(new SystemConvertProtocolConfig::Stub(channel, options));
  return stub;
}

SystemConvertProtocolConfig::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_SendSystemConvertProtocolConfig_(SystemConvertProtocolConfig_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status SystemConvertProtocolConfig::Stub::SendSystemConvertProtocolConfig(::grpc::ClientContext* context, const ::ConfigConvertProtocol& request, ::ConvertProtocolConfigResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::ConfigConvertProtocol, ::ConvertProtocolConfigResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_SendSystemConvertProtocolConfig_, context, request, response);
}

void SystemConvertProtocolConfig::Stub::async::SendSystemConvertProtocolConfig(::grpc::ClientContext* context, const ::ConfigConvertProtocol* request, ::ConvertProtocolConfigResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::ConfigConvertProtocol, ::ConvertProtocolConfigResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendSystemConvertProtocolConfig_, context, request, response, std::move(f));
}

void SystemConvertProtocolConfig::Stub::async::SendSystemConvertProtocolConfig(::grpc::ClientContext* context, const ::ConfigConvertProtocol* request, ::ConvertProtocolConfigResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendSystemConvertProtocolConfig_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::ConvertProtocolConfigResponse>* SystemConvertProtocolConfig::Stub::PrepareAsyncSendSystemConvertProtocolConfigRaw(::grpc::ClientContext* context, const ::ConfigConvertProtocol& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::ConvertProtocolConfigResponse, ::ConfigConvertProtocol, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_SendSystemConvertProtocolConfig_, context, request);
}

::grpc::ClientAsyncResponseReader< ::ConvertProtocolConfigResponse>* SystemConvertProtocolConfig::Stub::AsyncSendSystemConvertProtocolConfigRaw(::grpc::ClientContext* context, const ::ConfigConvertProtocol& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSendSystemConvertProtocolConfigRaw(context, request, cq);
  result->StartCall();
  return result;
}

SystemConvertProtocolConfig::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      SystemConvertProtocolConfig_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< SystemConvertProtocolConfig::Service, ::ConfigConvertProtocol, ::ConvertProtocolConfigResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](SystemConvertProtocolConfig::Service* service,
             ::grpc::ServerContext* ctx,
             const ::ConfigConvertProtocol* req,
             ::ConvertProtocolConfigResponse* resp) {
               return service->SendSystemConvertProtocolConfig(ctx, req, resp);
             }, this)));
}

SystemConvertProtocolConfig::Service::~Service() {
}

::grpc::Status SystemConvertProtocolConfig::Service::SendSystemConvertProtocolConfig(::grpc::ServerContext* context, const ::ConfigConvertProtocol* request, ::ConvertProtocolConfigResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


