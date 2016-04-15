// poly2.cxx - implements poly2.h version of class polynomial
// Sean Shelton, 2-15-2016

// INVARIANT for the polynomial class:
//   1. head_ptr and tail_ptr are the head and tail pointers for a
//      doubly-linked list of nodes that contain the polynomial's terms in
//      order from smallest to largest exponent. To simplify certain operations,
//      we always keep a node for the zero-order term (x^0), but other nodes are
//      kept only if the coefficient is non-zero.
//   2. We always maintain recent_ptr as a pointer to some node in the
//      list--preferably the most recently used node. If the list is null,
//      then we set recent_ptr to null.
//   3. The degree of the polynomial is stored in current_degree
//      (using zero for the case of all zero coefficients).

#include <iostream>
#include <cassert> // provides assert
#include <climits> // provides UINT_MAX
#include <cmath>   // provides pow and fabs
#include <cstdlib> // provides NULL
#include "poly2.h"
using namespace std;

namespace main_savitch_5
{
    
    
    // YOUR WORK HERE
    
    // declarations for my jams
    
    //void head_del(polynode *first_pointer);
    //polynode polySearchExp (unsigned int e, polynode *headPtr/*, double target*/);
    


    // CONSTRUCTORS and DESTRUCTOR
    polynomial::polynomial(double c, unsigned int exponent) {
        //head_ptr = new polynode(c, exponent, tail_ptr, head_ptr);
        //if (c == 0)
        //   exponent = 0;
        
        head_ptr = new polynode(c, exponent, NULL, NULL);
        tail_ptr = head_ptr;
        //head_ptr->coef_field = c;
        //head_ptr->exponent_field = exponent;
        //head_ptr->link_back = head_ptr;
        //head_ptr->link_fore = tail_ptr;
        
        /*cout << head_ptr->coef() << endl;
        cout << tail_ptr->coef() << endl;
        cout << head_ptr->exponent() << endl;
        cout << tail_ptr->exponent() << endl;*/
        
        // it's possible that this is supposed to make the entire
        // list up to the exponent... but nah
        if (c == 0)
            current_degree = 0;
        else
            current_degree = exponent;
    }
    
    polynomial::polynomial(const polynomial &source) {
        // copy everything from source into this polynomial
        // probably gonna use a cursor and point along the way?
        
        // works, i don't think it has to delete everything bc it's a copy
        // constructor...
        
        polynode *cursor = source.head_ptr;
        //polynode *cleanUp;
        /*polynode *cleanCursor = head_ptr;
        while (cleanCursor != NULL) {
        // should delete everything
            //head_del(head_ptr);
            polynode *cleanUp = cleanCursor;
            cleanCursor = cleanCursor->fore();
            delete cleanUp;
        }*/
        
        /*while (cursor != NULL)
            head_del(cursor);*/
        if (cursor != NULL) {
            //polynomial copyPoly(cursor->coef(), cursor->exponent());
            head_ptr = new polynode(cursor->coef(), cursor->exponent(), NULL, NULL);
            /*head_ptr->coef() = cursor->coef();
            head_ptr->exponent() = cursor->exponent();*/
            cursor = cursor->fore();
        }
        else {
            //polynomial copyPoly;
            //return copyPoly;
            return;
        }
            
        polynode *cursor2 = head_ptr;
        polynode *behindCursor2 = head_ptr;
        cursor2 = cursor2->fore();
        
        while (cursor != NULL) {
            cursor2 = new polynode(cursor->coef(), cursor->exponent(), NULL, behindCursor2);
            behindCursor2->set_fore(cursor2);
            cursor = cursor->fore();
            cursor2 = cursor2->fore();
            behindCursor2 = behindCursor2->fore();
        }
        
        tail_ptr = behindCursor2;
        current_degree = source.current_degree;
    }
    
