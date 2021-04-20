/*********************************************
 * OPL 20.1.0.0 Model
 * Author: Asus
 * Creation Date: 03/04/2021 at 22:33:14
 *********************************************/

 //Sets:
 {int} Warehouses = ...; // Number of potential warehouses
 {int} Customers = ...; // Number of costumers
 {int} Products = ...; // Product types
 int MinWarehouse = ...;
 int MaxWarehouse = ...;
 
 //Parameters:
 
float Capacity[Warehouses][Products] = ...;
float MinDelivery[Warehouses] = ...;
float FixedCost[Warehouses] = ...;
float Demand[Customers][Products] = ...;
float TransportationCost[Warehouses][Customers] = ...;
float ProductCost[Warehouses][Products] = ...;

//Decision Variables:
dvar float+ FracDemand[Warehouses][Customers][Products];
dvar boolean OpenWarehouse[Warehouses];

minimize
  (sum(i in Warehouses) sum(j in Customers) sum(k in Products) FracDemand[i][j][k]*(TransportationCost[i][j]+ProductCost[i][k])) + (sum(i in Warehouses)OpenWarehouse[i]*FixedCost[i]);
  

subject to {
  
  forall (j in Customers, k in Products)	
    ctDemand:
    sum(i in Warehouses) FracDemand[i][j][k] >= 1;
  
  forall (i in Warehouses, k in Products)
    ctWarehouseCapacity:
    sum(j in Customers) Demand[j][k]*FracDemand[i][j][k] <= Capacity[i][k]*OpenWarehouse[i];

  forall (i in Warehouses, j in Customers, k in Products)
    ctDemandFraction:
    FracDemand[i][j][k] <= minl(1, (Capacity[i][k]/Demand[j][k]))*OpenWarehouse[i];
    
  ctWarehouseMinLimit:
  sum(i in Warehouses) OpenWarehouse[i] >= MinWarehouse;  
  
  ctWarehouseMaxLimit:
  sum(i in Warehouses) OpenWarehouse[i] <= MaxWarehouse;  
  
  forall (i in Warehouses)
    ctWarehouseMinDelivery:
    sum(j in Customers) (sum(k in Products) Demand[j][k]*FracDemand[i][j][k]) >= MinDelivery[i]*OpenWarehouse[i]; 
  
}
