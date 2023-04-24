#include "Observer.h"

void Subject::addObserver(std::weak_ptr<Observer> observer)
{
	observers_.push_back(observer);
}

void Subject::warning(const std::string& message) const
{
	for (auto& o : observers_)
	{
		if (auto shared_obj = o.lock()) shared_obj->onWarning(message);
	}
}

void Subject::error(const std::string& message) const
{
	for (auto& o : observers_)
	{
		if (auto shared_obj = o.lock()) shared_obj->onError(message);
	}
}

void Subject::fatalError(const std::string& message) const
{
	for (auto& o : observers_)
	{
		if (auto shared_obj = o.lock()) shared_obj->onFatalError(message);
	}
}

WarningObs::WarningObs(Subject* subj)
{
	subj->addObserver(std::make_shared<Observer>(*this));
}
