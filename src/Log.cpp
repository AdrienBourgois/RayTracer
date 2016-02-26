#include <sys/stat.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include <csignal>

#include "Log.h"

Log* Log::log = nullptr;

auto Log::init(ELogOutput output_type) -> void
{	
    
    mkdir("logs/", 0741);

    time_t rawTime;
    struct tm* timeinfo;
    char buffer[20];

    time(&rawTime);
    timeinfo = localtime(&rawTime);
    strftime(buffer, 20, "%a%b%d-%H%M%S", timeinfo);

	this->output = output_type;
	this->pathToFile = "logs/";
	this->pathToFile.append(buffer);
	this->pathToFile.append(".log");
	this->fileStream.open(this->pathToFile, std::ios_base::app);

	this->setOutput(output_type);
}

auto Log::info(std::string message) -> void
{
	switch (this->output)
        {
            case ELogOutput::BOTH:
            {
                this->fileStream << "[INFO]: " << message << std::endl;
                std::cout << "[INFO]: " << message << std::endl;
                break;
            }

            case ELogOutput::TERMINAL:
            {
                std::cout << "[INFO]: " << message << std::endl;
                break;
            }

            case ELogOutput::IN_FILE:
            {
                this->fileStream << "[INFO]: " << message  << std::endl;
                break;
            }

            default:
                break;
        }


}

auto Log::alert(std::string message) -> void
{
    switch (this->output)
    {
        case ELogOutput::BOTH:
        {
            this->fileStream << "[ALERT]: " << message << std::endl;
            std::cout << "[ALERT]: " << message << std::endl;
            break;
        }

        case ELogOutput::TERMINAL:
        {
            std::cout << "[ALERT]: " << message << std::endl;
            break;
        }

        case ELogOutput::IN_FILE:
        {
            this->fileStream << "[ALERT]: " << message << std::endl;
            break;
        }

        default:
            break;
    }
}

auto Log::error(std::string message) -> void
{
	switch (this->output)
        {
            case ELogOutput::BOTH:
            {
                this->fileStream << "[ERROR]: " << message << std::endl;
                std::cout << "[ERROR]: " << message << std::endl;
                break;
            }

            case ELogOutput::TERMINAL:
            {
                std::cout << "[ERROR]: " << message << std::endl;
                break;
            }

            case ELogOutput::IN_FILE:
            {
                this->fileStream << "[ERROR]: " << message << std::endl;
                break;
            }

            default:
                break;
        }

}

auto Log::debug(std::string message) -> void
{
	switch (this->output)
        {
            case ELogOutput::BOTH:
            {
                this->fileStream << "[DEBUG]: " << message << ", Checkpoint reached !" << std::endl;
                std::cout << "[DEBUG]: " << message << ", Checkpoint reached !" << std::endl;
                break;
            }

            case ELogOutput::TERMINAL:
            {
                std::cout << "[DEBUG]: " << message << ", Checkpoint reached !" << std::endl;
                break;
            }

            case ELogOutput::IN_FILE:
            {
                this->fileStream << "[DEBUG]: " << message << ", Checkpoint reached !" << std::endl;
                break;
            }

            default:
                break;
        }

}

auto Log::fatalError(std::string message) -> void
{
	switch (this->output)
        {
            case ELogOutput::BOTH:
            {
                this->fileStream << "[FATAL]: " << message << "\nAborting..." << std::endl;
                std::cout << "[FATAL]: " << message << "\nAborting..." << std::endl;
                break;
            }

            case ELogOutput::TERMINAL:
            {
                std::cout << "[FATAL]: " << message << "\nAborting..." << std::endl;
                break;
            }

            case ELogOutput::IN_FILE:
            {
                this->fileStream << "[FATAL]: " << message << "\nAborting..." << std::endl;
                break;
            }

            default:
                break;
        }
        raise(SIGABRT);

}

auto Log::setOutput(ELogOutput output_type) -> void
{
	if (output_type != this->output)
        this->output = output_type;

    if ((this->output == ELogOutput::IN_FILE || this->output == ELogOutput::BOTH) && this->fileStream.is_open())
    {
        this->fileStream << "[SWITCH]: File log enabled !\n";

        std::cout << "[SWITCH]: File log enabled !\n";

    }

    else if ((this->output == ELogOutput::TERMINAL) && this->fileStream.is_open())
    {
        std::cout << "[SWITCH]: File log disabled !\n";
        this->fileStream << "[SWITCH]: File log disabled !\n";
    }

    else
    {
        std::cout << "[SWITCH]: Log disabled !\n";
        this->fileStream << "[SWITCH]: Log disabled !\n";
    }

}

auto Log::getInstance() -> Log*
{
    if(Log::log == nullptr)
    {
        Log::log = new Log;
        Log::log->init(ELogOutput::BOTH);
    }

    return Log::log;
}

Log::~Log()
{
    Log::fileStream << "[END]: Log stopped for " << Log::pathToFile << ".\n" << std::endl;

    std::cout << "[END]: Stopping log" << ".\n";

    Log::fileStream.close();

    delete Log::log;

    Log::log = nullptr;
}
