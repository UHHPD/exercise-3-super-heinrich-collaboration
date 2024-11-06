#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu, int k) {
    double pow(double x, double k);
    double exp(double x);
    double tgamma(double x);
    double poisson_out = 1/tgamma(k+1) * pow(mu, k) * exp(-mu);
    return poisson_out;
}

int main() {
    using namespace std;


    ifstream fin("datensumme.txt");
    ofstream outputfile("hist.txt");
    ofstream histout("histpoi.txt");
    int n_i;
    vector<int> zaehler(11);
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        zaehler[n_i] += 1;
    }
    for (unsigned int k = 0; k < zaehler.size(); ++k) {
        cout << k << ":" << zaehler [k] << endl;
        outputfile << k << " " << zaehler[k] << endl;
        histout << k << " " << zaehler[k] << " " << 234 * poisson(3.11538, k) << endl;
    }
    fin.close();
    outputfile.close();
    histout.close();
}