#include <Instruction.hpp>

Instruction::Instruction( const std::string &line )
{
	std::string str = trim(line);
	this->op = NULL;
	if (str.rfind("push", 0) == 0)
	{
		this->instruction = push;
		this->op = parser.parseOperand(line);
	}
	else if (str.rfind("pop", 0) == 0)
		this->instruction = pop;
	else if (str.rfind("dump", 0) == 0)
		this->instruction = dump;
	else if (str.rfind("assert", 0) == 0)
	{
		this->instruction = assert;
		this->op = parser.parseOperand(line);
	}
	else if (str.rfind("add", 0) == 0)
		this->instruction = add;
	else if (str.rfind("sub", 0) == 0)
		this->instruction = sub;
	else if (str.rfind("mul", 0) == 0)
		this->instruction = mul;
	else if (str.rfind("div", 0) == 0)
		this->instruction = div;
	else if (str.rfind("mod", 0) == 0)
		this->instruction = mod;
	else if (str.rfind("print", 0) == 0)
		this->instruction = print;
	else if (str.rfind("exit", 0) == 0)
		this->instruction = exit;
	else {
		throw UnknownOperationException();
	}
}

Instruction::Instruction( const Instruction &inst )
{
	const IOperand *op = inst.getOperand();
	this->instruction = inst.getInstruction();
	if (op == NULL)
		this->op = NULL;
	else
		this->op = this->factory.createOperand(op->getType(), op->toString());
}

Instruction &	Instruction::operator=( Instruction const &rhs )
{
	this->instruction = rhs.getInstruction();
	this->op = this->factory.createOperand(rhs.getOperand()->getType(), rhs.getOperand()->toString());
	return (*this);
}

Instruction::~Instruction( void )
{
	delete this->op;
}

Instruction::eInstruction	Instruction::getInstruction( void ) const
{
	return (this->instruction);
}

IOperand const *Instruction::getOperand( void ) const
{
	return (this->op);
}

std::string const Instruction::toString( void ) const
{
	switch(this->instruction)
	{
		case push:
			return "push " + this->op->toString();
			break;
		case pop:
			return "pop";
			break;
		case dump:
			return "dump";
			break;
		case assert:
			return "assert " + this->op->toString();
			break;
		case add:
			return "add";
			break;
		case sub:
			return "sub";
			break;
		case mul:
			return "mul";
			break;
		case div:
			return "div";
			break;
		case mod:
			return "mod";
			break;
		case print:
			return "print";
			break;
		case exit:
			return "exit";
			break;
		default:
			return "unknown";
	}
}

bool	Instruction::exec(std::vector<const IOperand *> &stack)
{
	switch(this->instruction)
	{
		case push: {
			const IOperand *copy = this->factory.createOperand(
				this->op->getType(), this->op->toString()
			);
			stack.push_back(copy);
			break;
		}
		case pop:
			if (stack.size() == 0)
				throw NotEnoughOperandsOnStackException();
			delete stack.back();
			stack.pop_back();
			break;
		case dump: {
			int i = stack.size() - 1;
			while (i >= 0)
			{
				std::cout << *stack[i] << std::endl;
				--i;
			}
			break;
		}
		case assert:
			if (*this->op != *stack.back())
				throw AssertionException(this->op->toString(), stack.back()->toString());
			break;
		case add: {
			if (stack.size() < 2)
				throw NotEnoughOperandsOnStackException();
			const IOperand *op = *stack[stack.size() - 2] + *stack.back();
			delete stack.back();
			stack.pop_back();
			delete stack.back();
			stack.pop_back();
			stack.push_back(op);
			break;
		}
		case sub: {
			if (stack.size() < 2)
				throw NotEnoughOperandsOnStackException();
			const IOperand *op = *stack[stack.size() - 2] - *stack.back();
			delete stack.back();
			stack.pop_back();
			delete stack.back();
			stack.pop_back();
			stack.push_back(op);
			break;
		}
		case mul: {
			if (stack.size() < 2)
				throw NotEnoughOperandsOnStackException();
			const IOperand *op = *stack[stack.size() - 2] * *stack.back();
			delete stack.back();
			stack.pop_back();
			delete stack.back();
			stack.pop_back();
			stack.push_back(op);
			break;
		}
		case div: {
			if (stack.size() < 2)
				throw NotEnoughOperandsOnStackException();
			if (std::stoi(stack.back()->toString()) == 0)
				throw DivModtByZeroException();
			const IOperand *op = *stack[stack.size() - 2] / *stack.back();
			delete stack.back();
			stack.pop_back();
			delete stack.back();
			stack.pop_back();
			stack.push_back(op);
			break;
		}
		case mod: {
			if (stack.size() < 2)
				throw NotEnoughOperandsOnStackException();
			if (std::stoi(stack.back()->toString()) == 0)
				throw DivModtByZeroException();
			const IOperand *op = *stack[stack.size() - 2] % *stack.back();
			delete stack.back();
			stack.pop_back();
			delete stack.back();
			stack.pop_back();
			stack.push_back(op);
			break;
		}
		case print:
			if (stack.back()->getType() != IOperand::Int8)
				std::cout << "Expected an Int8 Operand for Instruction print" << std::endl;
			else {
				char val = std::stoi(stack.back()->toString());
				std::cout << val;
			}
			break;
		case exit:
			return (true);
			break;
		default:
			throw UnknownOperationException();
			break;
	}
	return (false);
}

Instruction::AssertionException::AssertionException(const std::string &expected, const std::string &got) :
str(std::string("Assertion exception: expected : expected " + expected + ", got " + got)) {}

const char * Instruction::AssertionException::what() const throw() {
	return this->str.c_str();
}

OperandParser Instruction::parser = OperandParser();

OperandFactory Instruction::factory = OperandFactory();

std::ostream &	operator<<( std::ostream &o, Instruction const &src)
{
	o << src.toString();
	return (o);
}
