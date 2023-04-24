#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>

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
};

class WarningObs : public Observer
{
public:
    WarningObs(Subject* subj);
    void onWarning(const std::string& message) override;
};