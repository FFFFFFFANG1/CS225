//functor
class Doubler{
    public:
        int operator()(int x) const{
            return 2*x;
     }
};

//overload
template <class Value, class Modifier>
Value modify(Value v, Modifier m){
    return m(v); //use the type of m to call the right operator()
}

//use
Doubler d;
Tripler t;
int value = 4;
modify<int, Doubler>(value, d); //8
modify<int, Tripler>(value, t); //12