#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

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

//////////////////////////////////////////////////////////

class BaseType
{
public:

	BaseType() {}

	virtual void reader(istream& strm /*, BaseType* this */) = 0;

	friend istream& operator>> (istream& strm, BaseType& a)
	{
		a.readcycle(strm);
		return strm;
	}

private:
	void readcycle(istream& strm)
	{			
		bool flag = true;
		while (flag)
		{
			try
			{
				flag = false;
				
				char c = strm.peek();
				if (c == 4)// CTRL+D
				{
					break;
				}

				reader(strm);
			}
			catch (const std::invalid_argument)
			{
				flag = true;
				std::cerr << "invalid argument! try again..." << endl;
			}
			catch (const std::out_of_range)
			{
				flag = true;
				std::cerr << "entered value is out of range for <int> type! try again..." << endl;
			}
			catch (string s)//catch (string MyExeption)
			{
				flag = true;
				std::cerr << s << endl;
			}
		}
	}

};

class MyInt : public BaseType
{
public:
	int value = 0;

	vector<BaseIntValidator*> IntValArray;
	
	MyInt() {}

	MyInt(int input) : value(input) {}

	//MyInt(vector<BaseIntValidator> IntValArray) {}

	void addIntValidator(BaseIntValidator* IntVal)
	{
		IntValArray.push_back(IntVal);
	}

	bool checker(int value)
	{
		bool isEverythingOK = true;

		for (size_t i = 0; i < IntValArray.size(); i++)
		{
			if (IntValArray[i]->Check(value))
			{
				cout << "validator #" << i << " used. ----> true" << endl << endl;
			}
			else
			{
				cout << "validator #" << i << " used. ----> false" << endl << endl;
				isEverythingOK = false;
			}
		}

		return isEverythingOK;
	}

	void reader(istream& strm) override
	{
		bool isEverythingOK = false;

		while (!isEverythingOK)
		{
			cout << "you must enter normal value! ----->";
			string temp;
			strm >> temp;

			cout << endl;

			size_t position = 0;
			value = stoi(temp, &position);

			if (position < temp.size())
			{
				throw std::string("something hadn't been read! try again...");
			}

			isEverythingOK = checker(value);
		}	
	}
};

class MyDouble : public BaseType
{
public:
	double value = 0;

	vector<BaseDoubleValidator*> DoubleValArray;

	MyDouble() {}

	MyDouble(double input) : value(input) {}

	//MyDouble(vector<BaseDoubleValidator> DoubleValidatorArray) {}

	void addDoubleValidator(BaseDoubleValidator* DoubleVal)
	{
		DoubleValArray.push_back(DoubleVal);
	}

	bool checker(double value)
	{
		bool isEverythingOK = true;

		for (size_t i = 0; i < DoubleValArray.size(); i++)
		{
			if (DoubleValArray[i]->Check(value))
			{
				cout << "validator #" << i << " used. ----> true" << endl << endl;
			}
			else
			{
				cout << "validator #" << i << " used. ----> false" << endl << endl;
				isEverythingOK = false;
			}
		}

		return isEverythingOK;
	}

	void reader(istream& strm) override
	{
		bool isEverythingOK = false;

		while (!isEverythingOK)
		{
			cout << "you must enter normal value! ----->";
			string temp;
			strm >> temp;

			cout << endl;

			size_t position = 0;
			value = stod(temp, &position);

			if (position < temp.size())
			{
				throw std::string("something hadn't been read! try again...");
			}

			isEverythingOK = checker(value);
		}				
	}
};

class MyChar : public BaseType
{
public:
	char value = 0;

	vector<BaseCharValidator*> CharValArray;

	MyChar() {}
	
	MyChar(char input) : value(input) {}

	//MyChar(vector<BaseCharValidator> CharValidatorArray) {}

	void addCharValidator(BaseCharValidator* CharVal)
	{
		CharValArray.push_back(CharVal);
	}

	bool checker(char value)
	{
		bool isEverythingOK = true;

		for (size_t i = 0; i < CharValArray.size(); i++)
		{
			if (CharValArray[i]->Check(value))
			{
				cout << "validator #" << i << " used. ----> true" << endl << endl;
			}
			else
			{
				cout << "validator #" << i << " used. ----> false" << endl << endl;
				isEverythingOK = false;
			}
		}

		return isEverythingOK;
	}

