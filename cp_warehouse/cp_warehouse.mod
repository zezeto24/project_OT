/*********************************************
 * OPL 20.1.0.0 Model
 * Creation Date: 28/05/2021 at 11:03:06
 *********************************************/
 using CP;
 
execute{
   cp.param.TimeLimit = 36000;	//seconds
}
 
//Sets:
{int} Warehouses = ...; 	// Number of potential warehouses
{int} Customers = ...; 		// Number of costumers
{int} Products = ...; 		// Product types
{int} Dummies = ...;		// Number of potential dummy warehouses
int MinWarehouse = ...;
int MaxWarehouse = ...;
 
//Parameters:
float Capacity[Warehouses][Products] = ...;
//int Capacity[Warehouses] = ...;
int DummyCapacity[Dummies][Products] = ...;
float MinDelivery[Warehouses] = ...;
int FixedCost[Warehouses] = ...;
int Demand[Customers][Products] = ...;
//int Demand[Customers] = ...;
float TransportationCost[Products][Warehouses][Customers] = ...;
//float TransportationCost[Warehouses][Customers] = ...;
float DummyCost[Products][Warehouses][Dummies] = ...;
int DummyCoverage[Dummies][Warehouses] = ...;

//Decision Variables:
dvar int+ SuppDemand[z in Dummies][k in Products][i in Warehouses][j in Customers] in 0..DummyCapacity[z][k]*DummyCoverage[z][i];
//dvar int+ SuppDemand[i in Warehouses][j in Customers] in 0..Capacity[i];
dvar boolean OpenWarehouse[Warehouses];

//Objective Function:
dexpr float totalCost = sum(i in Warehouses) sum(k in Products) ( sum(j in Customers)(TransportationCost[k][i][j] * sum(z in Dummies)SuppDemand[z][k][i][j]/Demand[j][k]) + sum(z in Dummies)(DummyCost[k][i][z] * sum(j in Customers) SuppDemand[z][k][i][j]/Demand[j][k]))  + (sum(i in Warehouses) OpenWarehouse[i]*FixedCost[i]);
//dexpr float totalCost = (sum(i in Warehouses) sum(j in Customers) SuppDemand[i][j]/Demand[j]*TransportationCost[i][j]) + (sum(i in Warehouses)OpenWarehouse[i]*FixedCost[i]);
minimize totalCost;

subject to
{
  
	forall (j in Customers, k in Products)	
    	ctDemand:
    	sum(i in Warehouses) sum(z in Dummies) SuppDemand[z][k][i][j] >= Demand[j][k];
    	
    forall (i in Warehouses, k in Products)
    	ctWarehouseCapacity:
    	sum(j in Customers) (sum(z in Dummies) SuppDemand[z][k][i][j]) <= Capacity[i][k]*OpenWarehouse[i];
    	
    forall (i in Warehouses)
    	ctWarehouseMinDelivery:
    	sum(j in Customers) (sum(k in Products) (sum(z in Dummies) SuppDemand[z][k][i][j])) >= MinDelivery[i]*OpenWarehouse[i]; 
    
    ctWarehouseMinLimit:
  	sum(i in Warehouses) OpenWarehouse[i] >= MinWarehouse;  
  
  	ctWarehouseMaxLimit:
  	sum(i in Warehouses) OpenWarehouse[i] <= MaxWarehouse;  
  
  /*	
  	forall (j in Customers)	
    	ctDemand:
    	sum(i in Warehouses) SuppDemand[i][j] >= Demand[j];
  
  	forall (i in Warehouses)
    	ctWarehouseCapacity:
    	sum(j in Customers) SuppDemand[i][j] <= Capacity[i]*OpenWarehouse[i];

  	forall (i in Warehouses, j in Customers)
    	ctDemandFraction:
    	SuppDemand[i][j] <= minl(Demand[j], Capacity[i])*OpenWarehouse[i];
    	
    ctWarehouseMinLimit:
  	sum(i in Warehouses) OpenWarehouse[i] >= MinWarehouse;  
  
  	ctWarehouseMaxLimit:
  	sum(i in Warehouses) OpenWarehouse[i] <= MaxWarehouse; 
  	
  	forall (i in Warehouses)
    	ctWarehouseMinDelivery:
    	sum(j in Customers) SuppDemand[i][j] >= MinDelivery[i]*OpenWarehouse[i];  
   */
}