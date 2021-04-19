/*********************************************
 * OPL 20.1.0.0 Model
 * Author: Asus
 * Creation Date: 03/04/2021 at 22:33:14
 *********************************************/

 //Sets:
 {int} Warehouses = ...; // Number of potential warehouses
 {int} Customers = ...; // Number of costumers
 int MinWarehouse = ...;
 int MaxWarehouse = ...;
 
 //Parameters:
 
float Capacity[Warehouses] = ...;
float MinDelivery[Warehouses] = ...;
float FixedCost[Warehouses] = ...;
float Demand[Customers] = ...;
float TransportationCost[Warehouses][Customers] = ...;

//Decision Variables:
dvar float+ FracDemand[Warehouses][Customers];
dvar boolean OpenWarehouse[Warehouses];

minimize
  (sum(i in Warehouses) sum(j in Customers) FracDemand[i][j]*TransportationCost[i][j]) + (sum(i in Warehouses)OpenWarehouse[i]*FixedCost[i]);
  

subject to {
  
  forall (j in Customers)	
    ctDemand:
    sum(i in Warehouses) FracDemand[i][j] >= 1;
  
  forall (i in Warehouses)
    ctWarehouseCapacity:
    sum(j in Customers) Demand[j]*FracDemand[i][j] <= Capacity[i]*OpenWarehouse[i];

  forall (i in Warehouses, j in Customers)
    ctDemandFraction:
    FracDemand[i][j] <= minl(1, (Capacity[i]/Demand[j]))*OpenWarehouse[i];
    
  ctWarehouseMinLimit:
  sum(i in Warehouses) OpenWarehouse[i] >= MinWarehouse;  
  
  ctWarehouseMaxLimit:
  sum(i in Warehouses) OpenWarehouse[i] <= MaxWarehouse;  
  
  forall (i in Warehouses)
    ctWarehouseMinDelivery:
    sum(j in Customers) Demand[j]*FracDemand[i][j] >= MinDelivery[i]*OpenWarehouse[i]; 
  
}
