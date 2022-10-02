#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <array>
#include <stdlib.h>
#include <math.h>
using namespace std;
string col1;
string col2;
string col3;
array<array<double,3>,3000> input;
array<int,4000> dout;
array<array<double,3>,1000> test;

void hard_train_neuron(std::string file){

    // extract and store data
    std::ifstream group (file);
    int incr=0;
    while (incr<3000) {
        getline(group,col1, ',' );
        getline (group,col2, ',' );
        group >> col3; 
        input[incr][0]=atof(col1.c_str());
        input[incr][1]=atof(col2.c_str());
        input[incr][2]=1;
        dout[incr]=atof(col3.c_str());
        incr++;
    }

    incr=0;
    while(!group.eof()){
        getline(group,col1, ',' );
        getline (group,col2, ',' );
        group >> col3; 
        test[incr][0]=atof(col1.c_str());
        test[incr][1]=atof(col2.c_str());
        test[incr][2]=1;
        dout[incr]=atof(col3.c_str());
        incr++;
    }

    //initialize variables
    int ite=5000;
    int ninputs=3;
    float alpha=0.0001;
    float weights[3]{1,1,1};
    float net; int sign;

    //learn
    for(int i=0; i<ite;i++){
        for(int j=0; j<3000; j++){
            net=0;sign=0;
            for(int k=0; k<3; k++){
                net=net + weights[k]*input[j][k];
            }
            if(net>=0){sign=1;}else{sign=-1;}
            for(int k=0;k<3;k++){
                weights[k]=weights[k]+alpha*input[j][k]*(dout[j]-sign);
            }
        }
    }

    //test
    int correct=0;
    int wrong=0;
    for(int i=0; i<1000;i++){
        net=0;
        for(int k=0; k<3;k++){
            net+=weights[k]*test[i][k];
        }
        if(net>=0 and dout[i+3000]==1){
            correct++;
        }else if(net<0 and dout[i+3000]==0){
            correct++;
        }else{
            wrong++;
        }

    }
    cout<<"correct: "<<correct<<"\n";
    cout<<"wrong: "<<wrong<<"\n";
   
}

void soft_train_neuron(std::string file){
    // extract and store data
    std::ifstream group (file);
    int incr=0;
    while (incr<3000) {
        getline(group,col1, ',' );
        getline (group,col2, ',' );
        group >> col3; 
        input[incr][0]=atof(col1.c_str());
        input[incr][1]=atof(col2.c_str());
        input[incr][2]=1;
        dout[incr]=atof(col3.c_str());
        incr++;
    }

    incr=0;
    while(!group.eof()){
        getline(group,col1, ',' );
        getline (group,col2, ',' );
        group >> col3; 
        test[incr][0]=atof(col1.c_str());
        test[incr][1]=atof(col2.c_str());
        test[incr][2]=1;
        dout[incr]=atof(col3.c_str());
        incr++;
    }

    //initialize variables
    int ite=5000;
    int ninputs=3;
    float alpha=0.0001;
    float weights[3]{1,1,1};
    float net; float fbip; int k=0;

    //learn
    for(int i=0; i<ite;i++){
        for(int j=0; j<3000; j++){
            net=0;
            for(int k=0; k<3; k++){
                net=net + weights[k]*input[j][k];
            }
            fbip=1/(1+exp(-2*k*net))-1;
            for(int k=0;k<3;k++){
                weights[k]=weights[k]+alpha*input[j][k]*(fbip);
            }
        }
    }

    //test
    int correct=0;
    int wrong=0;
    for(int i=0; i<1000;i++){
        net=0;
        for(int k=0; k<3;k++){
            net+=weights[k]*test[i][k];
        }
        if(net>=0 and dout[i+3000]==1){
            correct++;
        }else if(net<0 and dout[i+3000]==0){
            correct++;
        }else{
            wrong++;
        }

    }
    cout<<"correct: "<<correct<<"\n";
    cout<<"wrong: "<<wrong;
}

int main(){
    hard_train_neuron("data.csv");
    soft_train_neuron("data.csv");
}