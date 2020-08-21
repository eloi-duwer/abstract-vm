#include <avm.hpp>
#include <OperandFactory.hpp>
#include <Instruction.hpp>
#include <queue>
#include <vector>

std::string trim(std::string const &str)
{
	size_t deb = 0;
	size_t end = str.size() - 1;

	while (deb < str.size() && std::isspace(str.at(deb)))
		deb++;

	while (end >= deb && std::isspace(str.at(end)))
		end--;

	if (end < deb)
		return std::string("");
	
	return str.substr(deb, end - deb + 1);
}

void execInstructions(std::queue<Instruction*> &queue)
{
	std::vector<const IOperand *>	stack;
	bool should_return = false;

	if (queue.size() != 0 && queue.back()->getInstruction() != Instruction::exit)
	{
		std::cout << "No exit instruction or exit is not the last instruction, aborting" << std::endl;
		exit(1);
	}
	while(should_return == false && !queue.empty())
	{
		try {
			if (queue.front()->exec(stack) == true)
				should_return = true;
			delete queue.front();
			queue.pop();
		} catch(const std::exception &e) {
			std::cout << "Runtime error: " << e.what() << ". Aborting" << std::endl;
			std::cout << "\tInstruction: \"" << *queue.front() << "\""<< std::endl;
			std::cout << "\tStack: ";
			for (std::vector<const IOperand*>::size_type i = 0; i < stack.size(); i++) {
				std::cout << *stack[i] << " ";
			}
			std::cout << std::endl;
			exit(1);
		}
	}
	for (std::vector<const IOperand*>::size_type i = 0; i < stack.size(); i++) {
		delete stack[i];
	}
	stack.clear();
}

void	readFile(std::istream& file, bool is_stdin)
{
	std::string					line;
	std::queue<Instruction*>	queue;
	bool 						had_parsing_errors = false;
	int							line_nb = 1;
	bool						should_return = false;

	while (should_return == false && file.good())
	{
		std::getline(file, line);
		if (line.length() > 0)
		{
			if (line[0] == ';')
			{
				if (is_stdin == true && line.length() > 1 && line[1] == ';')
					should_return = true;
			}
			else {
				try {
					queue.push(new Instruction(line));
				} catch(const std::exception &e) {
					std::cout << "Parsing error: " << e.what() << std::endl;
					std::cout << "\tLine " << line_nb << ": \"" << line << "\"" << std::endl;
					had_parsing_errors = true;
				}
			}
		}
		line_nb++;
	}
	if (had_parsing_errors) {
		std::cout << "Parsing error detected, aborting" << std::endl;
		exit(1);
	}
	execInstructions(queue);
}

int		main(int argc, char **argv)
{
	if (argc == 1)
		readFile(std::cin, true);
	else {
		std::ifstream file(argv[1], std::ifstream::in);
		if (!file.good()) {
			std::cout << "Cannot open file " << argv[1] << std::endl;
			return (1);
		} 
		readFile(file, false);
		file.close();
	}

	return (0);
}
