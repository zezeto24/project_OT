#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main() {
    string instance = "41";
    int nWarehouses, nCustomers, i, j;
    ifstream origin("instances/cap"+instance+".txt");
    ofstream final("cp_warehouse/cp_warehouse.dat");

    int maxWarehouse = 3, minWarehouse = 3;

    //read nWarehouses & nCustomers
    origin >> nWarehouses;
    origin >> nCustomers;

    //aux var for saving data
    float cap[nWarehouses][2] = {0};
    int demand[nCustomers] = {0};
    double tpCost[nWarehouses][nCustomers] = {0};

    //read capacity & fixed costs
    for(i=0; i<nWarehouses; i++){
        origin >> cap[i][0];
        origin >> cap[i][1];
    }

    //read demand & transportation costs
    for(j=0; j<nCustomers; j++){
        origin >> demand[j];

        for(i=0; i<nWarehouses; i++)
            origin >> tpCost[i][j];
    }

    nWarehouses = 5;    //limit problem size
    nCustomers = 10;

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

    //print capacity & fixed costs
    final << "Capacity = [";  
    for(i=0; i<nWarehouses; i++){
        final << " " << cap[i][0];
    }
    final << "];" << endl;

    final << "FixedCost = [";  
    for(i=0; i<nWarehouses; i++){
        final << " " << cap[i][1];
    }
    final << "];" << endl;

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