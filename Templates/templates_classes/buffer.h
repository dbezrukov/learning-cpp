#ifndef BUFFER_H
#define BUFFER_H 1

template <typename T, int size> // nSize is the expression parameter
class Buffer
{
private:
    // The expression parameter controls the size of the array
	T buffer[size];
public:
    T* GetBuffer();
    T& operator[](int index);
};

#endif /* BUFFER_H */
