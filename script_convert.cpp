#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
using namespace std;

int main() {
    srand(time(nullptr));

    string instance = "41";
    int nWarehouses, nCustomers, i, j, randNum;

    ifstream origin("instances/cap"+instance+".txt");
    ofstream final("Warehouse_Location_Problem/Warehouse_Location_Problem.dat");

    int maxWarehouse = 10, minWarehouse = 1;
    int maxPercent = 30, minPercent = 20;

    //read nWarehouses & nCustomers
    origin >> nWarehouses;
    origin >> nCustomers;

    //aux var for saving data
    float cap[nWarehouses][2] = {0};
    int demand[nCustomers] = {0};
    double tpCost[nWarehouses][nCustomers] = {0};

    //print list of warehouses
    final << "Warehouses = {";
    for(i=1; i<=nWarehouses; i++){
        final << " " << i;
    }
    final << "};" << endl; 

    final << "Customers = {";
    for(i=1; i<=nCustomers; i++){
        final << " " << i;
    }
    final << "};" << endl;    

    //print warehouse limitations
    final << "MaxWarehouse = " << maxWarehouse << ";" << endl;
    final << "MinWarehouse = " << minWarehouse << ";" << endl;

    //read capacity & fixed costs
    for(i=0; i<nWarehouses; i++){
        origin >> cap[i][0];
        origin >> cap[i][1];
    }

    //print capacity, minimum delivery & fixed costs
    final << "Capacity = [";  
    for(i=0; i<nWarehouses; i++){
        final << " " << cap[i][0];
    }
    final << "];" << endl;

    final << "MinDelivery = [";  
        for(i=0; i<nWarehouses; i++){
            final << " " << ((double)((rand()%(maxPercent-minPercent+1)) + minPercent))/100*cap[i][0];
        }
    final << "];" << endl;

    final << "FixedCost = [";  
    for(i=0; i<nWarehouses; i++){
        final << " " << cap[i][1];
    }
    final << "];" << endl;

    //read demand & transportation costs
    for(j=0; j<nCustomers; j++){
        origin >> demand[j];

        for(i=0; i<nWarehouses; i++)
            origin >> tpCost[i][j];
    }

    //print demand & transportation costs
    final << "Demand = [";  
    for(j=0; j<nCustomers; j++){
        final << " " << demand[j];
    }
    final << "];" << endl;

    final << "TransportationCost = [" << endl;  
    for(i=0; i<nWarehouses; i++){
        final << "\t[";
        for(j=0; j<nCustomers; j++)
            final << " " << fixed << setprecision(5) << tpCost[i][j];

        if (i != (nWarehouses-1))
            final << "]," << endl;
        else   
            final << "] ";
    }
    final << "];";

    final.close(); 
    origin.close();
}