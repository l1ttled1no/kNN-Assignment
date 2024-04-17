#ifndef DSA232_A1_MAIN_H
#define DSA232_A1_MAIN_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cassert>

void tc_knn_score(int k, int size_X){
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");

    kNN knn = kNN(k);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, size_X, 1, -1);
    Dataset label = dataset.extract(0, size_X, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}

void tc_knn_p(int k, int size_X){
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");

    kNN knn = kNN(k);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, size_X, 1, -1);
    Dataset label = dataset.extract(0, size_X, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);

    cout << "y_pred" << endl;
    y_pred.printHead(10, 10);
    cout << endl;
    cout << "y_test" << endl;
    y_test.printHead(10, 10);
    cout << endl;
}

using namespace std;

#endif //DSA232_A1_MAIN_H