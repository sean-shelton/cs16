// stats.cxx - implements statistician class as defined in stats.h
// Sean Shelton, Patrick Vidican
// Jan 15 2016

#include <cassert>  // provides assert
#include "stats.h"  // defines what must be implemented
#include <iostream>

namespace main_savitch_2C {
    statistician::statistician() {
        count = 0;
        total = 0;
        tiniest = 0;
        largest = 0;
    }
    
    void statistician::next(double r) {
        total += r;
        if (count == 0) {
            tiniest = r;
            largest = r;
        }
        if (r <= tiniest) { 
           tiniest = r;
        }
       
        if (r >= largest) { 
           largest = r;
       }
       count++;
    }
    
    void statistician::reset( ) {
        count = 0;
        total = 0;
    }
   
   double statistician::mean( ) const {
        if (count > 0)
            return (total/count);
        else
            return 0;
   }
   
   double statistician::minimum( ) const {
       assert(length() >= 0);
       return tiniest; 
   }
   
   double statistician::maximum( ) const {
       assert(length() >= 0);
       return largest; 
   }
   
   statistician operator +
        (const statistician &s1, const statistician &s2) {
            statistician Result;
            Result.count = s1.length() + s2.length();
            Result.total = s1.sum() + s2.sum();
            
            if (s1.tiniest <= s2.tiniest)
                Result.tiniest = s1.tiniest;
            else
                Result.tiniest = s2.tiniest;
             
            if (s1.largest >= s2.largest)
                Result.largest = s1.largest;
            else
                Result.largest = s2.largest;
                
            if (s1.count == 0) {
                Result.tiniest = s2.tiniest;
                Result.largest = s2.largest;
            }
            
            if (s2.count == 0) {
                Result.tiniest = s1.tiniest;
                Result.largest = s1.largest;
            }
                
            return (Result);
        }
   
   statistician operator *
        (double scale, const statistician &s) {
            statistician Result;
            Result.count = s.count;
            Result.total = s.total * scale;
            Result.largest = s.largest * scale;
            Result.tiniest = s.tiniest * scale;
            
            if (scale < 0) {
                Result.tiniest = s.largest * scale;
                Result.largest = s.tiniest * scale;
            }
            return (Result);
        }
   
   bool operator ==
       (const statistician& s1, const statistician& s2){
            return (
                (s1.length() == s2.length())
                &&
                (s1.sum() == s2.sum())
                &&
                (s1.mean() == s2.mean())
                &&
                (s1.maximum() == s2.maximum())
                &&
                (s1.minimum() == s2.minimum())
            );
       }
}