// Copyright 2019 Obolenskiy Arseniy
#ifndef MODULES_TREE_INCLUDE_APPLICATION_H_
#define MODULES_TREE_INCLUDE_APPLICATION_H_
#include <sstream>
#include "tree.h"

class TreeApplication {
 private:
    std::string Help(const char *appname);
    int ParseOperation(const char **argv);
    long ParseNumber(const char *s);
    Tree t_;
    std::stringstream out_;
 public:
    TreeApplication() = default;
    std::string operator()(int argc, const char** argv);
};

#endif  // MODULES_TREE_INCLUDE_APPLICATION_H_
