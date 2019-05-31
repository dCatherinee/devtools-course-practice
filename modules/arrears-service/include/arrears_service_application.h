// Copyright 2019 Guseva Catherine

#ifndef MODULES_ARREARS_SERVICE_INCLUDE_ARREARS_SERVICE_APPLICATION_H_
#define MODULES_ARREARS_SERVICE_INCLUDE_ARREARS_SERVICE_APPLICATION_H_

#include <string>

class ArrearsServiceApplication {
 public:
    ArrearsServiceApplication();
    std::string operator()(int argc, const char** argv);
    int parseOperation(const char* arg, int argc);

 private:
    std::string message_;
    void help(const char* appname, const char* message = "");
    int op;
};

#endif  // MODULES_ARREARS_SERVICE_INCLUDE_ARREARS_SERVICE_APPLICATION_H_
