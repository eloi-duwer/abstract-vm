#include <avm.hpp>
#include <OperandFactory.hpp>
#include <Instruction.hpp>

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

void	readFile(std::istream& file)
{
	std::string line;
	std::queue<Instruction*> queue;

	while (file.good())
	{
		std::getline(file, line);
		if (line.length() > 0)
		{
			queue.push(new Instruction(line));
		}
	}
	while(!queue.empty())
	{
		std::cout << *queue.front() << std::endl;
		delete queue.front();
		queue.pop();
	}
}

int		main(int argc, char **argv)
{
	if (argc == 1)
		readFile(std::cin);
	else {
		std::ifstream file(argv[1], std::ifstream::in);
		if (!file.good()) {
			std::cout << "Cannot open file " << argv[1] << std::endl;
			return (1);
		} 
		readFile(file);
		file.close();
	}

	/*OperandFactory fact = OperandFactory();
	IOperand const *op = fact.createOperand(IOperand::Double, "3.141592654");
	IOperand const *op1 = fact.createOperand(IOperand::Int8, "20");
	IOperand const *op2 = *op1 + *op;
	std::cout << *op2 << std::endl;

	delete op;
	delete op1;
	delete op2;*/

	return (0);
}
