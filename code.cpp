#include <iostream>
using namespace std;

struct Node
{
	char data;
	Node* next;
};

class stack
{
public:
	Node* top;
	int size;
public:
	stack();
	void push(char);
	char pop();
	char peek();
	bool isempty();

};

stack::stack()
{
	top = NULL;
	size = 0;
}

void stack::push(char n)
{
	if (isempty())
	{
		Node* temp = new Node;
		temp->data = n;
		temp->next = NULL;
		top = temp;
	}

	else
	{
		Node* temp = new Node;
		temp->data = n;
		temp->next = top;
		top = temp;
	}

	size++;

}

char stack::peek()
{
	return top->data;
}

bool stack::isempty()
{
	if (top == NULL)
		return 1;
	return 0;
}

char stack::pop()
{
	if (isempty())
	{
		cout << "empty stack";
		return -999;
	}

	else
	{
		int temp = top->data;
		top = top->next;
		size--;
		return temp;
	}
}
//----------------------------------------------------
class queue
{
public:
	Node* front;
	Node* rear;
	int size;
public:
	queue();
	void enqueue(char);
	char peek();
	bool isEmpty();
	char dequeue();
};

queue::queue()
{
	front = NULL;
	rear = NULL;
	size = 0;
}

void queue::enqueue(char d)
{
	Node* temp = new Node;
	temp->data = d;
	temp->next = NULL;

	if (isEmpty())
	{
		rear = temp;
		front = temp;
	}

	else
	{
		rear->next = temp;
		rear = temp;
	}

	this->size++;
}

char queue::peek()
{
	return front->data;
}

bool queue::isEmpty()
{
	if (front == NULL)
		return 1;
	return 0;
}

char queue::dequeue()
{

	if (front == NULL)
	{
		cout << "List is empty";
		return -99;
	}
	int temp = front->data;
	front = front->next;
	size--;
	return temp;
}

class Equation
{
	char* eq;
	int size;
	stack s1;
	queue q1;
public:
	Equation();
	void input();
	void display() const;
	bool isOperator(char);
	bool isBracket(char);
	bool isNumber(char);
	bool Eq_check();
	bool precedence(char, char);
	bool isAddition(char);
	bool isMultiplication(char);
	void postfix();
	void prefix();
	void queue_display(); //to display postfix and prefix equations
	int evaluate();
};

Equation::Equation()
{
	eq = new char[100];
	for (int i = 0; i < 100; i++)
		eq[i] = 0;
	this->size = 0;
}

void Equation::input()
{
	char x;		//making a temp char to store before storing in array to avoid last input
	cout << "\nTo exit input enter =\n";
	for (int i = 0; i < 100; i++)
	{
		cin >> x;
		if (x == '=')
			break;

		eq[i] = x;
		size++;
	}
}

void Equation::display() const
{
	cout << "\nThe equation is : ";
	for (int i = 0; i < size; i++)
		cout << eq[i] << " ";
}

bool Equation::isOperator(char x)
{
	if (x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '%')
		return 1;

	return 0;
}

bool Equation::isBracket(char x)
{
	if (x == '(' || x == ')')
		return 1;

	return 0;
}

bool Equation::isNumber(char x)
{
	if (!isOperator(x) || !isBracket(x))		//if it is not an operator it would be a number
		return 1;

	return 0;
}

bool Equation::Eq_check()
{
	int f_bracket = 0;
	int l_bracket = 0;

	for (int i = 0; i < size; i++)
	{
		if (eq[i] == '(')
			f_bracket++;

		if (eq[i] == ')')
			l_bracket++;

		if (i == 0 && eq[i] == ')') //Equation cannot start with closing bracket			
			return 0;

		if (eq[i] == '(' && eq[i + 1] == ')')	//empty brackets
			return 0;

		if (isOperator(eq[i]) && isOperator(eq[i + 1]))	//2 operators together not possible
			return 0;

		if (eq[i] == '(' && isNumber(eq[i + 1]) && eq[i + 2] == ')' && isNumber(eq[i + 3]))	// (7)7 is not correct so error
			return 0;

		//if (isNumber(eq[i]) && isNumber(eq[i + 1]))	//2 Numbers together not possible due to data type char
			//return 0;
	}


	if (f_bracket != l_bracket)
		return 0;

	if (isOperator(eq[size])) // last element cannot be an operator
		return 0;

	return 1;
}

bool Equation::isAddition(char x)
{
	if (x == '+' || x == '-')
		return 1;

	return 0;
}

