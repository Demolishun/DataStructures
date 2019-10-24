#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <cstddef> // size_t
#include <vector>

template<typename T>
class CircularBuffer
{
    using DataCont = std::vector<T>;
    using DataContIter = typename DataCont::iterator;
public:
    class CircularIter
    {
    public:
        CircularIter(CircularBuffer& circbuff, DataContIter iter)
            : m_circbuff(circbuff)
            , m_iter(iter)
        {
        }

        // inc operator
        void operator++(){
            m_circbuff.inc(m_iter);
        }

        // get value operator
        T operator*(){
            return *m_iter;
        }

    private:
        CircularBuffer& m_circbuff;
        DataContIter m_iter;
    };
    //friend CircularIter; // not needed?

    CircularBuffer(){
        resize(256);
    }
    CircularBuffer(size_t length){
        resize(length);
    }

    // resize clears contents
    void resize(size_t length){
        m_buffer.resize(length, 0.0);
        //m_buffer.clear(); // clears values
        m_begin = m_buffer.begin();
        m_end = m_buffer.begin();
    }
    int size(){
        return (m_begin <= m_end) ? (m_end - m_begin) : (m_begin - m_buffer.begin()) + (--m_buffer.end() - m_end);
    }
    size_t innerSize(){
        return m_buffer.size();
    }
    int beginPos(){
        return m_begin - m_buffer.begin();
    }
    int endPos(){
        return m_end - m_buffer.begin();
    }

    // begin and end of buffer
    //const DataContIter begin(){
    CircularIter begin(){
        return CircularIter(*this, m_begin);
    }
    //const DataContIter end(){
    CircularIter end(){
        return CircularIter(*this, m_end);
    }

    // insert and remove
    // pop from front
    T pop(){
        if(m_begin != m_end){
            T val = *m_begin;
            inc(m_begin);

            return val;
        }

        return T();
    }
    // push onto back
    void push(T value){
        *m_end = value;
        inc(m_end);

        if(m_end == m_begin){
            inc(m_begin);
        }
    }

private:
    void inc(DataContIter& iter){
        iter++;
        if(iter == m_buffer.end()) iter = m_buffer.begin();
    }

    DataCont m_buffer;
    DataContIter m_begin;
    DataContIter m_end;
};

#endif // CIRCULARBUFFER_H
