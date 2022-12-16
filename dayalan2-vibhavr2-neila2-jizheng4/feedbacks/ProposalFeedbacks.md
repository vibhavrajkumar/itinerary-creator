### Grade
Incomplete (0%), must submit for regrade

### Comments 

**Dataset** 
One major problem exists with your dataset selection, namely that airlines.dat doesn't work. Look carefully at airlines.dat, does it really contanis the origin and destinatino of
an airline? No. I think what you need to look at for this information is routes.dat. Please research your dataset carefully. For error-handling, you really want to be checking
for data points that don't contain enough information for you to build a node out of it. This means, instead of checking for things like "at least 1km apart", etc. which can't 
really affect how you build your graph, you should consider what to do if you encounter a record that, say, is missing the destination airport. I suggest just dropping such records.

**Algorithms** 
You did not mention which traversal algorithm you would like to implement. You can choose to implement either BFS or DFS, but in either case you need to clearly specify. 
This is the primary reason that you are getting a 0% for this proposal. 
Secondly, you are trying to solve the Hamilton path problem using an algorithm that has exponential run time. While this is totally fine as an uncovered algorithm, 
a word of caution is in order, namely, that exponential run time is really scary, even with the computing power we have today. Consider a graph on 400 vertices, Then 1.657^n 
would be on the magnitude of 5.3580081e+87, much more than the number of atoms in the observable universe. Think whether its possible to perform that amount of computation in
a reasonable amount of time.  

**Timeline**
Timeline is too rough. I need schedule precise to each week.  

### Grade update
Sophisticated (100%), but with -10% regrade penalty, the final grade is 90%.
