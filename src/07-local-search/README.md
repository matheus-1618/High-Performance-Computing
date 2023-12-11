# Local Search
Two strategies were implemented:

* Random Search, where iterates all over itens in the scope of the problem, and takes each one with a probability of 50%, until reaches the full capacity of the bag;
* Full  bag, after executing the strategy above, iterates all over the other itens to add new solutions;

## Executing
```bash
python3 check.py <number_of_input>
```