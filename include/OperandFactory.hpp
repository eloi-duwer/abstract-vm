#ifndef __IOPERANDFACTORY_HPP__
# define __IOPERANDFACTORY_HPP__
# include <IOperand.hpp>
# include <avm.hpp>
# include <limits.h>
# include <cfloat>

class OperandFactory {

	public:

		OperandFactory ( void );
		IOperand const * createOperand( IOperand::eOperandType type, std::string const & value ) const;

		struct Overflow : public std::exception {
			virtual const char *what() const throw() {
				return ("Creating a new Operand would yield to an overflow");
			}
		};

	private: 

		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;

		static IOperand const * (OperandFactory::*operandArray[5])( std::string const & value) const;

};

# endif
