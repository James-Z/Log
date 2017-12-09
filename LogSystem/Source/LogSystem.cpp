#include "LogSystem.h"

LogSystem::Garbage LogSystem::_garbage;
std::string LogSystem::_path = "";
std::ofstream LogSystem::_logFile;