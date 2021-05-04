#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <numeric>
using namespace std;

int main() {
    srand(time(nullptr));

    string instance = "41";
    int nWarehouses, nCustomers, i, j, k, randNum;
    int sum = 0;

    ifstream origin("instances/cap"+instance+".txt");
    ofstream final("Warehouse_Location_Problem/Warehouse_Location_Problem.dat");

    int maxWarehouse = 13, minWarehouse = 1;                                //
    int maxPercentMinDelivery = 10, minPercentMinDelivery = 5;              //
    int offsetPdCost = 20, maxPdCost = 40;                                  //
    int nProducts = 5;                                                      //
    int nDummies = 10;                                                      //

    //read nWarehouses & nCustomers
    origin >> nWarehouses;
    origin >> nCustomers;

    //aux var for saving data
    float cap[nWarehouses][2] = {0};
    int demand[nCustomers] = {0};
    double tpCost[nWarehouses][nCustomers] = {0};
    double pdCost[nWarehouses] = {0};
    int usedResellers = 0;
    int dummies[nDummies] = {0};

    //print list of warehouses, costumers, products, and dummy warehouses
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

    final << "Dummies = {";
    for(i=1; i<=nDummies; i++){
        final << " " << i;
    }
    final << "};" << endl;         

    //allocate resellers
    int nDummyResellers = round(0.3*nDummies);

    for(i=0; i<nDummies; i++){
        if ((usedResellers < nDummyResellers) && (rand()%2)){
            usedResellers++;
            dummies[i] = 1;
        }
        if ((nDummies-i) == (nDummyResellers-usedResellers)){
            for(j=i; j<nDummies; j++){
                dummies[j] = 1;
            }
            break;
        }
    }

    //create coverage matrix for dummies
    final << "DummyCoverage = [" << endl;  
    for(i=0; i<nDummies; i++){
        final << "\t[";
        for(j=0; j<nWarehouses; j++)
            final << " " << (rand()%2); 

        if (i != (nDummies-1))
            final << "]," << endl;
        else   
            final << "] ";
    }
    final << "];" << endl;

    //print warehouse limitations
    final << "MaxWarehouse = " << maxWarehouse << ";" << endl;
    final << "MinWarehouse = " << minWarehouse << ";" << endl;

    //read capacity & fixed costs
    for(i=0; i<nWarehouses; i++){
        origin >> cap[i][0];
        origin >> cap[i][1];
    }

    //print capacity, dummy capacity, minimum delivery & fixed costs
    final << "Capacity = [" << endl;  
    for(i=0; i<nWarehouses; i++){
        final << "\t[";
        for(j=0; j<nProducts; j++){
            if (j != 0)
                final << " " << ((double)((rand()%(12-8+1)) + 8))/10 * cap[i][0];   //generate values between 0.8 and 1.2 the original value
            else
                final << " " << cap[i][0];
        }

        if (i != (nWarehouses-1))
            final << "]," << endl;
        else   
            final << "] ";
    }
    final << "];" << endl;

    //calculate average capacity per number of dummies (We need the Max number of warehouse and not he number of warehouses)
    for(k=0; k<maxWarehouse; k++){
            sum += cap[k][0];
    }
    sum = sum/nDummies;

    final << "DummyCapacity = [" << endl;  
    for(i=0; i<nDummies; i++){
        final << "\t[";

        for(j=0; j<nProducts; j++){
            if (dummies[i])
                final << " " << 0.4*sum;
            else
                final << " " << 2*sum;
        }

        if (i != (nDummies-1))
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

    //finish computing costs
    final << "DummyCost = [" << endl;  
    for (k=0; k<nProducts; k++) {
        for(i=0; i<nWarehouses; i++){
            if (i == 0)
                final << "\t[[";
            else
                final << "\t [";

            for(j=0; j<nDummies; j++) {
                if (dummies[j])
                    //generate values of 0.2 or -0.2 times the original value, depending on dummy type
                    final << " " << fixed << setprecision(5) << 0.1*tpCost[i][j];            
                else
                    final << " " << fixed << setprecision(5) << 0.3*tpCost[i][j];                          
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