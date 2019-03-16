#include <iostream>
#include <conio.h>
using namespace std;

class IntegralCount
{
private:
	double(*func)(double arg);
	double downlim, uplim;
	unsigned int quantity;
	char mode;
	long double result;
public:
	IntegralCount()
	{
		uplim = downlim = 0;
		quantity = 0;
		mode = 'm';
		result = 0;
	}

	IntegralCount(double(*f)(double a), double down, double up, unsigned int num, char m)
	{
		func = f;
		downlim = down;
		uplim = up;
		quantity = num;
		mode = m;
		result = 0;
	}

	IntegralCount(const IntegralCount& count)
	{
		func = count.func;
		downlim = count.downlim;
		uplim = count.uplim;
		quantity = count.quantity;
		mode = count.mode;
		result = 0;
	}

	~IntegralCount() {}

	void SetFunc(double(*f) (double a))
	{
		func = f;
	}

	void SetLimits(double down, double up)
	{
		uplim = up;
		downlim = down;
	}

	void GetLimits(double &down, double &up)
	{
		up = uplim;
		down = downlim;
	}

	void SetNumber(unsigned int num)
	{
		quantity = num;
	}

	void SetMode(char m)
	{
		mode = m;
	}

	void ShowResult()
	{
		cout << endl << "Result = " << result << endl;
	}

	long double Count()
	{
		double step = (uplim - downlim) / quantity;
		bool flag = true;
		result = 0;

		for (unsigned int i = 0; (i < quantity) && (flag); i++)
		{
			double a, b;
			switch (mode)
			{
			case 'l':
				a = downlim + step * i;
				b = a + step;
				result += func(a) * (b - a);
				break;
			case 'm':
				a = downlim + step * i;
				b = a + step;
				result += func((a + b) / 2) * (b - a);
				break;
			case 'r':
				a = downlim + step * i;
				b = a - step;
				result += func(a) * (a - b);
				break;
			default:
				flag = false;
				cout << "This integration method does not exist" << endl;
				break;
			}
		}
		return result;
	}
};

void main()
{
	IntegralCount test;

	unsigned short int another;
	do
	{
		cout << "1 - abs(x)" << endl;
		cout << "2 - sqrt(x)" << endl;
		cout << "3 - exp(x)" << endl;
		cout << "4 - sin(x)" << endl;
		cout << "5 - cos(x)" << endl;
		cout << "6 - log(x)" << endl;
		cout << "7 - log10(x)" << endl;
		cout << "8 - asin(x)" << endl;
		cout << "Choose the function from the list above: ";
		unsigned short int num;
		cin >> num;
		num -= 1;
		double(*func[8])(double arg) = { abs, sqrt, exp, sin, cos, log, log10, asin };
		test.SetFunc(func[num]);

		cout << endl << "Set the limits of the integration: ";
		double down, up;
		cin >> down >> up;
		test.SetLimits(down, up);

		cout << endl << "Set the number of cuts: ";
		unsigned int cuts;
		cin >> cuts;
		test.SetNumber(cuts);

		cout << endl << "Set the mode (l - left rectangles; m - middle rectangles; r - right rectangles): ";
		char mode;
		cin >> mode;
		test.SetMode(mode);

		double result = test.Count();
		test.ShowResult();

		double downtest, uptest;
		test.GetLimits(downtest, uptest);
		cout << "The limits were: " << downtest << " " << uptest << endl;

		cout << endl << "Want to calculate another integral? (1 - Yes; 0 - No)" << endl;
		cin >> another;
	} while (another != 0);
	cout << "Have a nice day!" << endl;
	_getch();
}