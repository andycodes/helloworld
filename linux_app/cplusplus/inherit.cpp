#include <iostream>
using namespace std;

class CPolygon {
      protected:
        int width, height;
      public:
        void set_values (int a, int b){width=a; height=b;}
		CPolygon (){ cout << "mother: no parameters\n"; }
		CPolygon (int a){ cout << "mother: int parameter\n"; }
};

class COutput {
      public:
        void output (int i);
};
    
void COutput::output (int i) {
        cout << i << endl;
}

class CRectangle: public CPolygon , public COutput {
public:
    int area (void){ return (width * height); }
};
    
class CTriangle: public CPolygon, public COutput {
public:
	int area (void){ return (width * height / 2); }
};
    
class daughter : public CPolygon {
public:
    daughter (int a){ cout << "daughter: int parameter\n\n"; }
};
    
class son : public CPolygon {
public:
	son (int a) : CPolygon (a){ cout << "son: int parameter\n\n"; }
};

int main () {
        daughter cynthia (1);
        son daniel(1);
        
        CRectangle rect;
        CTriangle trgl;
        rect.set_values (4,5);
        trgl.set_values (4,5);
        cout << rect.area() << endl;
        cout << trgl.area() << endl;
        rect.output (rect.area());
        trgl.output (trgl.area());
        return 0;
}
