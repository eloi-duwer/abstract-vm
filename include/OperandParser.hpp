#ifndef __OPERAND_PARSER_HPP__
# define __OPERAND_PARSER_HPP__
# include <OperandFactory.hpp>
# include <IOperand.hpp>

class OperandParser {

	public:

		IOperand const * parseOperand( std::string const & line );

		struct UnknownOperandException : public std::exception {
			virtual const char *what() const throw() {
				return ("Operand unknown");
			}
		};

		struct ExpectedOperand : public std::exception {
			virtual const char *what() const throw() {
				return ("Operand expected");
			}
		};
	
	private:

		IOperand const * doParseOperand( IOperand::eOperandType, std::string const & line );

		static OperandFactory factory;
};

# endif
