#include <iostream>
using namespace std;

int NOD_pos(int a, int b)
{
	while ((a != 0) && (b != 0))
	{
		if (a > b)
			a = a % b;
		else
			b = b % a;
	}
	if (a == 0)
		return b;
	else
		return a;
}

class Fraction
{
private:
	int nom, denom;
public:
	Fraction()
	{
		nom = 0;
		denom = 1;
	}

	Fraction(int a, int b)
	{
		nom = a;
		denom = b;
		if (denom == 0)
			cout << "Invalid fraction: denominator set as 0." << endl;
		else
			Reduction();
	}

	Fraction(const Fraction& frac)
	{
		nom = frac.nom;
		denom = frac.denom;
	}

	void Reduction()
	{
		int del;
		do
		{
			del = NOD_pos(abs(nom), abs(denom));
			nom /= del;
			denom /= del;
		} while (del > 1);
		if (denom < 0)
		{
			nom *= -1;
			denom *= -1;
		}
	}

	void Show()
	{
		cout << nom << "/" << denom;
	}

	Fraction& operator= (const Fraction& frac)
	{
		nom = frac.nom;
		denom = frac.denom;
		Reduction();
		return *this;
	}

	Fraction operator+ (const Fraction& frac)
	{
		int nok = denom * frac.denom / NOD_pos(denom, frac.denom);
		int tmp_nom = nom * nok / denom + frac.nom * nok / frac.denom;
		int tmp_denom = nok;
		Fraction tmp = Fraction(tmp_nom, tmp_denom);
		return tmp;
	}

	Fraction operator- (const Fraction& frac)
	{
		int nok = denom * frac.denom / NOD_pos(denom, frac.denom);
		int tmp_nom = nom * nok / denom - frac.nom * nok / frac.denom;
		int tmp_denom = nok;
		Fraction tmp = Fraction(tmp_nom, tmp_denom);
		return tmp;
	}

	Fraction operator* (const Fraction& frac)
	{
		int tmp_nom = nom * frac.nom;
		int tmp_denom = denom * frac.denom;
		Fraction tmp = Fraction(tmp_nom, tmp_denom);
		return tmp;
	}

	Fraction operator/ (const Fraction& frac)
	{
		int tmp_nom = nom * frac.denom;
		int tmp_denom = denom * frac.nom;
		Fraction tmp = Fraction(tmp_nom, tmp_denom);
		return tmp;
	}
};



void main()
{
	Fraction frac_1, frac_2;
	int another;
	do
	{
		int nom_1, denom_1;
		do
		{
			cout << "Enter the first fraction in format a/b: ";
			char tmp;
			cin >> nom_1 >> tmp >> denom_1;
			frac_1 = Fraction(nom_1, denom_1);
		} while (denom_1 == 0);

		int nom_2, denom_2;
		do
		{
			cout << "Enter the second fraction in format a/b: ";
			char tmp;
			cin >> nom_2 >> tmp >> denom_2;
			frac_2 = Fraction(nom_2, denom_2);
		} while (denom_2 == 0);

		cout << "Choose the operator:" << endl;
		cout << "1 - addition" << endl << "2 - subtraction" << endl << "3 - multiplication" << endl << "4 - division" << endl;
		int mode;
		cin >> mode;

		Fraction res;
		switch (mode)
		{
		case 1:
			res = frac_1 + frac_2;
			break;
		case 2:
			res = frac_1 - frac_2;
			break;
		case 3:
			res = frac_1 * frac_2;
			break;
		case 4:
			res = frac_1 / frac_2;
			break;
		}
		cout << endl; res.Show(); cout << endl << endl;

		cout << "Try another action? 1 - Yes; 0 - No" << endl;
		cin >> another;
	} while (another == 1);
}