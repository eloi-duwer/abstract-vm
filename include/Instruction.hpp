#ifndef __INSTRUCTION_HPP__
# define __INSTRUCTION_HPP__
# include <IOperand.hpp>
# include <OperandParser.hpp>
# include <vector>

class Instruction
{

	public:

		enum eInstruction { push, pop, dump, assert, add, sub, mul, div, mod, print, exit };
		
		Instruction( const std::string &line );
		Instruction( const Instruction &inst );
		~Instruction( void );

		Instruction &		operator=( Instruction const &rhs );
		eInstruction		getInstruction( void ) const;
		IOperand const		*getOperand( void ) const;
		std::string const	toString( void ) const;
		bool				exec(std::vector<const IOperand *> &stack);

		struct UnknownOperationException : public std::exception {
			virtual const char *what() const throw() {
				return ("Operation unknown");
			}
		};

		struct NotEnoughOperandsOnStackException : public std::exception {
			virtual const char *what() const throw() {
				return ("Not enough operands are available on the stack");
			}
		};

		struct DivModtByZeroException : public std::exception {
			virtual const char *what() const throw() {
				return ("Division or Modulo by zero is not permitted");
			}
		};

		class AssertionException : public std::exception {

			public:

				AssertionException(const std::string &expected, const std::string &got);
				virtual const char *what() const throw();

			private:

				const std::string str;

		};

	private:

		static OperandParser	parser;
		static OperandFactory	factory;
		eInstruction	instruction;
		IOperand const	*op;
 
};

std::ostream &		operator<<( std::ostream &o, Instruction const &src);

# endif
