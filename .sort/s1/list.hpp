#pragma once

#include "stuff/shared.hpp"

/*
===============================================================================

        List template
        Does not allocate memory until the first item is added.

===============================================================================
*/

enum memTag_t {
    TAG_TOOLS,
    TAG_IDLIB_LIST,
    TAG_THREAD,
    TAG_JOBLIST,
    TAG_NUM_TAGS,
};

/*
========================
idListArrayNew
========================
*/
template <typename _type_, memTag_t _tag_>
void* idListArrayNew(int num, bool zeroBuffer) {
    _type_* ptr = NULL;
    if (zeroBuffer) {
        ptr = (_type_*)malloc(sizeof(_type_) * num/*, _tag_*/);
    } else {
        ptr = (_type_*)malloc(sizeof(_type_) * num/*, _tag_*/);
    }
    for (int i = 0; i < num; i++) {
        new (&ptr[i]) _type_;
    }
    return ptr;
}

/*
========================
idListArrayDelete
========================
*/
template <typename _type_>
void idListArrayDelete(void* ptr, int num) {
    // Call the destructors on all the elements
    for (int i = 0; i < num; i++) {
        ((_type_*)ptr)[i].~_type_();
    }
    free(ptr);
}

/*
========================
idListArrayResize
========================
*/
template <typename _type_, memTag_t _tag_>
void* idListArrayResize(void* voldptr, int oldNum, int newNum, bool zeroBuffer) {
    _type_* oldptr = (_type_*)voldptr;
    _type_* newptr = NULL;
    if (newNum > 0) {
        newptr      = (_type_*)idListArrayNew<_type_, _tag_>(newNum, zeroBuffer);
        int overlap = Minimum(oldNum, newNum);
        for (int i = 0; i < overlap; i++) {
            newptr[i] = oldptr[i];
        }
    }
    idListArrayDelete<_type_>(voldptr, oldNum);
    return newptr;
}

/*
================
idListNewElement<type>
================
*/
template <class type>
type* idListNewElement() {
    return new type;
}

template <typename _type_, memTag_t _tag_ = TAG_IDLIB_LIST>
class idList {
  public:
    typedef int    cmp_t(const _type_*, const _type_*);
    typedef _type_ new_t();

    idList(int newgranularity = 16);
    idList(const idList& other);
    ~idList();

    void Clear();                            // clear the list
    int  Num() const;                        // returns number of elements in list
    int  NumAllocated() const;               // returns number of elements allocated for
    void SetGranularity(int newgranularity); // set new granularity
    int  GetGranularity() const;             // get the current granularity

    size_t Allocated() const;  // returns total size of allocated memory
    size_t Size() const;       // returns total size of allocated memory including size of list _type_
    size_t MemoryUsed() const; // returns size of the used elements in the list

    idList<_type_, _tag_>& operator=(const idList<_type_, _tag_>& other);
    const _type_&          operator[](int index) const;
    _type_&                operator[](int index);

    void Condense();                                       // resizes list to exactly the number of elements it contains
    void Resize(int newsize);                              // resizes list to the given number of elements
    void Resize(int newsize, int newgranularity);          // resizes list and sets new granularity
    void SetNum(int newnum);                               // set number of elements in list and resize to exactly this number if needed
    void AssureSize(int newSize);                          // assure list has given number of elements, but leave them uninitialized
    void AssureSize(int newSize, const _type_& initValue); // assure list has given number of elements and initialize any new elements
    void AssureSizeAlloc(int    newSize,
                         new_t* allocator); // assure the pointer list has the given number of elements and allocate any new elements

    _type_*       Ptr();                                    // returns a pointer to the list
    const _type_* Ptr() const;                              // returns a pointer to the list
    _type_&       Alloc();                                  // returns reference to a new data element at the end of the list
    int           Append(const _type_& obj);                // append element
    int           Append(const idList& other);              // append list
    int           AddUnique(const _type_& obj);             // add unique element
    int           Insert(const _type_& obj, int index = 0); // insert the element at the given index
    int           FindIndex(const _type_& obj) const;       // find the index for the given element
    _type_*       Find(_type_ const& obj) const;            // find pointer to the given element
    int           FindNull() const;                         // find the index for the first NULL pointer in the list
    int           IndexOf(const _type_* obj) const;         // returns the index for the pointer to an element in the list
    bool          RemoveIndex(int index);                   // remove the element at the given index
    // removes the element at the given index and places the last element into its spot - DOES NOT PRESERVE LIST ORDER
    bool RemoveIndexFast(int index);
    bool Remove(const _type_& obj); // remove the element
                                    //	void			Sort( cmp_t *compare = ( cmp_t * )&idListSortCompare<_type_, _tag_> );
    //	void			SortSubSection( int startIndex, int endIndex, cmp_t *compare = ( cmp_t * )&idListSortCompare<_type_> );
    void Swap(idList& other);               // swap the contents of the lists
    void DeleteContents(bool clear = true); // delete the contents of the list

