template <class QE> class Queue {   
    public:     
        class QueueIterator : public std::iterator<std::bidirectional_iterator_tag, T> {       
            public:         
                QueueIterator(unsigned index);         
                QueueIterator& operator++();         
                bool operator==(const QueueIterator &other);         
                bool operator!=(const QueueIterator &other);         
                QE& operator*();         
                QE* operator->();       
            private:         
                int location_;
    };   
    /* ... */   
    private:     
        QE* arr_; 
        unsigned capacity_, count_, entry_, exit_;
};

//generate the definition of functions listed above
template <class QE>
Queue<QE>::QueueIterator::QueueIterator(unsigned index) : location_(index) {}
//operator ++
template <class QE>
Queue<QE>::QueueIterator& Queue<QE>::QueueIterator::operator++() {
    location_++;
    return *this;
}
//operator ==
template <class QE>
bool Queue<QE>::QueueIterator::operator==(const QueueIterator &other) {
    return location_ == other.location_;
}
//operator !=
template <class QE>
bool Queue<QE>::QueueIterator::operator!=(const QueueIterator &other) {
    return location_ != other.location_;
}
//operator *
template <class QE>
QE& Queue<QE>::QueueIterator::operator*() {
    return arr_[location_];
}
//operator ->
template <class QE>
QE* Queue<QE>::QueueIterator::operator->() {
    return &arr_[location_];
}
