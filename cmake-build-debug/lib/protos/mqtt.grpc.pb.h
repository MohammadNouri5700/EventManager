// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: mqtt.proto
#ifndef GRPC_mqtt_2eproto__INCLUDED
#define GRPC_mqtt_2eproto__INCLUDED

#include "mqtt.pb.h"

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

class MqttClientsConfig final {
 public:
  static constexpr char const* service_full_name() {
    return "MqttClientsConfig";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status SendMqttClientsConfig(::grpc::ClientContext* context, const ::MqttClients& request, ::ConfigResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ConfigResponse>> AsyncSendMqttClientsConfig(::grpc::ClientContext* context, const ::MqttClients& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ConfigResponse>>(AsyncSendMqttClientsConfigRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ConfigResponse>> PrepareAsyncSendMqttClientsConfig(::grpc::ClientContext* context, const ::MqttClients& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ConfigResponse>>(PrepareAsyncSendMqttClientsConfigRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void SendMqttClientsConfig(::grpc::ClientContext* context, const ::MqttClients* request, ::ConfigResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void SendMqttClientsConfig(::grpc::ClientContext* context, const ::MqttClients* request, ::ConfigResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::ConfigResponse>* AsyncSendMqttClientsConfigRaw(::grpc::ClientContext* context, const ::MqttClients& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::ConfigResponse>* PrepareAsyncSendMqttClientsConfigRaw(::grpc::ClientContext* context, const ::MqttClients& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status SendMqttClientsConfig(::grpc::ClientContext* context, const ::MqttClients& request, ::ConfigResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ConfigResponse>> AsyncSendMqttClientsConfig(::grpc::ClientContext* context, const ::MqttClients& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ConfigResponse>>(AsyncSendMqttClientsConfigRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ConfigResponse>> PrepareAsyncSendMqttClientsConfig(::grpc::ClientContext* context, const ::MqttClients& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ConfigResponse>>(PrepareAsyncSendMqttClientsConfigRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void SendMqttClientsConfig(::grpc::ClientContext* context, const ::MqttClients* request, ::ConfigResponse* response, std::function<void(::grpc::Status)>) override;
      void SendMqttClientsConfig(::grpc::ClientContext* context, const ::MqttClients* request, ::ConfigResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
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
    ::grpc::ClientAsyncResponseReader< ::ConfigResponse>* AsyncSendMqttClientsConfigRaw(::grpc::ClientContext* context, const ::MqttClients& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::ConfigResponse>* PrepareAsyncSendMqttClientsConfigRaw(::grpc::ClientContext* context, const ::MqttClients& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_SendMqttClientsConfig_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status SendMqttClientsConfig(::grpc::ServerContext* context, const ::MqttClients* request, ::ConfigResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_SendMqttClientsConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_SendMqttClientsConfig() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_SendMqttClientsConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendMqttClientsConfig(::grpc::ServerContext* /*context*/, const ::MqttClients* /*request*/, ::ConfigResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSendMqttClientsConfig(::grpc::ServerContext* context, ::MqttClients* request, ::grpc::ServerAsyncResponseWriter< ::ConfigResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_SendMqttClientsConfig<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_SendMqttClientsConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_SendMqttClientsConfig() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::MqttClients, ::ConfigResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::MqttClients* request, ::ConfigResponse* response) { return this->SendMqttClientsConfig(context, request, response); }));}
    void SetMessageAllocatorFor_SendMqttClientsConfig(
        ::grpc::MessageAllocator< ::MqttClients, ::ConfigResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::MqttClients, ::ConfigResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_SendMqttClientsConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendMqttClientsConfig(::grpc::ServerContext* /*context*/, const ::MqttClients* /*request*/, ::ConfigResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* SendMqttClientsConfig(
      ::grpc::CallbackServerContext* /*context*/, const ::MqttClients* /*request*/, ::ConfigResponse* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_SendMqttClientsConfig<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_SendMqttClientsConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_SendMqttClientsConfig() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_SendMqttClientsConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendMqttClientsConfig(::grpc::ServerContext* /*context*/, const ::MqttClients* /*request*/, ::ConfigResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_SendMqttClientsConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_SendMqttClientsConfig() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_SendMqttClientsConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendMqttClientsConfig(::grpc::ServerContext* /*context*/, const ::MqttClients* /*request*/, ::ConfigResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSendMqttClientsConfig(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_SendMqttClientsConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_SendMqttClientsConfig() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->SendMqttClientsConfig(context, request, response); }));
    }
    ~WithRawCallbackMethod_SendMqttClientsConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendMqttClientsConfig(::grpc::ServerContext* /*context*/, const ::MqttClients* /*request*/, ::ConfigResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* SendMqttClientsConfig(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_SendMqttClientsConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_SendMqttClientsConfig() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::MqttClients, ::ConfigResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::MqttClients, ::ConfigResponse>* streamer) {
                       return this->StreamedSendMqttClientsConfig(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_SendMqttClientsConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status SendMqttClientsConfig(::grpc::ServerContext* /*context*/, const ::MqttClients* /*request*/, ::ConfigResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedSendMqttClientsConfig(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::MqttClients,::ConfigResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_SendMqttClientsConfig<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_SendMqttClientsConfig<Service > StreamedService;
};

class MqttBrokerConfig final {
 public:
  static constexpr char const* service_full_name() {
    return "MqttBrokerConfig";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status SendMqttBrokerConfig(::grpc::ClientContext* context, const ::MqttBorker& request, ::ConfigResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ConfigResponse>> AsyncSendMqttBrokerConfig(::grpc::ClientContext* context, const ::MqttBorker& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ConfigResponse>>(AsyncSendMqttBrokerConfigRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ConfigResponse>> PrepareAsyncSendMqttBrokerConfig(::grpc::ClientContext* context, const ::MqttBorker& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ConfigResponse>>(PrepareAsyncSendMqttBrokerConfigRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void SendMqttBrokerConfig(::grpc::ClientContext* context, const ::MqttBorker* request, ::ConfigResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void SendMqttBrokerConfig(::grpc::ClientContext* context, const ::MqttBorker* request, ::ConfigResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::ConfigResponse>* AsyncSendMqttBrokerConfigRaw(::grpc::ClientContext* context, const ::MqttBorker& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::ConfigResponse>* PrepareAsyncSendMqttBrokerConfigRaw(::grpc::ClientContext* context, const ::MqttBorker& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status SendMqttBrokerConfig(::grpc::ClientContext* context, const ::MqttBorker& request, ::ConfigResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ConfigResponse>> AsyncSendMqttBrokerConfig(::grpc::ClientContext* context, const ::MqttBorker& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ConfigResponse>>(AsyncSendMqttBrokerConfigRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ConfigResponse>> PrepareAsyncSendMqttBrokerConfig(::grpc::ClientContext* context, const ::MqttBorker& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ConfigResponse>>(PrepareAsyncSendMqttBrokerConfigRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void SendMqttBrokerConfig(::grpc::ClientContext* context, const ::MqttBorker* request, ::ConfigResponse* response, std::function<void(::grpc::Status)>) override;
      void SendMqttBrokerConfig(::grpc::ClientContext* context, const ::MqttBorker* request, ::ConfigResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
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
    ::grpc::ClientAsyncResponseReader< ::ConfigResponse>* AsyncSendMqttBrokerConfigRaw(::grpc::ClientContext* context, const ::MqttBorker& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::ConfigResponse>* PrepareAsyncSendMqttBrokerConfigRaw(::grpc::ClientContext* context, const ::MqttBorker& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_SendMqttBrokerConfig_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status SendMqttBrokerConfig(::grpc::ServerContext* context, const ::MqttBorker* request, ::ConfigResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_SendMqttBrokerConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_SendMqttBrokerConfig() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_SendMqttBrokerConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendMqttBrokerConfig(::grpc::ServerContext* /*context*/, const ::MqttBorker* /*request*/, ::ConfigResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSendMqttBrokerConfig(::grpc::ServerContext* context, ::MqttBorker* request, ::grpc::ServerAsyncResponseWriter< ::ConfigResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_SendMqttBrokerConfig<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_SendMqttBrokerConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_SendMqttBrokerConfig() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::MqttBorker, ::ConfigResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::MqttBorker* request, ::ConfigResponse* response) { return this->SendMqttBrokerConfig(context, request, response); }));}
    void SetMessageAllocatorFor_SendMqttBrokerConfig(
        ::grpc::MessageAllocator< ::MqttBorker, ::ConfigResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::MqttBorker, ::ConfigResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_SendMqttBrokerConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendMqttBrokerConfig(::grpc::ServerContext* /*context*/, const ::MqttBorker* /*request*/, ::ConfigResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* SendMqttBrokerConfig(
      ::grpc::CallbackServerContext* /*context*/, const ::MqttBorker* /*request*/, ::ConfigResponse* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_SendMqttBrokerConfig<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_SendMqttBrokerConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_SendMqttBrokerConfig() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_SendMqttBrokerConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendMqttBrokerConfig(::grpc::ServerContext* /*context*/, const ::MqttBorker* /*request*/, ::ConfigResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_SendMqttBrokerConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_SendMqttBrokerConfig() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_SendMqttBrokerConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendMqttBrokerConfig(::grpc::ServerContext* /*context*/, const ::MqttBorker* /*request*/, ::ConfigResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSendMqttBrokerConfig(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_SendMqttBrokerConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_SendMqttBrokerConfig() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->SendMqttBrokerConfig(context, request, response); }));
    }
    ~WithRawCallbackMethod_SendMqttBrokerConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendMqttBrokerConfig(::grpc::ServerContext* /*context*/, const ::MqttBorker* /*request*/, ::ConfigResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* SendMqttBrokerConfig(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_SendMqttBrokerConfig : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_SendMqttBrokerConfig() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::MqttBorker, ::ConfigResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::MqttBorker, ::ConfigResponse>* streamer) {
                       return this->StreamedSendMqttBrokerConfig(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_SendMqttBrokerConfig() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status SendMqttBrokerConfig(::grpc::ServerContext* /*context*/, const ::MqttBorker* /*request*/, ::ConfigResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedSendMqttBrokerConfig(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::MqttBorker,::ConfigResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_SendMqttBrokerConfig<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_SendMqttBrokerConfig<Service > StreamedService;
};


#endif  // GRPC_mqtt_2eproto__INCLUDED
