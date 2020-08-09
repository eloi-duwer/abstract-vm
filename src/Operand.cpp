#ifndef __OPERAND_CPP__
# define __OPERAND_CPP__
# include <IOperand.hpp>
# include <Operand.hpp>
# include <math.h>

template <>
Operand<int8_t>::Operand( int8_t val ):
	value(val), type(Int8),
	str(std::string(std::to_string(val))) {}

template <>
Operand<int16_t>::Operand( int16_t val ):
	value(val), type(Int16),
	str(std::string(std::to_string(val))) {}

template <>
Operand<int32_t>::Operand( int32_t val ):
	value(val), type(Int32),
	str(std::string(std::to_string(val))) {}

template <>
Operand<float>::Operand( float val ):
	value(val), type(Float),
	str(std::string(std::to_string(val))) {}

template <>
Operand<double>::Operand( double val ):
	value(val), type(Double),
	str(std::string(std::to_string(val))) {}

template <typename T>
Operand<T>::Operand( const Operand<T> &op )
{
	this->value = op.getValue();
	this->type = op.getType();
	this->str = std::string(std::to_string(this->value));
}

template <typename T>
Operand<T> &	Operand<T>::operator=( Operand const &rhs )
{
	this->value = rhs->getValue();
	this->type = rhs->getType();
	this->str = std::string(std::to_string(this->value));
	return (*this);
}

template <typename T>
Operand<T>::~Operand( void ) { }

template <typename T>
int					Operand<T>::getPrecision( void ) const
{
	return (this->type);
}

template <typename T>
IOperand::eOperandType		Operand<T>::getType( void ) const
{
	return (this->type);
}

template <typename T>
T					Operand<T>::getValue( void ) const
{
	return (this->value);
}

template <typename T>
std::string const &	Operand<T>::toString( void ) const
{
	return (this->str);
}

template <typename T>
IOperand const *	Operand<T>::operator+( IOperand const &rhs ) const
{
	double	res = (double)this->value + stod(rhs.toString());

	if (this->getPrecision() > rhs.getPrecision())
		return (Operand::factory.createOperand(this->getType(), std::to_string(res)));
	else
		return (Operand::factory.createOperand(rhs.getType(), std::to_string(res)));
}

template <typename T>
IOperand const *	Operand<T>::operator-( IOperand const &rhs ) const
{
	double	res = (double)this->value - stod(rhs.toString());

	if (this->getPrecision() > rhs.getPrecision())
		return (Operand::factory.createOperand(this->getType(), std::to_string(res)));
	else
		return (Operand::factory.createOperand(rhs.getType(), std::to_string(res)));
}

template <typename T>
IOperand const *	Operand<T>::operator*( IOperand const &rhs ) const
{
	double	res = (double)this->value * stod(rhs.toString());

	if (this->getPrecision() > rhs.getPrecision())
		return (Operand::factory.createOperand(this->getType(), std::to_string(res)));
	else
		return (Operand::factory.createOperand(rhs.getType(), std::to_string(res)));
}

template <typename T>
IOperand const *	Operand<T>::operator/( IOperand const &rhs ) const
{
	double	res = (double)this->value / stod(rhs.toString());

	if (this->getPrecision() > rhs.getPrecision())
		return (Operand::factory.createOperand(this->getType(), std::to_string(res)));
	else
		return (Operand::factory.createOperand(rhs.getType(), std::to_string(res)));
}

template <typename T>
IOperand const *	Operand<T>::operator%( IOperand const &rhs ) const
{
	double	res = fmod((double)this->value, stod(rhs.toString()));

	if (this->getPrecision() > rhs.getPrecision())
		return (Operand::factory.createOperand(this->getType(), std::to_string(res)));
	else
		return (Operand::factory.createOperand(rhs.getType(), std::to_string(res)));
}

template <typename T>
OperandFactory	Operand<T>::factory = OperandFactory();

std::ostream &		operator<<( std::ostream &o, IOperand const &src)
{
	o << src.toString();
	return (o);
}

# endif
