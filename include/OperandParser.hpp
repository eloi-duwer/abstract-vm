#ifndef __OPERAND_PARSER_HPP__
# define __OPERAND_PARSER_HPP__
# include <OperandFactory.hpp>
# include <IOperand.hpp>

class OperandParser {

	public:

		IOperand const * parseOperand( std::string const & line );
	
	private:

		static OperandFactory factory;
};

# endif
