#ifndef __IOPERAND_HPP__
# define __IOPERAND_HPP__
# include <avm.hpp>

class IOperand {

	public:

		enum eOperandType { Int8, Int16, Int32, Float, Double };

		virtual int				getPrecision( void ) const = 0;
		virtual eOperandType	getType( void ) const = 0;

		virtual IOperand const *	operator+( IOperand const & rhs ) const = 0;
		virtual IOperand const *	operator-( IOperand const & rhs ) const = 0;
		virtual IOperand const *	operator*( IOperand const & rhs ) const = 0;
		virtual IOperand const *	operator/( IOperand const & rhs ) const = 0;
		virtual IOperand const *	operator%( IOperand const & rhs ) const = 0;

		virtual std::string const & toString( void ) const = 0;

		virtual ~IOperand( void ) {}

};

std::ostream &		operator<<( std::ostream &o, IOperand const &src);

# endif