	polynomial::~polynomial( ) {
	    // deletes all of the polynodes in the linked list
	    // probably uses a cursor and deletes the head over and over
	    //for (polynode *cursor = head_ptr; cursor != tail_ptr; polynode *cursor = head) {
	    tail_ptr->set_fore(NULL);
	    while (head_ptr != NULL) {
	        /*polynode *cursor = head_ptr;
	        head_ptr = head_ptr->link_fore;
	        head_ptr->link_back = head_ptr;
	        delete cursor;*/
	        //head_del(head_ptr);
	        polynode *cleanUp = head_ptr;
            head_ptr = head_ptr->fore();
            delete cleanUp;
	    }
	    
	    //below might not be necessary, but w/e
	    //delete head_ptr;
	}
	
	// MODIFICATION MEMBER FUNCTIONS
    polynomial& polynomial::operator =(const polynomial& source) {
        // sets this = source
        // very similar to copy?
        if (this == &source)
            return *this;
            
        while (head_ptr != NULL) {
            polynode *removePtr = head_ptr;
            head_ptr = head_ptr->fore();
            delete removePtr;
        }
        
        polynode *cursor = source.head_ptr;
        polynomial *copyPoly = new polynomial(cursor->coef(), cursor->exponent());
        head_ptr = copyPoly->head_ptr;
        polynode *cursor2 = copyPoly->head_ptr;
        polynode *behindCursor2 = copyPoly->head_ptr;
        cursor2 = cursor2->fore();
        cursor = cursor->fore();
        
        while (cursor != NULL) {
            cursor2 = new polynode(cursor->coef(), cursor->exponent(), NULL, behindCursor2);
            behindCursor2->set_fore(cursor2);
            cursor = cursor->fore();
            cursor2 = cursor2->fore();
            behindCursor2 = behindCursor2->fore();
        }
        
        
        copyPoly->tail_ptr = behindCursor2;
        copyPoly->current_degree = source.current_degree;
        this->current_degree = source.current_degree;
        return *copyPoly;
    }
    
    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        // look for the spot that's equal to exponent, then
        // add on top of that spot
        // look out for amount < 0
        
        // so far this is exactly like assign coef, except when it finds the matching exponent
        // in that case, it'll add whatever's in there + amount
        
        polynode *cursor = head_ptr;
        while (cursor != NULL && cursor->exponent() < exponent)
            cursor = cursor->fore();
            
        if (cursor != NULL) {
            if (cursor->exponent() == exponent)
                cursor->set_coef(cursor->coef() + amount);
        }
        
        if (cursor == NULL) {
            polynode *ahead = new polynode(amount, exponent, 0, tail_ptr);
            tail_ptr->set_fore(ahead);
            tail_ptr = ahead;
        }
        else {
            if (cursor->exponent() != exponent) {
                polynode *inBetween = new polynode(amount, exponent, cursor, cursor->back());
                if (cursor->back() != NULL)
                    cursor->back()->set_fore(inBetween);
                else
                    head_ptr = inBetween;
                cursor->set_back(inBetween);
            }
        }
        if (amount != 0 && exponent > current_degree)
            current_degree = exponent;
            
        if (polynomial::coefficient(current_degree) == 0)
            current_degree = previous_term(current_degree);
            
