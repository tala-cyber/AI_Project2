#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <array>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
using namespace std;
string col1;
string col2;
string col3;
array<array<double,3>,3000> input;
array<int,4000> dout;
array<array<double,3>,1000> test;

//the plotting was done using MS Excel since plotting using c++ requires some dependencies and you
//wouldn't be able to run the code on your pc

void hard_train_neuron(std::string file, float te){

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
        dout[incr+3000]=atof(col3.c_str());
        incr++;
    }

    //random number generator

    //initialize variables
    int ite=5000;
    int ninputs=3;
    float alpha=0.001;
    float weights[3]{0.5,-0.5,-0.5};
    float net; float sign;float error;float TE;

    //learn
    for(int i=0; i<ite;i++){
        TE=0;
        for(int j=0; j<3000; j++){
            net=0;sign=0;
            for(int k=0; k<3; k++){
                net=net + weights[k]*input[j][k];
            }
            if(net>=0){sign=1;}else{sign=0;}
            error=dout[j]-sign;
            for(int k=0;k<3;k++){
                weights[k]=weights[k]+alpha*input[j][k]*error;
            }
            TE+=error*error;
        }
        if(TE<te){
            break;
        }
    }
    cout<<"final TE: "<<TE<<"    ";

    //test
    int true_pos=0; int true_neg=0;int false_pos=0; int false_neg=0;
    for(int i=0; i<1000;i++){
        net=0;
        for(int k=0; k<3;k++){
            net+=weights[k]*test[i][k];
        }
        if(net>=0){
            if(dout[i+3000]==1){
                true_pos++;
            }else{
                false_pos++;
            }    
        }else if(net<0){
            if(dout[i+3000]==0){
                true_neg++;
            }else{
                false_neg++;
            }    
        }
    }
    cout<<"correct: "<<true_pos+true_neg<<"    ";
    cout<<"TP: "<<true_pos<<"    ";
    cout<<"TN: "<<true_neg<<"    ";
    cout<<"FP: "<<false_pos<<"   ";
    cout<<"FN: "<<false_neg<<"    ";
    cout<<"wrong: "<<false_pos+false_neg<<"\n";
   
}

void soft_train_neuron(std::string file, float te){
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
        dout[incr+3000]=atof(col3.c_str());
        incr++;
    }

    //initialize variables
    int ite=5000;
    int ninputs=3;
    float alpha=0.1;
    //float r1= rand()%11-5;int r2= rand()%11-5;int r3= rand()%11-5;
    float weights[3]{0.5,0.2,-0.5};
    float net; float fbip; float k=0.1; float error=0; float TE=0; 
    //learn
    for(int i=0; i<ite;i++){
        TE=0;
        for(int j=0; j<3000; j++){
            net=0;
            for(int k=0; k<3; k++){
                net=net + weights[k]*input[j][k];
            }
            fbip=1/(1+exp(-k*net));
            error=dout[j]-fbip;
            for(int k=0;k<3;k++){
                weights[k]=weights[k]+alpha*input[j][k]*error;
            }
            TE+=error*error;
        }
        if(TE<te){
            break;
        }
    }
    cout<<"weights: ";
    for(int i=0; i<3; i++){
        cout<<weights[i]<<" ";
    }
    cout<<" final TE: "<<TE<<"    ";

    //test
    int true_pos=0; int true_neg=0;int false_pos=0; int false_neg=0;
    for(int i=0; i<1000;i++){
        net=0;
        for(int k=0; k<3;k++){
            net+=weights[k]*test[i][k];
        }
        net=1/(1+exp(-k*net));
        if(net>0.5){
            if(dout[i+3000]==1){
                true_pos++;
            }else{
                false_pos++;
            }    
        }else if(net<=0.5){
            if(dout[i+3000]==0){
                true_neg++;
            }else{
                false_neg++;
            }    
        }
    }
    cout<<"correct: "<<true_pos+true_neg<<"     ";
    cout<<"TP: "<<true_pos<<"    ";
    cout<<"TN: "<<true_neg<<"    ";
    cout<<"FP: "<<false_pos<<"   ";
    cout<<"FN: "<<false_neg<<"   ";
    cout<<"wrong: "<<false_pos+false_neg<<"\n";
}

int main(){
    //Hard Activation Part 1
    //groupA
    /*
    cout<<"Hard: "<<"\n";
    cout<<"group A"<<"\n";
    hard_train_neuron("Adata.csv",0.00001);
    //groupB
    cout<<"group B"<<"\n";
    hard_train_neuron("Bdata.csv",70);
    //groupC
    cout<<"group C"<<"\n";
    hard_train_neuron("Cdata.csv",400);
    */
    //Soft Activation Part 1
    //groupA
    cout<<"Soft: "<<"\n";
    cout<<"group A"<<"\n";
    soft_train_neuron("Adata.csv",0.00001);
    //groupB
    cout<<"group B"<<"\n";
    soft_train_neuron("Bdata.csv",40);
    //groupC
    cout<<"group C"<<"\n";
    soft_train_neuron("Cdata.csv",700);

}