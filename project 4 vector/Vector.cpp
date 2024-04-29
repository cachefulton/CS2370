#include "Vector.h"
#include <iostream>
#include <stdexcept>
using namespace std;

//constructors and destructor
Vector::Vector()
{
  data_ptr = new int[CHUNK];
  n_elems = 0;
  capacity = CHUNK;
}

Vector::Vector(const Vector& v)
{
  data_ptr = new int[v.capacity];
  for (size_t i = 0; i < v.n_elems; i++) 
  {
    data_ptr[i] = v.data_ptr[i];
  }
  n_elems = v.n_elems;
  capacity = v.capacity;
}

Vector::~Vector() 
{
  delete[] data_ptr;
}

//overload operators
Vector& Vector::operator=(const Vector& v)
{
  if (this != &v)     // 1. Don't self-assign
  {
    delete[] data_ptr;               // 2. Delete old dataObject
    data_ptr = new int[v.capacity];  // 3. Allocate new dataObject
    for (size_t i = 0; i < v.n_elems; i++) // 4. Copy dataObject
    {
      data_ptr[i] = v.data_ptr[i];
    }
    n_elems = v.n_elems;
  }
  return *this;
}

int& Vector:: operator[](size_t pos) 
{
  return data_ptr[pos];
}

bool Vector::operator==(const Vector& v) const
{
  if (this->n_elems != v.n_elems)
  {
    return false;
  }
  else
  {
    for (size_t i; i < v.n_elems; i++) //n-elems not capacity
    {
      if (data_ptr[i] != v.data_ptr[i]) { return false; }
    }
  }
  return true;
}

bool Vector::operator!=(const Vector& v) const
{
  return !(*this == v);
}

//implement class functions
//see if there's more space, if there is do nothing, if not make a bigger array
void Vector::grow() 
{
  if (capacity <= n_elems) //capacity should never be less than n_elems but just in case
  {
    Vector v = *this;
    capacity *= 1.6; //increase capacity by 1.6
    delete[] data_ptr;
    data_ptr = new int[capacity];
    for (size_t i = 0; i < v.n_elems; i++) 
    {
      data_ptr[i] = v.data_ptr[i];
    }

    /* couldn't get this to work
    for (size_t i = 0; i < n_elems; i++) 
    {
      newData[i] = data_ptr[i];
      cout << "appending" << endl;
    }
    delete[] data_ptr;
    *data_ptr = *newData; //make the old pointer point to new array
    */
  }
}

int Vector::front() const
{
  if (this->n_elems == 0) 
  { throw range_error("Index out of range"); }
  else
  { return data_ptr[0]; }
}

int Vector::back() const
{
  if (this->n_elems == 0) 
  { throw range_error("Index out of range"); }
  else
  { return data_ptr[n_elems - 1]; }
}

int Vector::at(size_t pos) const 
{
  if (n_elems == 0 || pos > n_elems - 1)
  { throw range_error("Index out of range"); }
  else
  { return data_ptr[pos]; }
}

size_t Vector::size() const 
{ return n_elems; }

bool Vector::empty() const
{ return n_elems == 0; }

void Vector::push_back(int item) 
{
  grow(); //make sure there is enough capacity
  n_elems++;
  data_ptr[n_elems-1] = item;
}

void Vector::pop_back() 
{ 
  if (n_elems > 0) 
  { n_elems--; } 
  else 
  { throw range_error("Index out of range"); }
}

void Vector::erase(size_t pos) 
{
  if (n_elems == 0 || pos > n_elems - 1 || pos < 0)
  { throw range_error("Index out of range"); }
  else if (pos == n_elems - 1) //erase last element
  { pop_back(); }
  else
  {
    n_elems--; //need this before the for loop or the loop will break if capacity is full
    for (size_t i = pos; i < n_elems; i++) 
    { 
      data_ptr[i] = data_ptr[i + 1]; 
    }
  }
}

void Vector::insert(size_t pos, int item) 
{
  if (n_elems == 0 || pos > n_elems || pos < 0)
  { throw range_error("Index out of range"); }
  else if (pos == n_elems) //not n_elems - 1 because inserting adds an index to array size
  { push_back(item); }
  else
  {
    grow(); //make sure there is enough capacity
    n_elems++;
    for (size_t i = n_elems - 1; i > pos; i--) // shift elements to the right
    {
      data_ptr[i] = data_ptr[i - 1];
    }
    data_ptr[pos] = item; // insert item
  }
}

void Vector::clear() { n_elems = 0; }

int* Vector::begin()
{
  if (n_elems == 0) { return nullptr; }
  else
  {
    return data_ptr; //returns pointer to first element in array
  }
}

int* Vector::end() //one past the last element
{
  if (n_elems == 0) { return nullptr; }
  else
  {
    return data_ptr + n_elems; //pointer arithmetic
  }
}
