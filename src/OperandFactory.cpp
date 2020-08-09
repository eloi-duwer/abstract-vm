#include <OperandFactory.hpp>
#include <IOperand.hpp>
#include <Operand.hpp>
#include <avm.hpp>

OperandFactory::OperandFactory( void )
{
	std::cout << "new operandFactory" << std::endl;
}

IOperand const * OperandFactory::createOperand( IOperand::eOperandType type, std::string const & value ) const {
	return ((this->*operandArray[type])(value));
}
	
IOperand const * OperandFactory::createInt8( std::string const & value ) const
{
	Operand<int8_t> *ret = new Operand<int8_t>((int8_t)std::stoi(value));
	return (ret);
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const
{
	Operand<int16_t> *ret = new Operand<int16_t>((int16_t)std::stoi(value));
	return (ret);
}

IOperand const * OperandFactory::createInt32( std::string const & value ) const
{
	Operand<int32_t> *ret = new Operand<int32_t>((int32_t)std::stoi(value));
	return (ret);
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const
{
	Operand<float> *ret = new Operand<float>(std::stof(value));
	return (ret);
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const
{
	Operand<double> *ret = new Operand<double>(std::stod(value));
	return (ret);
}

IOperand const * (OperandFactory::*(OperandFactory::operandArray)[5])( std::string const & value ) const = {
	&OperandFactory::createInt8,
	&OperandFactory::createInt16,
	&OperandFactory::createInt32,
	&OperandFactory::createFloat,
	&OperandFactory::createDouble
};
