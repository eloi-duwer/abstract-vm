#ifndef __IOPERANDFACTORY_HPP__
# define __IOPERANDFACTORY_HPP__
# include <IOperand.hpp>
# include <avm.hpp>

class OperandFactory {

	typedef IOperand const * (OperandFactory::*createPtr)( std::string const & value) const;

	public:

		OperandFactory ( void );
		IOperand const * createOperand( IOperand::eOperandType type, std::string const & value ) const;

	private: 

		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;

		//static createPtr operandArray[5];

		static IOperand const * (OperandFactory::*operandArray[5])( std::string const & value) const;

};

# endif