    //------------------------
    // auto-cast to other idList types with a different memory tag
    //------------------------

    template <memTag_t _t_>
    operator idList<_type_, _t_> &() {
        return *reinterpret_cast<idList<_type_, _t_>*>(this);
    }

    template <memTag_t _t_>
    operator const idList<_type_, _t_> &() const {
        return *reinterpret_cast<const idList<_type_, _t_>*>(this);
    }

    //------------------------
    // memTag
    //
    // Changing the memTag when the list has an allocated buffer will
    // result in corruption of the memory statistics.
    //------------------------
    memTag_t GetMemTag() const {
        return (memTag_t)memTag;
    };
    void SetMemTag(memTag_t tag_) {
        memTag = (uint8_t)tag_;
    };

  private:
    int     num;
    int     size;
    int     granularity;
    _type_* list;
    uint8_t    memTag;
};

/*
================
idList<_type_,_tag_>::idList( int )
================
*/
template <typename _type_, memTag_t _tag_>
idList<_type_, _tag_>::idList(int newgranularity) {
    assert(newgranularity > 0);

    list        = NULL;
    granularity = newgranularity;
    memTag      = _tag_;
    Clear();
}

/*
================
idList<_type_,_tag_>::idList( const idList< _type_, _tag_ > &other )
================
*/
template <typename _type_, memTag_t _tag_>
idList<_type_, _tag_>::idList(const idList& other) {
    list  = NULL;
    *this = other;
}

/*
================
idList<_type_,_tag_>::~idList< _type_, _tag_ >
================
*/
template <typename _type_, memTag_t _tag_>
idList<_type_, _tag_>::~idList() {
    Clear();
}

/*
================
idList<_type_,_tag_>::Clear

Frees up the memory allocated by the list.  Assumes that _type_ automatically handles freeing up memory.
================
*/
template <typename _type_, memTag_t _tag_>
void idList<_type_, _tag_>::Clear() {
    if (list) {
        idListArrayDelete<_type_>(list, size);
    }

    list = NULL;
    num  = 0;
    size = 0;
}

/*
================
idList<_type_,_tag_>::DeleteContents

Calls the destructor of all elements in the list.  Conditionally frees up memory used by the list.
Note that this only works on lists containing pointers to objects and will cause a compiler error
if called with non-pointers.  Since the list was not responsible for allocating the object, it has
no information on whether the object still exists or not, so care must be taken to ensure that
the pointers are still valid when this function is called.  Function will set all pointers in the
list to NULL.
================
*/
template <typename _type_, memTag_t _tag_>
void idList<_type_, _tag_>::DeleteContents(bool clear) {
    int i;

    for (i = 0; i < num; i++) {
        delete list[i];
        list[i] = NULL;
    }

    if (clear) {
        Clear();
    } else {
        memset(list, 0, size * sizeof(_type_));
    }
}

/*
================
idList<_type_,_tag_>::Allocated

return total memory allocated for the list in bytes, but doesn't take into account additional memory allocated by _type_
================
*/
template <typename _type_, memTag_t _tag_>
size_t idList<_type_, _tag_>::Allocated() const {
    return size * sizeof(_type_);
}

/*
================
idList<_type_,_tag_>::Size

return total size of list in bytes, but doesn't take into account additional memory allocated by _type_
================
*/
template <typename _type_, memTag_t _tag_>
size_t idList<_type_, _tag_>::Size() const {
    return sizeof(idList<_type_, _tag_>) + Allocated();
}

/*
================
idList<_type_,_tag_>::MemoryUsed
================
*/
template <typename _type_, memTag_t _tag_>
size_t idList<_type_, _tag_>::MemoryUsed() const {
    return num * sizeof(*list);
}

/*
================
idList<_type_,_tag_>::Num

Returns the number of elements currently contained in the list.
Note that this is NOT an indication of the memory allocated.
================
*/
template <typename _type_, memTag_t _tag_>
int idList<_type_, _tag_>::Num() const {
    return num;
}

/*
================
idList<_type_,_tag_>::NumAllocated

Returns the number of elements currently allocated for.
================
*/
template <typename _type_, memTag_t _tag_>
int idList<_type_, _tag_>::NumAllocated() const {
    return size;
}

/*
================
idList<_type_,_tag_>::SetNum
================
*/
template <typename _type_, memTag_t _tag_>
void idList<_type_, _tag_>::SetNum(int newnum) {
    assert(newnum >= 0);
    if (newnum > size) {
        Resize(newnum);
    }
    num = newnum;
}

