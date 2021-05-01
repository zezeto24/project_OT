#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
using namespace std;

int main() {
    srand(time(nullptr));

    string instance = "41";
    int nWarehouses, nCustomers, i, j, k, randNum;

    ifstream origin("instances/cap"+instance+".txt");
    ofstream final("Warehouse_Location_Problem/Warehouse_Location_Problem.dat");

    int maxWarehouse = 15, minWarehouse = 1;                                //
    int maxPercentMinDelivery = 30, minPercentMinDelivery = 20;             //
    int offsetPdCost = 20, maxPdCost = 40;                                  //
    int nProducts = 2;                                                      //

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
    for (k=0; k<nProducts; k++) {
        for(i=0; i<nWarehouses; i++){
            if (i == 0)
                final << "\t[[";
            else
                final << "\t [";

            if (k == 0) {    //print original transportation costs
                for(j=0; j<nCustomers; j++)
                    final << " " << fixed << setprecision(5) << tpCost[i][j];
            }   
            else {          //print newly generated transportation costs for new products
                for(j=0; j<nCustomers; j++)
                   final << " " << fixed << setprecision(5) << tpCost[i][j]+((double)(offsetPdCost-(rand()%(maxPdCost+1)))/100)*tpCost[i][j];
            }          

            if (i != (nWarehouses-1))
                final << "]," << endl;
            else if (k != (nProducts-1))   
                final << "]], " << endl << endl;
            else
                final << "]] ";
        }
    }
    final << "];" << endl;

    final.close(); 
    origin.close();
}