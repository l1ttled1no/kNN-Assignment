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
    // if (index < 0 || index > size) { throw std::out_of_range("get(): Out of range");}
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
    if(index < 0 || index >= size) { throw std::out_of_range("get(): Out of range");}
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
    if (temp == nullptr) { 
        return;
    }
    for (int i = 0; i < size; i++)
    {
        if (i == size - 1) { cout << temp->data; }
        else { cout << temp->data << " "; }
        temp = temp->next;
    }
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
List<T>* LList<T>::getSubList(int start, int end)
{
    // if (end >= size) end = size - 1;
    // if (start < 0 || start > end) return nullptr;
    // if (start >= size) return nullptr;
    // LList<T> *sub = new LList<T>();
    // Node *temp = head;
    // for (int i = 0; i < start; i++) { temp = temp->next; }
    // for (int i = start; i <= end; i++)
    // {
    //     sub->push_back(temp->data);
    //     temp = temp->next;
    // }
    // return sub;

    //subList dùng để cắt danh sách liên kết từ đoạn start đến end nếu end lớn hơn size thì lấy hết từ 
    //start đến cuối và nếu start lớn hơn size thì bỏ qua, không bao gồm end, luôn đảm bảo end > start
    LList<T> *sub = new LList<T>();
    if (end > size) end = size;
    if (start < 0 || start > end) return sub;
    if (start > size) return sub;
    Node *temp = head;
    for (int i = 0; i < start; i++) { temp = temp->next; }
    for (int i = start; i < end; i++)
    {
        sub->push_back(temp->data);
        temp = temp->next;
    }
    return sub; 
}


template<typename T>
void LList<T>::printStartEnd(int start, int end) const
{
    Node *temp = head;
    for (int i = 0; i < start; i++) { temp = temp->next; }
    for (int i = start; i < end && i < this->size; i++)
    {
        if(i == end - 1 || i == this->size - 1) { cout << temp->data; }
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
    for (int i = 0; i < this->data->length(); i++) {
        this->data->get(i)->clear();
        delete this->data->get(i);
    }
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
    if (this == &other) { return *this; }
    this->~Dataset();
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
        getline(file, dataLine);
        stringstream s(dataLine); 
        string colName;
        while (getline(s, colName, ',')) { this->colData->push_back(colName); }
        while (getline(file, dataLine))
        {
            stringstream s(dataLine);
            string value;
            bool isPushed = false;
            LList<int> *temp = new LList<int>();
            while (getline(s, value, ','))
            {
                if (value == "") {
                    isPushed = false;
                    break;
                }
                temp->push_back(stoi(value));
                isPushed = true;
            }
            if (isPushed) this->data->push_back(temp);
            else { delete temp; }
        }
        return true;
    }    
    return false; 
}

void Dataset::printHead(int nRows, int nCols) const
{
    int this_nRows, this_nCols;
    bool isPrintColToEnd = false;
    this->getShape(this_nRows, this_nCols);
    if (nRows <= 0 || nCols <= 0) { 
        // cout << "triggered 1" << endl; 
        return;     
    }
    if (!this->data->length()) {
        this->colData->printStartEnd(0, nCols);
        // cout << "triggered 2" << endl;
        return;
    }

    if (nRows > this_nRows || nCols > this_nCols) {
        bool isPrintColToEnd = false; 
        if (nRows > this_nRows) { nRows = this_nRows;}
        if (nCols > this_nCols) { 
            nCols = this_nCols;
            isPrintColToEnd = true; 
        }
        if (isPrintColToEnd){ 
            this->colData->printStartEnd(0, this->colData->length());
        }
        else {
            this->colData->printStartEnd(0, nCols);
        }
        cout << endl;
        for (int i = 0; i < nRows; i++) {
            this->data->get(i)->printStartEnd(0, nCols);
            if (i != nRows - 1) { cout << endl; }
        }
       
        return;
    }


    else {
        this->colData->printStartEnd(0, nCols);
        cout << endl;
        for (int i = 0; i < nRows; i++) {
            this->data->get(i)->printStartEnd(0, nCols);
            if (i != nRows - 1) { cout << endl; }
        }
       
        return;
    }
}

