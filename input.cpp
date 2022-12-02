#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int SelectData()
{
	cout << "Choose what you want to enter" << endl;

	cout << "1 - int" << endl
		<< "2 - double" << endl
		<< "3 - char" << endl
		<< "4 - string" << endl
		<< endl;

	cout << "Chosen: ----> ";

	string s;
	int number = 0;
	
	/*try
	{
		get;
	}
	catch (const exception& ex)
	{
		cout << e.what();
	}*/

	//cin >> number;

	//base check on normal input

	
	
	return number;
}

class MyInt
{
public:
	int value;
	
	MyInt(int input) : value(input) {}

	friend istream& operator>> (istream& strm, MyInt& a)
	{
		return std::cin >> a.value;
	}
};

class MyDouble
{
public:
	double value;

	friend istream& operator>> (istream& strm, MyDouble& a)
	{
		return std::cin >> a.value;
	}
};

class MyChar
{
public:
	char value;

	friend istream& operator>> (istream& strm, MyChar& a)
	{
		return std::cin >> a.value;
	}
};

class MyString
{
public:
	string value;

	friend istream& operator>> (istream& strm, MyString& a)
	{
		return std::cin >> a.value;
	}
};
/*
class Reader
{
public:
	virtual void read(istream& in) = 0;

	friend istream& operator>>(istream& in, Reader* r);
	friend istream& operator>>(istream& in, Reader& r);
}
*/

class BaseIntValidator
{
public:
	virtual bool Check(int input) = 0;
};

class BaseDoubleValidator
{
public:
	virtual bool Check(double input) = 0;
};

class BaseCharValidator
{
public:

	virtual bool Check(char input) = 0;
};

class IntValidatorIsGreater : public BaseIntValidator
{
public:
	int assignedvalue;

	IntValidatorIsGreater() {}

	IntValidatorIsGreater(int assigned) : assignedvalue(assigned) {}

	bool Check(int input) override
	{
		if (input > assignedvalue)
		{
			return true;
		}
		
		return false;
	}
	
};

class IntValidatorIsLess : public BaseIntValidator
{
public:
	int assignedvalue;

	IntValidatorIsLess() {}

	IntValidatorIsLess(int assigned) : assignedvalue(assigned) {}

	bool Check(int input) override
	{
		if (input < assignedvalue)
		{
			return true;
		}

		return false;
	}

};

class IntValidatorIsEqual : public BaseIntValidator
{
public:
	int assignedvalue;

	IntValidatorIsEqual() {}

	IntValidatorIsEqual(int assigned) : assignedvalue(assigned) {}

	bool Check(int input) override
	{
		if (input == assignedvalue)
		{
			return true;
		}

		return false;
	}
};

class IntValidatorInInterval : public BaseIntValidator
{
public:
	int leftborder;
	int rightborder;

	IntValidatorInInterval() {}
	IntValidatorInInterval(int left, int right) : leftborder(left), rightborder(right) {}

	bool Check(int input)
	{
		if ((input >= leftborder) && (input <= rightborder))
		{
			return true;
		}

		return false;
	}


	
};

class DoubleValidatorIsGreater : public BaseDoubleValidator
{
public:
	double assignedvalue;

	DoubleValidatorIsGreater() {}

	DoubleValidatorIsGreater(double assigned) : assignedvalue(assigned) {}

	bool Check(double input) override
	{
		if (input > assignedvalue)
		{
			return true;
		}

		return false;
	}

};

class DoubleValidatorIsLess : public BaseDoubleValidator
{
public:
	double assignedvalue;

	DoubleValidatorIsLess() {}

	DoubleValidatorIsLess(double assigned) : assignedvalue(assigned) {}

	bool Check(double input) override
	{
		if (input < assignedvalue)
		{
			return true;
		}

		return false;
	}

};

class CharValidatorIsEqual : public BaseCharValidator
{
public:
	char assignedvalue;

	CharValidatorIsEqual() {}

	CharValidatorIsEqual(char assigned) : assignedvalue(assigned) {}

	bool Check(char input) override
	{
		if (input == assignedvalue)
		{
			return true;
		}
		
		return false;
	}
};



int main(void)
{

	
/*
	int res;
	res = SelectData();
	cout << "res = " << res;
*/

/*
	int inum;
	double dnum;
	size_t position = 0;
	size_t* address = &position;

	string str;
	string str2;

	cout << "enter string" << endl;


	//getline(cin, str);

	str = "2326 443 35";
	while (!str.empty())
	{
		inum = stoi(str, address);//to integer
		cout << "string -->" << str << "<---" << endl;
		cout << "extracted number = " << inum << endl;
		str = str.substr(*address);
		cout << "new str -->" << str << "<--" << endl << endl;
	}
	
	str2 = "3.144 543.6 4.5";
	while (!str2.empty())
	{
		dnum = stof(str2, address);//to double
		cout << "string2 -->" << str2 << "<---" << endl;
		cout << "extracted number = " << dnum << endl;
		str2 = str2.substr(*address);
		cout << "new str2 -->" << str2 << "<--" << endl << endl;
	}
*/

///////////////////////operator>> test///////////////////////////

	MyInt ttt(5);

	cout << "enter integer value --->";
	cin >> ttt;

	cout << "value = " << ttt.value << endl;

	//string IntTest;

	//cout << "enter string --->";
	//getline(cin, IntTest);

////////////////////////IntValidator test///////////////////////////

	IntValidatorIsGreater IntValIG;
	IntValidatorIsLess IntValIL;
	IntValidatorIsEqual IntValIE;
	IntValidatorInInterval IntValII;

	IntValIG.assignedvalue = 100;
	IntValIL.assignedvalue = 100;
	IntValIE.assignedvalue = 100;
	IntValII.leftborder = 10;
	IntValII.rightborder = 50;
/*
	if (IntValIG.Check(500))
	{
		cout << "this is greater!" << endl;
	}
	else
	{
		cout << "this is not greater!" << endl;
	}

	if (IntValIL.Check(50))
	{
		cout << "this is less!" << endl;
	}
	else
	{
		cout << "this is not less!" << endl;
	}

	if (IntValIE.Check(100))
	{
		cout << "this is equal!" << endl;
	}
	else
	{
		cout << "this is not equal!" << endl;
	}

	if (IntValII.Check(-50))
	{
		cout << "this is in interval!" << endl;
	}
	else
	{
		cout << "this is not in interval!" << endl;
	}
*/

	if (IntValIG.Check(ttt.value))
	{
		cout << ttt.value << " is greater than "<< IntValIG.assignedvalue << endl;
	}
	else
	{
		cout << ttt.value << " is NOT greater than " << IntValIG.assignedvalue << endl;
	}


	return 0;
}