        if (current_degree == UINT_MAX)
                current_degree = 0;
         
        
        /*polynode *cursor = head_ptr;

        while ( (cursor->fore()) != tail_ptr || )*/
    }
    
    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        // go to an exponent and set it equal to coef
        
        polynode *cursor = head_ptr;
        // have a loop keep going until the next term is greater or the next node is the tail
        //polynode *cursor = headPtr; 
        // so let's set a polynode pointer to a polynode that matches the exponent we want
        
        while (cursor != NULL && cursor->exponent() < exponent)
            cursor = cursor->fore();
            
        if (cursor != NULL) {
            if (cursor->exponent() == exponent)
                cursor->set_coef(coefficient);
        }
        
        if (cursor == NULL) {
            polynode *ahead = new polynode(coefficient, exponent, 0, tail_ptr);
            tail_ptr->set_fore(ahead);
            tail_ptr = ahead;
        }
        else {
            if (cursor->exponent() != exponent) {
                polynode *inBetween = new polynode(coefficient, exponent, cursor, cursor->back());
                if (cursor->back() != NULL)
                    cursor->back()->set_fore(inBetween);
                else
                    head_ptr = inBetween;
                cursor->set_back(inBetween);
            }
        }
        
        if (coefficient != 0 && exponent > current_degree)
            current_degree = exponent;
            
        if (polynomial::coefficient(current_degree) == 0)
            current_degree = previous_term(current_degree);
            
        if (current_degree == UINT_MAX)
                current_degree = 0;   
        /*if (polynomial::coefficient(current_degree) == 0) {
            current_degree = previous_term(current_degree);
            if (current_degree == UINT_MAX)
                current_degree = 0;
        }*/
        /*while (cursor != NULL && cursor->exponent() < exponent) //&& cursor->exponent() < exponent) 
            cursor = cursor->fore();
        
        // this is when exponent is equal to cursor's exponent
        if (cursor->exponent() == exponent)
            cursor->set_coef(coefficient);
        // below is good if the thing we want is right before our cursor
        else if (cursor != NULL) {
            polynode inBetween(coefficient, exponent, cursor, cursor->back());
            if (cursor->back() != NULL)
                cursor->back()->set_fore(&inBetween);
            else
                head_ptr = &inBetween;
            cursor->set_back(&inBetween);
        }
        // this should run if cursor == null, aka this exponent is going to be the
        // biggest thing we have
        else {
            polynode ahead(coefficient, exponent, NULL, tail_ptr);
            tail_ptr->set_fore(&ahead);
            tail_ptr = &ahead;
        }*/
        /*
        else {
            // make it so that you make a new node in the right place
            polynode inBetween(coefficient, exponent, cursor->fore(), cursor);
            
            if (next_term(cursor->exponent()) != 0)
                cursor->fore()->set_back(&inBetween);
            else
                tail_ptr = &inBetween;
                
            cursor->set_fore(&inBetween);
        }*/
    }
    
    void polynomial::clear( ) {
        // loop through all nodes and assign everything to 0
        polynode *cursor = head_ptr;
        
        while (cursor != NULL) {
            cursor->set_coef(0);
            cursor = cursor->fore();
        }
        
        current_degree = 0;
    }
    
    // CONSTANT MEMBER FUNCTIONS
    double polynomial::coefficient(unsigned int exponent) const {
        // find the node w/ exponent and return its coef
        // else, return 0
        // works
        polynode *cursor = head_ptr;
        tail_ptr->set_fore(NULL);
        
        // below is causing issues due to accessing part of a null (cursor->exponent() part) NOTE: Maybe fixed
        // new issue: somehow exponent is changed to 0 in the next line?
        while (cursor != NULL) {
            if (cursor->exponent() == exponent)
                break;
            cursor = cursor->fore();
        }
        
        if (cursor == NULL)
            return 0;
        else
            return cursor->coef();
    }
    
    // next work in progress
    unsigned int polynomial::next_term(unsigned int e) const {
        // might want to use recent ptr instead of head ptr...
        if (e > current_degree)
            return 0;
            
        polynode *cursor = head_ptr;
        
        while ((cursor != NULL && cursor->exponent() <= e) || (cursor != NULL && cursor->coef() == 0))
            cursor = cursor->fore();
        
        if (cursor == NULL)// || cursor->coef() == 0)
            return 0;
        else
            return cursor->exponent();
    }
    
    unsigned int polynomial::previous_term(unsigned int e) const {
        polynode *cursor = tail_ptr;
        
        while ((cursor != NULL && cursor->exponent() >= e) || (cursor != NULL && cursor->coef() == 0))
            cursor = cursor->back();
        
        if (cursor == NULL)// || cursor->coef() == 0)
            return UINT_MAX;
        else
            return cursor->exponent();
    }
    
    //my own jams
    
    /*void head_del (polynode *first_pointer) {
        polynode *cursor = first_pointer;
        if (first_pointer->fore() != NULL) {
            first_pointer = first_pointer->fore();
            first_pointer->set_back(NULL);
        }
        delete cursor;
    }*/
    
    /*polynode* polySearchExp (unsigned int e, polynode *headPtr, double target) {
        polynode *cursor = headPtr; 
        // so let's set a polynode pointer to a polynode that matches the exponent we want
        
        while (cursor != tail_ptr || cursor->exponent() != e) {
            if (cursor->exponent() == e)
                return cursor;
            cursor = cursor->fore();
        }
        
        return NULL;
    }*/
    
    // end of my jams

    // YOU MAY EITHER SIMPLY USE OR YOU MAY REMOVE ANY OR ALL OF THE
    // FOLLOWING IMPLEMENTATIONS, BUT PLEASE ADD ALL NEW WORK ABOVE.
    
    polynomial polynomial::derivative( ) const {
        polynomial result;
        for (unsigned int exponent = 1;
             exponent <= degree() && exponent > 0;
             exponent = next_term(exponent)) {
            result.assign_coef(exponent * coefficient(exponent),
                               exponent - 1);
        }
        return result;
    }
    
    double polynomial::eval(double x) const {
        double result= coefficient(0);
        for (unsigned int e = next_term(0);
             e > 0 && e <= degree();
             e = next_term(e))
            result += coefficient(e) * pow(x, e);
        return result;
    }
    
    void polynomial::find_root(double &answer, bool &success, unsigned int &iterations,
                               double starting_guess, unsigned int maximum_iterations,
                               double epsilon) const {
        assert(epsilon > 0.0);
        polynomial prime = derivative();
        answer = starting_guess;
        double f = eval(answer), fprime = prime.eval(answer);
        iterations = 0;
        while (iterations < maximum_iterations &&
               fabs(f) > epsilon && fabs(fprime) > epsilon) {
            ++iterations;
            answer = answer - f / fprime;
            f = eval(answer);
            fprime = prime.eval(answer);
        }
        success = fabs(f) < epsilon;
    }
    
    polynomial operator +(const polynomial& p1, const polynomial& p2) {
        polynomial result(p1);
        for (unsigned int e = 0; e <= p2.degree(); e++)
            if (p2.coefficient(e) != 0.0)
                result.add_to_coef(p2.coefficient(e), e);
        return result;
    }
    
    polynomial operator -(const polynomial& p1, const polynomial& p2) {
        polynomial result(p1);
        for (unsigned int e = 0; e <= p2.degree(); e++)
            if (p2.coefficient(e) != 0.0)
                result.add_to_coef(-p2.coefficient(e), e);
        return result;
    }
    
    polynomial operator *(const polynomial& p1, const polynomial& p2) {
        polynomial result;
        for (unsigned int e1 = p1.degree(); e1 != UINT_MAX; e1 = p1.previous_term(e1))
            for (unsigned int e2 = p2.degree(); e2 != UINT_MAX; e2 = p2.previous_term(e2))
                result.add_to_coef(p1.coefficient(e1) * p2.coefficient(e2), e1 + e2);
        return result;
    }
    
    // utility prints one term to ostream
    void print_term(ostream& out, double coef, unsigned int exponent) {
        out << coef;
        if (exponent > 0)
            out << "x";
        if (exponent > 1)
            out << "^" << exponent;
    }
    
    std::ostream& operator << (std::ostream& out, const polynomial& p) {
        unsigned int degree = p.degree();
        if (degree == 0)
            out << p.coefficient(0);
        else {
            print_term(out, p.coefficient(degree), degree); // largest term
            unsigned exponent = p.previous_term(degree);
            while (exponent != UINT_MAX) {
                double coef =p.coefficient(exponent);
                out << (coef < 0.0 ? " - " : " + ");
                if (coef < 0.0)
                    coef *= -1;
                print_term(out, coef, exponent);
                exponent = p.previous_term(exponent);
            }
        }
        out << std::endl;
        return out;
    }
}
