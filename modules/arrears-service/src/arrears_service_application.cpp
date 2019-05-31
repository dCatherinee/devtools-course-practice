// Copyright 2019 Guseva Catherine

#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <limits>

#include "include/arrears_service_application.h"
#include "include/arrears_service.h"

ArrearsServiceApplication::ArrearsServiceApplication() : message_(""), op(0) {}

void ArrearsServiceApplication::help(const char* appname, const char* message) {
    message_ =
        std::string(message) +
        "This is a arrears service application.\n\n" +
        "To do operations, you need to write command & parameters " +
        "in right format.\n" +
        "There all formats, you can write:\n" +
        "\t'express_pay' <debt> <procent> <rate> <time> - Urgent payment\n" +
        "\t'year_pay_val' <debt> <procent> <rate> <time> <prog> " +
        "- Annual payment\n" +
        "\n Warning!" +
        " Almost all arguments are integers, except <prog> - double.\n\n" +
        "EXAMPLE:\n" +
        "\t year_pay_val 15000 30 10 2 5.5\n" +
        "\n RESULT:\n" +
        "\t 6519.35\n";
}

int parseInt(const char* arg) {
    char* arr;

    int64_t value = strtol(arg, &arr, 10);

    if (arr[0]) {
        throw std::string("Wrong number format!");
    }
    if (value <= static_cast<int64_t>(std::numeric_limits<int>::min()) ||
        value >= static_cast<int64_t>(std::numeric_limits<int>::max())) {
        throw std::string("Number is out of bounds!");
    }

    return value;
}

double parseDouble(const char* arg) {
    double value = atof(arg);

    return value;
}

int ArrearsServiceApplication::parseOperation(const char* arg, int argc) {
    int temp;

    if ((strcmp(arg, "express_pay") == 0)) {
        if (argc != 6)
            throw std::string("ERROR: Must be 5 arguments for 'express_pay'");
        temp = 0;
    } else if (strcmp(arg, "year_pay_val") == 0) {
        if (argc != 7)
            throw std::string("ERROR: Must be 6 arguments for 'year_pay_val'");
        temp = 1;
    } else {
        throw std::string("Wrong operation format!");
    }

    return temp;
}

std::string ArrearsServiceApplication::operator()(int argc, const char** arg) {
    if (argc == 1) {
        help(arg[0]);
        return message_;
    }

    try {
        op = parseOperation(arg[1], argc);
    }
    catch (std::string& str) {
        return str;
    }

    ArrearService c(1, 1, 1, 1);
    try {
        c.SetDebt(parseInt(arg[2]));
        c.SetProcent(parseInt(arg[3]));
        c.SetRate(parseInt(arg[4]));
        c.SetTime(parseInt(arg[5]));
    }
    catch (std::string& str) {
        return str;
    }

    std::ostringstream stream;

    switch (op) {
    case 0:
        c.SetExpress();
        stream << "Express_pay = " << c.GetExpress();
        break;

    case 1:
        try {
            c.SetYearPay(parseDouble(arg[6]));
        }
        catch (std::string &str) {
            return str;
        }
        stream << "Year_pay_val = " << c.GetYearPay();
        break;
    }

    message_ = stream.str();

    return message_;
}
