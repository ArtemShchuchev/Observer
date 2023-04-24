#include "Observer.h"

void Observed::addObserver(std::weak_ptr<Observer> observer)
{
	observers_.push_back(observer);
}

void Observed::warning(const std::string& message) const
{
	for (auto& o : observers_)
	{
		if (auto shared_obj = o.lock()) shared_obj->onWarning(message);
	}
}

void Observed::error(const std::string& message) const
{
	for (auto& o : observers_)
	{
		if (auto shared_obj = o.lock()) shared_obj->onError(message);
	}
}

void Observed::fatalError(const std::string& message) const
{
	for (auto& o : observers_)
	{
		if (auto shared_obj = o.lock()) shared_obj->onFatalError(message);
	}
}
