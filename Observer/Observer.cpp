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

void Subject::VeryImportantWork()
{
	for (int i(0);  i < 10;  ++i)
	{
		std::wcout << L"Очень важные вычисления.... ";

		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		int random_variable = std::rand() % 3;

		switch (random_variable)
		{
		case 0:
			warning("onWarning: Предупреждение!");
			break;
		case 1:
			std::wcout << L"onError: см. файл...\n";
			error("onError: Ошибка!");
			break;
		case 2:
			fatalError("onFatalError: Ваще беда! (");
			break;
		default:
			break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	}
}

WarningObs::WarningObs(Subject* subj)
{
	thisPtr = std::make_shared<WarningObs>(*this);
	subj->addObserver(thisPtr);
}

// в консоль
void WarningObs::onWarning(const std::string& message)
{
	std::wcout << ansi2wide(message) << "\n";
}

ErrorObs::ErrorObs(Subject* subj, const std::string& filePath) : filePath_(filePath)
{
	thisPtr = std::make_shared<ErrorObs>(*this);
	subj->addObserver(thisPtr);
}

// в файл
void ErrorObs::onError(const std::string& message)
{
	std::ofstream fout;
	fout.open(filePath_, std::ios_base::app);
	if (fout.is_open()) fout << message << std::endl;
}

FatalErrorObs::FatalErrorObs(Subject* subj, const std::string& filePath) : filePath_(filePath)
{
	thisPtr = std::make_shared<FatalErrorObs>(*this);
	subj->addObserver(thisPtr);
}

// в консоль и файл
void FatalErrorObs::onFatalError(const std::string& message)
{
	std::wcout << ansi2wide(message) << "\n";
	
	std::ofstream fout;
	fout.open(filePath_, std::ios_base::app);
	if (fout.is_open()) fout << message << std::endl;
}
