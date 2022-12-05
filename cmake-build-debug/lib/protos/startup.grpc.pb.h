// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: startup.proto
#ifndef GRPC_startup_2eproto__INCLUDED
#define GRPC_startup_2eproto__INCLUDED

#include "startup.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

class SystemStartupConfig final {
 public:
  static constexpr char const* service_full_name() {
    return "SystemStartupConfig";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status SendSystemStartupConfig(::grpc::ClientContext* context, const ::StartupConfig& request, ::StartupResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::StartupResponse>> AsyncSendSystemStartupConfig(::grpc::ClientContext* context, const ::StartupConfig& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::StartupResponse>>(AsyncSendSystemStartupConfigRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::StartupResponse>> PrepareAsyncSendSystemStartupConfig(::grpc::ClientContext* context, const ::StartupConfig& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::StartupResponse>>(PrepareAsyncSendSystemStartupConfigRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void SendSystemStartupConfig(::grpc::ClientContext* context, const ::StartupConfig* request, ::StartupResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void SendSystemStartupConfig(::grpc::ClientContext* context, const ::StartupConfig* request, ::StartupResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::StartupResponse>* AsyncSendSystemStartupConfigRaw(::grpc::ClientContext* context, const ::StartupConfig& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::StartupResponse>* PrepareAsyncSendSystemStartupConfigRaw(::grpc::ClientContext* context, const ::StartupConfig& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status SendSystemStartupConfig(::grpc::ClientContext* context, const ::StartupConfig& request, ::StartupResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::StartupResponse>> AsyncSendSystemStartupConfig(::grpc::ClientContext* context, const ::StartupConfig& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::StartupResponse>>(AsyncSendSystemStartupConfigRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::StartupResponse>> PrepareAsyncSendSystemStartupConfig(::grpc::ClientContext* context, const ::StartupConfig& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::StartupResponse>>(PrepareAsyncSendSystemStartupConfigRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void SendSystemStartupConfig(::grpc::ClientContext* context, const ::StartupConfig* request, ::StartupResponse* response, std::function<void(::grpc::Status)>) override;
      void SendSystemStartupConfig(::grpc::ClientContext* context, const ::StartupConfig* request, ::StartupResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::StartupResponse>* AsyncSendSystemStartupConfigRaw(::grpc::ClientContext* context, const ::StartupConfig& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::StartupResponse>* PrepareAsyncSendSystemStartupConfigRaw(::grpc::ClientContext* context, const ::StartupConfig& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_SendSystemStartupConfig_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status SendSystemStartupConfig(::grpc::ServerContext* context, const ::StartupConfig* request, ::StartupResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_SendSystemStartupConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_SendSystemStartupConfig() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_SendSystemStartupConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendSystemStartupConfig(::grpc::ServerContext* /*context*/, const ::StartupConfig* /*request*/, ::StartupResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSendSystemStartupConfig(::grpc::ServerContext* context, ::StartupConfig* request, ::grpc::ServerAsyncResponseWriter< ::StartupResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_SendSystemStartupConfig<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_SendSystemStartupConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_SendSystemStartupConfig() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::StartupConfig, ::StartupResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::StartupConfig* request, ::StartupResponse* response) { return this->SendSystemStartupConfig(context, request, response); }));}
    void SetMessageAllocatorFor_SendSystemStartupConfig(
        ::grpc::MessageAllocator< ::StartupConfig, ::StartupResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::StartupConfig, ::StartupResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_SendSystemStartupConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendSystemStartupConfig(::grpc::ServerContext* /*context*/, const ::StartupConfig* /*request*/, ::StartupResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* SendSystemStartupConfig(
      ::grpc::CallbackServerContext* /*context*/, const ::StartupConfig* /*request*/, ::StartupResponse* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_SendSystemStartupConfig<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_SendSystemStartupConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_SendSystemStartupConfig() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_SendSystemStartupConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendSystemStartupConfig(::grpc::ServerContext* /*context*/, const ::StartupConfig* /*request*/, ::StartupResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_SendSystemStartupConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_SendSystemStartupConfig() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_SendSystemStartupConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendSystemStartupConfig(::grpc::ServerContext* /*context*/, const ::StartupConfig* /*request*/, ::StartupResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSendSystemStartupConfig(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_SendSystemStartupConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_SendSystemStartupConfig() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->SendSystemStartupConfig(context, request, response); }));
    }
    ~WithRawCallbackMethod_SendSystemStartupConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendSystemStartupConfig(::grpc::ServerContext* /*context*/, const ::StartupConfig* /*request*/, ::StartupResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* SendSystemStartupConfig(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_SendSystemStartupConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_SendSystemStartupConfig() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::StartupConfig, ::StartupResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::StartupConfig, ::StartupResponse>* streamer) {
                       return this->StreamedSendSystemStartupConfig(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_SendSystemStartupConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status SendSystemStartupConfig(::grpc::ServerContext* /*context*/, const ::StartupConfig* /*request*/, ::StartupResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedSendSystemStartupConfig(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::StartupConfig,::StartupResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_SendSystemStartupConfig<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_SendSystemStartupConfig<Service > StreamedService;
};


#endif  // GRPC_startup_2eproto__INCLUDED