void Dataset::printTail(int nRows, int nCols) const
{
    int this_nRows, this_nCols;
    this->getShape(this_nRows, this_nCols);
    if (nRows <= 0 || nCols <= 0) { return; }
    if (!this->data->length()) {
        this->colData->printStartEnd(this->colData->length() - nCols, this->colData->length());
        return;
    }
    // cout << "this_nRows: " << this_nRows << " this_nCols: " << this_nCols << endl;
    if (nRows > this_nRows || nCols > this_nCols) {
        bool isPrintColToEnd = false; 
        if (nRows > this_nRows) { nRows = this_nRows; }
        if (nCols > this_nCols) { 
            nCols = this_nCols;
            isPrintColToEnd = true; 
        }
        if (isPrintColToEnd){ 
            this->colData->printStartEnd(this_nCols - nCols, this->colData->length());
            if (this->data->length() == 0) { return; }
            else { cout << endl; }
        }
        else {
            this->colData->printStartEnd(this_nCols - nCols, this_nCols);
            if (this->data->length() == 0) { return; }
            else { cout << endl; }
        }
        
        for (int i = this_nRows - nRows; i < this_nRows; i++) {
            this->data->get(i)->printStartEnd(this_nCols - nCols, this_nCols);
            if (i != this_nRows - 1) { cout << endl; }
        }
        return;
    }
    else {
        this->colData->printStartEnd(this_nCols - nCols, this_nCols);
        cout << endl;
        for (int i = this_nRows - nRows; i < this_nRows; i++) {
            this->data->get(i)->printStartEnd(this_nCols - nCols, this_nCols);
            if (i != this_nRows - 1) { cout << endl; }
        }
        return;
    }
}

void Dataset::getShape (int& nRows, int& nCols) const
{
    if (!this->data->length() || !this->colData->length()) { nRows = nCols = 0; return; }
    nRows = this->data->length();
    int max = this->data->get(0)->length();
    for (int i = 1; i < this->data->length(); i++) {
        if (this->data->get(i)->length() > max) { max = this->data->get(i)->length(); }
    }
    nCols = max;
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
            int idx = -1;
            for (int i = 0; i < this->colData->length(); i++) {
                if (this->colData->get(i) == column) { //find the index of the column
                    idx = i;
                    break;
                }
            }
            if (idx == -1) { return false; } //cannot find the column
            else {
                this->colData->remove(idx);
                for (int i = 0; i < this->data->length(); i++) {
                    this->data->get(i)->remove(idx);
                }
                if (this->colData->length() != this->data->length()) { this->colData->insert(idx, ""); }
                if (this->colData->length() == 0) { this->data->clear(); }
                return true;
            }
        }
        default: { return false; }
    }
}

Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const {
    int nRows, nCols;
    Dataset extractData;
    this->getShape(nRows, nCols);

    // cout << "DATA LENGTH: " << this->data->length() << endl;
    // cout << "nRows: " << nRows << " nCols: " << nCols << endl;
    if ((nRows == 0 && nCols == 0) || this->colData->length() == 0) { throw std::out_of_range("get(): Out of range");}
    // if (startRow < 0 || startRow >= nRows) { return extractData; }
    // if (startCol < 0 || startCol >= nCols) { return extractData; }
    // if (endCol < 0 && endCol != -1) { return extractData; } //endCol = -1 means extract to the end
    // if (endRow < 0 && endRow != -1) { return extractData; } //endRow = -1 means extract to the end

if (startRow < 0 || startRow >= nRows || 
    startCol < 0 || startCol >= nCols || 
    startCol >= colData->length() ||
    (endCol < -1) || (endRow < -1)) { 
        throw std::out_of_range("get(): Out of range");
}

    if (endRow == -1 || endRow >= nRows) { endRow = nRows - 1; }
    if (endCol == -1 || endCol >= nCols) { endCol = nCols - 1; }

    if (startRow > endRow || startCol > endCol) { throw std::out_of_range("get(): Out of range");}
    // cout << "if pass" << endl;
    for (int i = startCol; i <= endCol; i++) {
        if (i < this->colData->length()) { extractData.colData->push_back(this->colData->get(i)); }
        else { extractData.colData->push_back(""); }
    }
    for (int i = startRow; i <= endRow; i++) {
        List <int>* temp = new LList<int>;
        for (int j = startCol; j <= endCol; j++) {
            temp->push_back(this->data->get(i)->get(j));
        }
        extractData.data->push_back(temp);
    }
    return extractData;
}

