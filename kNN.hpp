#include "main.hpp"
#pragma once
/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
/*--------------------Start of class List--------------------*/
template<typename T>
class List {
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
    // virtual void sort() = 0;
    virtual List<T>* subList(int start, int end) = 0;
    virtual void printStartToEnd(int start, int end) const = 0; 
    virtual void supportGetArray(T* arr) const = 0;
    // virtual T EuclidTe1stSquared(List<T>* others, bool& ifError) const = 0;
};
/*--------------------End of class List--------------------*/



/*--------------------Start of class LList--------------------*/
template<typename T>
class LList : public List<T> {
    private: 
        class Node {
            public:
                T data;
                Node* next;
            public: 
                Node (T data, Node* next = nullptr) {
                    this->data = data;
                    this->next = next;
                }
        };
    private:
        Node* head;
        Node* tail;
        int size;
    public:
        LList() : head(nullptr), tail(nullptr), size(0) {};
        ~LList() { this->clear(); }
        void push_back(T value);
        void push_front(T value);
        void insert(int index, T value);
        void remove(int index);
        T& get(int index) const;
        int length() const;
        void clear();
        void print() const;
        void reverse();
        // void begin();
        // void end();
        // void sort();
        List<T>* subList(int start, int end);
        void printStartToEnd (int start, int end) const;
        void supportGetArray(T* arr) const{
            Node* temp = head;
            for (int i = 0; i < size; i++) {
                arr[i] = temp->data;
                temp = temp->next;
            }
        }
};
/*--------------------End of class LList--------------------*/

/*--------------------Start of class DataSet--------------------*/
class Dataset {
private:
    List<string>* colData; 
    List<List<int>*>* data;
    // ArrayList<ArrayList<int>*>* data;
    //You may need to define more
public:
    Dataset(); //Done
    ~Dataset(); //Done
    Dataset(const Dataset& other); //Done
    Dataset& operator=(const Dataset& other); //Done
    bool loadFromCSV(const char* fileName); //Done
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    void getShape(int& nRows, int& nCols) const;
    void columns() const;
    List<List<int>*>* getData() const;
    bool drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    double EuclideanDistance(const List<int>* a, const List<int>* b) const;
    Dataset predict(const Dataset& X_train, const Dataset& Y_train, const int k) const;
    double score(const Dataset& y_test) const;
};
/*----------------------end of DataSet Class------------------------*/

/*--------------------Start of class kNN--------------------*/
class kNN {
private:
    int k;
    Dataset X_train;
    Dataset y_train;
    //You may need to define more
public:
    kNN(int k = 5);
    ~kNN();
    void fit(const Dataset& X_train, const Dataset& y_train);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);
};
/*--------------------End of class kNN--------------------*/


/*--------------------Others supporting functions--------------------*/
string commaToSpace(string str = "");

void train_test_split(Dataset& X, Dataset& y, double test_size, 
                      Dataset& X_train, Dataset& X_test, 
                      Dataset& y_train, Dataset& y_test);

int findMaxIndexOf10 (int arr[]);

int roundedNumber (double num);

// int partition(double mainArr[], int labelArr[], int low, int high);
// void quickSort(double mainArr[], int labelArr[], int low, int high);

// void bubbleSort(double mainArr[], int labelArr[], int n);

void selectionSort(double mainArr[], int labelArr[], int n);

// int minIdx(double mainArr[], int n, int index);
// void recurSelectionSort(double mainArr[], int labelArr[], int n, int index);

// void insertionSort(double mainArr[], int labelArr[], int n);

void merge(double mainArr[], int labelArr[], int l, int m, int r);
void mergeSort(double mainArr[], int labelArr[], int l, int r);

//------------------ End of declaration ------------------//



/*--------------------------------------------------------------------------------*/
/*
--------------------------------praying section-----------------------------------
                      _oo0oo_
                     o8888888o
                     88" . "88
                     (| -_- |)
                     0\  =  /0
                   ___/`---'\___
                 .' \\|     |// '.
                / \\|||  :  |||// \
               / _||||| -:- |||||- \
              |   | \\\  -  /// |   |
              | \_|  ''\---/''  |_/ |
              \  .-\__  '-'  ___/-. /
            ___'. .'  /--.--\  `. .'___
         ."" '<  `.___\_<|>_/___.' >' "".
        | | :  `- \`.;`\ _ /`;.`/ - ` : | |
        \  \ `_.   \_ __\ /__ _/   .-` /  /
    =====`-.____`.___ \_____/___.-`___.-'=====
                      `=---='

    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
           Phật phù hộ, không bao giờ BUG
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

          _.-/`)
         // / / )
      .=// / / / )
     //`/ / / / /
    // /     ` /
   ||         /
    \\       /
     ))    .'
    //    /
         /


Our program, who art in memory,
    called by thy name;
  thy operating system run;
thy function be done at runtime
  as it was on development.
Give us this day our daily output.
And forgive us our code duplication,
    as we forgive those who
  duplicate code against us.
And lead us not into frustration;
  but deliver us from GOTOs.
    For thine is algorithm,
the computation, and the solution,
    looping forever and ever.
          Return;


--------------------------------end of praying section---------------------------------
*/