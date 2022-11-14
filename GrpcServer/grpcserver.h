#pragma once
#include <string>
#include <memory>
#include <grpcpp/grpcpp.h>
#include "../ConnectionManager/ConnectionManager.h"
class GrpcServer 
{
public:
    GrpcServer(const std::string &address , CONNECTION::ConnectionManager *ConnMan);
private:
    std::unique_ptr<grpc::Server> server;
};