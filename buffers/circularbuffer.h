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
        using self_type = CircularIter;
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = ptrdiff_t;

        CircularIter(CircularBuffer& circbuff, DataContIter iter, bool isbegin)
            : m_circbuff(circbuff)
            , m_iter(iter)
            , m_isBegin(isbegin)
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

        // comparison operators
        friend bool operator==(const CircularIter& lhs, const CircularIter& rhs){
            return lhs.m_iter == rhs.m_iter;
        }
        friend bool operator!=(const CircularIter& lhs, const CircularIter& rhs){
            return lhs.m_iter != rhs.m_iter;
        }
        /*
        // add operator
        friend CircularIter operator+(int inc){

        }
        */
        // cannot do other comparisons, not known if iter is m_begin or m_end
        /*
        friend bool operator<(const CircularIter& lhs, const CircularIter& rhs){

            return lhs.m_iter < rhs.m_iter;
        }
        friend bool operator>(const CircularIter& lhs, const CircularIter& rhs){
            return lhs.m_iter > rhs.m_iter;
        }
        friend bool operator<=(const CircularIter& lhs, const CircularIter& rhs){
            return lhs.m_iter <= rhs.m_iter;
        }
        friend bool operator>=(const CircularIter& lhs, const CircularIter& rhs){
            return lhs.m_iter >= rhs.m_iter;
        }
        */

    private:
        CircularBuffer& m_circbuff;
        DataContIter m_iter;
        bool m_isBegin;

        friend CircularBuffer;
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
        m_buffer.resize(length, T());
        //m_buffer.clear(); // clears values
        m_begin = m_buffer.begin();
        m_end = m_buffer.begin();
    }
    int size(){
        return (m_begin <= m_end) ? (m_end - m_begin) : (m_begin - m_buffer.begin()) + (--m_buffer.end() - m_end);
    }
    int innerSize(){
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
        return CircularIter(*this, m_begin, true);
    }
    //const DataContIter end(){
    CircularIter end(){
        return CircularIter(*this, m_end, false);
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
    // bulk remove from front m_begin to pos
    void remove(const CircularIter& pos){
        // nothing to remove
        if(m_begin == m_end || m_begin == pos.m_iter){
            return;
        }
        // empty whole buffer
        if(pos.m_iter == m_end){
            m_begin = m_end;
            return;
        }
        if(m_begin < m_end){
            if(pos.m_iter > m_begin && pos.m_iter < m_end){
                m_begin = pos.m_iter;
            }
        }else if(m_begin > m_end){
            if(pos.m_iter < m_end && pos.m_iter < m_begin){
                m_begin = pos.m_iter;
            }else if(pos.m_iter > m_end && pos.m_iter > m_begin){
                m_begin = pos.m_iter;
            }
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
