#include "game.h"
#include "AnyOption/anyoption.h"

int main(int argc, char *argv[])
{
	AnyOption *opt = new AnyOption();
	opt->addUsage("ZweiStein usage: ");
	opt->addUsage("");
	opt->addUsage(" -h  --help      Prints this help ");
	opt->addUsage(" -v  --vertical  Hint Vertical");
	opt->addUsage(" -a  --ajacent   Hint Ajacent");
	opt->addUsage(" -l  --leftright Hint LeftRight");
	opt->addUsage(" -t  --three     Hint ThreeAjacent");
	opt->addUsage("");
	opt->addUsage("Default values will be used for all unspecified parameters.");
	opt->addUsage("Avoid zero values. Those will be replaced with 1 anyway.");

	opt->setFlag("help", 'h');
	opt->setCommandOption("vertical", 'v');
	opt->setCommandOption("ajacent", 'a');
	opt->setCommandOption("leftright", 'l');
	opt->setCommandOption("three", 't');

	std::map<HintType, int> hints_prob;
	opt->processCommandArgs(argc, argv);

	if (opt->hasOptions())
	{
		if (opt->getFlag("help") || opt->getFlag('h'))
		{
			opt->printUsage();
			return EXIT_SUCCESS;
		}

		if (opt->getValue('v') != NULL || opt->getValue("vertical") != NULL)
		{
			hints_prob[HintType::vertical] = std::stoi(opt->getValue('v'));
		}
		if (opt->getValue('a') != NULL || opt->getValue("ajacent") != NULL)
		{
			hints_prob[HintType::ajacent] = std::stoi(opt->getValue('a'));
		}
		if (opt->getValue('l') != NULL || opt->getValue("leftright") != NULL)
		{
			hints_prob[HintType::leftRight] = std::stoi(opt->getValue('l'));
		}
		if (opt->getValue('t') != NULL || opt->getValue("three") != NULL)
		{
			hints_prob[HintType::threeAjacent] = std::stoi(opt->getValue('t'));
		}
	}


	Game game(hints_prob);
	game.initPuzzle();
	game.start();

	return EXIT_SUCCESS;
}
