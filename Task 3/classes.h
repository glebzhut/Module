#pragma once
#include <iostream>
#include <vector>

using namespace std;

int S = 0;

class Base 
{
private:
    static int StaticNumberBase;
    int N;

protected:
    Base* child1;
    Base* child2;

    Base(int N) 
    {
        this->N = N;
    }

    Base(Base* child, int N) 
    {
        this->N = N;
        this->child1 = child;
    }

    Base(Base* child1, Base* child2, int N) 
    {
        this->N = N;
        this->child1 = child1;
        this->child2 = child2;
    }

public:
    Base() 
    {
        this->N = StaticNumberBase++;
    }

    Base(Base* child) 
    {
        this->N = StaticNumberBase++;
        this->child1 = child;
    }

    Base(Base* child1, Base* child2) 
    {
        N = StaticNumberBase++;
        this->child1 = child1;
        this->child2 = child2;
    }

    int GetN() const
    {
        return N;
    }

    Base* GetChild1() const
    {
        return child1;
    }

    Base* GetChild2() const 
    {
        return child2;
    }

    virtual ~Base() 
    {
        S = 3 * S + N - 19;
    }
};

int Base::StaticNumberBase = 1;

class Alpha : public Base 
{
private:
    static int StaticNumberAlpha;
    int N;

protected:
    Alpha(int N) : Base(N) 
    {
        this->N = N;
    }

    Alpha(Base* child, int N) : Base(child, N) 
    {
        this->N = N;
    }

    Alpha(Base* child1, Base* child2, int N) : Base(child1, child2, N) 
    {
        this->N = N;
    }

public:
    Alpha() : Base(StaticNumberAlpha) 
    {
        this->N = StaticNumberAlpha++;
    }

    Alpha(Base* child) : Base(child, StaticNumberAlpha) 
    {
        this->N = StaticNumberAlpha++;
    }

    Alpha(Base* child1, Base* child2) : Base(child1, child2, StaticNumberAlpha) 
    {
        this->N = StaticNumberAlpha++;
    }

    virtual ~Alpha() 
    {
        S = S / 3 - N;
    }
};

int Alpha::StaticNumberAlpha = 1;

class Red : public Alpha 
{
private:
    static int StaticNumberRed;
    int N;

public:
    Red() : Alpha(StaticNumberRed) 
    {
        this->N = StaticNumberRed++;
    }

    Red(Base* child) : Alpha(child, StaticNumberRed) 
    {
        this->N = StaticNumberRed++;
    }

    Red(Base* child1, Base* child2) : Alpha(child1, child2, StaticNumberRed) 
    {
        this->N = StaticNumberRed++;
    }

    virtual ~Red() 
    {
        S = S - N / 2;
    }
};

int Red::StaticNumberRed = 1;

class Green : public Alpha 
{
private:
    static int StaticNumberGreen;
    int N;

public:
    Green() : Alpha(StaticNumberGreen) 
    {
        this->N = StaticNumberGreen++;
    }

    Green(Base* child) : Alpha(child, StaticNumberGreen) 
    {
        this->N = StaticNumberGreen++;
    }

    Green(Base* child1, Base* child2) : Alpha(child1, child2, StaticNumberGreen) 
    {
        this->N = StaticNumberGreen++;
    }

    virtual ~Green() 
    {
        S = S - N / 2 - 4;
    }
};

int Green::StaticNumberGreen = 1;

class Beta : public Base 
{
private:
    static int StaticNumberBeta;
    int N;

public:
    Beta() : Base(StaticNumberBeta) 
    {
        this->N = StaticNumberBeta++;
    }

    Beta(Base* child) : Base(child, StaticNumberBeta) 
    {
        this->N = StaticNumberBeta++;
    }

    Beta(Base* child1, Base* child2) : Base(child1, child2, StaticNumberBeta) 
    {
        this->N = StaticNumberBeta++;
    }

    virtual ~Beta() 
    {
        S = S + 2 * N + 5;
    }
};

int Beta::StaticNumberBeta = 1;
/*
int Predict(const Base* element, int S) 
{
    if (element->GetChild1() != nullptr) {
        S = predict(element->getChild1(), S);
    }
    if (element->getChild2() != nullptr) {
        S = predict(element->getChild2(), S);
    }
    string type = typeid(*element).name();
    if (type.find("Alpha") != std::string::npos)
        S = S / 3 - element->getN();
    else if (type.find("Beta") != std::string::npos)
        S = S + 2 * element->getN() + 23;
    else if (type.find("Green") != std::string::npos) {
        S = S - element->getN() / 2 - 40;
        S = S / 3 - element->getN();
    }
    else if (type.find("Red") != std::string::npos) {
        S = S - element->getN() / 2;
        S = S / 3 - element->getN();
    }
    S = 4 * S + element->getN() - 40;
    return S;
}*/

int Prediction(const vector<Base*>& elements) 
{
    int S = 0;
    for (const Base* element : elements) 
    {
        string type = typeid(*element).name();
        if (type.find("Alpha") != std::string::npos)
            S = S / 3 - element->GetN();
        else if (type.find("Beta") != std::string::npos)
            S = S + 2 * element->GetN() + 5;
        else if (type.find("Green") != std::string::npos) 
        {
            S = S - element->GetN() / 2 - 4;
            S = S / 3 - element->GetN();
        }
        else if (type.find("Red") != std::string::npos) 
        {
            S = S - element->GetN() / 2;
            S = S / 3 - element->GetN();
        }
        S = 3 * S + element->GetN() - 19;
    }
    return S;
}