/*
================
idList<_type_,_tag_>::SetGranularity

Sets the base size of the array and resizes the array to match.
================
*/
template <typename _type_, memTag_t _tag_>
void idList<_type_, _tag_>::SetGranularity(int newgranularity) {
    int newsize;

    assert(newgranularity > 0);
    granularity = newgranularity;

    if (list) {
        // resize it to the closest level of granularity
        newsize = num + granularity - 1;
        newsize -= newsize % granularity;
        if (newsize != size) {
            Resize(newsize);
        }
    }
}

/*
================
idList<_type_,_tag_>::GetGranularity

Get the current granularity.
================
*/
template <typename _type_, memTag_t _tag_>
int idList<_type_, _tag_>::GetGranularity() const {
    return granularity;
}

/*
================
idList<_type_,_tag_>::Condense

Resizes the array to exactly the number of elements it contains or frees up memory if empty.
================
*/
template <typename _type_, memTag_t _tag_>
void idList<_type_, _tag_>::Condense() {
    if (list) {
        if (num) {
            Resize(num);
        } else {
            Clear();
        }
    }
}

/*
================
idList<_type_,_tag_>::Resize

Allocates memory for the amount of elements requested while keeping the contents intact.
Contents are copied using their = operator so that data is correnctly instantiated.
================
*/
template <typename _type_, memTag_t _tag_>
void idList<_type_, _tag_>::Resize(int newsize) {
    assert(newsize >= 0);

    // free up the list if no data is being reserved
    if (newsize <= 0) {
        Clear();
        return;
    }

    if (newsize == size) {
        // not changing the size, so just exit
        return;
    }

    list = (_type_*)idListArrayResize<_type_, _tag_>(list, size, newsize, false);
    size = newsize;
    if (size < num) {
        num = size;
    }
}

/*
================
idList<_type_,_tag_>::Resize

Allocates memory for the amount of elements requested while keeping the contents intact.
Contents are copied using their = operator so that data is correnctly instantiated.
================
*/
template <typename _type_, memTag_t _tag_>
void idList<_type_, _tag_>::Resize(int newsize, int newgranularity) {
    assert(newsize >= 0);

    assert(newgranularity > 0);
    granularity = newgranularity;

    // free up the list if no data is being reserved
    if (newsize <= 0) {
        Clear();
        return;
    }

    list = (_type_*)idListArrayResize<_type_, _tag_>(list, size, newsize, false);
    size = newsize;
    if (size < num) {
        num = size;
    }
}

/*
================
idList<_type_,_tag_>::AssureSize

Makes sure the list has at least the given number of elements.
================
*/
template <typename _type_, memTag_t _tag_>
void idList<_type_, _tag_>::AssureSize(int newSize) {
    int newNum = newSize;

    if (newSize > size) {
        if (granularity == 0) // this is a hack to fix our memset classes
        {
            granularity = 16;
        }

        newSize += granularity - 1;
        newSize -= newSize % granularity;
        Resize(newSize);
    }

    num = newNum;
}

/*
================
idList<_type_,_tag_>::AssureSize

Makes sure the list has at least the given number of elements and initialize any elements not yet initialized.
================
*/
template <typename _type_, memTag_t _tag_>
void idList<_type_, _tag_>::AssureSize(int newSize, const _type_& initValue) {
    int newNum = newSize;

    if (newSize > size) {
        if (granularity == 0) // this is a hack to fix our memset classes
        {
            granularity = 16;
        }

        newSize += granularity - 1;
        newSize -= newSize % granularity;
        num = size;
        Resize(newSize);

        for (int i = num; i < newSize; i++) {
            list[i] = initValue;
        }
    }

    num = newNum;
}

/*
================
idList<_type_,_tag_>::AssureSizeAlloc

Makes sure the list has at least the given number of elements and allocates any elements using the allocator.

NOTE: This function can only be called on lists containing pointers. Calling it
on non-pointer lists will cause a compiler error.
================
*/
template <typename _type_, memTag_t _tag_>
void idList<_type_, _tag_>::AssureSizeAlloc(int newSize, new_t* allocator) {
    int newNum = newSize;

    if (newSize > size) {
        if (granularity == 0) // this is a hack to fix our memset classes
        {
            granularity = 16;
        }

        newSize += granularity - 1;
        newSize -= newSize % granularity;
        num = size;
        Resize(newSize);

        for (int i = num; i < newSize; i++) {
            list[i] = (*allocator)();
        }
    }

    num = newNum;
}

/*
================
idList<_type_,_tag_>::operator=

Copies the contents and size attributes of another list.
================
*/
template <typename _type_, memTag_t _tag_>
idList<_type_, _tag_>& idList<_type_, _tag_>::operator=(const idList<_type_, _tag_>& other) {
    int i;

    Clear();

    num         = other.num;
    size        = other.size;
    granularity = other.granularity;
    memTag      = other.memTag;

    if (size) {
        list = (_type_*)idListArrayNew<_type_, _tag_>(size, false);
        for (i = 0; i < num; i++) {
            list[i] = other.list[i];
        }
    }

    return *this;
}

