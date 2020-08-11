#include <OperandFactory.hpp>
#include <IOperand.hpp>
#include <Operand.hpp>
#include <avm.hpp>

OperandFactory::OperandFactory( void ) {}

IOperand const * OperandFactory::createOperand( IOperand::eOperandType type, std::string const & value ) const {
	return ((this->*operandArray[type])(value));
}
	
IOperand const * OperandFactory::createInt8( std::string const & value ) const
{
	int val = std::stoi(value);
	if (val < INT8_MIN || val > INT8_MAX)
		throw OverflowException();
	Operand<int8_t> *ret = new Operand<int8_t>((int8_t)val);
	return (ret);
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const
{
	int val = std::stoi(value);
	if (val < INT16_MIN || val > INT16_MAX)
		throw OverflowException();
	Operand<int16_t> *ret = new Operand<int16_t>((int16_t)val);
	return (ret);
}

IOperand const * OperandFactory::createInt32( std::string const & value ) const
{
	float val = std::stof(value);
	if (val < INT32_MIN || val > INT32_MAX)
		throw OverflowException();
	Operand<int32_t> *ret = new Operand<int32_t>((int32_t)val);
	return (ret);
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const
{
	double val = std::stod(value);
	if (val < FLT_MIN || val > FLT_MAX)
		throw OverflowException();
	Operand<float> *ret = new Operand<float>((float)val);
	return (ret);
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const
{
	double val = std::stod(value);
	if (val < DBL_MIN || val > DBL_MAX)
		throw OverflowException();
	Operand<double> *ret = new Operand<double>(val);
	return (ret);
}

IOperand const * (OperandFactory::*(OperandFactory::operandArray)[5])( std::string const & value ) const = {
	&OperandFactory::createInt8,
	&OperandFactory::createInt16,
	&OperandFactory::createInt32,
	&OperandFactory::createFloat,
	&OperandFactory::createDouble
};
