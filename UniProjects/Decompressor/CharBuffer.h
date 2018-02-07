#ifndef CHARBUFFER_H
#define CHARBUFFER_H

using namespace std;
const int buffer_size = 100;
class CharBuffer
{
    char* buffer;
    int length;
    int capacity;
    public:
        CharBuffer()
        {
            length = 0;
            capacity = buffer_size;
            buffer = new char[capacity];
        }
        CharBuffer(const CharBuffer& other)
        {
            copy(other);
        }
        CharBuffer& operator=(const CharBuffer& other)
        {
            if(this != &other)
            {
                removeAll();
                copy(other);
            }

            return *this;
        }
        ~CharBuffer()
        {
            removeAll();
        }
        void push(char symbol)
        {
            if(capacity <= length)
            {
                resize(2 * capacity);
            }
            buffer[length] = symbol;
            length++;
        }
        void reverse()
        {
            char* tmp = new char[length];
            for(int i = length - 1,j = 0; i >=0; i--,j++)
            {
                tmp[j] = buffer[i];
            }
            removeAll();
            buffer = tmp;
        }
        CharBuffer& concat(const CharBuffer& other)
        {
            int len = other.length;
            for(int i = 0; i < len; i++)
            {
                push(other.buffer[i]);
            }
            return *this;
        }
        const char* getBuffer() const
        {
            return buffer;
        }
        const char get(int index) const
        {
            if(index >= length)
            {
                throw "Out of range";
            }

            return buffer[index];

        }
        int getLength() const
        {
            return length;
        }
        void copy(const CharBuffer& other)
        {
            length = other.length;
            capacity = other.capacity;
            buffer = new char[capacity];
            for(int i = 0; i < length; i++)
            {
                buffer[i] = other.buffer[i];
            }

        }
        void removeAll()
        {
            delete[] buffer;
        }
        void resize(int newCapacity)
        {
            capacity = newCapacity;
            char* tmp = new char[capacity];
            for(int i = 0; i < length; i++)
            {
                tmp[i] = buffer[i];
            }

            removeAll();
            buffer = tmp;
        }
};

#endif // CHARBUFFER_H
