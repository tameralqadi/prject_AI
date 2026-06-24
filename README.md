# Q-Learning Grid World Solver (C++)
A pure C++ implementation of the Q-Learning algorithm (Reinforcement Learning) solved from scratch. The agent learns to navigate a 5x5 grid world, finding the optimal path from a starting position to the goal while dynamically avoiding static obstacles (monsters).

## Key Highlights
- Pure C++ Solution: Implemented without any external AI or Machine Learning frameworks.
- Dynamic Action Glide: The environment introduces random glide steps (1 or 2 steps) during training to enforce robust policy mapping.
- Custom Reward Matrix: Pre-calculated rewards penalize boundary collisions and obstacles (-100) while rewarding goal completion (+100).
- Explicit Q-Table: Manually computed state-action values using the Bellman Equation.

## Grid Environment Layout
- 1: Agent Starting Position (Bottom-Right)
- 2: Obstacles / Monsters (Negative Reward)
- 3: Target Goal (Positive Reward / Terminal State)
- 0: Safe Walkable Paths (-1 step cost)

## Requirements
- Any modern C++ compiler (like g++) supporting C++11 or higher.

## How to Run
Compile and run the source file using your terminal:
```bash
g++ sliding_man.cpp -o q_learning_solver
./q_learning_solver
