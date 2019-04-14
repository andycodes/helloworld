    // friend functions
#include <iostream>
using namespace std;

    class CSquare;
    class CRectangle {
        int width, height;
      public:
        void set_values (int, int);
        int area (void) {return (width * height);}
        friend CRectangle duplicate (CRectangle);
        void convert (CSquare a);
    };
    
    void CRectangle::set_values (int a, int b) {
        width = a;
        height = b;
    }
    
    CRectangle duplicate (CRectangle rectparam) {
        CRectangle rectres;
        rectres.width = rectparam.width*2;
        rectres.height = rectparam.height*2;
        return (rectres);
    }

class CSquare {
      private:
        int side;
      public:
        void set_side (int a){side=a;}
        friend class CRectangle;
};

void CRectangle::convert (CSquare a) {
        width = a.side;
        height = a.side;
}
    
    int main () {
        CSquare sqr;
        CRectangle rect;
        sqr.set_side(4);
        rect.convert(sqr);
        cout << rect.area()<<endl;
        
        
        CRectangle recta, rectb;
        recta.set_values (2,3);
        rectb = duplicate (recta);
        cout << rectb.area()<<endl;
    }
