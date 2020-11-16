#include <iostream>
#include "classes.h"

int main()
{
    Base* base1 = new Base();
    Base* base2 = new Base(base1);
    Alpha* a1 = new Alpha(base1, base2);
    Alpha* a2 = new Alpha(a1);
    Red* r1 = new Red();
    Red* r2 = new Red(base1, r1);
    Green* g1 = new Green(base2);
    Green* g2 = new Green();
    Beta* b1 = new Beta();
    Beta* b2 = new Beta(base1);
    cout << Prediction({ a1,a2,r1,r2,base1,base2,b1,g2,b2,g1 }) << endl;
    a1->~Alpha();
    a2->~Alpha();
    r1->~Red();
    r2->~Red();
    base1->~Base();
    base2->~Base();
    b1->~Beta();
    g2->~Green();
    b2->~Beta();
    g1->~Green();
    cout << S;
}
