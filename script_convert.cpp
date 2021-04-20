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

    int maxWarehouse = 15, minWarehouse = 1;
    int maxPercentMinDelivery = 30, minPercentMinDelivery = 20;
    int maxPercentPdCost = 15, minPercentPdCost = 5;
    int nProducts = 1;

    //read nWarehouses & nCustomers
    origin >> nWarehouses;
    origin >> nCustomers;

    //aux var for saving data
    float cap[nWarehouses][2] = {0};
    int demand[nCustomers] = {0};
    double tpCost[nWarehouses][nCustomers] = {0};
    double pdCost[nWarehouses] = {0};

    //print list of warehouses, costumers and products
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

    final << "Products = {";
    for(i=1; i<=nProducts; i++){
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
    final << "Capacity = [" << endl;  
    for(i=0; i<nWarehouses; i++){
        final << "\t[";
        for(j=0; j<nProducts; j++){
            if (j != 0)
                final << " " << ((double)((rand()%(12-8+1)) + 8))/10 * cap[i][0];
            else
                final << " " << cap[i][0];
        }

        if (i != (nWarehouses-1))
            final << "]," << endl;
        else   
            final << "] ";
    }

    final << "];" << endl;

    final << "MinDelivery = [";  
        for(i=0; i<nWarehouses; i++){
            final << " " << ((double)((rand()%(maxPercentMinDelivery-minPercentMinDelivery+1)) + minPercentMinDelivery))/100*cap[i][0];
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

    //print demand, transportation costs & product costs
    final << "Demand = [";  
    for(i=0; i<nCustomers; i++){
        final << "\t[";
        for(j=0; j<nProducts; j++){
            if (j != 0)
                final << " " << ((double)((rand()%(12-8+1)) + 8))/10 * demand[i];
            else
                final << " " << demand[i];
        }

        if (i != (nCustomers-1))
            final << "]," << endl;
        else   
            final << "] ";
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
    final << "];" << endl;

    //get average transportation cost for each warehouse
    for(i=0; i<nWarehouses; i++){
        for(j=0; j<nCustomers; j++)
            pdCost[i] += tpCost[i][j]/nCustomers;
    }

    final << "ProductCost = [" << endl;  
    for(i=0; i<nWarehouses; i++){
        final << "\t[";
        for(j=0; j<nProducts; j++)
            final << " " << fixed << setprecision(5) << ((double)((rand()%(maxPercentPdCost-minPercentPdCost+1)) + minPercentPdCost))/100*pdCost[i];

        if (i != (nWarehouses-1))
            final << "]," << endl;
        else   
            final << "] ";
    }
    final << "];";

    final.close(); 
    origin.close();
}