bool Equation::isMultiplication(char x)
{
	if (x == '^' || x == '*' || x == '/')
		return 1;

	return 0;
}

bool Equation::precedence(char first, char second)
{
	if (first == second)
		return true;

	if (isMultiplication(first) && isAddition(second))
		return true;

	if (isAddition(first) && isMultiplication(second))
		return false;

	if (isOperator(first) && second == '(')
		return false;

	if (first == '(' && isOperator(second))
		return false;

	if (isOperator(first) && second == ')')
		return true;

	if (first == '(' && second == ')')
		return false;

	if (first == ')' && isOperator(second))
		return false;					//error condtion

	if (isAddition(first) && isAddition(second) || isMultiplication(first) && isMultiplication(second))
		return true;

	if (first == '%' && (isMultiplication(second) || isAddition(second)))
		return true;

	if ((isMultiplication(first) || isAddition(first)) && second == '%')
		return false;
}

void Equation::queue_display()
{
	while (!q1.isEmpty())
	{
		//	if (isBracket(q1.peek()))	//this is used to remove () if they get included by mistake in cue
		//		q1.dequeue();
		//	else
		cout << q1.dequeue() << " ";
	}
}

void Equation::postfix()
{

	for (int i = 0; i < size; i++)
	{
		if (!isBracket(eq[i]) && !isOperator(eq[i]))
			q1.enqueue(eq[i]);

		else
		{
			while (!s1.isempty() && precedence(s1.peek(), eq[i]))
				q1.enqueue(s1.pop());

			if (s1.isempty() || eq[i] != ')')
				s1.push(eq[i]);

			else
				s1.pop();
		}
	}

	while (!s1.isempty())
		q1.enqueue(s1.pop());

}

void Equation::prefix()
{
	char* reverse = new char[100];
	char* orignal = eq;			//storing the orignal array for later use
	for (int i = 0, j = size - 1; i < size; i++, j--)
	{
		reverse[i] = eq[j];

		if (reverse[i] == ')')			//reversing the brackets 
			reverse[i] = '(';

		else if (reverse[i] == ')')
			reverse[i] = '(';
	}

	eq = reverse; //storing the reverse in orignal equation to run the in class functions

	//turned to postfix
	postfix();

	stack temp;		//using stack s1 to store and reverse post fix equation

	while (!q1.isEmpty())			//queue to stack
		temp.push(q1.dequeue());

	while (!temp.isempty())			//back from stack to queue
		q1.enqueue(temp.pop());


	eq = orignal;
}

int Equation::evaluate()
{
	postfix();

	int s = 0;	//size of this equation
	int i;	// used for loop
	stack temp;

	for (i = 0; !q1.isEmpty(); i++, s++)	//storing postfix queue in equation
		eq[i] = q1.dequeue();

	eq[i + 1] = '?';//terminating point

	int a, b, value = 0;

	for (int i = 0; eq[i] != '?'; i++)
	{
		if (!isBracket(eq[i]) && !isOperator(eq[i]))
			temp.push(eq[i] - '0');	//storing ascii

		else if (isOperator(eq[i]))
		{
			b = temp.pop();
			a = temp.pop();

			switch (eq[i])
			{
			case '+':
				value = a + b;
				break;

			case '-':
				value = a - b;
				break;

			case '*':
				value = a * b;
				break;

			case '/':
				value = a / b;
				break;

			case '%':
				value = a % b;
				break;

			case '^':
				//for (int i = 0; i < b; i++)
					//value += a * a;
				int temp = 1;
				for (int i = 0; i < b; i++)
					temp *= a;
				value = temp;

				break;

			}
			temp.push(value);
		}
	}

	return value;
}

int main()
{
	stack s1;
	queue q1;
	Equation x;

jump1:

	int choice;
	cout << "\nPress 1 to enter a numerical Equation e.g.(1+2+3)\nPress 2 to enter abstract equation e.g.(a+b+c)\nEnter your choice : ";
	cin >> choice;

	x.input();

	if (!x.Eq_check())
	{
		int choice;
		cout << "\n\nEquation is not correct\nPress 1 to re-enter\nPress 2 to Abort\nEnter your choice : ";
		cin >> choice;
		if (choice == 1)
			goto jump1;

		return 0;		//code terminated
	}

	x.display();

	x.postfix();
	cout << "\nPostfix equation : ";
	x.queue_display();


	x.prefix();
	cout << "\nPrefix equation : ";
	x.queue_display();


	if (choice == 1)
		cout << "\nAnswer after evaluating equation is : " << x.evaluate();

	cout << endl << endl;

}