	void reader(istream& strm) override
	{
		bool isEverythingOK = false;

		while (!isEverythingOK)
		{
			cout << "you must enter normal value! ----->";
			string temp;
			strm >> temp;

			if (temp.size() > 1)
			{
				throw std::string("you entered more than 1 symbol, invalid input! try again...");
			}

			value = temp[0];

			isEverythingOK = checker(value);
		}

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

//////////////////////////////////////////////////////////

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
			cout << "IntValidatorIsGreater: " << input << " is greater than " << assignedvalue << endl;
			return true;
		}
		else
		{
			cout << "IntValidatorIsGreater: " << input << " is NOT greater than " << assignedvalue << endl;
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
			cout << "IntValidatorIsLess: " << input << " is less than " << assignedvalue << endl;
			return true;
		}
		else
		{
			cout << "IntValidatorIsLess: " << input << " is NOT less than " << assignedvalue << endl;
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
			cout << "IntValidatorIsEqual: " << input << " is equal to " << assignedvalue << endl;
			return true;
		}
		else
		{
			cout << "IntValidatorIsEqual: " << input << " is NOT equal to " << assignedvalue << endl;
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

	bool Check(int input) override
	{
		if ((input >= leftborder) && (input <= rightborder))
		{
			cout << "IntValidatorInInterval: " << input << " is in interval [" << leftborder << "; " << rightborder << "]" << endl;
			return true;
		}
		else
		{
			cout << "IntValidatorInInterval: " << input << " is NOT in interval [" << leftborder << "; " << rightborder << "]" << endl;
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
			cout << "DoubleValidatorIsGreater: " << input << " is greater than " << assignedvalue << endl;
			return true;
		}
		else
		{
			cout << "DoubleValidatorIsGreater: " << input << " is NOT greater than " << assignedvalue << endl;
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
			cout << "DoubleValidatorIsLess: " << input << " is less than " << assignedvalue << endl;
			return true;
		}
		else
		{
			cout << "DoubleValidatorIsLess: " << input << " is NOT less than " << assignedvalue << endl;
		}

		return false;
	}

};

class DoubleValidatorIsEqual : public BaseDoubleValidator
{
public:
	double assignedvalue;

	DoubleValidatorIsEqual() {}

	DoubleValidatorIsEqual(double assigned) : assignedvalue(assigned) {}

	bool Check(double input) override
	{
		if (input == assignedvalue)
		{
			cout << "DoubleValidatorIsEqual: " << input << " is equal to " << assignedvalue << endl;
			return true;
		}
		else
		{
			cout << "DoubleValidatorIsEqual: " << input << " is NOT equal to " << assignedvalue << endl;
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
			cout << "CharValidatorIsEqual: " << input << " is equal to " << assignedvalue << endl;
			return true;
		}
		else
		{
			cout << "CharValidatorIsEqual: " << input << " is NOT equal to " << assignedvalue << endl;
		}
		
		return false;
	}
};

class CharValidatorIsDigit : public BaseCharValidator
{
public:
	char assignedvalue;

	CharValidatorIsDigit() {}

	bool Check(char input) override
	{
		if (isdigit(input))
		{
			cout << "CharValidatorIsDigit: '" << input << "' is digit" << endl;
			return true;
		}
		else
		{
			cout << "CharValidatorIsDigit: '" << input << "' is NOT a digit" << endl;
		}

		return false;
	}
};



int main(void)
{
/*
	int inum;
	double dnum;
	size_t position = 0;
	size_t* address = &position;

	string str;
	string str2;

	cout << "enter string" << endl;


	//getline(cin, str);

	cin >> str;

	//str = "2326 443 35";
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
/*
	

	//cout << "enter integer value --->";
	//cin >> ttt;

	//cout << "value = " << ttt.value << endl;

	//string IntTest;

	//cout << "enter string --->";
	//getline(cin, IntTest);
*/	
////////////////////////IntValidator test///////////////////////////

	MyInt ttt;

	IntValidatorIsGreater IntValIG;
	IntValidatorIsLess IntValIL;
	IntValidatorIsEqual IntValIE;
	IntValidatorInInterval IntValII;

	IntValIG.assignedvalue = 100;
	IntValIL.assignedvalue = 100;
	IntValIE.assignedvalue = 25;
	IntValII.leftborder = 10;
	IntValII.rightborder = 50;

	//ttt.addIntValidator(&IntValIG);
	ttt.addIntValidator(&IntValIL);
	ttt.addIntValidator(&IntValIE);
	ttt.addIntValidator(&IntValII);

	//with validators now
	cout << "enter integer value --->";
	cin >> ttt;


////////////////////////DoubleValidator test//////////////////////////////////////

	
	MyDouble ddd;

	DoubleValidatorIsGreater DoubleValIG;
	DoubleValidatorIsLess DoubleValIL;
	DoubleValidatorIsEqual DoubleValIE;

	DoubleValIG.assignedvalue = 100.0;
	DoubleValIL.assignedvalue = 100.0;
	DoubleValIE.assignedvalue = 25.0;

	//ddd.addDoubleValidator(&IntValIG);
	ddd.addDoubleValidator(&DoubleValIL);
	ddd.addDoubleValidator(&DoubleValIE);

	//with validators now
	cout << "enter double value --->";
	cin >> ddd;


//////////////////////////CharValidator test////////////////////////////////////

	MyChar kkk;

	CharValidatorIsEqual CharValIE;
	CharValidatorIsDigit CharValID;

	CharValIE.assignedvalue = '5';

	kkk.addCharValidator(&CharValIE);
	kkk.addCharValidator(&CharValID);

	//with validators now
	cout << "enter char value --->";
	cin >> kkk;





	return 0;
}
