//lang::CwC 
#pragma once
#include "string.h"
#include "object.h"

#include <assert.h>
#include <cstring>

/*
* ArrayObject: This class represents a list of Objects.
* author: shetty.y@husky.neu.edu, eldrid.s@husky.neu.edu
*/
class ArrayObject : public Object {
public:

    Object** _storage = new Object*[1];
    size_t _capacity = 1;
    size_t _length = 0;

    /**
	 * Constructor.
	*/
    ArrayObject() {}

    /**
     * Reallocates the buffer to be of size _capacity and then copies all of the elements currently in the array
     * to the new buffer.
     */
    void _reallocateStorage() {
        Object** newStorage = new Object*[_capacity];
        memcpy(newStorage, _storage, sizeof(Object*) * _length);

        delete [] _storage;
        _storage = newStorage;
    }

    /**
     * Doubles the size of the array if it is full
     */
    void _expandIfNeeded() {
        if (_length == _capacity) {
            _capacity *= 2;
            _reallocateStorage();
        }
    }

    /**
     * Appends e to end of the list.
     * @arg e: the Object to be appended.
    */
    virtual void push_back(Object* e) {
        _expandIfNeeded();
        _storage[_length] = e;
        _length += 1;
    }

    /**
     * Inserts e at i. All Objects from i right, are moved a position to the right.
     * @arg i: the index where you want to add the Object.
     * @arg e: the Object to be appended.
    */
    virtual void add(size_t i, Object* e) {
        assert(i >= 0 && i <= _length);
        _expandIfNeeded();

        if (i != _length) {
            for (size_t index = _length; index > i; index--) {
                _storage[index] = _storage[index - 1];
            }
        }

        _storage[i] = e;
        _length += 1;
    }
    
    /**
     * Inserts all of elements in c into this list at i
     * @arg i: the index starting where you want to add the string.
     * @arg e: the List of Objects to be appended.
    */
    virtual void add_all(size_t i, ArrayObject* c) {
        assert(i >= 0 && i <= _length);
        size_t requiredCapacity = _length + c->_length;
        if (requiredCapacity > _capacity) {
            _capacity = requiredCapacity;
            _reallocateStorage();
        }

        if (i != _length) {
            for (size_t index = _length - 1; index <= i; index--) {
                _storage[index + c->_length] = _storage[index];
            }
        }

        for (size_t index = i; index < c->_length; index++) {
            _storage[i + index] = c->_storage[index];
        }

        _length += c->_length;
    }

    /**
     * Removes all of elements from this list
    */
    virtual void clear() { _length = 0; }

