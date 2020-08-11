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

	private:

		static OperandParser	parser;
		static OperandFactory	factory;
		eInstruction	instruction;
		IOperand const	*op;
 
};

std::ostream &		operator<<( std::ostream &o, Instruction const &src);

# endif
