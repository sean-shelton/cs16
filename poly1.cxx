// Sean Shelton, Patrick Vidican
// Feb 7 2016
// poly1.cxx

// Duplicated our original solution with the purpose of trying to figure out each part slowly, one at a time.
// Currently working on: test 2, the derivative
// Need to overload assignment operator
// Destructor is causing certain problems, not implemented for now.

#include <iostream>
#include <cassert>
#include "poly1.h"
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;
//test 2  (derivative)           FAIL
//test 11 (assignment operator)  FAIL (incorrect degree)
//test 5  (operator +)           ERROR
//test 6  (operator -)           ERROR
//test 7  (operator *)           malloc corruption
//test 9  (find_root)            FAIL not implemented
//test 8  (operator <<)          PASS
//test 1  (basics)               PASS
//test 10 (copy constructor)     PASS
//test 4  (next and prev)        PASS
//test 3  (eval and operator() ) PASS

namespace main_savitch_4 {
    bool near(double a, double b);
    bool near(double a, double b) {
        const double small = 0.0001;

        return (fabs(a-b) < small) || (fabs(1-a/b) < small);
    }

    //constructor
    polynomial::polynomial(double c, unsigned int exponent) {
    //    assert(exponent <= DEFAULT_CAPACITY);

        if (near(c, 0))
	        current_degree = 0;
	        //size = 1; //might change to 0 if needed
        else
            current_degree = exponent;
	        //size = exponent + 1;

        /*for (int i=DEFAULT_CAPACITY; i>current_degree; i--)
            *(coef + i) = 0;*/

	    //if (current_degree < DEFAULT_CAPACITY)

	    if (exponent == 0)
	        size = DEFAULT_CAPACITY;
	    else
	        size = exponent + 1;
            //coef = new double [current_degree + 1];

	    coef = new double[size];

 	    for (int j=0; j < size; j++)
            *(coef + j) = 0;

        *(coef + exponent) = c;
    }

    // copy constructor
    polynomial::polynomial(const polynomial &source) {

	    /*if (source.current_degree < DEFAULT_CAPACITY)
	        size = DEFAULT_CAPACITY;
	        //coef = new double[DEFAULT_CAPACITY];
	    else
	        size = source.size;
	        //coef = new double[source.current_degree + 1];*/
	    size = source.size;
	    coef = new double[size];
	    current_degree = source.current_degree;
	    //copy(source.coef, source.coef + size, coef);
	    copy(source.coef, source.coef + size, coef);
    }

	polynomial::~polynomial( ) {
	    //cout << "delete!\n";
	    //if (coef)
	    delete [] coef;
	}

    // not tested yet
    polynomial& polynomial::operator =(const polynomial& source){
        //polynomial p;
	    double *new_coef;

	    // Check for possible self-assignment:
	    if (this == &source)
	        return *this;

	    // If needed, allocate an array with a different size:
	    if (this->size != source.size) {
	        new_coef = new double[ source.size ];
	        delete [ ] this->coef;
	        this->coef = new_coef;
	        this->size = source.size;
	    }

	    // Copy the data from the source array:
	    this->current_degree = source.current_degree;
	    copy(source.coef, source.coef + source.size, this->coef);

	    return *this;
	}

    //modification members
    void polynomial::add_to_coef(double amount, unsigned int exponent) {
    //    assert(exponent <= DEFAULT_CAPACITY);

        if ((current_degree < exponent) && (amount != 0))
	        current_degree = exponent;


    	if ((exponent >= size) && (amount != 0)) {
    	    reserve(exponent+1);
    	    size = exponent + 1;
	    }

	    *(coef + exponent) += amount;

        //if (*(coef + current_degree) == 0)
        if (near(0, coef[current_degree])) {
            current_degree = previous_term(current_degree);
            if (current_degree == UINT_MAX)
                current_degree = 0;
            //coef[current_degree] = 0;
        }
	       /* for (int i = 0; i <= DEFAULT_CAPACITY; i++) {
            if ( coef[i] != 0){
                current_degree = i;
            }
        }*/
    }

    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
    //    assert(exponent <= DEFAULT_CAPACITY);
        //coef[exponent] = coefficient;

    	if (exponent >= size) {
	        size = exponent + 1;
            //reserve(exponent+1);
            reserve(size);
	    }

