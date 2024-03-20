#include "kNN.hpp"
#include <chrono>

void tc1(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead();
    dataset.printTail();
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}

void tc1002()
{
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int> *row = dataset.getData()->get(0);

    row->push_back(2);

    cout << row->length() << endl;
    row->print();
}

// void measureTestCase1Time(){
//     auto start = std::chrono::high_resolution_clock::now();
//     tc1();
//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> diff = end-start;
//     cout << "Time: " << diff.count() << " s" << endl;
// }


// void tc3(){
//     Dataset dataset;
//     dataset.loadFromCSV("mnist.csv");
//     int nRows, nCols;

//     kNN knn;
//     Dataset X_train, X_test, y_train, y_test;
//     Dataset feature = dataset.extract(0, -1, 1, -1);
//     Dataset label = dataset.extract(0, -1, 0, 0);

//     train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
//     X_train.getShape(nRows, nCols);
//     cout << "X_train shape: " << nRows << "x" << nCols << endl;
//     X_test.getShape(nRows, nCols);
//     cout << "X_test shape: " << nRows << "x" << nCols << endl;
//     y_train.getShape(nRows, nCols);
//     cout << "y_train shape: " << nRows << "x" << nCols << endl;
//     y_test.getShape(nRows, nCols);
//     cout << "y_test shape: " << nRows << "x" << nCols << endl;
// }

// void dinotc(){
//     Dataset dataset;
//     dataset.loadFromCSV("mnist.csv");
//     int nRows, nCols;

//     kNN knn;
//     Dataset X_train, X_test, y_train, y_test;
//     Dataset feature = dataset.extract(0, -1, 1, -1);
//     Dataset label = dataset.extract(0, -1, 0, 0);

//     Dataset dino = dataset.extract(0, -1, 0, 0);
//     dino.printHead(1000, 1000);
//     dino.getShape(nRows, nCols);
//     cout << "dino shape: " << nRows << "x" << nCols << endl;
// }


// void tc1lms(){
//     Dataset dataset;
//     dataset.loadFromCSV("mnist.csv");
//     dataset.printHead(10, 10);
//     cout << endl;
//     dataset.printTail(10, 10);
//     cout << endl;
//     int nRows, nCols;
//     dataset.getShape(nRows, nCols);
//     cout << "Shape: " << nRows << "x" << nCols << endl;
// }

void tc1175()
{
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");

    // dataset.getShape(nRows, nCols);
    // cout << "Shape Dataset: " << nRows << "x" << nCols << endl;

    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);

    train_test_split(feature, label, 0.5, X_train, X_test, y_train, y_test);

    X_train.getShape(nRows, nCols);
    cout << "X_train shape: " << nRows << "x" << nCols << endl;
    X_test.getShape(nRows, nCols);
    cout << "X_test shape: " << nRows << "x" << nCols << endl;
    y_train.getShape(nRows, nCols);
    cout << "y_train shape: " << nRows << "x" << nCols << endl;
    y_test.getShape(nRows, nCols);
    cout << "y_test shape: " << nRows << "x" << nCols << endl;

    feature.getShape(nRows, nCols);
    cout << "X shape: " << nRows << "x" << nCols << endl;
    label.getShape(nRows, nCols);
    cout << "y shape: " << nRows << "x" << nCols << endl;
}

void tc1158()
{
int nRows, nCols;
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
Dataset dataset_extract = dataset.extract(0, -2, 0, -1);
Dataset dataset_extract2 = Dataset(dataset_extract);
dataset_extract2.getShape(nRows, nCols);
cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}

void tc1160()
{
int nRows, nCols;
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
Dataset dataset_extract = dataset.extract(30, 20, 0, -1);
Dataset dataset_extract2 = dataset_extract;
dataset_extract2.getShape(nRows, nCols);
cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}

void tc1148(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    int nRows, nCols;
    bool result = dataset.drop(1, 0, "labels");
    cout << "Drop result: " << result << endl;

}

int main() {

    // tc3();
    // tc1lms();
    // tc1002();
    // tc1();
    // tc1175();
    // tc1158();
    // tc1160();
    tc1148();
    return 0;
}