/*
================
idList<_type_,_tag_>::operator[] const

Access operator.  Index must be within range or an assert will be issued in debug builds.
Release builds do no range checking.
================
*/
template <typename _type_, memTag_t _tag_>
const _type_& idList<_type_, _tag_>::operator[](int index) const {
    assert(index >= 0);
    assert(index < num);

    return list[index];
}

/*
================
idList<_type_,_tag_>::operator[]

Access operator.  Index must be within range or an assert will be issued in debug builds.
Release builds do no range checking.
================
*/
template <typename _type_, memTag_t _tag_>
_type_& idList<_type_, _tag_>::operator[](int index) {
    assert(index >= 0);
    assert(index < num);

    return list[index];
}

/*
================
idList<_type_,_tag_>::Ptr

Returns a pointer to the begining of the array.  Useful for iterating through the list in loops.

Note: may return NULL if the list is empty.

FIXME: Create an iterator template for this kind of thing.
================
*/
template <typename _type_, memTag_t _tag_>
_type_* idList<_type_, _tag_>::Ptr() {
    return list;
}

/*
================
idList<_type_,_tag_>::Ptr

Returns a pointer to the begining of the array.  Useful for iterating through the list in loops.

Note: may return NULL if the list is empty.

FIXME: Create an iterator template for this kind of thing.
================
*/
template <typename _type_, memTag_t _tag_>
const _type_* idList<_type_, _tag_>::Ptr() const {
    return list;
}

/*
================
idList<_type_,_tag_>::Alloc

Returns a reference to a new data element at the end of the list.
================
*/
template <typename _type_, memTag_t _tag_>
_type_& idList<_type_, _tag_>::Alloc() {
    if (!list) {
        Resize(granularity);
    }

    if (num == size) {
        Resize(size + granularity);
    }

    return list[num++];
}

/*
================
idList<_type_,_tag_>::Append

Increases the size of the list by one element and copies the supplied data into it.

Returns the index of the new element.
================
*/
template <typename _type_, memTag_t _tag_>
int idList<_type_, _tag_>::Append(_type_ const& obj) {
    if (!list) {
        Resize(granularity);
    }

    if (num == size) {
        int newsize;

        if (granularity == 0) // this is a hack to fix our memset classes
        {
            granularity = 16;
        }
        newsize = size + granularity;
        Resize(newsize - newsize % granularity);
    }

    list[num] = obj;
    num++;

    return num - 1;
}

/*
================
idList<_type_,_tag_>::Insert

Increases the size of the list by at leat one element if necessary
and inserts the supplied data into it.

Returns the index of the new element.
================
*/
template <typename _type_, memTag_t _tag_>
int idList<_type_, _tag_>::Insert(_type_ const& obj, int index) {
    if (!list) {
        Resize(granularity);
    }

    if (num == size) {
        int newsize;

        if (granularity == 0) // this is a hack to fix our memset classes
        {
            granularity = 16;
        }
        newsize = size + granularity;
        Resize(newsize - newsize % granularity);
    }

    if (index < 0) {
        index = 0;
    } else if (index > num) {
        index = num;
    }
    for (int i = num; i > index; --i) {
        list[i] = list[i - 1];
    }
    num++;
    list[index] = obj;
    return index;
}

/*
================
idList<_type_,_tag_>::Append

adds the other list to this one

Returns the size of the new combined list
================
*/
template <typename _type_, memTag_t _tag_>
int idList<_type_, _tag_>::Append(const idList<_type_, _tag_>& other) {
    if (!list) {
        if (granularity == 0) // this is a hack to fix our memset classes
        {
            granularity = 16;
        }
        Resize(granularity);
    }

    int n = other.Num();
    for (int i = 0; i < n; i++) {
        Append(other[i]);
    }

    return Num();
}

/*
================
idList<_type_,_tag_>::AddUnique

Adds the data to the list if it doesn't already exist.  Returns the index of the data in the list.
================
*/
template <typename _type_, memTag_t _tag_>
int idList<_type_, _tag_>::AddUnique(_type_ const& obj) {
    int index;

    index = FindIndex(obj);
    if (index < 0) {
        index = Append(obj);
    }

    return index;
}

/*
================
idList<_type_,_tag_>::FindIndex

Searches for the specified data in the list and returns it's index.  Returns -1 if the data is not found.
================
*/
template <typename _type_, memTag_t _tag_>
int idList<_type_, _tag_>::FindIndex(_type_ const& obj) const {
    int i;

    for (i = 0; i < num; i++) {
        if (list[i] == obj) {
            return i;
        }
    }

    // Not found
    return -1;
}

