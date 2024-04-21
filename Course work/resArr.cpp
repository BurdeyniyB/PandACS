
#ifndef RESARR_CPP
#define RESARR_CPP
class resArr {
    int initSize = 1;
    int curr = 0;
    int cap = 0;
    int* arr;

public:
    resArr() {
        arr = new int[initSize];
        cap = initSize;
    }

    void addElem(int val) {
        if (curr < cap) {
            arr[curr] = val;
            curr++;
        }
        else {
            int newCap = cap * 2;
            int* newArr = new int[newCap];
            for (int i = 0; i < cap; ++i) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            cap = newCap;
            arr[curr] = val;
            curr++;
        }
    }
    int getCurr(){
        return curr;
    }

    int getElem(int numEl){
        return arr[numEl];
    }
};
#endif
