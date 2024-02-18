/* Sample program to read a comma separated file into a structure and sort with host_name and price and then
   display the array of structures */
//including required library files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1024

//Structure that stores the records in the .csv file
struct listing {
    int id, host_id, minimum_nights, number_of_reviews, calculated_host_listings_count, availability_365;
    char *host_name, *neighbourhood_group, *neighbourhood, *room_type;
    float latitude, longitude, price;
};

//parsing of .csv file and getting the fields in the file
struct listing getfields(char *line) {
    struct listing item;

    /* Note: you have to pass the string to strtok on the first 
	    invocation and then pass NULL on subsequent invocations */
    item.id = atoi(strtok(line, ","));
    item.host_id = atoi(strtok(NULL, ","));
    item.host_name = strdup(strtok(NULL, ","));
    item.neighbourhood_group = strdup(strtok(NULL, ","));
    item.neighbourhood = strdup(strtok(NULL, ","));
    item.latitude = atof(strtok(NULL, ","));
    item.longitude = atof(strtok(NULL, ","));
    item.room_type = strdup(strtok(NULL, ","));
    item.price = atof(strtok(NULL, ","));
    item.minimum_nights = atoi(strtok(NULL, ","));
    item.number_of_reviews = atoi(strtok(NULL, ","));
    item.calculated_host_listings_count = atoi(strtok(NULL, ","));
    item.availability_365 = atoi(strtok(NULL, ","));

    return item;
}
//function to display the records of csv using structure
void displayStruct(struct listing item) {
	printf("ID : %d\n", item.id);
	printf("Host ID : %d\n", item.host_id);
	printf("Host Name : %s\n", item.host_name);
	printf("Neighbourhood Group : %s\n", item.neighbourhood_group);
	printf("Neighbourhood : %s\n", item.neighbourhood);
	printf("Latitude : %f\n", item.latitude);
	printf("Longitude : %f\n", item.longitude);
	printf("Room Type : %s\n", item.room_type);
	printf("Price : %f\n", item.price);
	printf("Minimum Nights : %d\n", item.minimum_nights);
	printf("Number of Reviews : %d\n", item.number_of_reviews);
	printf("Calculated Host Listings Count : %d\n", item.calculated_host_listings_count);
	printf("Availability_365 : %d\n\n", item.availability_365);
}

//comparing the records by hostname and returning the result to qsort function
int compareByHostName(const void *p1, const void *p2) 
{
    return strcmp(((struct listing *)p1)->host_name, ((struct listing *)p2)->host_name);
}
//comparing the records by price and returning the result to qsort function
int compareByPrice(const void *p1, const void *p2) 
{
    return ((struct listing *)p1)->price - ((struct listing *)p2)->price;
}
//writting the sorted details to file
void writeToFile(struct listing *list_items, int count, const char *filename) 
{
	//declaring file stream pointer of FILE type and check if file open is successful
    FILE *file = fopen(filename, "w");
    if (file == NULL) 
	{
        printf("Error opening file %s for writing\n", filename);
        exit(-1);
    }
	//writting the records into the file
    for (int i = 0; i < count; i++) 
	{
        fprintf(file, "%d,%d,%s,%s,%s,%f,%f,%s,%f,%d,%d,%d,%d\n",
                list_items[i].id, list_items[i].host_id, list_items[i].host_name,
                list_items[i].neighbourhood_group, list_items[i].neighbourhood,
                list_items[i].latitude, list_items[i].longitude, list_items[i].room_type,
                list_items[i].price, list_items[i].minimum_nights,
                list_items[i].number_of_reviews, list_items[i].calculated_host_listings_count,
                list_items[i].availability_365);
    }
	//closing the file stream pointer
    fclose(file);
}
//entry to the main function
int main() 
{
	//creating the structure variable of listing structure
    struct listing list_items[22555];
    char line[LINESIZE];
    int count;
	//declaring and initializing the file stream pointer to open the input file
    FILE *fptr = fopen("listings.csv", "r");
	//checking if file open is successful
    if (fptr == NULL) {
        printf("Error reading input file listings.csv\n");
        exit(-1);
    }

    count = 0;
	//reading the .csv file records and storing into the listing structure
    while (fgets(line, LINESIZE, fptr) != NULL) {
        list_items[count++] = getfields(line);
    }
	//closing the file stream pointer
    fclose(fptr);

    // Sort by host_name
    qsort(list_items, count, sizeof(struct listing), compareByHostName);

    // Write sorted data to a new file
    writeToFile(list_items, count, "sorted_by_host_name.csv");

    // Display sorted data
    for (int i = 0; i < count; i++)
        displayStruct(list_items[i]);

    // Sort by price
    qsort(list_items, count, sizeof(struct listing), compareByPrice);

    // Write sorted data to a new file
    writeToFile(list_items, count, "sorted_by_price.csv");

    // Display sorted data
    for (int i = 0; i < count; i++)
        displayStruct(list_items[i]);

    return 0;
}