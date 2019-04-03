# Predator-Prey-Simulation

The goal for this project was to create a simple two-dimensional predator-prey simulation. In this simulation the prey are ants and the pred-ators are doodlebugs. These critters live in a world composed of a 20 × 20 grid of cells. Only one critter may occupy a cell at a time. The grid is  enclosed, so a critter is not allowed to move off the edges of the world. Time is simulated in time steps. Each critter performs some action every time step.



The ants behave according to the following model:
* Move. Every time step, randomly try to move up, down, left, or right. If the neighboring cell in the selected direction is occupied or would move the ant off the grid, then the ant stays in the current cell.

* Breed. If an ant survives for three time steps, then at the end of the time step (that is; after moving) the ant will breed. This is simulated by creating a new ant in an adjacent (up, down, left, or right) cell that is empty. If there is no empty cell available, then no breeding occurs. Once an off-spring is produced, an ant cannot produce an offspring until three more time steps have elapsed.



The doodlebugs behave according to the following model:

* Move. Every time step, if there is an adjacent ant (up, down, left, or right), then the doodlebug moves to that cell and eat the ant. Otherwise, the doodlebug moves according to the same rules as the ant. Note that a doodlebug cannot eat other doodlebugs.

* Breed. If a doodlebug survives for eight time steps, then at the end of the time step it will spawn off a new doodlebug in the same manner as the ant.

* Starve. If a doodlebug has not eaten an ant within the last three time steps, then at the end of the third time step it starves and dies. The doodlebug is then be removed from the grid of cells.


During one turn, all the doodlebugs should move before the ants do.

The world is drawn using the ASCII characters of “o” for an ant and “X” for a doodlebug or "-" for an empty space. A class named Organism encapsulates basic data common to both ants and doodlebugs. This class has a virtual function named move that is defined in the derived classes of Ant and Doodlebug.

The world is initialized with 5 doodlebugs and 100 ants. After each time step, the user is prompted to press Enter to move to the next time step. There is a cyclical pattern between the population of predators and prey, although random perturbations may lead to the elimination of one or both species.
