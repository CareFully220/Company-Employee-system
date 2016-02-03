#pragma once

typedef std::vector <std::string> cmdArgs; //!< Vector of strings that can include all inputted arguments of a command
typedef std::function<bool(cmdArgs)> callback; //!< Command Callback function typedef
