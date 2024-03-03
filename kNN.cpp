#include "kNN.hpp"

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


--------------------------------praying section-----------------------------------
*/
/*--------------------------------------------------------------------------------*/



/*--------------------Others supporting functions--------------------*/
string commaToSpace(string str)
{
    for (int i = 0; i < str.length(); i++) { if (str[i] == ',') { str[i] = ' '; } }
    return str;
}
/*--------------------end of Other supporting functions--------------------*/
/* ----------------- LinkedList ----------------- */
template<typename T>
void LList<T>::push_back(T value) 
{
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


template<typename T>
void LList<T>::push_front(T value)
{
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


template<typename T>
void LList<T>::insert(int index, T value)
{
    if(index < 0 || index > size) { return; }
    if (index == 0)              { push_front(value); }
    else if (index == size)      { push_back(value); }
    else 
    {
        Node *temp = head;
        for (int i = 0; i < index - 1; i++) { temp = temp->next; }
        Node *newNode = new Node(value, temp->next);
        temp->next = newNode;
        ++size;
    }
}


template<typename T>
void LList<T>::remove(int index)
{
    if(index < 0 || index >= size) { return; }
    else
    {
        Node *temp = head;
        if (index == 0)
        {
            head = head->next;
            delete temp;
        }
        else
        {
            for (int i = 0; i < index - 1; i++) { temp = temp->next; }
            Node *del = temp->next;
            temp->next = del->next;
            delete del;
            if (index == size - 1) { tail = temp; }
        }
        --size;
    }
}


template<typename T>
T& LList<T>::get(int index) const
{
    if(index < 0 || index >= size) { throw std::out_of_range("get(): Out of range"); }
    Node *curr = head;
    for (int i = 0; i < index; i++) { curr = curr->next; }
    return curr->data;
}


template<typename T>
int LList<T>::length() const
{
    return size;
}


template<typename T>
void LList<T>::clear()
{
    while (head != nullptr)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    head = tail = nullptr;
    size = 0;
}


template<typename T>
void LList<T>::print() const
{
    Node *temp = head;
    for (int i = 0; i < size; i++)
    {
        if(i == size - 1) { std::cout << temp->data; }
        else { std::cout << temp->data << " "; }
        temp = temp->next;
    }
    std::cout << std::endl;
}


template<typename T>
void LList<T>::reverse()
{
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


template<typename T>
List<T>* LList<T>::subList(int start, int end)
{
    if(start < 0 || start >= size || end < 0 || end >= size || start > end) { return nullptr; }
    LList<T> *sub = new LList<T>();
    Node *temp = head;
    for (int i = 0; i < start; i++) { temp = temp->next; }
    for (int i = start; i <= end; i++) { sub->push_back(temp->data); temp = temp->next; }
    return sub;
}


template<typename T>
void LList<T>::printStartToEnd(int start, int end) const
{
    Node *temp = head;
    for (int i = 0; i < start; i++) { temp = temp->next; }
    for (int i = start; i < end && i < this->size; i++)
    {
        if(i == end - 1 || i == this->size - 1) { cout << temp->data << endl; }
        else { cout << temp->data << " "; }
        temp = temp->next;
    }
}
/*----------------end of LList--------------- */



/* ----------------- Dataset ----------------- */
Dataset::Dataset()
{
    this->colData = new LList<string>();
    this->data = new LList<List<int>*>();
}


Dataset::~Dataset()
{
    delete this->colData;
    delete this->data;
}


Dataset::Dataset(const Dataset &other)
{
    this->colData = new LList<string>();
    this->data = new LList<List<int>*>();
    for (int i = 0; i < other.colData->length(); i++) { this->colData->push_back(other.colData->get(i)); }
    for (int i = 0; i < other.data->length(); i++)
    {
        LList<int> *temp = new LList<int>();
        for (int j = 0; j < other.data->get(i)->length(); j++) 
        { 
            temp->push_back(other.data->get(i)->get(j)); 
        }
        this->data->push_back(temp);
    }
}


Dataset& Dataset::operator=(const Dataset &other)
{
    if (this != &other)
    {
        delete this->colData;
        delete this->data;
        this->colData = new LList<string>();
        this->data = new LList<List<int>*>();
        for (int i = 0; i < other.colData->length(); i++){
            this->colData->push_back(other.colData->get(i));
        }
        for (int i = 0; i < other.data->length(); i++)
        {
            LList<int> *temp = new LList<int>();
            for (int j = 0; j < other.data->get(i)->length(); j++) 
            { 
                temp->push_back(other.data->get(i)->get(j)); 
            }
            this->data->push_back(temp);
        }
    }
    return *this;
}


bool Dataset::loadFromCSV(const char* fileName)
{
    ifstream file(fileName);
    if (!file.is_open()) { return false; }
    string lineData; 
    // analyzing Column names
    file >> lineData;
    lineData = commaToSpace(lineData); // replace comma with space
    stringstream ss(lineData);
    while (ss >> lineData) { this->colData->push_back(lineData); }

    // analyzing data
    while (file >> lineData)
    {
        lineData = commaToSpace(lineData); // replace comma with space
        stringstream ss(lineData);
        LList<int> *temp = new LList<int>();
        while (ss >> lineData) { temp->push_back(stoi(lineData)); }
        this->data->push_back(temp);
    }

    // close file and return true
    file.close();
    return true;
}


void Dataset::printHead(int nRows, int nCols) const
{
    if (nRows <= 0 || nCols <= 0) { return; }
    if (nRows > this->data->length()) { nRows = this->data->length(); } // if nRows > length of data, then nRows = length of data
    if (nCols > this->colData->length()) { nCols = this->colData->length(); } // if nCols > length of colData, then nCols = length of colData

    // print column names
    this->colData->printStartToEnd(0, nCols);

    // print data
    for (int i = 0; i < nRows; i++)
    {
        this->data->get(i)->printStartToEnd(0, nCols);
    }
}

void Dataset::printTail(int nRows, int nCols) const
{
    if (nRows <= 0 || nCols <= 0) { return; }
    if (nRows > this->data->length()) { nRows = this->data->length(); } // if nRows > length of data, then nRows = length of data
    if (nCols > this->colData->length()) { nCols = this->colData->length(); } // if nCols > length of colData, then nCols = length of colData

    // print column names
    this->colData->printStartToEnd(this->colData->length() - nCols, this->colData->length());

    // print data
    for (int i = this->data->length() - nRows; i < this->data->length(); i++)
    {
        this->data->get(i)->printStartToEnd(this->colData->length() - nCols, this->colData->length());
    }
}

void Dataset::getShape (int& nRows, int& nCols) const
{
    nRows = this->data->length();
    nCols = this->colData->length();
}


void Dataset::columns() const
{
    this->colData->print();
}

// void Dataset::clear() {
//     delete this->colData;
//     delete this->data;
// }

bool Dataset::drop (int axis, int index, string column) {
    switch (axis) {
        case 0: {
            //delete a row 
            if (index < 0 || index >= this->data->length()) { return false; }
            this->data->remove(index);
            return true;
            break;
        }
        case 1: {
            //delete a column
            if (column == "") { return false; }
            int index = -1;
            for (int i = 0; i < this->colData->length(); i++) {
                if (this->colData->get(i) == column) { //find the index of the column
                    index = i;
                    break;
                }
            }
            if (index == -1) { return false; } //cannot find the column
            else {
                for (int i = 0; i < this->data->length(); i++) {
                    this->data->get(i)->remove(index);
                }
                this->colData->remove(index);
                return true;
            }
        }
        default: { return false; }
    }
}

Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const {
    if (endRow < 0 || endRow >= this->data->length()) { endRow = this->data->length() - 1; }
    if (endCol < 0 || endCol >= this->data->get(0)->length()) { endCol = this->data->get(0)->length() - 1; }

    Dataset extractData; 
    
    // for (int i = startCol; i <= endCol; i++) {
    //     extractData.colData->push_back(this->colData->get(i));
    // }
    // for (int i = startRow; i <= endRow; i++) {
    //     List <int>* temp1 = new LList<int>;
    //     for (int j = startCol; j <= endCol; j++) {
    //         temp1->push_back(this->data->get(i)->get(j));
    //     }
    //     extractData.data->push_back(temp1);
    // }
    // return extractData;

    //using sub list
    extractData.colData = this->colData->subList(startCol, endCol);
    //using sublist
    for (int i = startRow; i <= endRow; i++) {
        extractData.data->push_back(this->data->get(i)->subList(startCol, endCol));
    }
    return extractData;
}

double Dataset::EuclideanDistance(const List<int>* x, const List<int>* y) const {
    List<int>* x_ = new LList<int>;
    List<int>* y_ = new LList<int>;
    int maxSize = max(x->length(), y->length());
    for (int i = 0; i < maxSize; i++) {
        if (i < x->length()) { x_->push_back(x->get(i)); }
        else { x_->push_back(0); }
        if (i < y->length()) { y_->push_back(y->get(i)); }
        else { y_->push_back(0); }
    }
    double distance = 0;
    for (int i = 0; i < x_->length(); i++) {
        distance += pow(x_->get(i) - y_->get(i), 2);
    }
    distance = sqrt(distance);
    delete x_; 
    delete y_;
    return distance;
}


/* ----------------- end of Dataset ----------------- */

