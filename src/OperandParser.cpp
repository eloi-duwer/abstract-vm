#include <OperandFactory.hpp>
#include <OperandParser.hpp>
#include <IOperand.hpp>

IOperand const * OperandParser::parseOperand ( std::string const & line )
{
	int index = line.find(" ", 0);
	if (index <= 0)
		return (NULL);
	if (line.compare(index + 1, 4, "int8") == 0)
	{
		return this->factory.createOperand(
			IOperand::Int8,
			line.substr(index + 6, line.length() - (index + 6) - 1)
		);
	}
	else if (line.compare(index + 1, 5, "int16") == 0)
	{
		return this->factory.createOperand(
			IOperand::Int16,
			line.substr(index + 7, line.length() - (index + 7) - 1)
		);
	}
	else if (line.compare(index + 1, 5, "int32") == 0)
	{
		return this->factory.createOperand(
			IOperand::Int32,
			line.substr(index + 7, line.length() - (index + 7) - 1)
		);
	}
	else if (line.compare(index + 1, 5, "float") == 0)
	{
		return this->factory.createOperand(
			IOperand::Float,
			line.substr(index + 7, line.length() - (index + 7) - 1));
	}
	else if (line.compare(index + 1, 6, "double") == 0)
	{
		return this->factory.createOperand(
			IOperand::Double,
			line.substr(index + 8, line.length() - (index + 8) - 1)
		);
	}
	else
		return (NULL);
}

OperandFactory OperandParser::factory = OperandFactory();
