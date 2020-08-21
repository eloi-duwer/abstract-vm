#include <OperandFactory.hpp>
#include <OperandParser.hpp>
#include <IOperand.hpp>

IOperand const * OperandParser::parseOperand ( std::string const & line )
{
	int index = line.find(" ", 0);
	if (index <= 0)
		throw ExpectedOperand();
	if (line.compare(index + 1, 4, "int8") == 0)
		return this->doParseOperand(IOperand::Int8, line);
	else if (line.compare(index + 1, 5, "int16") == 0)
		return this->doParseOperand(IOperand::Int16, line);
	else if (line.compare(index + 1, 5, "int32") == 0)
		return this->doParseOperand(IOperand::Int32, line);
	else if (line.compare(index + 1, 5, "float") == 0)
		return this->doParseOperand(IOperand::Float, line);
	else if (line.compare(index + 1, 6, "double") == 0)
		return this->doParseOperand(IOperand::Double, line);
	else
		throw UnknownOperandException();
}

IOperand const * OperandParser::doParseOperand( IOperand::eOperandType type, std::string const & line )
{
	size_t begin = line.find("(");
	size_t end = line.rfind(")");

	return this->factory.createOperand(
		type,
		line.substr(begin + 1, end - begin - 1)
	);
}

OperandFactory OperandParser::factory = OperandFactory();
