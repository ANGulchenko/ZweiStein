#ifndef COMMAND_H
#define COMMAND_H

#include <string>

enum class CommandType { error, claim, switch_subvalue, switch_hint};

class Command
{
public:
	Command();
	void	parse(std::string);
	CommandType type;
	int			row;
	int			column;
	int			value;
};

#endif // COMMAND_H
