#include <iostream>
#include <fstream>
#include <vector>


double poisson(double mu, int k) {
    double pow(double base, double exponent);
    double exp(double exponent);
    double tgamma(double x);
    double poisson_out = 1/tgamma(k+1) * pow(mu, k) * exp(-mu);
    return poisson_out;
}

double probability(std::vector<int> data, double mu) {
    double prob = 1;
    for(int entry: data){
        prob = prob * poisson(mu, entry);
    }
    return prob;
}

double probability2(std::vector<int> data) {
    double prob = 1;
    for(int entry: data){
        prob = prob * poisson(entry, entry);
    }
    return prob;
}

double variance(std::vector<int> data, double mu) {
    double entry_variance = 0;
    for(int entry: data) {
        entry_variance += pow((entry-mu), 2);
    }
    return entry_variance/data.size();
}

int main() {
    using namespace std;


    // Exercise a)
    ifstream filein("datensumme.txt");
    double zahl;
    vector<int> daten;
    while(filein >> zahl) {
        daten.push_back(zahl);
    }
    
    /*
    filein.close();
    for(int entry: daten) {
        cout << entry << endl;
    }
    cout << daten.size() << endl;
    */
    cout << probability(daten, 3.11538) << endl;


    //Exercise b)
    ofstream fileout("likelihood.txt");
    for(int mean = 0 ; mean < 60 ; ++mean) {
        fileout << mean * 0.1 << " " << probability(daten, mean * 0.1) << endl;
    }
    fileout.close();


    //Exercise c)
    ofstream fileout2("nll.txt");
    for(int mean = 0 ; mean < 60 ; ++mean) {
    fileout2 << mean * 0.1 << " " << -2 * log(probability(daten, mean * 0.1)) << endl;
    }
    fileout2.close();


    //Exercise d)
    ofstream fileout3("deltanll.txt");
    for(int mean = 0 ; mean < 60 ; ++mean) {
    fileout3 << mean * 0.1 << " " << -2 * log(probability(daten, mean * 0.1)) + 2 * log(probability(daten, 3.11538)) << endl;
    }
    fileout3.close();

    // From deltanll.txt mu = 3.1 is the best estimator

    for(int mean = 0 ; mean < 60 ; ++mean) {
        if (-2 * log(probability(daten, mean * 0.1)/probability(daten, 3.1)) < 1.0) {
            cout << mean*0.1 << endl;
        }
    }

    //probably wrong
    cout << variance(daten, 3.1)/sqrt(daten.size()) << endl;
    cout << variance(daten, 3.2)/sqrt(daten.size()) << endl;

    //Exercise e)
    double ratio = probability(daten, 3.11538)/probability2(daten);
    double likelihood_ratio = -2*log(ratio);
    cout << likelihood_ratio << endl;

    double ndof = 233;
    double std_ndof = sqrt(2*ndof);
    double z = (likelihood_ratio-ndof)/std_ndof;
    cout << z << endl;

}