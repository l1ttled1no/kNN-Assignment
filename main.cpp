#include "kNN.hpp"

// void tc1(){
//     Dataset dataset;
//     dataset.loadFromCSV("mnist.csv");
//     dataset.printHead();
//     dataset.printTail();
//     int nRows, nCols;
//     dataset.getShape(nRows, nCols);
//     cout << "Shape: " << nRows << "x" << nCols << endl;

//     kNN knn;
//     Dataset X_train, X_test, y_train, y_test;
//     Dataset feature = dataset.extract(0, -1, 1, -1);
//     Dataset label = dataset.extract(0, -1, 0, 0);
//     train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);

//     knn.fit(X_train, y_train);
//     Dataset y_pred = knn.predict(X_test);
//     double accuracy = knn.score(y_test, y_pred);
//     cout << "Accuracy: " << accuracy << endl;
// }



void tc2(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    // dataset.printHead();
    // dataset.printTail();
    // int nRows, nCols;
    // dataset.getShape(nRows, nCols);
    // cout << "Shape: " << nRows << "x" << nCols << endl;
    
    // dataset.columns();

    // Dataset data2 = dataset;
    // data2.printHead();
    // data2.printTail();
    // int nRows2, nCols2;
    // data2.getShape(nRows2, nCols2);
    // cout << "Shape: " << nRows2 << "x" << nCols2 << endl;
    // data2.columns();

    Dataset data3;
    //extract data 0, 7, 1, 2
    data3 = dataset.extract(10, 30, 20, 90);
    // dataset.clear();
    data3.printHead();
    data3.printTail();
    int nRows3, nCols3;
    data3.getShape(nRows3, nCols3);
    cout << "Shape: " << nRows3 << "x" << nCols3 << endl;
}

int main() {
    tc2();
    return 0;
}