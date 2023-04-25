#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "SecondaryFunction.h"

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

class Subject
{
    std::vector<std::weak_ptr<Observer>> observers_;
public:
    void addObserver(std::weak_ptr<Observer> observer);
    void warning(const std::string& message) const;
    void error(const std::string& message) const;
    void fatalError(const std::string& message) const;

    void VeryImportantWork();
};

class WarningObs : public Observer
{
    std::shared_ptr<WarningObs> thisPtr;
public:
    WarningObs(Subject* subj);
    void onWarning(const std::string& message) override;
};

class ErrorObs : public Observer
{
    std::shared_ptr<ErrorObs> thisPtr;
    std::string filePath_;
public:
    ErrorObs(Subject* subj, const std::string& filePath);
    void onError(const std::string& message) override;
};

class FatalErrorObs : public Observer
{
    std::shared_ptr<FatalErrorObs> thisPtr;
    std::string filePath_;
public:
    FatalErrorObs(Subject* subj, const std::string& filePath);
    void onFatalError(const std::string& message) override;
};
