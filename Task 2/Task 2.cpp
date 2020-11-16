#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

enum Color
{
	RED,
	BLUE,
    GREEN
};

int NumberOfWords(string line)
{
	line += ' ';
	int counter = 0;
	int word_length = 0;
	for (int i = 0; i < line.length(); i++)
	{
		word_length++;
		if (line[i] == ' ')
		{
			if (word_length > 1 && word_length < 6)
				counter++;
			word_length = 0;
		}
	}
	return counter;
}

Color GetColor(Color c1, Color c2)
{
	if (c1 == BLUE && c2 == RED || c1 == RED && c2 == BLUE)
		return GREEN;
	else if (c1 == BLUE && c2 == GREEN || c1 == GREEN && c2 == BLUE)
		return RED;
	else return BLUE;
}

pair<Color, double> Calc1(pair<Color, double> f1, pair<Color, double> f2)
{
	Color color;
	if (f1.first == f2.first)
		color = f1.first;
	else color = GetColor(f1.first, f2.first);
	return { color, fmod(pow(f1.second, f2.second),661) };
}

pair<Color, double> Calc2(vector<pair<Color, double>> res)
{
	vector<int> colors(3, 0);
	double sum = 0;
	for (int i = 0; i < res.size(); i++)
	{
		colors[res[i].first]++;
		sum += res[i].second * res[res.size() - i].second;
	}
	if (colors[0] > colors[1] && colors[0] > colors[2])
		return { RED,fmod(sum,761) };
	else if (colors[1] > colors[0] && colors[1] > colors[2])
		return { BLUE,fmod(sum,761) };
	else return { GREEN,fmod(sum,761) };
}

template<typename T>
pair<Color,double> f(T value)
{
	
	if constexpr (is_same_v<T, int>)
	{
		if (value >= 0)
		{
			return { Color::RED, fmod(pow(2,value) + pow(value,2),161) };
		}
		return {Color::GREEN, fmod((pow(value,5) + value - 1),261)};
	}
	if constexpr (is_same_v<T, double>)
		return { BLUE, int(1 / sin(log2(value))) % 361 };
	if constexpr (is_same_v<T, string>)
		return { GREEN, NumberOfWords(value) };
	if constexpr (is_same_v < T, pair<int, int>>)
	{
		pair<Color, double> f1 = f<int>(value.first);
		pair<Color, double> f2 = f<int>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v < T, pair<int, double>>)
	{
		pair<Color, double> f1 = f<int>(value.first);
		pair<Color, double> f2 = f<double>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v < T, pair<int, char>>)
	{
		pair<Color, double> f1 = f<int>(value.first);
		pair<Color, double> f2 = f<char>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v < T, pair<int, string>>)
	{
		pair<Color, double> f1 = f<int>(value.first);
		pair<Color, double> f2 = f<string>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v < T, pair<double, int>>)
	{
		pair<Color, double> f1 = f<double>(value.first);
		pair<Color, double> f2 = f<int>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v < T, pair<double, double>>)
	{
		pair<Color, double> f1 = f<double>(value.first);
		pair<Color, double> f2 = f<double>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v < T, pair<int, char>>)
	{
		pair<Color, double> f1 = f<double>(value.first);
		pair<Color, double> f2 = f<char>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v < T, pair<double, string>>)
	{
		pair<Color, double> f1 = f<double>(value.first);
		pair<Color, double> f2 = f<string>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v < T, pair<char, int>>)
	{
		pair<Color, double> f1 = f<char>(value.first);
		pair<Color, double> f2 = f<int>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v < T, pair<char, double>>)
	{
		pair<Color, double> f1 = f<char>(value.first);
		pair<Color, double> f2 = f<double>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v < T, pair<char, char>>)
	{
		pair<Color, double> f1 = f<char>(value.first);
		pair<Color, double> f2 = f<char>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v < T, pair<char, string>>)
	{
		pair<Color, double> f1 = f<char>(value.first);
		pair<Color, double> f2 = f<string>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v < T, pair<string, int>>)
	{
		pair<Color, double> f1 = f<string>(value.first);
		pair<Color, double> f2 = f<int>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v < T, pair<string, double>>)
	{
		pair<Color, double> f1 = f<string>(value.first);
		pair<Color, double> f2 = f<double>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v < T, pair<string, char>>)
	{
		pair<Color, double> f1 = f<string>(value.first);
		pair<Color, double> f2 = f<char>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v < T, pair<string, string>>)
	{
		pair<Color, double> f1 = f<string>(value.first);
		pair<Color, double> f2 = f<string>(value.second);
		return Calc1(f1, f2);
	}

	if constexpr (is_same_v<T, vector<int>>)
	{
		vector<pair<Color,double>> res;
		for (int i = 0; i < value.size(); i++)
			res.push_back(f<int>(value[i]));
		return Calc2(res);
	}

	if constexpr (is_same_v<T, vector<double>>)
	{
		vector<pair<Color, double>> res;
		for (int i = 0; i < value.size(); i++)
			res.push_back(f<double>(value[i]));
		return Calc2(res);
	}

	if constexpr (is_same_v<T, vector<char>>)
	{
		vector<pair<Color, double>> res;
		for (int i = 0; i < value.size(); i++)
			res.push_back(f<char>(value[i]));
		return Calc2(res);
	}

	if constexpr (is_same_v<T, vector<string>>)
	{
		vector<pair<Color, double>> res;
		for (int i = 0; i < value.size(); i++)
			res.push_back(f<string>(value[i]));
		return Calc2(res);
	}

	return { RED,8359 };
}

int main()
{
	return 0;
}
