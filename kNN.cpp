#include "kNN.hpp"


/*--------------------Start of class LList--------------------*/
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
    if (index == 0)              { push_front (value); }
    else if (index == size)      { push_back  (value); }
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
        if(i == size - 1) { cout << temp->data; }
        else { cout << temp->data << " "; }
        temp = temp->next;
    }
    cout << endl;
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

// template<typename T>
// void LList<T>::begin() {
//     Node* temp = head;
//     cout << temp->data << endl;
// }

template<typename T>
void LList<T>::sort()
{
    for (int i = 0; i < size - 1; i++)
    {
        Node *min = head;
        Node *temp = head;
        for (int j = i + 1; j < size; j++)
        {
            if (temp->data < min->data) { min = temp; }
            temp = temp->next;
        }
        swap(min->data, head->data);
        head = head->next;
    }
    Node *temp = head;
    while (temp->next != nullptr) { temp = temp->next; }
    tail = temp;
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
    for (int i = 0; i < other.colData->length(); i++) { 
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



Dataset& Dataset::operator=(const Dataset &other)
{
    this->colData = new LList<string>();
    this->data = new LList<List<int>*>();
    for (int i = 0; i < other.colData->length(); i++) { 
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
    return *this;
}


bool Dataset::loadFromCSV(const char* fileName)
{   
    ifstream file(fileName);
    if(file.is_open())
    {
        string dataLine; 
        file >> dataLine;
        dataLine = commaToSpace(dataLine);
        stringstream strStream(dataLine);
        string temp;
        while (strStream >> temp) { this->colData->push_back(temp); }
        while (file >> dataLine)
        {
            dataLine = commaToSpace(dataLine);
            stringstream strStream(dataLine);
            LList<int> *temp = new LList<int>();
            int value;
            while (strStream >> value) { temp->push_back(value); }
            this->data->push_back(temp);
        }
        file.close();
        return true;
    }    
    // cout << "Cannot open file" << endl;
    return false; 
}

void Dataset::printHead(int nRows, int nCols) const
{
    if (nRows <= 0 || nCols <= 0 || !this->data->length()) { return; }
    if (nRows > this->data->length()) { nRows = this->data->length(); }
    if (nCols > this->colData->length()) { nCols = this->colData->length(); }
    this->colData->printStartToEnd(0, nCols);
    for (int i = 0; i < nRows; i++) {
        this->data->get(i)->printStartToEnd(0, nCols);
    }
}

void Dataset::printTail(int nRows, int nCols) const
{
    if (nRows <= 0 || nCols <= 0 || !this->data->length()) { return; }
    if (nRows > this->data->length()) { nRows = this->data->length(); }
    if (nCols > this->colData->length()) { nCols = this->colData->length(); }
    this->colData->printStartToEnd(this->colData->length() - nCols, this->colData->length());
    for (int i = this->data->length() - nRows; i < this->data->length(); i++) {
        this->data->get(i)->printStartToEnd(this->colData->length() - nCols, this->colData->length());
    }
}

void Dataset::getShape (int& nRows, int& nCols) const
{
    if (!this->data->length()) { nRows = nCols = 0; return; }
    nRows = this->data->length();
    nCols = this->colData->length();
}

void Dataset::columns() const
{
    this->colData->print();
}

List<List<int>*>* Dataset::getData() const {
    return this->data;
}
bool Dataset::drop (int axis, int index, string column) {
    switch (axis) {
        case 0: {
            //delete a row 
            if (index < 0 || index >= this->data->length()) { return false; }
            this->data->remove(index);
            return true;
        }
        case 1: {
            //delete a column
            if (column == "") { return false; }
            //if theres no data, return false
            if (this->data->length() == 0) { return false; }
            int idx = -1;
            for (int i = 0; i < this->colData->length(); i++) {
                if (this->colData->get(i) == column) { //find the index of the column
                    idx = i;
                    break;
                }
            }
            if (idx == -1) { return false; } //cannot find the column
            else {
                for (int i = 0; i < this->data->length(); i++) {
                    this->data->get(i)->remove(idx);
                }
                this->colData->remove(idx);
                return true;
            }
        }
        default: { return false; }
    }
}

Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const {
    if (endRow == -1 || endRow >= this->data->length()) endRow = this->data->length() - 1;
    if (endCol == -1 || endCol >= this->colData->length()) endCol = this->colData->length() - 1;
    if (startRow > endRow || startCol > endCol) { return Dataset(); }
    if (startRow < 0 || startCol < 0) { return Dataset(); }
    Dataset extractData; 
    //using subList
    for (int i = startCol; i <= endCol; i++) {
        extractData.colData->push_back(this->colData->get(i));
    }
    for (int i = startRow; i <= endRow; i++) {
        extractData.data->push_back(this->data->get(i)->subList(startCol, endCol));
    }
    return extractData;
}

double Dataset::EuclideanDistance(const List<int>* x, const List<int>* y) const {
    double distance = 0.00;
    if (x->length() != y->length()) { return -1; }
    for (int i = 0; i < x->length(); i++) {
        distance += pow(x->get(i) - y->get(i), 2);
    }
    return sqrt(distance);
}

Dataset Dataset::predict(const Dataset& X_train, const Dataset& y_train, int k) const {
    //this = X_test
    Dataset y_pred;
    y_pred.colData->push_back("label");
    for (int i = 0; i < this->data->length(); ++i){
        double *distance = new double[X_train.data->length()]();
        int *labels = new int[X_train.data->length()]();

        for (int j = 0; j < X_train.data->length(); ++j){
            distance[j] = EuclideanDistance(this->data->get(i), X_train.data->get(j));
            labels[j] = y_train.data->get(j)->get(0);
            // cout << "distance: " << distance[j] << " label: " << labels[j] << endl;
        }
        // Sorting the distances and labels
        for (int j = 0; j < X_train.data->length() - 1; ++j){
            int min_idx = j;
            for (int k = j + 1; k < X_train.data->length(); ++k){
                if (distance[k] < distance[min_idx]){
                    min_idx = k;
                }
            }
            if (min_idx != j){
                swap(distance[j], distance[min_idx]);
                swap(labels[j], labels[min_idx]);
            }
        }

        int *label_counts = new int[10]();
        for (int j = 0; j < k; ++j){
            label_counts[labels[j]]++;
        }

        int max_idx = findMaxIndexOf10(label_counts);
        // cout << "max_idx: " << max_idx << endl;
        List<int>* temp = new LList<int>;
        temp->push_back(max_idx);
        y_pred.data->push_back(temp);

        delete[] distance;
        delete[] labels;
        delete[] label_counts;
    }
    return y_pred;
}


double Dataset::score(const Dataset& y_test) const {
    if ( this->data->length() != y_test.data->length() || 
         this->data->length() == 0 ||
        y_test.data->length() == 0 ){ 
        return -1; 
        }
    int count = 0;
    for (int i = 0; i < this->data->length(); i++) {
        if (this->data->get(i)->get(0) == y_test.data->get(i)->get(0)) {
            count++;
        }
    }
    return (double)count / this->data->length();
}
// /* ----------------- end of Dataset ----------------- */

/* ----------------- start of kNN ----------------- */
kNN::kNN(int k) { this->k = k; }

kNN::~kNN() {}

void kNN::fit(const Dataset& X_train, const Dataset& y_train) {
    this->X_train = X_train;
    this->y_train = y_train;
}

Dataset kNN::predict(const Dataset& X_test) {
    return X_test.predict(this->X_train, this->y_train, this->k);
}

double kNN::score(const Dataset& y_test, const Dataset& y_pred) {
    return y_test.score(y_pred);
    // return -1;
}

/* ----------------- end of kNN ----------------- */

/*--------------------Other supporting functions--------------------*/
string commaToSpace(string str)
{
    for (int i = 0; i < str.length(); i++) { if (str[i] == ',') { str[i] = ' '; } }
    return str;
}

void train_test_split(Dataset &X, Dataset &Y, double test_size,
                      Dataset &X_train, Dataset &X_test, 
                      Dataset &Y_train, Dataset &Y_test)
{
    if (test_size >= 1 || test_size <= 0) return;
    


    int xRows, xCols, yRows, yCols;
    X.getShape(xRows, xCols);
    Y.getShape(yRows, yCols);



    X_train = X.extract(0, (1 - test_size) * xRows - 1, 0, -1);
    Y_train = Y.extract(0, (1 - test_size) * yRows - 1, 0, 0);


    X_test = X.extract((1 - test_size) * xRows, xRows, 0, -1);
    Y_test = Y.extract((1 - test_size) * yRows, yRows, 0, 0);
}

int findMaxIndexOf10 (int arr[]) {
    int max = arr[0];
    int max_idx = 0;
    for (int i = 1; i < 10; i++) {
        if (arr[i] > max) {
            max = arr[i];
            max_idx = i;
        }
    }
    return max_idx;
}

int roundedNumber(double n){
    if (n - (int)n < 0.5){
        return n;
    }
    else{
        return n + 1;
    }
}

/*--------------------end of Other supporting functions--------------------*/