/*
================
idList<_type_,_tag_>::Find

Searches for the specified data in the list and returns it's address. Returns NULL if the data is not found.
================
*/
template <typename _type_, memTag_t _tag_>
_type_* idList<_type_, _tag_>::Find(_type_ const& obj) const {
    int i;

    i = FindIndex(obj);
    if (i >= 0) {
        return &list[i];
    }

    return NULL;
}

/*
================
idList<_type_,_tag_>::FindNull

Searches for a NULL pointer in the list.  Returns -1 if NULL is not found.

NOTE: This function can only be called on lists containing pointers. Calling it
on non-pointer lists will cause a compiler error.
================
*/
template <typename _type_, memTag_t _tag_>
int idList<_type_, _tag_>::FindNull() const {
    int i;

    for (i = 0; i < num; i++) {
        if (list[i] == NULL) {
            return i;
        }
    }

    // Not found
    return -1;
}

/*
================
idList<_type_,_tag_>::IndexOf

Takes a pointer to an element in the list and returns the index of the element.
This is NOT a guarantee that the object is really in the list.
Function will assert in debug builds if pointer is outside the bounds of the list,
but remains silent in release builds.
================
*/
template <typename _type_, memTag_t _tag_>
int idList<_type_, _tag_>::IndexOf(_type_ const* objptr) const {
    int index;

    index = objptr - list;

    assert(index >= 0);
    assert(index < num);

    return index;
}

/*
================
idList<_type_,_tag_>::RemoveIndex

Removes the element at the specified index and moves all data following the element down to fill in the gap.
The number of elements in the list is reduced by one.  Returns false if the index is outside the bounds of the list.
Note that the element is not destroyed, so any memory used by it may not be freed until the destruction of the list.
================
*/
template <typename _type_, memTag_t _tag_>
bool idList<_type_, _tag_>::RemoveIndex(int index) {
    int i;

    assert(list != NULL);
    assert(index >= 0);
    assert(index < num);

    if ((index < 0) || (index >= num)) {
        return false;
    }

    num--;
    for (i = index; i < num; i++) {
        list[i] = list[i + 1];
    }

    return true;
}

/*
========================
idList<_type_,_tag_>::RemoveIndexFast

Removes the element at the specified index and moves the last element into its spot, rather
than moving the whole array down by one. Of course, this doesn't maintain the order of
elements! The number of elements in the list is reduced by one.

return:	bool	- false if the data is not found in the list.

NOTE:	The element is not destroyed, so any memory used by it may not be freed until the
                destruction of the list.
========================
*/
template <typename _type_, memTag_t _tag_>
bool idList<_type_, _tag_>::RemoveIndexFast(int index) {
    if ((index < 0) || (index >= num)) {
        return false;
    }

    num--;
    if (index != num) {
        list[index] = list[num];
    }

    return true;
}

/*
================
idList<_type_,_tag_>::Remove

Removes the element if it is found within the list and moves all data following the element down to fill in the gap.
The number of elements in the list is reduced by one.  Returns false if the data is not found in the list.  Note that
the element is not destroyed, so any memory used by it may not be freed until the destruction of the list.
================
*/
template <typename _type_, memTag_t _tag_>
bool idList<_type_, _tag_>::Remove(_type_ const& obj) {
    int index;

    index = FindIndex(obj);
    if (index >= 0) {
        return RemoveIndex(index);
    }

    return false;
}
//
///*
//================
// idList<_type_,_tag_>::Sort
//
// Performs a qsort on the list using the supplied comparison function.  Note that the data is merely moved around the
// list, so any pointers to data within the list may no longer be valid.
//================
//*/
// template< typename _type_, memTag_t _tag_ >
// void idList<_type_,_tag_>::Sort( cmp_t *compare ) {
//	if ( !list ) {
//		return;
//	}
//	typedef int cmp_c(const void *, const void *);
//
//	cmp_c *vCompare = (cmp_c *)compare;
//	qsort( ( void * )list, ( size_t )num, sizeof( _type_ ), vCompare );
//}

//
///*
//================
// idList<_type_,_tag_>::SortSubSection
//
// Sorts a subsection of the list.
//================
//*/
// template< typename _type_, memTag_t _tag_ >
// void idList<_type_,_tag_>::SortSubSection( int startIndex, int endIndex, cmp_t *compare ) {
//	if ( !list ) {
//		return;
//	}
//	if ( startIndex < 0 ) {
//		startIndex = 0;
//	}
//	if ( endIndex >= num ) {
//		endIndex = num - 1;
//	}
//	if ( startIndex >= endIndex ) {
//		return;
//	}
//	typedef int cmp_c(const void *, const void *);
//
//	cmp_c *vCompare = (cmp_c *)compare;
//	qsort( ( void * )( &list[startIndex] ), ( size_t )( endIndex - startIndex + 1 ), sizeof( _type_ ), vCompare );
//}

