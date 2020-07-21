#ifndef COMMAND_H
#define COMMAND_H

enum class CommandType { error, quit,
						 move_up, move_down, move_left, move_right,
						 claim, dismiss,
						 toggle_autohide,
						 help};

class Command
{
public:
	Command();
	void	parse(int button);
	CommandType type;
};

#endif // COMMAND_H
