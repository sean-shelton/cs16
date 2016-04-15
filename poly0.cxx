// Sean Shelton, Patrick Vidican
// Jan 24 2016
// poly0.cxx

#include <iostream>
#include <cassert>
#include "poly0.h"
#include <cmath>
#include <climits>

namespace main_savitch_3 {
    //constructor
    polynomial::polynomial(double c, unsigned int exponent){
        assert(exponent <= MAX_EX);
        
        if (c == 0) { current_degree = 0; }
        else { current_degree = exponent; }
        
        for (int i=MAX_EX; i>current_degree; i--){
            coef[i] = 0;
        }
        
        coef[current_degree] = c;
        
        for (int j=0; j<current_degree; j++){
            coef[j] = 0;
        }
    }
    const unsigned int CAPACITY = 30;
	const unsigned int MAX_EX = CAPACITY - 1;
    //modification members
    void polynomial::add_to_coef(double amount, unsigned int exponent){
        assert(exponent <= MAX_EX);
        //if the amount passed here is the negative version of what is already
        //in coef[exponent] then the current degree goes down by 1
        coef[exponent] += amount;
        for (int i = 0; i <= MAX_EX; i++) { 
            if ( coef[i] != 0){
                current_degree = i; 
            }
        }
    }
    void polynomial::assign_coef(double coefficient, unsigned int exponent){
        assert(exponent <= MAX_EX);
        coef[exponent] = coefficient;
        current_degree = exponent;
        // the segfault was because the << wasn't implemented yet but now
        // we have something printing woohoo
        for (int i = 0; i <= MAX_EX; i++) { 
            if ( coef[i] != 0){
                current_degree = i;
            }
        }
 
    }
    void polynomial::clear(){
        for (int i=0; i<=degree(); i++){
            coef[i] = 0;
        }
        current_degree = 0;
    }
    double polynomial::coefficient(unsigned int exponent) const{
        if (exponent > MAX_EX) { return 0; }
        else{ return( coef[exponent] ); }
    }
    // FROM HERE ON OUT DONT USE PRIVATE VARIABLES as per directions
    polynomial polynomial::derivative() const{
        polynomial d;
        for (int j = 0; j <= degree(); j++){
            d.assign_coef( coefficient(j+1)*(j+1), j );
        }
        return ( d );
    }
    
    double polynomial::eval(double x) const{
        double result = coefficient(0); // i changed this to use the function rather than accessing the private array directly
        for (int i=1; i<=degree(); i++){
            result += coefficient(i) * pow( x, i);
        }
        return( result );
    }
    
    unsigned int polynomial::next_term(unsigned int e) const{
        for (int i = (e+1); i <= MAX_EX; i++){
            if (coefficient(i) != 0)
                return i;
        }
        return 0;
    }
    
    unsigned int polynomial::previous_term(unsigned int e) const{
        int prev = UINT_MAX;
        for (int i = 0; i < e; i++){
            if (coefficient(i) != 0)
                prev = i;
        }
        return prev;
    }
    //constant operator is inline so nothing to do here
    
    //nonmember binary operators
    polynomial operator +(const polynomial& p1, const polynomial& p2){
        //double sum;
        polynomial polySum;
        for (int i = 0; i <= MAX_EX; i++) {
            /*sum = (p1.coefficient(i) + p2.coefficient(i));
            polySum.assign_coef*/
            polySum.add_to_coef(p1.coefficient(i), i);
            polySum.add_to_coef(p2.coefficient(i), i);
        }
        return polySum;
    }
    
    //this operator below is done
    polynomial operator -(const polynomial& p1, const polynomial& p2){
        polynomial polySum;
        
        for (int i = 0; i <= MAX_EX; i++) {
            /*sum = (p1.coefficient(i) + p2.coefficient(i));
            polySum.assign_coef*/
            polySum.add_to_coef(p1.coefficient(i), i);
            polySum.add_to_coef((p2.coefficient(i) * -1), i);
        }
        return polySum;
    }
    
    polynomial operator *(const polynomial& p1, const polynomial& p2){
        polynomial product;
        for (int i = 0; i <= p1.degree(); i++) {
            if (p1.coefficient(i) != 0) {
                for (int j = 0; j <= p2.degree(); j++) {
                    if (p2.coefficient(j) != 0) 
                        product.add_to_coef((p1.coefficient(i) * p2.coefficient(j)), (i+j));
                }
            }
        }
        return product;
    }
    //nonmember output function
    std::ostream& operator << (std::ostream& out, const polynomial& p){
        for (int i = p.degree(); i >= 0; i--) {
        
            // this part is just dealing with the coefficients
            
            if (i == p.degree())
                out << p.coefficient( p.degree() );
                
            if (p.coefficient(i) < 0 && i != p.degree()) 
                out << p.coefficient(i) * -1;
            
           
            if (p.coefficient(i) > 0 && i != p.degree()) 
                out << p.coefficient(i);
            
            
           // below is dealing with the x and stuff 
            if (p.coefficient(i) != 0 && i == 1)
                out << "x";
                
            if (p.coefficient(i) != 0 && i > 1)
                out << "x^" << i;
                
            // below deals with + or -
            
            if (p.previous_term(i) != UINT_MAX) {
                if (p.coefficient(p.previous_term(i)) < 0 && p.coefficient(i-1) != 0)
                    out << " - ";
                if (p.coefficient(p.previous_term(i)) > 0 && p.coefficient(i-1) != 0)
                    out << " + ";
            }
        }
        out << "\n";
        return out;
    }
}