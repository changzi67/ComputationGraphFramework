#include "Meow.h"
#include "Newton.h"
#include <fstream>
#include <bits/stdc++.h>

int main () {

    // x为输入层包含 28*28 , y为期待输出分别代表0~9 (即若图像是5, y为[0,0,0,0,0,1,0,0,0,0])
    auto x = Placeholder(500, 784, "x");
    auto y = Placeholder(500, 10, "y");

    // weights init
    auto w1 = Variable(784, 10);
    auto w2 = Variable(30, 10);

    auto init_w1 = Tensor(784, 10, rand);
    auto init_w2 = Tensor(30, 10, rand);
    w1.Set(init_w1);
    w2.Set(init_w2);

    // bias init
    auto b1 = Variable(1, 10);
    //auto b2 = Variable(1, 10);

    auto init_b1 = Tensor(1, 10, rand);
    //auto init_b2 = Tensor(1, 10, rand);
    b1.Set(init_b1);
    //b2.Set(init_b2);

    // layers
    auto layer1 = Sigmoid(x * w1 + b1);
    auto layer2 = Sigmoid(layer1 * w2 );

    // loss calculation
    //auto lamda = Constant(0.1);
    //auto w1_sq = Quadratic(w1);
    //auto w2_sq = Quadratic(w2);
    //auto regu = lamda * (w1_sq + w2_sq);
    auto loss = Quadratic(layer1 - y);
    //auto loss = loss1 + regu;

    // 梯度下降
    auto gra = loss.Grad();
    auto Cast = Tensor(0.001);

    std::ifstream fin_x("train-images.idx3-ubyte", std::ios::binary);
    std::ifstream fin_y("train-labels.idx1-ubyte", std::ios::binary);

    fin_x.seekg(16, std::ios::beg);
    fin_y.seekg(8, std::ios::beg);
    unsigned char *x_data = new unsigned char[784];
    char y_data;

    double **x1 = new double *[500];
    double **y1 = new double *[500];
    for (int i = 0; i < 500; i++) {
        x1[i] = new double[784];
        y1[i] = new double[10];
    }

    for (int i = 0; i < 500; i++) {
        fin_x.read((char *) x_data, 784);
        fin_y.read(&y_data, 1);

        for (int j = 0; j < 10; j++) {
            y1[i][j] = 0;
        }
        y1[i][y_data] = 1;

        for (int j = 0; j < 784; j++) {
            x1[i][j] = (double) x_data[j] / 256;
        }
    }

    Tensor t1(500, 784, x1);
    Tensor t2(500, 10, y1);

    //cout << w1.Eval({{"x", t1}, {"y", t2}}).Print();
    //cout << gra[w1].Eval({{"x", t1}, {"y", t2}}).Print();
    for (int j = 0; j < 1300; j++) {

        w1 -= Cast * gra[w1].Eval({{"x", t1}, {"y", t2}});
        //w2 -= Cast * gra[w2].Eval({{"x", t1}, {"y", t2}});
        b1 -= Cast * gra[b1].Eval({{"x", t1}, {"y", t2}});
        //b2 -= Cast * gra[b2].Eval({{"x", t1}, {"y", t2}});
        if (j % 50 == 0) {
            double tmp = loss.Eval({{"x", t1},
                                    {"y", t2}}).Value();
            //cout << w1.Eval({{"x", t1}, {"y", t2}}).Print();
            //cout << gra[w1].Eval({{"x", t1}, {"y", t2}}).Print();
            cout << "loss after " << j << " steps : " << tmp << endl;
            root.Save("hhhh");
        }
    }

        //root.Restore("hhhh");
    //std::cout << x.Eval({{"x", t1}, {"y", t2}}).Print() << endl;
    for (int i = 0; i < 500; i++) {
        fin_x.read((char *) x_data, 784);
        fin_y.read(&y_data, 1);

        for (int j = 0; j < 10; j++) {
            y1[i][j] = 0;
        }
        y1[i][y_data] = 1;

        for (int j = 0; j < 784; j++) {
            x1[i][j] = (double) x_data[j] / 256;
        }
    }

    Tensor t1_test(500, 784, x1);
    Tensor t2_test(500, 10, y1);

    int right = 0;
    for (int i = 0; i < 500; i ++) {
        double ** a = layer1.Eval({{"x", t1_test}, {"y", t2_test}}).Matrix();
        double tmp = 0;
        int max = -1, max1 = -1;
        for (int j = 0; j < 10; j++) {
            if (y1[i][j] == 1) max1 = j;
            if (a[i][j] > tmp) {
                tmp = a[i][j];
                max = j;
            }
        }
        if (max == max1) right++;
    }
    cout << "The correct number is " << right << endl;

    // test
    /*fin_x.seekg(16, std::ios::beg);
    fin_y.seekg(8, std::ios::beg);
    fin_x.read((char*)x_data, 784);
    fin_y.read(&y_data, 1);

    for (int i = 0; i < 10; i++) {
        y1[0][i] = 0;
    }
    y1[0][y_data] = 1;

    for (int i = 0; i < 784; i++) {
        x1[0][i] = x_data[i] / 256;
    }

    Tensor t1_test(1, 784, x1);
    Tensor t2_test(1, 10, y1);

    std::cout << loss.Eval({{"x", t1_test}, {"y", t2_test}}).Print() << endl;
    std::cout << layer2.Eval({{"x", t1_test}, {"y", t2_test}}).Print() << endl;*/

    fin_x.close();
    fin_y.close();
    return 0;
}