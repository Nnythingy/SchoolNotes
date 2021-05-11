// NearbyStores.c
#include <stdio.h> 
#include <string.h>
#include <math.h>

#define MAX_STORES 100

typedef struct {
	char      sname[13];
	int       x, y;
	float     radius;
} store_t;

int readStores(store_t []); 
int withinRadius(int, int, store_t);
void printNearbyStores(int, int, store_t [], int); 

int main(void){
	store_t storeList[MAX_STORES];
	int numStore, userX, userY;
	
	numStore = readStores(storeList);	
	
	printf("Enter user location: ");
	scanf("%d %d", &userX, &userY);
	
	printNearbyStores(userX, userY, storeList, numStore);	

	return 0;
}

// Read the number of stores and details of each store 
// into array storeList.
// Return the number of stores.
int readStores(store_t storeList[]) {
	int i, numStore;

	printf("Enter number of stores: ");
	scanf("%d", &numStore); 
	
	printf("Enter store information:\n");
	
	for (i=0; i<numStore; i++) 
		scanf("%s %d %d %f", storeList[i].sname, &storeList[i].x, &storeList[i].y, &storeList[i].radius); 
			
	return numStore;
}

// Returns 1 if user is within store's radius of influence, 
// or 0 otherwise.
int withinRadius(int x, int y, store_t store) {
	float distance = sqrt((store.x - x)*(store.x - x) + (store.y - y)*(store.y - y));

	return (distance < store.radius);
}

// Prints the names of stores where the user's current 
// location is within their circles of influence.
void printNearbyStores(int x, int y, store_t storeList[], int numStore) {
	int i;
	
	printf("The nearby stores are:\n");
	
	for (i=0; i<numStore; i++) 
		if (withinRadius(x, y, storeList[i]))
			printf("%s\n", storeList[i].sname);
}
