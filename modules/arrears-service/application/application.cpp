// Copyright 2019 Guseva Catherine

#include <iostream>

#include "include/arrears_service_application.h"

int main(int argc, const char** argv) {
    ArrearsServiceApplication app;
    std::cout << app(argc, argv);
    return 0;
}
