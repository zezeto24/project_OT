/*********************************************
 * OPL 20.1.0.0 Model
 * Creation Date: 28/05/2021 at 11:03:06
 *********************************************/
 using CP;
 
//Sets:
{int} Warehouses = ...; 	// Number of potential warehouses
{int} Customers = ...; 		// Number of costumers
{int} Products = ...; 		// Product types
{int} Dummies = ...;		// Number of potential dummy warehouses
int MinWarehouse = ...;
int MaxWarehouse = ...;
 
//Parameters:
int Capacity[Warehouses][Products] = ...;
float DummyCapacity[Dummies][Products] = ...;
float MinDelivery[Warehouses] = ...;
float FixedCost[Warehouses] = ...;
float Demand[Customers][Products] = ...;
float TransportationCost[Products][Warehouses][Customers] = ...;
float DummyCost[Products][Warehouses][Dummies] = ...;
int DummyCoverage[Dummies][Warehouses] = ...;

//Decision Variables:
dvar int+ SuppDemand[z in Dummies][k in Products][i in Warehouses][j in Customers] in 0..Capacity[i][k]*DummyCoverage[z][i];
dvar boolean OpenWarehouse[Warehouses];

//Objective Function:
dexpr float totalCost = sum(i in Warehouses) sum(k in Products) ( sum(j in Customers)(TransportationCost[k][i][j] * sum(z in Dummies)SuppDemand[z][k][i][j]) + sum(z in Dummies)(DummyCost[k][i][z] * sum(j in Customers) SuppDemand[z][k][i][j]))  + (sum(i in Warehouses) OpenWarehouse[i]*FixedCost[i]);
minimize totalCost;

subject to
{
	forall (j in Customers, k in Products)	
    	ctDemand:
    	sum(i in Warehouses) sum(z in Dummies) SuppDemand[z][k][i][j] >= Demand[j][k];
    	    
}