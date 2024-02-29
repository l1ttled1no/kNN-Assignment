#include "main.hpp"
static ofstream OUTPUT;
/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

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

    virtual List<T>* subList(int start, int end) = 0;
    virtual void printStartToEnd(int start, int end) const = 0; 
    virtual double EuclideanDist(const List<T>* data) = 0;
};

template<typename T>
class LinkedList : public List<T> {
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
        LinkedList() : head(nullptr), tail(nullptr), size(0) {};
        ~LinkedList()
        {
            this->clear();
        };
        void push_back(T value) {
            Node* newNode = new Node(value);
            if(size == 0){
                head = newNode;
                tail = newNode;
            }
            else{
                tail->next = newNode;
                tail = newNode;
            }
            ++size;
        }

        void push_front(T value){
        Node* newNode = new Node(value);
        if (size == 0){
            head = newNode;
            tail = newNode;
        }
        else{
            newNode->next = head;
            head = newNode;
        }
        ++size;
        }

        void insert(int index, T value){
            if(index < 0 || index > size) return;
            if (index == 0) push_front(value);
            else if (index == size) push_back(value);
            else {
                Node *temp = head;
                for (int i = 0; i < index - 1; i++)
                {
                    temp = temp->next;
                }
                Node *newNode = new Node(value, temp->next);
                temp->next = newNode;
                ++size;
            }
        }
        void remove(int index){
            if(index < 0 || index >= size) return;
            else{
                Node *temp = head;
                if (index == 0){
                    head = head->next;
                    delete temp;
                }
                else{
                    for (int i = 0; i < index - 1; i++)
                    {
                        temp = temp->next;
                    }
                    Node *del = temp->next;
                    temp->next = del->next;
                    delete del;
                    if (index == size - 1) tail = temp;
                }
                --size;
            }
        }

        T& get(int index) const {
            if(index < 0 || index >= this->size)  throw std::out_of_range("get(): Out of range");
            Node *curr = head;
            for (int i = 0; i < index; i++)
            {
                curr = curr->next;
            }
            return curr->pointer;
        }

        int length() const { return size; }

        void clear(){
            while (head != nullptr)
            {
                Node *temp = head;
                head = head->next;
                delete temp;
            }
            head = tail = nullptr;
            size = 0;
        }
        void print() const {
            Node *temp = head;
            while (temp != nullptr)
            {
                OUTPUT << temp->data << " ";
                temp = temp->next;
            }
            OUTPUT << endl;
        }
        void reverse(){  
            Node* prev = nullptr;
            Node* curr = head;
            Node* next = nullptr;
            tail = head;
            while (curr != nullptr) {
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }
            head = prev;
        }
        
        List<T>* subList(int start, int end) {
            if(this->size <= start) return nullptr;
            List<T>* result = new LinkedList<T>();
            Node* curr = head; 
            for (int i = 0; i < start; i++){
                curr = curr->next;
            }
            for (int i = start; i < end && i < this->size; i++){
                result->push_back(curr->pointer);
                curr = curr->next;
            }
            return result;
        }
        
        void printStartToEnd (int start, int end) const {
            Node* temp = head;
            for(int i = start; i < end && i < this->size; i++)
            {
                if(i == end - 1 || i == this->size - 1) OUTPUT << temp->pointer << endl;
                else OUTPUT << temp->pointer << " ";
            }
        }

        double EuclideanDist(const List<T>* data){
            double distance = 0.0;
            int maxSize = max(this->size, data->length());
            List<T>* thisList = new LinkedList<T>();
            for (int i = 0; i < this->size; i++){
                thisList->push_back(this->get(i));
            }
            List<T>* otherList = (LinkedList<T>*)data;
            if (this->size < maxSize){
                for (int i = this->size; i < maxSize; i++){
                    thisList->push_back(0);
                }
            }
            else if (otherList->length() < maxSize){
                for (int i = otherList->length(); i < maxSize; i++){
                    otherList->push_back(0);
                }
            }
            for (int i = 0; i < maxSize; i++){
                distance += pow(thisList->get(i) - otherList->get(i), 2);
            }
            return sqrt(distance);
        }
};


/*----------------------DataSet Class------------------------*/
class Dataset {
private:
    List<List<int>*>* data;
    // ArrayList<ArrayList<int>*>* data;
    //You may need to define more
public:
    Dataset();
    ~Dataset();
    Dataset(const Dataset& other);
    Dataset& operator=(const Dataset& other);
    bool loadFromCSV(const char* fileName);
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    void getShape(int& nRows, int& nCols) const;
    void columns() const;
    bool drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
};
/*----------------------end of DataSet Class------------------------*/




class kNN {
private:
    int k;
    //You may need to define more
public:
    kNN(int k = 5);
    void fit(const Dataset& X_train, const Dataset& y_train);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);
};

void train_test_split(Dataset& X, Dataset& y, double test_size, 
                      Dataset& X_train, Dataset& X_test, 
                      Dataset& y_train, Dataset& y_test);

// Please add more or modify as needed