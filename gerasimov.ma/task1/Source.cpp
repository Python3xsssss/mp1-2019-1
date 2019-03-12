#include <iostream>
#include <conio.h>
using namespace std;

class Polynom
{
private:
	int power;
	double * coeff;

public:
	Polynom()
	{
		power = 0;
		coeff = new double[power + 1];
		for (int i = 0; i <= power; i++)
			coeff[i] = 0;
	}

	Polynom(int p, double * c)
	{
		power = p;
		coeff = new double[power + 1];
		for (int i = 0; i <= power; i++)
			coeff[i] = c[i];
	}

	Polynom(const Polynom& pol)
	{
		power = pol.power;
		coeff = new double[power + 1];
		for (int i = 0; i <= power; i++)
			coeff[i] = pol.coeff[i];
	}

	~Polynom()
	{
		delete[] coeff;
	}

	void Adapt(int pre_power)
	{
		double * tmp = new double[pre_power + 1];
		for (int i = 0; i <= pre_power; i++)
			tmp[i] = coeff[i];
		delete[] coeff;
		coeff = new double[power + 1];
		for (int i = 0; i <= power; i++)
			if (pre_power - i < 0)
				coeff[power - i] = 0;
			else
				coeff[power - i] = tmp[pre_power - i];
		delete[] tmp;
	}

	void SetPower(int p)
	{
		int tmp = power;
		power = p;
		Adapt(tmp);
	}

	void SetCoeff(double * c)
	{
		for (int i = 0; i <= power; i++)
			coeff[i] = c[i];
	}

	void Show()
	{
		bool flag = true;
		for (int i = 0; i <= power; i++)
		{
			if (coeff[i] != 0)
			{
				if (coeff[i] < 0)
					cout << " - ";
				else if (!flag)
					cout << " + ";
				double tmp = abs(coeff[i]);
				if (tmp != 1)
					cout << tmp;
				if (i < power)
					cout << "x";
				if (i < power - 1)
					cout << "^" << power - i;
				flag = false;
			}
		}
		if (flag)
			cout << "0";
	}

	int GetPower()
	{
		return power;
	}

	double GetCoeff(int number)
	{
		return coeff[number];
	}

	double GetValue(double x)
	{
		double result = coeff[power];
		int tmp = x;
		for (int i = power - 1; i >= 0; i--)
		{
			result = result + coeff[i] * tmp;
			tmp *= x;
		}
		return result;
	}

	Polynom GetDerivative()
	{
		double *tmp = new double[power];
		for (int i = 0; i < power; i++)
			tmp[i] = coeff[i] * (power - i);
		Polynom pol = Polynom(power - 1, tmp);
		return pol;
	}

	Polynom& operator= (const Polynom& pol)
	{
		if (power != pol.power)
		{
			delete[] coeff;
			power = pol.power;
			coeff = new double[power + 1];
		}
		for (int i = 0; i <= power; i++)
			coeff[i] = pol.coeff[i];
		return *this;
	}
};

int main()
{
	Polynom pol, der;
	int number, power;
	double x;


	cout << "Enter the power of the polynomial: ";
	cin >> power;
	pol.SetPower(power);
	pol.Show();
	cout << endl;
	double *mas = new double[power];
	cout << "Enter the " << power + 1 << " coefficients of the polynomial: ";
	for (int i = 0; i <= power; i++)
		cin >> mas[i];
	cout << endl;
	pol.SetCoeff(mas);
	pol.Show();
	cout << endl;
	cout << "The power of the polynomial is " << pol.GetPower() << endl << endl;
	cout << "Enter the number of the coefficient which value you want to know: ";
	cin >> number;
	cout << "The value of the coefficient " << number << " is " << pol.GetCoeff(number) << endl << endl;
	cout << "Enter the value of x: ";
	cin >> x;
	cout << "The value of the polynomial with x = " << x << " is " << pol.GetValue(x) << endl << endl;
	der = pol.GetDerivative();
	cout << "The first derivative of the polynomial is: ";
	der.Show();
	cout << endl << "Press any key to exit" << endl;
	_getch();
}