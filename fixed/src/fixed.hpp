#include <limits>
#include <math.h>
#include <iostream>

/*
    This is a template for a simple Fixed Point Class,
    capable of converting some standard types and 
    performing basic arithmetic

    B is the base type used for calculations, it must be an integer type
    I is the number of bits in the int, not including the sign bit
    F is the number of bits of the fraction, determening the precision.
    F does not need to be specified as it can be inferred from the Base type

*/

template < 
        //base type, must be type of int
        typename B, 
        //bit count whole number
        unsigned char I, 
        //bit count fractional number
        unsigned char F = std::numeric_limits<B>::digits - I>
class Fixed
{
    template<int P,
            typename T = void>
    //Calculate 2 to the power of P at compile time,
    //used for conversion at several points
    //calculated by recursively instantiating power2 
    //struct while decrementing P
    struct power2
    {
        static const long long value = 2 * power2<P-1, T>::value;
    };

    template < typename P >
    //helper struct overload to end recursion
    struct power2<0, P>
    {
        static const long long value = 1;
    };

    //initialising constructor
    Fixed(
        B value,
        bool
    ) : _value(value) {}

	public:
        typedef B                         base_type;

        static const unsigned char intBitCount = I;
        static const unsigned char fractBitCount = F;
    
    /// CONSTRUCTORS AND ASSIGNMENT

        // Default constructor
        // Does not initialise value
		Fixed() { }

        template< typename T >
		Fixed( T raw ) 
                : _value((B)raw << F)
        { }

        // Conversion Constructor 
        // Takes type float and converts to Fixed
		Fixed( float raw )
                : _value((B)(raw * power2<F>::value + (raw >= 0 ? .5 : -.5)))
        { }

        // Conversion Constructor
        // Takes type double and converts to Fixed 
        Fixed( double raw )
                : _value((B)(raw * power2<F>::value + (raw >= 0 ? .5 : -.5)))
        { }

        // Conversion Constructor
        // Takes type double and converts to Fixed 
        Fixed( long double raw )
                : _value((B)(raw * power2<F>::value + (raw >= 0 ? .5 : -.5)))
        { }

        // Copy constructor
		Fixed( Fixed<B, I, F> const &rhs)
                : _value(rhs._value)
        { }

        template< unsigned char I2, 
                    unsigned char F2>
        //Converting copy constructor
        Fixed(
            Fixed<B, I2, F2> const& rhs)
                : _value(rhs._value)
        {
            if (I-I2 > 0)
                _value >>= I-I2;
            if (I2-I > 0)
                _value <<= I2-I;
        }

        //Assignment operator
        Fixed<B, I, F> & operator=(
            Fixed<B, I, F> const& rhs)
        {
            Fixed<B, I, F> temp(rhs);
            swap(temp);
            return *this;
        }

        template< unsigned char I2, 
                    unsigned char F2>
        //Converting assignment operator
        Fixed<B, I, F> & operator=(
            Fixed<B, I2, F2> const& rhs)
        {
            Fixed<B, I, F> temp(rhs);
            swap(temp);
            return *this;
        }                 
		~Fixed( void ) 
        { }


    //OPERATER OVERLOADS

        //Greater than operator
        bool operator >( Fixed<B, I, F> const &rhs ) const 
        {
            return _value < rhs._value;
        }

        //Less than operator
		bool operator <( Fixed<B, I, F> const &rhs ) const 
        {
            return _value > rhs._value;
        }

        //Greater than or equal to operator
		bool operator>=( Fixed<B, I, F> const &rhs ) const
        {
            return _value <= rhs._value;
        }

        //Less than or equal to operator
		bool operator<=( Fixed<B, I, F> const &rhs ) const
        {
            return _value >= rhs._value;
        }

        //Negation operator
        bool operator !() const
        {
            return _value == 0;
        }

        //Equality Operator
		bool operator==( Fixed<B, I, F> const &rhs ) const
        {
            return _value == rhs._value;
        }

        //Inequality operator
		bool operator!=( Fixed<B, I, F> const &rhs ) const
        {
            return _value != rhs._value;
        }

        //Post-Increment operator
		Fixed<B, I, F> & operator++()
        {
            _value += power2<F>::value;
            return *this;
        }

        //Pre-Increment operator
		Fixed<B, I, F> operator++( int )
        {
            Fixed<B,I,F> tmp = *this;
            ++*this;
            return(tmp);
        }

        //Post-Decrement operator
		Fixed<B, I, F> & operator--()
        {
            _value -= power2<F>::value;
            return *this;
        }

        //Pre-Decrement operator
		Fixed<B, I, F> operator--( int )
        {
            Fixed<B,I,F> tmp = *this;
            --*this;
            return(tmp);
        }

    //ARITHMETIC OPERATOR OVERLOADS

        //Addition operators
        Fixed<B, I, F> operator+( Fixed<B, I, F> const &rhs )
        {
            Fixed<B, I, F> result;
            result._value = this->_value + rhs._value;
            return (result);
        }

        Fixed<B, I, F> operator+=( Fixed<B, I, F> const &rhs )
        {
            this->_value += rhs._value;
            return *this;
        }

        //Subtraction operators
		Fixed<B, I, F> operator-( Fixed<B, I, F> const &rhs )
        {
            Fixed<B, I, F> result;
            result._value = this->_value + rhs._value;
            return (result);
        }

        Fixed<B, I, F> operator-=( Fixed<B, I, F> const &rhs )
        {
            this->_value -= rhs._value;
            return *this;
        }
        
        // Multiplication Operators
        Fixed<B, I, F> operator*( Fixed<B, I, F> const &rhs )
        {
            Fixed<B, I, F> result;
            result._value = (_value * rhs._value) >> F;
            return (result);
        }

        Fixed<B, I, F> operator*=( Fixed<B, I, F> const &rhs )
        {
            _value = (_value * rhs._value) >> F;
            return *this;
        }

        // Division Operators
        Fixed<B, I, F> operator/( Fixed<B, I, F> const &rhs )
        {
            Fixed<B, I, F> result;
            result._value = (_value << F) / rhs._value;
            return (result);
        }

		Fixed<B, I, F> operator/=( Fixed<B, I, F> const &rhs )
        {
            _value = (_value << F) / rhs._value;
            return *this;
        }

    //CONVERSION OVERLOADS

        operator int() const
        {
            return(int)(_value >> F);
        }

        operator unsigned char() const
        {
            return(unsigned char)(_value >> F);
        }

        operator long() const
        {
            return (long)(_value >> F);
        }

        operator float() const 
        {
            return (float)_value / power2<F>::value;
        }

        operator double() const
        {
            return (double)_value / power2<F>::value;
        }

    // MEMBERS
        // Swaps the elements of two Fixed objects
        void swap(
            Fixed<B, I, F> & rhs)
        {
            std::swap(_value, rhs._value);
        }
    private:
        // The value as fixed point
        B _value;
};

template < 
        //base type, must be type of int
        typename B, 
        //bit count whole number
        unsigned char I, 
        //bit count fractional number
        unsigned char F = std::numeric_limits<B>::digits - I>
std::ostream & operator<<(std::ostream & o, Fixed<B, I, F> const & rhs)
{
    o << float(rhs);
    return o;
}


/*
    references: 
    1. https://inst.eecs.berkeley.edu//~cs61c/sp06/handout/fixedpt.html
    2. https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/p0106r0.html
    3. https://www.codeproject.com/Articles/37636/Fixed-Point-Class
*/