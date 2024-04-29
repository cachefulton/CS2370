#include <ostream>
#include <bitset>
#include <cassert>

class Bits {
    using IType = unsigned long long; // We only have to change the integer type here, if desired
    enum {NBITS = sizeof(IType)*8};
    IType bits = 0;
public:
    Bits() = default;
    Bits(IType n) {
        bits = n;
    }
    static int size() {
        return NBITS;
    }
    bool at(int pos) const {  // Returns (tests) the bit at bit-position pos
        assert(0 <= pos && pos < NBITS);
        return bits & (IType(1) << pos);
    }
    void set(int pos);        // Sets the bit at position pos
    void set();               // Sets all bits
    void reset(int pos);      // Resets (makes zero) the bit at position pos
    void reset();             // Resets all bits
    void assign(int pos, bool val); // Sets or resets the bit at position pos depending on val
    void assign(IType n);     // Replaces the underlying integer with n
    void toggle(int pos);     // Flips the bit at position pos
    void toggle();            // Flips all bits
    void shift(int n);        // If n > 0, shifts bits right n places; if n < 0, shifts left
    void rotate(int n);       // If n > 0, rotates right n places; if n < 0, rotates left
    int ones() const;         // Returns how many bits are set in the underlying integer
    int zeroes() const {      // Returns how many bits are reset in the underlying integer
        return NBITS - ones();
    }
    IType to_int() const {
        return bits;
    }
    friend bool operator==(const Bits& b1, const Bits& b2) {
        return b1.bits == b2.bits;
    }
    friend bool operator!=(const Bits& b1, const Bits& b2) {
        return b1.bits != b2.bits;
    }
    friend std::ostream& operator<<(std::ostream& os, const Bits& b) {
        return os << std::bitset<NBITS>(b.bits);    // Be sure to #include <bitset>
    }
};

void Bits::set(int pos)
{
    assert(0 <= pos && pos < NBITS);
    bits |= (IType(1) << pos);
}

void Bits::set()
{
    bits = -1; //-1 is the same as all bits set
}

void Bits::reset(int pos)
{
    assert(0 <= pos && pos < NBITS);
    if(at(pos)) //if position is a 1
    {
        bits &= ~(IType(1) << pos);
    }  
}

void Bits::reset()
{
    bits = 0; //0 is the same as all bits not set
}

void Bits::assign(int pos, bool val)
{
    assert(0 <= pos && pos < NBITS);
    if(!val) //val == 0
    {
        bits &= ~(IType(1) << pos);
    }
    else //val == 1
    {
        bits |= (IType(1) << pos);
    }
}

void Bits::assign(IType n)
{
    bits = n;
}

void Bits::toggle(int pos)
{
    if(at(pos)) //pos == 1
    {
        bits &= ~(IType(1) << pos);
    }
    else //pos == 0
    {
        bits |= (IType(1) << pos);
    }
}

void Bits::toggle()
{
    IType mask = -1;
    bits ^= mask;
}

void Bits::shift(int n)
{
    if (n > 0) {bits >>= n;}
    else if (n < 0) {bits <<= abs(n);}
}

int Bits::ones() const
{
    int count = 0;
    for (int i = 0; i < size(); i++)
    {
        if(at(i)) {count++;}
    }
    return count;
}

void Bits::rotate(int n) 
{
    int mod = abs(n) % size(); //if n is bigger than amount of bits, we need continue to rotate bits
    if (n > 0 && mod != 0) //rotate right
    {
        bits = (bits >> mod) | (bits << (size() - mod));
    }
    else if (n < 0 && mod != 0) //rotate left
    {
        bits = (bits << mod) | (bits >> (size() - mod));
    }
}