#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "base85.hpp"

class InputStreamInterface
{
    public:
        virtual ~InputStreamInterface() = default;
        virtual std :: string readDataPiece() = 0;
        virtual bool isEndOfStream() const = 0;
};

class MockInputStream : public InputStreamInterface
{
    public:
        MOCK_METHOD(std :: string, readDataPiece, (), (override));
        MOCK_METHOD(bool, isEndOfStream, (), (const, override));
};