	    *(coef + exponent) = coefficient;
        /*for (int i = 0; i <= DEFAULT_CAPACITY; i++) {
            if ( coef[i] != 0){
                current_degree = i;
            }
        }*/
        if (current_degree < exponent)
	        current_degree = exponent;

        if (*(coef + current_degree) == 0) {
            current_degree = previous_term(current_degree);
            if (current_degree == UINT_MAX)
                current_degree = 0;
        }

    }

    void polynomial::clear(){
        for (int i=0; i<=degree(); i++)
    	    *(coef + i) = 0;
            //coef[i] = 0;

        current_degree = 0;
    }

    void polynomial::reserve(unsigned int number) {
	    /*if (number == size)
	        return;*/

	    if (number < size)
	        number = degree()+1;
	        //return;
	        //number = size;
        number += 5;
	    double *largerCoef = new double[number];

	    for (int i = 0; i < number; i++)
	        largerCoef[i] = 0;

	    //copy(coef, coef + size, largerCoef);
	    copy(coef, coef + size+1, largerCoef);
    	delete [ ] coef;
    	coef = largerCoef;
    	size = number;
    }

    double polynomial::coefficient(unsigned int exponent) const{
        //if (exponent > DEFAULT_CAPACITY)
    	if (exponent > size)
    	    return 0;
        else
    	    return( *(coef + exponent) );
    }
    // FROM HERE ON OUT DONT USE PRIVATE VARIABLES as per directions
    polynomial polynomial::derivative() const{
        polynomial d(0,0);
        if ( degree() == 0 ){
            return d;
        }
        //polynomial d( degree()*coefficient( degree() ), degree()-1 );

        for (int i = degree(); i != UINT_MAX; i = previous_term(i)){
            if (i == 0)
                return d;
                //d.assign_coef(0, 0);
            else
                d.assign_coef(i*coefficient(i), i-1);
        }
        /*for (int j = 0; j <= degree(); j++)
            d.assign_coef( coefficient(j+1)*(j+1), j );*/

        return d;
    }

    double polynomial::eval(double x) const{
        double result = coefficient(0); // i changed this to use the function rather than accessing the private array directly
        for (int i=1; i<=degree(); i++){
            result += coefficient(i) * pow( x, i);
        }
        return( result );
    }

    void polynomial::find_root(
	    double& answer,
	    bool& success,
	    unsigned int& iterations,
	    double guess,
	    unsigned int maximum_iterations,
	    double epsilon
	    )
    const {
        assert( epsilon > 0 );                                                  //assert precondition that epsilon must be greater than zero
        polynomial d( derivative() );                                           // calculate derivative of the polynomial
        answer = guess;                                                         // set answer to starting guess
        double f = eval( answer );                                              // initialize a variable f by evaluating polynomial at answer
        double fprime = d.eval( answer );                                       // initialize a variable fprime by evaluating derivative at answer
        
        // set iterations to 0 // loop until maximum iterations or until either |f| or |fprime| is less than or equal to epsilon: // increment iterations
        /*for (iterations = 0; iterations <= maximum_iterations|| ((fabs(fprime) > epsilon)||(fabs(f) > epsilon)); iterations++){
            answer -= (f/fprime);                                               // calculate new answer as prior answer - f / fprime
            f = eval( answer );                                                 // reset f by evaluating polynomial at new answer
            fprime = d.eval( answer );                                          // reset fprime by evaluating derivative at new answer
        }
        if ( fabs(f) < epsilon )                                            // set success true if |f| is less than epsilon, or false otherwise
            success = true;
        else 
            success = false;*/
        
        for (iterations = 0; iterations < maximum_iterations; iterations++){
            if (fabs(f) < epsilon)
                success = true;
            else
                success = false;
            if ((fabs(fprime) <= epsilon)||(fabs(f) <= epsilon)) {
                //success = true;
                return;
            }
            answer -= (f/fprime);                                               // calculate new answer as prior answer - f / fprime
            f = eval( answer );                                                 // reset f by evaluating polynomial at new answer
            fprime = d.eval( answer );                                          // reset fprime by evaluating derivative at new answer
        }
        //success = false;
    }

    unsigned int polynomial::next_term(unsigned int e) const{
        for (int i = (e+1); i < size /*DEFAULT_CAPACITY*/; i++){
            if (coefficient(i) != 0)
                return i;
        }
        return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const{
        //int prev = UINT_MAX;
        /*for (int i = 0; i < e; i++){
            if (coefficient(i) != 0)
                prev = i;
        }*/
        for (int i = e-1; i >= 0; i--) {
            //if (coefficient(i) != 0) {
            if (fabs(coefficient(i))-0 >= 0.0001)
                return i;
        }
        //return prev;
        return UINT_MAX;
    }
    //constant operator is inline so nothing to do here

    //nonmember binary operators
    polynomial operator +(const polynomial& p1, const polynomial& p2){
        //double sum;
    	unsigned int largest_degree = 0;

    	if (p1.degree() > p2.degree())
    	    largest_degree = p1.degree();
    	else
    	    largest_degree = p2.degree();

    	polynomial polySum(0, largest_degree);
    	//polySum.reserve(largest_degree + 1);
        /*for (int i = 0; i <= largest_degree; i++) {
            //sum = (p1.coefficient(i) + p2.coefficient(i));
            //polySum.assign_coef
            polySum.add_to_coef(p1.coefficient(i), i);
            polySum.add_to_coef(p2.coefficient(i), i);
        }*/
        //polynomial polySum;

        for (int i = p1.degree(); i != UINT_MAX; i = p1.previous_term(i))
            polySum.add_to_coef(p1.coefficient(i), i);

        for (int j = p2.degree(); j != UINT_MAX; j = p2.previous_term(j))
            polySum.add_to_coef(p2.coefficient(j), j);


        return polySum;
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2){
        unsigned int largest_degree = 0;

    	if (p1.degree() >= p2.degree())
    	    largest_degree = p1.degree();
    	else
    	    largest_degree = p2.degree();

    	polynomial polySum(0, largest_degree);

        /*for (int i = 0; i <= largest_degree; i++) {
            //sum = (p1.coefficient(i) + p2.coefficient(i));
            //polySum.assign_coef
            polySum.add_to_coef(p1.coefficient(i), i);
            polySum.add_to_coef((p2.coefficient(i) * -1), i);
        }*/
        //polynomial polySum;
        for (int i = p1.degree(); i != UINT_MAX; i = p1.previous_term(i))
            polySum.add_to_coef(p1.coefficient(i), i);

        for (int j = p2.degree(); j != UINT_MAX; j = p2.previous_term(j))
            polySum.add_to_coef((p2.coefficient(j) * -1), j);

        return polySum;
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2){
        unsigned int largest_degree = 0;

    	if (p1.degree() >= p2.degree())
    	    largest_degree = p1.degree();
    	else
    	    largest_degree = p2.degree();

    	polynomial product(0, largest_degree);

        /*for (int i = 0; i <= p1.degree(); i++) {
            if (p1.coefficient(i) != 0) {
                for (int j = 0; j <= p2.degree(); j++) {
                    if (p2.coefficient(j) != 0)
                        product.add_to_coef((p1.coefficient(i) * p2.coefficient(j)), (i+j));
                }
            }
        }*/
        for (int i = p1.degree(); i != UINT_MAX; i = p1.previous_term(i)) {
            for (int j = p2.degree(); j != UINT_MAX; j = p2.previous_term(j))
                product.add_to_coef((p1.coefficient(i) * p2.coefficient(j)), (i+j));
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


            if (p.coefficient(i) > 0 && i != p.degree() && !(near(0, p.coefficient(i))))
                out << p.coefficient(i);


           // below is dealing with the x and degrees
            if (p.coefficient(i) != 0 && i == 1 && !(near(0, p.coefficient(i))))
                out << "x";

            if (p.coefficient(i) != 0 && i > 1 && !(near(0, p.coefficient(i))))
                out << "x^" << i;

            // below deals with + or -

            if (p.previous_term(i) != UINT_MAX) {
                if (p.coefficient(p.previous_term(i)) < 0 && p.coefficient(i-1) != 0 && !(near(0, p.coefficient(i-1))))
                    out << " - ";
                if (p.coefficient(p.previous_term(i)) > 0 && p.coefficient(i-1) != 0 && !(near(0, p.coefficient(p.previous_term(i)))) && !(near(0, p.coefficient(i-1))))
                    out << " + ";
            }
        }
        out << "\n";
        return out;
    }
}