/*
========================
FindFromGeneric

Finds an item in a list based on any another datatype.  Your _type_ must overload operator()== for the _type_.
If your _type_ is a ptr, use the FindFromGenericPtr function instead.
========================
*/
template <typename _type_, memTag_t _tag_, typename _compare_type_>
_type_* FindFromGeneric(idList<_type_, _tag_>& list, const _compare_type_& other) {
    for (int i = 0; i < list.Num(); i++) {
        if (list[i] == other) {
            return &list[i];
        }
    }
    return NULL;
}

/*
========================
FindFromGenericPtr
========================
*/
template <typename _type_, memTag_t _tag_, typename _compare_type_>
_type_* FindFromGenericPtr(idList<_type_, _tag_>& list, const _compare_type_& other) {
    for (int i = 0; i < list.Num(); i++) {
        if (*list[i] == other) {
            return &list[i];
        }
    }
    return NULL;
}

/*
===============================================================================

        Static list template
        A non-growing, memset-able list using no memory allocation.

===============================================================================
*/

template <class type, int size>
class idStaticList {
  public:
    idStaticList();
    idStaticList(const idStaticList<type, size>& other);
    ~idStaticList<type, size>();

    void Clear();            // marks the list as empty.  does not deallocate or intialize data.
    int  Num() const;        // returns number of elements in list
    int  Maximum() const;        // returns the maximum number of elements in the list
    void SetNum(int newnum); // set number of elements in list

    // sets the number of elements in list and initializes any newly allocated elements to the given value
    void SetNum(int newNum, const type& initValue);

    size_t Allocated() const;  // returns total size of allocated memory
    size_t Size() const;       // returns total size of allocated memory including size of list type
    size_t MemoryUsed() const; // returns size of the used elements in the list

    const type& operator[](int index) const;
    type&       operator[](int index);

    type*       Ptr();                   // returns a pointer to the list
    const type* Ptr() const;             // returns a pointer to the list
    type*       Alloc();                 // returns reference to a new data element at the end of the list.  returns NULL when full.
    int         Append(const type& obj); // append element
    int         Append(const idStaticList<type, size>& other); // append list
    int         AddUnique(const type& obj);                    // add unique element
    int         Insert(const type& obj, int index = 0);        // insert the element at the given index
    int         FindIndex(const type& obj) const;              // find the index for the given element
    type*       Find(type const& obj) const;                   // find pointer to the given element
    int         FindNull() const;                              // find the index for the first NULL pointer in the list
    int         IndexOf(const type* obj) const;                // returns the index for the pointer to an element in the list
    bool        RemoveIndex(int index);                        // remove the element at the given index
    bool        RemoveIndexFast(int index);                    // remove the element at the given index
    bool        Remove(const type& obj);                       // remove the element
    void        Swap(idStaticList<type, size>& other);         // swap the contents of the lists
    void        DeleteContents(bool clear);                    // delete the contents of the list

  private:
    int  num;
    type list[size];

  private:
    // resizes list to the given number of elements
    void Resize(int newsize);
};

/*
================
idStaticList<type,size>::idStaticList()
================
*/
template <class type, int size>
idStaticList<type, size>::idStaticList() {
    num = 0;
}

/*
================
idStaticList<type,size>::idStaticList( const idStaticList<type,size> &other )
================
*/
template <class type, int size>
idStaticList<type, size>::idStaticList(const idStaticList<type, size>& other) {
    *this = other;
}

/*
================
idStaticList<type,size>::~idStaticList<type,size>
================
*/
template <class type, int size>
idStaticList<type, size>::~idStaticList() {
}

/*
================
idStaticList<type,size>::Clear

Sets the number of elements in the list to 0.  Assumes that type automatically handles freeing up memory.
================
*/
template <class type, int size>
void idStaticList<type, size>::Clear() {
    num = 0;
}

/*
================
idStaticList<type,size>::DeleteContents

Calls the destructor of all elements in the list.  Conditionally frees up memory used by the list.
Note that this only works on lists containing pointers to objects and will cause a compiler error
if called with non-pointers.  Since the list was not responsible for allocating the object, it has
no information on whether the object still exists or not, so care must be taken to ensure that
the pointers are still valid when this function is called.  Function will set all pointers in the
list to NULL.
================
*/
template <class type, int size>
void idStaticList<type, size>::DeleteContents(bool clear) {
    int i;

    for (i = 0; i < num; i++) {
        delete list[i];
        list[i] = NULL;
    }

    if (clear) {
        Clear();
    } else {
        memset(list, 0, sizeof(list));
    }
}

