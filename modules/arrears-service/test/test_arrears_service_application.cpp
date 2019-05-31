// Copyright 2019 Guseva Catherine

#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

#include "include/arrears_service_application.h"

using ::testing::internal::RE;
using std::vector;
using std::string;

class ArrearsServiceApplicationTest : public ::testing::Test {
 protected:
    void Act(vector<string> args_) {
        vector<const char*> options;

        options.push_back("range");
        for (size_t i = 0; i < args_.size(); ++i) {
            options.push_back(args_[i].c_str());
        }

        const char** argv = &options.front();
        int argc = static_cast<int>(args_.size()) + 1;

        output_ = app_(argc, argv);
    }

    void Assert(std::string expected) {
        EXPECT_TRUE(RE::PartialMatch(output_, RE(expected)));
    }

 private:
    ArrearsServiceApplication app_;
    string output_;
};

TEST_F(ArrearsServiceApplicationTest, Do_Print_Help_Without_Arguments) {
    vector<string> args = {};

    Act(args);

    Assert("This is a arrears service application\\..*");
}

TEST_F(ArrearsServiceApplicationTest, Can_Detect_Wrong_Number_Format) {
    vector<string> args = { "express_pay", "30", "xx", "25", "5" };

    Act(args);

    Assert("Wrong number format!.*");
}

TEST_F(ArrearsServiceApplicationTest, Can_Detect_Wrong_Format_Operation) {
    vector<string> args = { "expre_pay", "30" };

    Act(args);

    Assert("Wrong operation format!");
}

TEST_F(ArrearsServiceApplicationTest, Can_Check_Right_Operation_Express_Pay) {
    vector<string> args = { "express_pay", "15000", "30", "10", "2" };

    Act(args);

    Assert("8021.74");
}

TEST_F(ArrearsServiceApplicationTest, Can_Check_Right_Operation_Year_Pay_Val) {
    vector<string> args = { "year_pay_val", "15000", "30", "10", "2", "5.5" };

    Act(args);

    Assert("6519.35");
}

TEST_F(ArrearsServiceApplicationTest, Can_Detect_Wrong_Number_Express_Pay) {
    vector<string> args = { "express_pay", "30", "5", "25" };

    Act(args);

    Assert("ERROR: Must be 5 arguments for 'express_pay'");
}

TEST_F(ArrearsServiceApplicationTest, Can_Detect_Wrong_Number_Year_Pay_Val) {
    vector<string> args = { "year_pay_val", "30" };

    Act(args);

    Assert("ERROR: Must be 6 arguments for 'year_pay_val'");
}

TEST_F(ArrearsServiceApplicationTest, Can_Detect_Negative_Number_Debt) {
    vector<string> args = { "express_pay", "-30", "5", "25", "5" };

    Act(args);

    Assert("No debt to serv.*");
}

TEST_F(ArrearsServiceApplicationTest, Can_Detect_Negative_Number_Procent) {
    vector<string> args = { "express_pay", "30", "-5", "25", "5" };

    Act(args);

    Assert("Invalid procent.*");
}

TEST_F(ArrearsServiceApplicationTest, Can_Detect_Negative_Number_Time) {
    vector<string> args = { "express_pay", "30", "5", "25", "-5" };

    Act(args);

    Assert("No time to service.*");
}

TEST_F(ArrearsServiceApplicationTest, Can_Detect_Wrong_Overflow) {
    vector<string> args = { "year_pay_val", "3", "9999999999", "5", "5", "1" };

    Act(args);

    Assert("Number is out of bounds!");
}

TEST_F(ArrearsServiceApplicationTest, Can_Detect_Zero_Prog) {
    vector<string> args = { "year_pay_val", "30", "10", "30", "1", "0" };

    Act(args);

    Assert("No progression to calculate year pay");
}
