#ifndef POLY_H
#define POLY_H

using namespace std;

class Polynomial {

  private:
    unsigned int order_;    // polynomial order
    float *a_;              // polynomial coefficients

    void copy_(const Polynomial &p);   // helper function to copy 
    void destroy_();                   // helper function to destroy

  public:
    // Default constructor
    // constructs a first-order polynomial with all coefficients set to 1.
    Polynomial();
    // One-parameter constructor
    // constructs a polynomial of user-supplied order with all coefficients set to 1.
    Polynomial(int order);
    // Copy constructor - must use copy_() function
    // constructs a new polynomial that is a copy of an existing polynomial
    Polynomial(Polynomial const & other);
    // Destructor - must use destroy_() function
    // destroys a polynomial object
    ~Polynomial();
    // Assignment operator - must use copy_() function
    // assigns rhs Polynomila object to 'this' Polynomila object
    Polynomial const & operator= (Polynomial const & other);
    // addition operator
    // adds two polynomials together and returns a new polynomial 
    Polynomial const & operator + (Polynomial const & other);
    // getPolyOrder
    // returns the polynomial order
    int getPolyOrder();
    // getCoeff
    // returns the coefficient of the x^i term in polynomial
    // note: If the object does not contain a term with power i (e.g., 
    //       i>order_), a coefficient value of zero is returned.
    float getCoeff(uint i);
    // setCoeff
    // If i <= order_, set a term, value*x^i, in a polynomial
    void setCoeff(uint i, float value);
    // insertion operator for output
    // note: This function has been provided for you -- DO NOT CHANGE IT!
    friend ostream& operator<< (ostream& os, const Polynomial &p);

};

#endif
