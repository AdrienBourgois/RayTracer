#ifndef __LOG_DECLARATION__
#define __LOG_DECLARATION__

#include <string>
#include <fstream>

enum class ELogOutput
{
	NONE,
	TERMINAL,
	IN_FILE,
	BOTH
};

class Log
{
	public:
		Log(Log const&) = delete;
		~Log();


		auto init(ELogOutput output_type) -> void;
		auto info(std::string) -> 								void;
		auto alert(std::string) -> 								void;
		auto error(std::string) -> 								void;
		auto debug(std::string) -> 								void;
		auto fatalError(std::string) -> 						void;

		static auto getInstance() -> 			                Log*;
		
	private:
        Log() = default;

        static auto create() ->                                 void;
		auto setOutput(ELogOutput output_type) -> 									void;
		auto setInstance(Log* log_instance) ->          		void { this->log = log_instance; }

		static Log* log;
		ELogOutput output;

		std::ofstream fileStream;
		std::string pathToFile;
};

#endif
