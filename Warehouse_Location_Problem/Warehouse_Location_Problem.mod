/*********************************************
 * OPL 20.1.0.0 Model
 * Author: Asus
 * Creation Date: 03/04/2021 at 22:33:14
 *********************************************/

 //Sets:
 {int} Warehouses = ...; 	// Number of potential warehouses
 {int} Customers = ...; 	// Number of costumers
 {int} Products = ...; 		// Product types
 {int} Dummies = ...;		// Number of potential dummy warehouses
 int MinWarehouse = ...;
 int MaxWarehouse = ...;
 
 //Parameters:
 
float Capacity[Warehouses][Products] = ...;
float DummyCapacity[Dummies][Products] = ...;
float MinDelivery[Warehouses] = ...;
float FixedCost[Warehouses] = ...;
float Demand[Customers][Products] = ...;
float TransportationCost[Products][Warehouses][Customers] = ...;
float DummyCost[Products][Warehouses][Dummies] = ...;
int DummyCoverage[Dummies][Warehouses] = ...;

//Decision Variables:
dvar float+ FracDemand[Dummies][Products][Warehouses][Customers];
dvar boolean OpenWarehouse[Warehouses];

minimize
  (sum(i in Warehouses) sum(j in Customers) sum(k in Products) sum(z in Dummies) FracDemand[z][k][i][j]*(TransportationCost[k][i][j]+DummyCost[k][i][z])) + (sum(i in Warehouses) OpenWarehouse[i]*FixedCost[i]);
  

subject to {
  
  forall (j in Customers, k in Products)	
    ctDemand:
    sum(i in Warehouses) FracDemand[k][i][j] >= 1;
  
  forall (i in Warehouses, k in Products)
    ctWarehouseCapacity:
    sum(j in Customers) Demand[j][k]*FracDemand[k][i][j] <= Capacity[i][k]*OpenWarehouse[i];

  forall (i in Warehouses, j in Customers, k in Products)
    ctDemandFraction:
    FracDemand[k][i][j] <= minl(1, (Capacity[i][k]/Demand[j][k]))*OpenWarehouse[i];
    
  ctWarehouseMinLimit:
  sum(i in Warehouses) OpenWarehouse[i] >= MinWarehouse;  
  
  ctWarehouseMaxLimit:
  sum(i in Warehouses) OpenWarehouse[i] <= MaxWarehouse;  
  
  forall (i in Warehouses)
    ctWarehouseMinDelivery:
    sum(j in Customers) (sum(k in Products) Demand[j][k]*FracDemand[k][i][j]) >= MinDelivery[i]*OpenWarehouse[i]; 
  
}