/*
================
idStaticList<type,size>::Num

Returns the number of elements currently contained in the list.
================
*/
template <class type, int size>
int idStaticList<type, size>::Num() const {
    return num;
}

/*
================
idStaticList<type,size>::Num

Returns the maximum number of elements in the list.
================
*/
template <class type, int size>
int idStaticList<type, size>::Maximum() const {
    return size;
}

/*
================
idStaticList<type>::Allocated
================
*/
template <class type, int size>
size_t idStaticList<type, size>::Allocated() const {
    return size * sizeof(type);
}

/*
================
idStaticList<type>::Size
================
*/
template <class type, int size>
size_t idStaticList<type, size>::Size() const {
    return sizeof(idStaticList<type, size>) + Allocated();
}

/*
================
idStaticList<type,size>::Num
================
*/
template <class type, int size>
size_t idStaticList<type, size>::MemoryUsed() const {
    return num * sizeof(list[0]);
}

/*
================
idStaticList<type,size>::SetNum

Set number of elements in list.
================
*/
template <class type, int size>
void idStaticList<type, size>::SetNum(int newnum) {
    assert(newnum >= 0);
    assert(newnum <= size);
    num = newnum;
}

/*
========================
idStaticList<_type_,_tag_>::SetNum
========================
*/
template <class type, int size>
void idStaticList<type, size>::SetNum(int newNum, const type& initValue) {
    assert(newNum >= 0);
    newNum = Minimum(newNum, size);
    assert(newNum <= size);
    for (int i = num; i < newNum; i++) {
        list[i] = initValue;
    }
    num = newNum;
}

/*
================
idStaticList<type,size>::operator[] const

Access operator.  Index must be within range or an assert will be issued in debug builds.
Release builds do no range checking.
================
*/
template <class type, int size>
const type& idStaticList<type, size>::operator[](int index) const {
    assert(index >= 0);
    assert(index < num);

    return list[index];
}

/*
================
idStaticList<type,size>::operator[]

Access operator.  Index must be within range or an assert will be issued in debug builds.
Release builds do no range checking.
================
*/
template <class type, int size>
type& idStaticList<type, size>::operator[](int index) {
    assert(index >= 0);
    assert(index < num);

    return list[index];
}

/*
================
idStaticList<type,size>::Ptr

Returns a pointer to the begining of the array.  Useful for iterating through the list in loops.

Note: may return NULL if the list is empty.

FIXME: Create an iterator template for this kind of thing.
================
*/
template <class type, int size>
type* idStaticList<type, size>::Ptr() {
    return &list[0];
}

/*
================
idStaticList<type,size>::Ptr

Returns a pointer to the begining of the array.  Useful for iterating through the list in loops.

Note: may return NULL if the list is empty.

FIXME: Create an iterator template for this kind of thing.
================
*/
template <class type, int size>
const type* idStaticList<type, size>::Ptr() const {
    return &list[0];
}

/*
================
idStaticList<type,size>::Alloc

Returns a pointer to a new data element at the end of the list.
================
*/
template <class type, int size>
type* idStaticList<type, size>::Alloc() {
    if (num >= size) {
        return NULL;
    }

    return &list[num++];
}

/*
================
idStaticList<type,size>::Append

Increases the size of the list by one element and copies the supplied data into it.

Returns the index of the new element, or -1 when list is full.
================
*/
template <class type, int size>
int idStaticList<type, size>::Append(type const& obj) {
    assert(num < size);
    if (num < size) {
        list[num] = obj;
        num++;
        return num - 1;
    }

    return -1;
}

/*
================
idStaticList<type,size>::Insert

Increases the size of the list by at leat one element if necessary
and inserts the supplied data into it.

Returns the index of the new element, or -1 when list is full.
================
*/
template <class type, int size>
int idStaticList<type, size>::Insert(type const& obj, int index) {
    int i;

    assert(num < size);
    if (num >= size) {
        return -1;
    }

    assert(index >= 0);
    if (index < 0) {
        index = 0;
    } else if (index > num) {
        index = num;
    }

    for (i = num; i > index; --i) {
        list[i] = list[i - 1];
    }

    num++;
    list[index] = obj;
    return index;
}

/*
================
idStaticList<type,size>::Append

adds the other list to this one

Returns the size of the new combined list
================
*/
template <class type, int size>
int idStaticList<type, size>::Append(const idStaticList<type, size>& other) {
    int i;
    int n = other.Num();

    if (num + n > size) {
        n = size - num;
    }
    for (i = 0; i < n; i++) {
        list[i + num] = other.list[i];
    }
    num += n;
    return Num();
}

/*
================
idStaticList<type,size>::AddUnique

Adds the data to the list if it doesn't already exist.  Returns the index of the data in the list.
================
*/
template <class type, int size>
int idStaticList<type, size>::AddUnique(type const& obj) {
    int index;

    index = FindIndex(obj);
    if (index < 0) {
        index = Append(obj);
    }

    return index;
}