double Dataset::EuclideanDistance(const List<int>* x, const List<int>* y) const {
    double distance = 0.00;
    int maxLength = max(x->length(), y->length());
    int *xArr = new int[maxLength]();
    int *yArr = new int[maxLength]();
    x->supportGetArray(xArr);
    y->supportGetArray(yArr);
    for (int i = 0; i < x->length(); i++) {
        distance += pow(xArr[i] - yArr[i], 2);
    }
    delete[] xArr;
    delete[] yArr;
    return sqrt(distance);
}

Dataset Dataset::predictDataset(const Dataset& X_train, const Dataset& y_train, int k) const {
    //this = X_test     
    Dataset y_pred;
    if (this->data->length() == 0 || X_train.data->length() == 0) { throw std::out_of_range("get(): Out of range"); }
    y_pred.colData->push_back("label");
    for (int i = 0; i < this->data->length(); ++i){
        double *distance = new double[X_train.data->length()]();
        // int *labels = new int[X_train.data->length()]();
        int *labelIndex = new int[X_train.data->length()]();

        for (int j = 0; j < X_train.data->length(); ++j){

            distance[j] = EuclideanDistance(this->data->get(i), X_train.data->get(j));
            labelIndex[j] = j;
        }

        mergeSort(distance, labelIndex, 0, X_train.data->length() - 1);

        int *label_counts = new int[10]();
        if (k > X_train.data->length()) { throw std::out_of_range("get(): Out of range");}
        for (int j = 0; j < k; ++j){
            // label_counts[labels[j]]++;
            label_counts[y_train.data->get(labelIndex[j])->get(0)]++;
        }

        int max_idx = findMaxIndexOf10(label_counts);
        List<int>* temp = new LList<int>;
        temp->push_back(max_idx);
        y_pred.data->push_back(temp);

        delete[] distance;
        // delete[] labels;
        delete[] labelIndex;
        delete[] label_counts;
    }
    return y_pred;
}


