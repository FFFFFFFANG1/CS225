template <class T>
void Heap<T>::insert(const T & key){
    if (size == capacity){
        resize();
    }
    size++;
    data[size] = key;
    heapifyUp(size);
}

template <class T>
void Heap<T>::heapifyUp(unsigned int index){
    if (index == 1){
        return;
    }
    unsigned int parent = index / 2; //ground of idx/2
    if (data[index] < data[parent]){
        std::swap(index, parent); //using reference to swap
        heapifyUp(parent);
    }
}

template <class T>
void Heap<T>::resize(){
    capacity *= 2;
    T * temp = new T[capacity];
    for (unsigned int i = 0; i < size; i++){
        temp[i] = data[i];
    }
    delete[] data;
    data = temp;
}

template <class T>
T Heap<T>::removeMin(){
    if (size == 0){
        return;
    }
    T min = data[1];
    data[1] = data[size];
    size--; //pop
    heapifyDown(1);
    return min;
}

template <class T>
void Heap<T>::heapifyDown(unsigned int index){
    unsigned int left = index * 2;
    unsigned int right = index * 2 + 1;
    unsigned int smallest = index;
    if (left <= size && data[left] < data[smallest]){
        smallest = left;
    }
    if (right <= size && data[right] < data[smallest]){
        smallest = right;
    }
    if (smallest != index){
        std::swap(data[index], data[smallest]);
        heapifyDown(smallest);
    }
}

template <class T>
void Heap<T>::buildHeap(){
    for (unsigned int i = size / 2; i > 0; i--){
        heapifyDown(i);
    }
}

template <class T>
void Heap<T>::buildHeap(){
    for (unsigned int i = 0; i < size; i++){
        heapifyUp(i);
    }
}

template <class T>
void Heap<T>::heapSort(){
    buildHeap();
    size_t s = 0;
    for (unsigned int i = size; i > 0; i--){
        T elem = removeMin();
        std::swap(data[s], elem);
        s++;
        size --;
    }
    size = capacity;
}