/*
================
idStaticList<type,size>::FindIndex

Searches for the specified data in the list and returns it's index.  Returns -1 if the data is not found.
================
*/
template <class type, int size>
int idStaticList<type, size>::FindIndex(type const& obj) const {
    int i;

    for (i = 0; i < num; i++) {
        if (list[i] == obj) {
            return i;
        }
    }

    // Not found
    return -1;
}

/*
================
idStaticList<type,size>::Find

Searches for the specified data in the list and returns it's address. Returns NULL if the data is not found.
================
*/
template <class type, int size>
type* idStaticList<type, size>::Find(type const& obj) const {
    int i;

    i = FindIndex(obj);
    if (i >= 0) {
        return (type*)&list[i];
    }

    return NULL;
}

/*
================
idStaticList<type,size>::FindNull

Searches for a NULL pointer in the list.  Returns -1 if NULL is not found.

NOTE: This function can only be called on lists containing pointers. Calling it
on non-pointer lists will cause a compiler error.
================
*/
template <class type, int size>
int idStaticList<type, size>::FindNull() const {
    int i;

    for (i = 0; i < num; i++) {
        if (list[i] == NULL) {
            return i;
        }
    }

    // Not found
    return -1;
}

/*
================
idStaticList<type,size>::IndexOf

Takes a pointer to an element in the list and returns the index of the element.
This is NOT a guarantee that the object is really in the list.
Function will assert in debug builds if pointer is outside the bounds of the list,
but remains silent in release builds.
================
*/
template <class type, int size>
int idStaticList<type, size>::IndexOf(type const* objptr) const {
    int index;

    index = objptr - list;

    assert(index >= 0);
    assert(index < num);

    return index;
}

/*
================
idStaticList<type,size>::RemoveIndex

Removes the element at the specified index and moves all data following the element down to fill in the gap.
The number of elements in the list is reduced by one.  Returns false if the index is outside the bounds of the list.
Note that the element is not destroyed, so any memory used by it may not be freed until the destruction of the list.
================
*/
template <class type, int size>
bool idStaticList<type, size>::RemoveIndex(int index) {
    int i;

    assert(index >= 0);
    assert(index < num);

    if ((index < 0) || (index >= num)) {
        return false;
    }

    num--;
    for (i = index; i < num; i++) {
        list[i] = std::move(list[i + 1]);
    }

    return true;
}

/*
========================
idList<_type_,_tag_>::RemoveIndexFast

Removes the element at the specified index and moves the last element into its spot, rather
than moving the whole array down by one. Of course, this doesn't maintain the order of
elements! The number of elements in the list is reduced by one.

return:	bool	- false if the data is not found in the list.

NOTE:	The element is not destroyed, so any memory used by it may not be freed until the
                destruction of the list.
========================
*/
template <typename _type_, int size>
bool idStaticList<_type_, size>::RemoveIndexFast(int index) {
    if ((index < 0) || (index >= num)) {
        return false;
    }

    num--;
    if (index != num) {
        list[index] = list[num];
    }

    return true;
}

/*
================
idStaticList<type,size>::Remove

Removes the element if it is found within the list and moves all data following the element down to fill in the gap.
The number of elements in the list is reduced by one.  Returns false if the data is not found in the list.  Note that
the element is not destroyed, so any memory used by it may not be freed until the destruction of the list.
================
*/
template <class type, int size>
bool idStaticList<type, size>::Remove(type const& obj) {
    int index;

    index = FindIndex(obj);
    if (index >= 0) {
        return RemoveIndex(index);
    }

    return false;
}

/*
================
idStaticList<type,size>::Swap

Swaps the contents of two lists
================
*/
template <class type, int size>
void idStaticList<type, size>::Swap(idStaticList<type, size>& other) {
    idStaticList<type, size> temp = *this;
    *this                         = other;
    other                         = temp;
}

// debug tool to find uses of idlist that are dynamically growing
// Ideally, most lists on shipping titles will explicitly set their size correctly
// instead of relying on allocate-on-add
void BreakOnListGrowth();
void BreakOnListDefault();

/*
========================
idList<_type_,_tag_>::Resize

Allocates memory for the amount of elements requested while keeping the contents intact.
Contents are copied using their = operator so that data is correctly instantiated.
========================
*/
template <class type, int size>
void idStaticList<type, size>::Resize(int newsize) {
    assert(newsize >= 0);

    // free up the list if no data is being reserved
    if (newsize <= 0) {
        Clear();
        return;
    }

    if (newsize == size) {
        // not changing the size, so just exit
        return;
    }

    assert(newsize < size);
    return;
}
