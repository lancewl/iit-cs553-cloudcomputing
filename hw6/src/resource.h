#ifndef RESOURCE_H_
#define RESOURCE_H_

/*Function that compute the total memory used
 * returned the value of the total memory used
 */
long long memory();

/*Function that compute the percentage of cpu used
 * returned the value of current percentage of cpu used
 */
double getCurCpu();

/* Function create and write in files for the creation of graphs
 */
int graph();



#endif /* RESOURCE_H_ */