double Dataset::score(const Dataset& y_test) const {
    if ( this->data->length() != y_test.data->length() || 
         this->data->length() == 0 ||
        y_test.data->length() == 0 ){ 
        throw std::out_of_range("get(): Out of range");
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
    return X_test.predictDataset(this->X_train, this->y_train, this->k);
}

double kNN::score(const Dataset& y_test, const Dataset& y_pred) {
    return y_test.score(y_pred);
}

/* ----------------- end of kNN ----------------- */

/*--------------------Other supporting functions--------------------*/
string commaToSpace(string str)
{
    for (int i = 0; i < str.length(); i++) { if (str[i] == ',') { str[i] = ' '; } }
    return str;
}


// int partition(double mainArr[], int labelArr[], int low, int high)
// {
//     double pivot = mainArr[high];
//     int i = low - 1;
//     for (int j = low; j < high; j++)
//     {
//         if (mainArr[j] < pivot)
//         {
//             i++;
//             swap(mainArr[i], mainArr[j]);
//             swap(labelArr[i], labelArr[j]);
//         }
//     }
//     swap(mainArr[i + 1], mainArr[high]);
//     swap(labelArr[i + 1], labelArr[high]);
//     return i + 1;
// }

// void quickSort(double mainArr[], int labelArr[], int low, int high)
// {
//     if (low < high)
//     {
//         int pi = partition(mainArr, labelArr, low, high);
//         quickSort(mainArr, labelArr, low, pi - 1);
//         quickSort(mainArr, labelArr, pi + 1, high);
//     }
// }

// void bubbleSort(double mainArr[], int labelArr[], int n)
// {
//     for (int i = 0; i < n - 1; i++)
//     {
//         for (int j = 0; j < n - i - 1; j++)
//         {
//             if (mainArr[j] > mainArr[j + 1])
//             {
//                 swap(mainArr[j], mainArr[j + 1]);
//                 swap(labelArr[j], labelArr[j + 1]);
//             }
//         }
//     }
// }

// void selectionSort(double mainArr[], int labelArr[], int n)
// {
//     for (int i = 0; i < n - 1; i++)
//     {
//         int min_idx = i;
//         for (int j = i + 1; j < n; j++)
//         {
//             if (mainArr[j] < mainArr[min_idx])
//             {
//                 min_idx = j;
//             }
//         }
//         if (min_idx != i)
//         {
//             swap(mainArr[i], mainArr[min_idx]);
//             swap(labelArr[i], labelArr[min_idx]);
//         }
//     }
// }

// int minIdx(double mainArr[], int n, int index)
// {
//     int min_idx = index;
//     for (int i = index + 1; i < n; i++)
//     {
//         if (mainArr[i] < mainArr[min_idx])
//         {
//             min_idx = i;
//         }
//     }
//     return min_idx;
// }

// void recurSelectionSort(double mainArr[], int labelArr[], int n, int index)
// {
//     if (index == n) { return; }
//     int min_idx = minIdx(mainArr, n, index);
//     if (min_idx != index)
//     {
//         swap(mainArr[min_idx], mainArr[index]);
//         swap(labelArr[min_idx], labelArr[index]);
//     }
//     recurSelectionSort(mainArr, labelArr, n, index + 1);
// }

// void insertionSort(double mainArr[], int labelArr[], int n)
// {
//     for (int i = 1; i < n; i++)
//     {
//         double key = mainArr[i];
//         int key_label = labelArr[i];
//         int j = i - 1;
//         while (j >= 0 && mainArr[j] > key)
//         {
//             mainArr[j + 1] = mainArr[j];
//             labelArr[j + 1] = labelArr[j];
//             j--;
//         }
//         mainArr[j + 1] = key;
//         labelArr[j + 1] = key_label;
//     }
// }

void merge(double mainArr[], int labelArr[], int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r - m;

    double *L = new double[n1], *R = new double[n2];
    int *L_label = new int[n1], *R_label = new int[n2];

    for (int i = 0; i < n1; i++){
        L[i] = mainArr[l + i];
        L_label[i] = labelArr[l + i];
    }
    for (int i = 0; i < n2; i++){
        R[i] = mainArr[m + 1 + i];
        R_label[i] = labelArr[m + 1 + i];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            mainArr[k] = L[i];
            labelArr[k] = L_label[i];
            i++;
        }
        else{
            mainArr[k] = R[j];
            labelArr[k] = R_label[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        mainArr[k] = L[i];
        labelArr[k] = L_label[i];
        i++;
        k++;
    }

    while (j < n2){
        mainArr[k] = R[j];
        labelArr[k] = R_label[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
    delete[] L_label;
    delete[] R_label;
}

void mergeSort(double mainArr[], int labelArr[], int l, int r){
    if (l < r){
        int m = l + (r - l) / 2;
        mergeSort(mainArr, labelArr, l, m);
        mergeSort(mainArr, labelArr, m + 1, r);
        merge(mainArr, labelArr, l, m, r);
    }
}

void train_test_split(Dataset &X, Dataset &Y, double test_size,
                      Dataset &X_train, Dataset &X_test, 
                      Dataset &Y_train, Dataset &Y_test)
{
    // X = feature, Y = label
    if (X.getData()->length() != Y.getData()->length()) throw std::out_of_range("get(): Out of range");
    // cout << "test_size: " << test_size << endl;
    if (test_size <= 0 || test_size >= 1) throw std::out_of_range("get(): Out of range");
    int nRows, nCols;
    X.getShape(nRows, nCols);

    double train_size = 1 - test_size;
    double nRows_train = (nRows * train_size) - 1;

    // Y_train < X_train, return 
    // if (nRows_train < 0) return;

    X_train = X.extract(0, nRows_train, 0, - 1);
    Y_train = Y.extract(0, nRows_train, 0,   0);

    X_test = X.extract(nRows_train + 1, nRows, 0, -1);
    Y_test = Y.extract(nRows_train + 1, nRows, 0,  0);


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

// int roundedNumber(double n){
//     if (n - (int)n < 0.5){
//         return n;
//     }
//     else{
//         return n + 1;
//     }
// }



/*--------------------end of Other supporting functions--------------------*/
