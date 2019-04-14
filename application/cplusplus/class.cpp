// classes example
#include <iostream>
using namespace std;
    
class CRectangle {
		int t1,t2;
		int *width, *height;
	public:
		static int n;
		CRectangle();		
		CRectangle (int,int);
		~CRectangle();
		CRectangle operator + (CRectangle);        
		void set_values(int,int);
		int area(void) {return (*width * *height);}
		int isitme (CRectangle& param);
		friend CRectangle duplicate (CRectangle);
};

CRectangle::CRectangle () {
	width = new int;
	height = new int;
	*width = 5;
	*height = 5;
	t1 = 1;
	t2 = 1;
	n++;
}

CRectangle::CRectangle (int a, int b) {
	width = new int;
	height = new int;
	*width = a;
	*height = b;
	t1 = 2;
	t2 = 2;
	n++;
}

CRectangle::~CRectangle () {
	delete width;
	delete height;
	n--;
}

void CRectangle::set_values (int a, int b) {
        *width = a;
        *height = b;
}

int CRectangle::isitme (CRectangle& param) {
        if (&param == this) return 1;
        else return 0;
}

int CRectangle::n=0;
 
int main () {
	CRectangle recta(3,4);
	CRectangle rectb(5,6);
	CRectangle rectc;
	recta.set_values(4,4);
	
	cout << rectc.n << endl;
	cout << "recta area: " << recta.area()<<endl;
	cout << "rectb area: " << rectb.area()<<endl;
	cout << "rectc area: " << rectc.area()<<endl;


	CRectangle a;
	CRectangle *pb = new CRectangle;
	CRectangle *pc = &a;
	CRectangle *pe = new CRectangle(3,4);
	CRectangle *pd = new CRectangle[2];

	a.set_values (1,2);
	pd->set_values (5,6);
	pd[1].set_values (7,8);


	cout << "a area: " << a.area() << endl;
	cout << "b area: " << pb->area() << endl;
	cout << "*c area: " << pc->area() << endl;
	cout << "d[0] area: " << pd[0].area() << endl;
	cout << "d[1] area: " << pd[1].area() << endl;
	cout << "e area: " << pe->area()<<endl;
	
	if ( pc->isitme(a) )
            cout << "yes, &a is pc"<<endl;
	return 0;
}	
