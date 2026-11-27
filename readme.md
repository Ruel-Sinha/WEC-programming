## Campus Microgrid Energy Optimization System
# Overview

This project was developed for the University of Waterloo Engineering Competition (WEC) Programming Challenge.

The goal was to design and implement an automated energy management system for a university microgrid. The system distributes electricity across campus buildings while minimizing operating costs and responding to changing energy demands and simulated random events.

The microgrid incorporates multiple power sources, including
- Solar generation
- Battery storage
- Electrical grid power
- Backup generation

The algorithm must be able to adapt to random events, including 
- Cloudy weather where solar power can’t be used
- Generator failure where the generator can't be used
- Battery failure where the battery can't be used
- Grid failure where the grid can't be used

Our solution evaluates available energy sources and allocates power according to system constraints and energy costs.

# Our Approach
We designed a cost-aware energy allocation strategy based on the following principles:

1. Prioritize Free Solar Energy
Since solar generation incurs no operating cost, available solar energy is allocated first whenever possible.

2. Evaluate Battery vs Grid Usage
When solar energy is insufficient, the algorithm determines whether energy should be supplied from Battery storage or the Electrical grid. This decision depends on electricity pricing and battery availability.

3. Battery Pre-Generation Strategy
The system forecasts future energy requirements and determines when storing energy in the battery is beneficial. This allows the microgrid to reduce costs during periods of expensive grid electricity.

4. Event Handling
The simulation includes random operating events that may affect energy generation, storage, or demand. Each event type is implemented in its own C++ source file, allowing event-specific logic to remain isolated and making the codebase easier to test, debug, and maintain.


# Technologies Used
C++
Struct-based data modeling
