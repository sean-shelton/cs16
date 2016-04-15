// recfun.cpp
// Sean Shelton, Patrick Vidican
// 3/6/16

#include "recfun.h"
using namespace std;

void stars(int n);

void stars(int n) {
    if (n > 0){
    	cout << '*';
    	stars(n-1);
    }
}

void triangle(ostream& outs, unsigned int m, unsigned int n){ // finished
    if (m <= n) {
        stars(m);
        cout << endl;
        triangle(outs, ++m, n);
        stars(--m);
        cout << endl;
    }
}

void numbers(ostream& outs, const string& prefix, unsigned int levels){ // finished
    string s;
    if (levels > 0) {
        for (char i = '1'; i < ':'; i++) {            
            s = (prefix + i) + '.';
            numbers(outs, s, levels-1);
            // insert if here
            //outs << s << endl;
        }
    }
    else {
        outs << prefix << endl;
    }
}

bool bears(int n){ // finished
    // bool win = false;
    
    if ( n == 42 ){
        return true;
    }
    /*if (n < 0) {
        return false;
    }*/
    
    if ( n % 5 == 0){
        if (n % 2 == 0 && bears(n/2))
            return true;
        return bears(n-42);
        //return bears(42);
        //then you may give back exactly 42 bears.
    }
    
    if (( n % 3 == 0 )||( n % 4 == 0)){
        int returner = n % 10;
        //returner = n%10;
        returner = returner * ((n%100)/10);
        
        if (returner != 0) {
            if (n % 2 == 0 && bears(n/2))
                return true;
                //return bears(n/2);
            return bears(n-returner);
        }
        
        if ((returner == 0) && (n % 2 == 0))
            return bears(n/2);

    }
    
    if ( (n % 2) == 0 ){                        // If n is even, then you may give back exactly n/2 bears.
        return bears( n/2 );
    }
    
    return false;
}

void pattern(ostream& outs, unsigned int n, unsigned int i){
    if (n >= 1) {
        
        pattern(outs, n/2, i);
        for (int j = 0; j < i; ++j){
            outs << ' ';
        }
        for (int k = 0; k < n; ++k){
            outs << "* ";
        }
        outs << endl;
        pattern(outs, n/2, i+n);
    }
}