    /**
     * Compares o with this list for equality.
     * arg o: the Object you're testing equality against.
    */
    virtual bool equals(Object* o) {
        ArrayObject* array = dynamic_cast<ArrayObject*>(o);
        if (array && array->_length == _length) {
            for (size_t i = 0; i < _length; i++) {
                if (!array->_storage[i]->equals(_storage[i])) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    /**
     * Returns the element at index
     * arg index: the index of the element that you want.
    */
    virtual Object* get(size_t index) {
        assert(index >= 0 && index < _length);
        return _storage[index];
    }

    /**
     * Returns the hash code value for this list.
    */
    virtual size_t hash() {
        size_t hash = 0;
        for (size_t i = 0; i < _length; i++) { hash += _storage[i]->hash(); }
        return hash;
    }

    /**
     * Returns the index of the first occurrence of o, or >size() if not there
     * arg o: the Object that you want the index for.
    */
    virtual size_t index_of(Object* o) {
        for (size_t index = 0; index < _length; index++) {
            if (o->equals(_storage[index])) { return index; }
        }
        return size() + 1;
    }

    /**
     * Removes the element at i
     * arg i: the index of the element you want to remove. 
    */
    virtual Object* remove(size_t i) {
        assert(i >= 0 && i < _length);
        Object* removed = _storage[i];

        for (size_t index = i; index < _length - 1; index++) {
            _storage[index] = _storage[index + 1];
        }
        _length -= 1;
        return removed;
    }

    /**
     * Replaces the element at i with e
     * arg i: the index of the element you want to replace. 
     * arg e: the element that you're replacing it with.
    */
    virtual Object* set(size_t i, Object* o) {
        assert(i >= 0 && i < _length);
        Object* replacing = _storage[i];
        _storage[i] = o;

        return replacing;
    }

    /**
     * Return the number of elements in the collection
    */
    virtual size_t size() { return _length; }

    /**
     * Destructor.
    */
    virtual ~ArrayObject() {
        delete [] _storage;
    } 

    /**
     * Tests whether this list contains an Object, with the same value as e.
     * @arg e: The Object you want to test for containment.
    */
    virtual bool contains(Object* e) {
        for (int i = 0; i < _length; i++) {
            if (_storage[i]->equals(e)) { return true; }
        }
        return false;
    }
};


/*
* ArrayString: This class represents a list of String objects.
* author: shetty.y@husky.neu.edu, eldrid.s@husky.neu.edu
*/
class ArrayString : public Object {
public:
        ArrayObject _array;

    /**
	 * Constructor.
	*/
    ArrayString() {
    }

    /**
     * Appends e to end of the list.
     * @arg e: the String to be appended.
    */
    virtual void push_back(String* e) {
        _array.push_back(e);
    }

    /**
     * Inserts e at i. All strings from i right, are moved a position to the right.
     * @arg i: the index where you want to add the string.
     * @arg e: the String to be appended.
    */
    virtual void add(size_t i, String* e) {
        _array.add(i, e);
    }
    
    /**
     * Inserts all of elements in c into this list at i
     * @arg i: the index starting where you want to add the string.
     * @arg e: the List of Strings to be appended.
    */
    virtual void add_all(size_t i, ArrayString* c) {
        _array.add_all(i, &c->_array);
    }

    /**
     * Removes all of elements from this list
    */
    virtual void clear() {
        _array.clear();
    }

    /**
     * Compares o with this list for equality.
     * arg o: the Object you're testing equality against.
    */
    virtual bool equals(Object* o) {
        ArrayString* other = dynamic_cast<ArrayString*>(o);
        return other ? _array.equals(&other->_array) : false;
    }

    /**
     * Returns the element at index
     * arg index: the index of the element that you want.
    */
    virtual String* get(size_t index) {
        return dynamic_cast<String*>(_array.get(index));
    }

    /**
     * Returns the hash code value for this list.
    */
    virtual size_t hash() {
        return _array.hash();
    }

    /**
     * Returns the index of the first occurrence of o, or >size() if not there
     * arg o: the Object that you want the index for.
    */
    virtual size_t index_of(Object* o) {
        return _array.index_of(o);
    }

    /**
     * Removes the element at i
     * arg i: the index of the element you want to remove. 
    */
    virtual String* remove(size_t i) {
        return dynamic_cast<String*>(_array.remove(i));
    }

    /**
     * Replaces the element at i with e
     * arg i: the index of the element you want to replace. 
     * arg e: the element that you're replacing it with.
    */
    virtual String* set(size_t i, String* e) {
        return dynamic_cast<String*>(_array.set(i, e));
    }

    /**
     * Return the number of elements in the collection
    */
    virtual size_t size() {
        return _array.size();
    }

    /**
     * Destructor.
    */
    virtual ~ArrayString() {}

    /**
     * Tests whether this list contains a String, with the same value as e.
     * @arg e: The string you want to test for containment.
    */
    virtual bool contains(String* e) {
        return _array.contains(e);
    }
};

class ArrayInt : public Object {
public:
    /**
     * Constructor.
    */
    ArrayInt() {
    }

    /**
     * Appends e to end of the list.
     * @arg e: the int to be appended.
    */
    virtual void push_back(int e) {
    }

    /**
     * Inserts e at i. All Objects from i right, are moved a position to the right.
     * @arg i: the index where you want to add the int.
     * @arg e: the int to be appended.
    */
    virtual void add(size_t i, int e) {
    }
    
    /**
     * Inserts all of elements in c into this list at i
     * @arg i: the index starting where you want to add the string.
     * @arg e: the List of Objects to be appended.
    */
    virtual void add_all(size_t i, ArrayInt* e) {
    }

    /**
     * Removes all of elements from this list
    */
    virtual void clear() {
    }

    /**
     * Compares o with this list for equality.
     * arg o: the Object you're testing equality against.
    */
    virtual bool equals(Object* o) {
    }

    /**
     * Returns the element at index
     * arg index: the index of the element that you want.
    */
    virtual int get(size_t index) {
    }

    /**
     * Returns the hash code value for this list.
    */
    virtual size_t hash() {
    }

    /**
     * Returns the index of the first occurrence of o, or >size() if not there
     * arg i: the int that you want the index for.
    */
    virtual size_t index_of(int i) {
    }

    /**
     * Removes the element at i
     * arg i: the index of the element you want to remove. 
    */
    virtual int remove(size_t i) {
    }

    /**
     * Replaces the element at i with e
     * arg i: the index of the element you want to replace. 
     * arg e: the element that you're replacing it with.
    */
    virtual int set(size_t i, int e) {
    }

    /**
     * Return the number of elements in the collection
    */
    virtual size_t size() {
    }

    /**
     * Destructor.
    */
    virtual ~ArrayInt() {
    } 

    /**
     * Tests whether this list contains an int, with the same value as e.
     * @arg e: The int you want to test for containment.
    */
    virtual bool contains(int e) {
    }
};

class ArrayFloat : public Object {
public:
    /**
     * Constructor.
    */
    ArrayFloat() {
    }

    /**
     * Appends e to end of the list.
     * @arg e: the float to be appended.
    */
    virtual void push_back(float e) {
    }

    /**
     * Inserts e at i. All Objects from i right, are moved a position to the right.
     * @arg i: the index where you want to add the float.
     * @arg e: the float to be appended.
    */
    virtual void add(size_t i, float e) {
    }
    
    /**
     * Inserts all of elements in c into this list at i
     * @arg i: the index starting where you want to add the string.
     * @arg e: the List of floats to be appended.
    */
    virtual void add_all(size_t i, ArrayFloat* c) {
    }

    /**
     * Removes all of elements from this list
    */
    virtual void clear() {
    }

    /**
     * Compares o with this list for equality.
     * arg o: the Object you're testing equality against.
    */
    virtual bool equals(Object* o) {
    }

    /**
     * Returns the element at index
     * arg index: the index of the element that you want.
    */
    virtual float get(size_t index) {
    }

    /**
     * Returns the hash code value for this list.
    */
    virtual size_t hash() {
    }

    /**
     * Returns the index of the first occurrence of o, or >size() if not there
     * arg o: the Object that you want the index for.
    */
    virtual size_t index_of(Object* o) {
    }

    /**
     * Removes the element at i
     * arg i: the index of the element you want to remove. 
    */
    virtual float remove(size_t i) {
    }

    /**
     * Replaces the element at i with e
     * arg i: the index of the element you want to replace. 
     * arg e: the element that you're replacing it with.
    */
    virtual float set(size_t i, Object* o) {
    }

    /**
     * Return the number of elements in the collection
    */
    virtual size_t size() {
    }

    /**
     * Destructor.
    */
    virtual ~ArrayFloat() {
    } 

    /**
     * Tests whether this list contains an float, with the same value as e.
     * @arg e: The float you want to test for containment.
    */
    virtual bool contains(float e) {
    }
};

class ArrayBool : public Object {
public:
    /**
     * Constructor.
    */
    ArrayBool() {
    }

    /**
     * Appends e to end of the list.
     * @arg e: the bool to be appended.
    */
    virtual void push_back(bool e) {
    }

    /**
     * Inserts e at i. All Objects from i right, are moved a position to the right.
     * @arg i: the index where you want to add the bool.
     * @arg e: the bool to be appended.
    */
    virtual void add(size_t i, bool e) {
    }
    
    /**
     * Inserts all of elements in c into this list at i
     * @arg i: the index starting where you want to add the string.
     * @arg e: the List of bools to be appended.
    */
    virtual void add_all(size_t i, ArrayBool* c) {
    }

    /**
     * Removes all of elements from this list
    */
    virtual void clear() {
    }

    /**
     * Compares o with this list for equality.
     * arg o: the Object you're testing equality against.
    */
    virtual bool equals(Object* o) {
    }

    /**
     * Returns the element at index
     * arg index: the index of the element that you want.
    */
    virtual bool get(size_t index) {
    }

    /**
     * Returns the hash code value for this list.
    */
    virtual size_t hash() {
    }

    /**
     * Returns the index of the first occurrence of o, or >size() if not there
     * arg o: the bool that you want the index for.
    */
    virtual size_t index_of(bool o) {
    }

    /**
     * Removes the element at i
     * arg i: the index of the element you want to remove. 
    */
    virtual bool remove(size_t i) {
    }

    /**
     * Replaces the element at i with e
     * arg i: the index of the element you want to replace. 
     * arg e: the element that you're replacing it with.
    */
    virtual bool set(size_t i, Object* o) {
    }

    /**
     * Return the number of elements in the collection
    */
    virtual size_t size() {
    }

    /**
     * Destructor.
    */
    virtual ~ArrayBool() {
    } 

    /**
     * Tests whether this list contains an bool, with the same value as e.
     * @arg e: The bool you want to test for containment.
    */
    virtual bool contains(bool e) {
    }
};