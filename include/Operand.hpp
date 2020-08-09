#ifndef __OPERAND_HPP__
# define __OPERAND_HPP__
# include <IOperand.hpp>
# include <OperandFactory.hpp>

template< typename T>
class Operand : public IOperand {
	
	public :

		int				getPrecision( void ) const;
		eOperandType	getType( void )	const;
		T				getValue( void ) const;

		Operand( T val );
		Operand( const Operand &op );
		virtual ~Operand();

		Operand &		 operator=( Operand const &rhs );
		IOperand const * operator+( IOperand const &rhs ) const;
		IOperand const * operator-( IOperand const &rhs ) const;
		IOperand const * operator*( IOperand const &rhs ) const;
		IOperand const * operator/( IOperand const &rhs ) const;
		IOperand const * operator%( IOperand const &rhs ) const;

		std::string const & toString( void ) const;

	private:

		T						value;
		eOperandType			type;
		std::string				str;
		static OperandFactory	factory;

};

# include <Operand.cpp>

# endif
